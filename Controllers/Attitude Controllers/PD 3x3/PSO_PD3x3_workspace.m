% k0=[1 1 1];
% a0=[1 1 1];
%persistent x vn K1 K2 K3 a1 a2 a3 pbest gbest bestG bestP
%First run through
% x = [k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)];
%Starting X                
x = [2.4615    2.6387    1.5181   -0.0817    0.0182    0.0474;
    3.4638    4.5995    3.4817    0.0199   -0.0579    0.0201];
vn = [0.1 0.1 0.1 0.02 0.02 0.02;
    0.1 0.1 0.1 0.02 0.02 0.02].';
K1=[0 x(1,1) x(1,4) x(1,5)];
K2=[0 x(1,4) x(1,2) x(1,6)];
K3=[0 x(1,5) x(1,6) x(1,3)];
a1=[0 x(2,1) x(2,4) x(2,5)];
a2=[0 x(2,4) x(1,2) x(2,6)];
a3=[0 x(2,5) x(2,6) x(2,3)];
Rb0 = [0 0 0];
pGe = [0 0 0];
pQe = [0 0 0];
pWe = [0 0 0];
i=1;
for psi = 20:60:360
    for theta = 20:60:360
        for rho = 20:60:360
            Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
            %hws = Simulink.ModelWorkspace;
            hws = get_param(bdroot, 'modelworkspace');
            hws.DataSource = 'MAT-File';
            hws.FileName = 'co-effs';
            hws.assignin('Rb0', Rb0);
            hws.assignin('K1', K1);
            hws.assignin('K2', K2);
            hws.assignin('K3', K3);
            hws.assignin('a1', a1);
            hws.assignin('a2', a2);
            hws.assignin('a3', a3);
            hws.saveToSource;
            hws.reload;
            try
                [Out]=sim('PD_3x3','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
                i = i + 1;
                pGe=pGe+Out.get('Ge');
                pQe=pWe+Out.get('Qe');
                pWe=pQe+Out.get('We');
            catch ME
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
pbest=x;
gbest=x;
Qe=pQe/i;
We=pWe/i;
Ge=pGe/i;
bestP1=[Qe(1:3) We(1:3)];    
bestP2=[Qe(1) Qe(2); Qe(1) Qe(3); Qe(2) Qe(3)];
bestP3=[We(1) We(2); We(1) We(3); We(2) We(3)];
bestG=Ge;
disp(bestG);
while(true)
    vn = vn + 2*(rand(6,2)).*(pbest-x).' + 1*(rand(6,2)).*(gbest-x).';
    x = x + 1*vn.';
    K1=[0 x(1,1) x(1,4) x(1,5)];
    K2=[0 x(1,4) x(1,2) x(1,6)];
    K3=[0 x(1,5) x(1,6) x(1,3)];
    a1=[0 x(2,1) x(2,4) x(2,5)];
    a2=[0 x(2,4) x(1,2) x(2,6)];
    a3=[0 x(2,5) x(2,6) x(2,3)];
    pGe=0;
    pQe=0;
    pWe=0;
    i=1;
    for psi = 20:60:360
        for theta = 20:60:360
            for rho = 20:60:360
                Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
                %hws = Simulink.ModelWorkspace;
                hws = get_param(bdroot, 'modelworkspace');
                hws.DataSource = 'MAT-File';
                hws.FileName = 'co-effs';
                hws.assignin('Rb0', Rb0);
                hws.assignin('K1', K1);
                hws.assignin('K2', K2);
                hws.assignin('K3', K3);
                hws.assignin('a1', a1);
                hws.assignin('a2', a2);
                hws.assignin('a3', a3);
                hws.saveToSource;
                hws.reload;
                try
                    [Out]=sim('PD_3x3','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
    [bestP1,bestP2,bestP3,pbest,gbest,bestG]=testE(bestP1,bestP2,bestP3,pbest,bestG,gbest,x,Qe,We,Ge);
end