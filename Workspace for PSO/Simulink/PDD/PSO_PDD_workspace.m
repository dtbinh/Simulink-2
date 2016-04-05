T1_0=[0.5 -0.1 -0.1; -0.1 0.5 0.1; -0.1 0.1 0.5]; %Positive Symmetric Definite Coeff
T2_0=[0.1 0 0; 0 0.1 0; 0 0 0.1]; %PD Diagonal
T3_0=[0.1 0 0; 0 0.1 0; 0 0 0.1]; %PD Diagonal
%First run through
 x = [T1_0(1,1) T1_0(2,2) T1_0(3,3) T1_0(1,2) T1_0(1,3) T1_0(2,3);
     T2_0(1,1) T2_0(2,2) T2_0(3,3) T3_0(1,1) T3_0(2,2) T3_0(3,3)];
%Starting swarm velocity
vn = [0.1 0.1 0.1 0.02 0.02 0.02;
    0.1 0.1 0.1 0.1 0.1 0.1].';
%Load Coefficient matrix 1
T1_1=[0 x(1,1) x(1,4) x(1,5)];
T1_2=[0 x(1,4) x(1,2) x(1,6)];
T1_3=[0 x(1,5) x(1,6) x(1,3)];
%Load Coefficient matrix 2
T2_1=[0 x(2,1) 0 0];
T2_2=[0 0 x(2,2) 0];
T2_3=[0 0 0 x(2,3)];
%Load Coefficient matrix 3
T3_1=[0 x(2,4) 0 0];
T3_2=[0 0 x(2,5) 0];
T3_3=[0 0 0 x(2,6)];
%Starting Positions
Rb0 = [0 0 0];
%Reset Global, Quaternion and Angular Velocity Error
pGe = [0 0 0];
pQe = [0 0 0];
pWe = [0 0 0];
i=1;
for psi = 20:60:360
    for theta = 20:60:360
        for rho = 20:60:360
            Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
            hws = get_param(bdroot, 'modelworkspace');
            hws.DataSource = 'MAT-File';
            hws.FileName = 'co-effs';
            hws.assignin('Rb0', Rb0);
            hws.assignin('T1_1', T1_1);
            hws.assignin('T1_2', T1_2);
            hws.assignin('T1_3', T1_3);
            hws.assignin('T2_1', T2_1);
            hws.assignin('T2_2', T2_2);
            hws.assignin('T2_3', T2_3);
            hws.assignin('T3_1', T3_1);
            hws.assignin('T3_2', T3_2);
            hws.assignin('T3_3', T3_3);
            hws.saveToSource;
            hws.reload;
            try
                [Out]=sim('PSO_PDD','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
bestP1=[Ge(1:3) We(1:3) Qe(1:3)];    
bestP2=[Ge(1) Ge(2); Ge(1) Ge(3); Ge(2) Ge(3)];
bestG=Ge;
disp(bestG);

while(true)
    vn = vn + 2*(rand(6,2)).*(pbest-x).' + 1*(rand(6,2)).*(gbest-x).';
    x = x + 0.1*vn.';
    T1_1=[0 x(1,1) x(1,4) x(1,5)];
    T1_2=[0 x(1,4) x(1,2) x(1,6)];
    T1_3=[0 x(1,5) x(1,6) x(1,3)];
    %Load Coefficient matrix 2
    T2_1=[0 x(2,1) 0 0];
    T2_2=[0 0 x(2,2) 0];
    T2_3=[0 0 0 x(2,3)];
    %Load Coefficient matrix 3
    T3_1=[0 x(2,4) 0 0];
    T3_2=[0 0 x(2,5) 0];
    T3_3=[0 0 0 x(2,6)];
    pGe=0;
    pQe=0;
    pWe=0;
    i=1;
    for psi = 20:60:360
        for theta = 20:60:360
            for rho = 20:60:359
                Rb0 = [0 psi theta rho]; %creates starting euler angles (rad)
                %hws = Simulink.ModelWorkspace;
                hws = get_param(bdroot, 'modelworkspace');
                hws.DataSource = 'MAT-File';
                hws.FileName = 'co-effs';
                hws.assignin('Rb0', Rb0);
                hws.assignin('T1_1', T1_1);
                hws.assignin('T1_2', T1_2);
                hws.assignin('T1_3', T1_3);
                hws.assignin('T2_1', T2_1);
                hws.assignin('T2_2', T2_2);
                hws.assignin('T2_3', T2_3);
                hws.assignin('T3_1', T3_1);
                hws.assignin('T3_2', T3_2);
                hws.assignin('T3_3', T3_3);
                hws.saveToSource;
                hws.reload;
                try
                    [Out]=sim('PSO_PDD','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base'); 
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
    if (Ge~=0)
        disp(bestG);
        disp(x);
        [bestP1,bestP2,pbest,gbest,bestG]=testE(bestP1,bestP2,pbest,bestG,gbest,x,Qe,We,Ge);
    end
end