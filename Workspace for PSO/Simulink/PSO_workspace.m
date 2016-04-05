C1_0=[1 -0.1 -0.1; -0.1 1 0.1; -0.1 0.1 1]; %Positive Symmetric Definite Coeff
%First run through
% x = [C1_0(1,1) C1_0(2,2) C1_0(3,3) C1_0(1,2) C1_0(1,3) C1_0(2,3)];
x = [12.6107    2.4265    6.2428   -1.5052   -0.9544   -0.1123];
%Starting swarm velocity
vn = [0.1 0.1 0.1 0.02 0.02 0.02].';
%Load Coefficient matrix 1
C1=[0 x(1,1) x(1,4) x(1,5)];
C2=[0 x(1,4) x(1,2) x(1,6)];
C3=[0 x(1,5) x(1,6) x(1,3)];
%Starting Positions
Rb0 = [0 0 0];
%Reset Global, Quaternion and Angular Velocity Error
pGe = [0 0 0];
pQe = [0 0 0];
pWe = [0 0 0];
i=1;
for psi = 20:60:180
    for theta = 20:60:180
        for rho = 20:60:180
            Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
            hws = get_param(bdroot, 'modelworkspace');
            hws.DataSource = 'MAT-File';
            hws.FileName = 'co-effs';
            hws.assignin('Rb0', Rb0);
            hws.assignin('C1', C1);
            hws.assignin('C2', C2);
            hws.assignin('C3', C3);
            hws.saveToSource;
            hws.reload;
            try
                [Out]=sim('PSO','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
disp(x);
pbest=x;
gbest=x;
Qe=pQe/i;
We=pWe/i;
Ge=pGe/i;
bestP1 = Ge;  
bestP2 = [Ge(1) Ge(2); Ge(1) Ge(3); Ge(2) Ge(3)]; 
bestG=norm(Ge);
disp(bestG);
while(true)
    vn = vn + 1*(rand(6,1)).*(pbest-x).' + 2*(rand(6,1)).*(gbest-x).';
    x = x + 1*vn.';
    C1=[0 x(1,1) x(1,4) x(1,5)];
    C2=[0 x(1,4) x(1,2) x(1,6)];
    C3=[0 x(1,5) x(1,6) x(1,3)];
    pGe=0;
    pQe=0;
    pWe=0;
    i=1;
    for psi = 20:60:180
        for theta = 20:60:180
            for rho = 20:60:180
                Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
                %hws = Simulink.ModelWorkspace;
                hws = get_param(bdroot, 'modelworkspace');
                hws.DataSource = 'MAT-File';
                hws.FileName = 'co-effs';
                hws.assignin('Rb0', Rb0);
                hws.assignin('C1', C1);
                hws.assignin('C2', C2);
                hws.assignin('C3', C3);
                hws.saveToSource;
                hws.reload;
                try
                    [Out]=sim('PSO','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
                    end
                end
            end
        end
    end
    Qe=pQe/i;
    We=pWe/i;
    Ge=pGe/i;
    disp(Ge);
    if (Ge~=0)
        disp(bestG);
        disp(x);
        [bestP1,bestP2,pbest,gbest,bestG] = testE(bestP1,bestP2,pbest,bestG,gbest,x,Ge);
    else
        x = x - vn.';
    end
end