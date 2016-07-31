% k0=[1 1 1];
% a0=[1 1 1];
%persistent x vn K1 K2 K3 a1 a2 a3 pbest gbest bestG bestP
%First run through
% x = [k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)];
x =  [2.7439    2.8826    1.7408    3.1718    4.2276    3.3682];
vn = [0.1 0.1 0.1 0.1 0.1 0.1].';
K1=[0 x(1) 0 0];
K2=[0 0 x(2) 0];
K3=[0 0 0 x(3)];
a1=[0 x(4) 0 0];
a2=[0 0 x(5) 0];
a3=[0 0 0 x(6)];
Rb0 = 0;
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
                [Out]=sim('PD_Diagonal','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
    x = x + 1*vn.';
    K1=[0 x(1) 0 0];
    K2=[0 0 x(2) 0];
    K3=[0 0 0 x(3)];
    a1=[0 x(4) 0 0];
    a2=[0 0 x(5) 0];
    a3=[0 0 0 x(6)];
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
                    [Out]=sim('PD_Diagonal','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
    [pbest,bestP,gbest,bestG]=testE_PD_Diagonal(bestP,pbest,bestG,gbest,x,Qe,We,Ge);
end