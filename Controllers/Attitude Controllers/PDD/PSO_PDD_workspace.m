% k0=[1 1 1];
% a0=[1 1 1];
%persistent x vn K1 K2 K3 a1 a2 a3 pbest gbest bestG bestP
%First run through
% x = [k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)];
x =  [ -0.7802   -1.2498   -1.0643    0.0014   -0.0986   -0.4594;
   -1.6423   -1.6407   -1.3797    0.8308    0.0275    0.6529];
vn = [0.1 0.1 0.1 0.1 0.1 0.1;
    0.1 0.1 0.1 0.1 0.1 0.1].';
A1=[0 x(1,1) x(1,4) x(1,5)];
A2=[0 x(1,4) x(1,2) x(1,6)];
A3=[0 x(1,5) x(1,6) x(1,3)];
B1=[0 x(2,1) 0 0];
B2=[0 0 x(2,2) 0];
B3=[0 0 0 x(2,3)];
C1=[0 x(2,4) 0 0];
C2=[0 0 x(2,5) 0];
C3=[0 0 0 x(2,6)];
Rb0 = 0;
pGe=0;
pQe=0;
pWe=0;
i=1;
for psi = 20:105:360
    for theta = 20:105:360
        for rho = 20:105:360
            Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
            %hws = Simulink.ModelWorkspace;
            hws = get_param(bdroot, 'modelworkspace');
            hws.DataSource = 'MAT-File';
            hws.FileName = 'co-effs_PDD';
            hws.assignin('Rb0', Rb0);
            hws.assignin('A1', A1);
            hws.assignin('A2', A2);
            hws.assignin('A3', A3);
            hws.assignin('B1', B1);
            hws.assignin('B2', B2);
            hws.assignin('B3', B3);
            hws.assignin('C1', C1);
            hws.assignin('C2', C2);
            hws.assignin('C3', C3);
            hws.saveToSource;
            hws.reload;
            try
                [Out]=sim('PD_PDD','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
bestP1=[Ge(1:3) We(1:3) Qe(1:3)];    
bestP2=[Ge(1) Ge(2); Ge(1) Ge(3); Ge(2) Ge(3)];
bestG=Ge;
disp(bestG);
while(true)
    vn = vn + 1*(rand(6,2)).*(pbest-x).' + 2*(rand(6,2)).*(gbest-x).';
    x = x + 0.5*vn.';
    A1=[0 x(1,1) x(1,4) x(1,5)];
    A2=[0 x(1,4) x(1,2) x(1,6)];
    A3=[0 x(1,5) x(1,6) x(1,3)];
    B1=[0 x(2,1) 0 0];
    B2=[0 0 x(2,2) 0];
    B3=[0 0 0 x(2,3)];
    C1=[0 x(2,4) 0 0];
    C2=[0 0 x(2,5) 0];
    C3=[0 0 0 x(2,6)];
    pGe=0;
    pQe=0;
    pWe=0;
    i=1;
    for psi = 20:105:360
        for theta = 20:105:360
            for rho = 20:105:360
                Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
                %hws = Simulink.ModelWorkspace;
                hws = get_param(bdroot, 'modelworkspace');
                hws.DataSource = 'MAT-File';
                hws.FileName = 'co-effs_PDD';
                hws.assignin('Rb0', Rb0);
                hws.assignin('A1', A1);
                hws.assignin('A2', A2);
                hws.assignin('A3', A3);
                hws.assignin('B1', B1);
                hws.assignin('B2', B2);
                hws.assignin('B3', B3);
                hws.assignin('C1', C1);
                hws.assignin('C2', C2);
                hws.assignin('C3', C3);
                hws.saveToSource;
                hws.reload;
                try
                    [Out]=sim('PD_PDD','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
    [bestP1,bestP2,pbest,gbest,bestG] = testE_PDD(bestP1,bestP2,pbest,bestG,gbest,x,Qe,We,Ge);
end