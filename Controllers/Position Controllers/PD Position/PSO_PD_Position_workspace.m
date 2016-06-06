%persistent x vn P1 P2 P3 D1 D2 D3 pbest gbest bestG bestP
%First run through
%x = [0.6732    0.6641    0.1283    2.0737    2.0761    0.3630];
x =  [1.2117    0.9507    1.3854    2.7244    2.6296    3.1198];
vn = [0.1 0.1 0.1 0.1 0.1 0.1].'; %Velocity
P1=[0 x(1) 0 0];
P2=[0 0 x(2) 0];
P3=[0 0 0 x(3)];
D1=[0 x(4) 0 0];
D2=[0 0 x(5) 0];
D3=[0 0 0 x(6)];
Eb0 = [0 0 0 0]; %Starting Position. Aims for Eb = [3 3 3]
pGe=0;
pQe=0;
pWe=0;
i=1;
for psi = 20:130:360
    rz = [cos(psi) sin(psi) 0; -sin(psi) cos(psi) 0; 0 0 1];
    for theta = 20:130:360
        ry = [cos(theta) 0 -sin(theta); 0 1 0; sin(theta) 0 cos(theta)];
        for rho = 20:130:360
            rx = [1 0 0; 0 cos(rho) sin(rho); 0 -sin(rho) cos(rho)];
            R0 = rz*ry*rx;
            dR = R0*([0 0 5].');
            Eb0 = [3 3 3] + dR.';
            %hws = Simulink.ModelWorkspace;
            hws = get_param(bdroot, 'modelworkspace');
            hws.DataSource = 'MAT-File';
            hws.FileName = 'co-effs';
            hws.assignin('Eb0', [0 Eb0]);
            hws.assignin('P1', P1);
            hws.assignin('P2', P2);
            hws.assignin('P3', P3);
            hws.assignin('D1', D1);
            hws.assignin('D2', D2);
            hws.assignin('D3', D3);
            hws.saveToSource;
            hws.reload;
            try
                [Out]=sim('PD_Position','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
                i = i + 1;
                disp(i);
                disp(Out.get('Ge'));
                pGe=pGe+Out.get('Ge');
                pQe=pWe+Out.get('Qe');
                pWe=pQe+Out.get('We');
            catch ME
                disp('not ok');
                if (strcmp(ME.identifier,'Simulink:Engine:DerivNotFinite'))
                    disp('Null');
                    break;
                end
                if (strcmp(ME.identifier,'SL_SERVICES:utils:UNDEFINED_ID'))
                    disp('Err');
                    break;
                end
            end
        end
    end
end
disp(x);
%Qe=pQe/i;
%We=pWe/i;
%Ge=pGe/i;
%disp(Ge);
%disp(x);
%[pbest,bestP,gbest,bestG]=testE(bestP,pbest,bestG,gbest,x,Qe,We,Ge);
pbest=x;
gbest=x;
Qe=pQe/i;
We=pWe/i;
Ge=pGe/i;
bestP=[Qe(1:3) We(1:3)];    
bestG=Ge;
disp(bestG);
while(true)
    vn = vn + 1*(rand(6,1)).*(pbest-x).' + 2*(rand(6,1)).*(gbest-x).';
    x = x + 0.1*vn.';
    P1=[0 x(1) 0 0];
    P2=[0 0 x(2) 0];
    P3=[0 0 0 x(3)];
    D1=[0 x(4) 0 0];
    D2=[0 0 x(5) 0];
    D3=[0 0 0 x(6)];
    pGe=0;
    pQe=0;
    pWe=0;
    i=1;
    for psi = 20:130:360
        for theta = 20:130:360
            for rho = 20:130:360
                Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
                rz = [cos(psi) sin(psi) 0; -sin(psi) cos(psi) 0; 0 0 1];
                ry = [cos(theta) 0 -sin(theta); 0 1 0; sin(theta) 0 cos(theta)];
                rx = [1 0 0; 0 cos(rho) sin(rho); 0 -sin(rho) cos(rho)];
                R0 = rz*ry*rx;
                dR = R0*([0 0 5].');
                Eb0 = [3 3 3] + dR.';
                %hws = Simulink.ModelWorkspace;
                hws = get_param(bdroot, 'modelworkspace');
                hws.DataSource = 'MAT-File';
                hws.FileName = 'co-effs';
                hws.assignin('Eb0', [0 Eb0]);
                hws.assignin('P1', P1);
                hws.assignin('P2', P2);
                hws.assignin('P3', P3);
                hws.assignin('D1', D1);
                hws.assignin('D2', D2);
                hws.assignin('D3', D3);
                hws.saveToSource;
                hws.reload;
                try
                    [Out]=sim('PD_Position','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
                    i = i + 1;
                    pGe=pGe+Out.get('Ge');
                    pQe=pWe+Out.get('Qe');
                    pWe=pQe+Out.get('We');
                catch ME
                    if (strcmp(ME.identifier,'Simulink:Engine:DerivNotFinite'))
                        disp('Null');
                    end
                    if (strcmp(ME.identifier,'SL_SERVICES:utils:UNDEFINED_ID'))
                        disp('Err');
                    end
                end
            end
        end
    end
    Qe=pQe/i;
    We=pWe/i;
    Ge=pGe/i;
    disp(Ge);
    disp(x);
    [pbest,bestP,gbest,bestG]=testE(bestP,pbest,bestG,gbest,x,Qe,We,Ge);
end