T1_0=[1 -0.1 -0.1; -0.1 1 0.1; -0.1 0.1 1]; %Positive Symmetric Definite Coeff
T2_0=[0.5 -0.1 -0.1; -0.1 0.5 0.1; -0.1 0.1 0.5]; %Positive Symmetric Definite Coeff
a = 1;
%First run through
% x = [T1_0(1,1) T1_0(2,2) T1_0(3,3) T1_0(1,2) T1_0(1,3) T1_0(2,3) a;
%     T2_0(1,1) T2_0(2,2) T2_0(3,3) T2_0(1,2) T2_0(1,3) T2_0(2,3) 0];
% x = [-3.2573   -3.1001   -3.0157    0.2756    0.7527    0.7079   40.4673;
%     8.8601    7.0391    7.2873    2.5049    2.6942    2.0894         0];
x = [-3.6277   -3.0688   -2.5705    0.9304    0.8644    0.7217   40.4185;
    7.8292    6.5022    6.8149    2.0757    2.1150    1.4498         0];
%x = [10 10 10 1 1 1 5;
%    10 10 10 10 10 10 0];
%Starting swarm velocity
vn = [0.1 0.1 0.1 0.02 0.02 0.02 0.1;
    0.1 0.1 0.1 0.1 0.1 0.1 0].';
%Load Coefficient matrix 1
T1_1=[0 x(1,1) x(1,4) x(1,5)];
T1_2=[0 x(1,4) x(1,2) x(1,6)];
T1_3=[0 x(1,5) x(1,6) x(1,3)];
%Load Coefficient matrix 2
T2_1=[0 x(2,1) x(2,4) x(2,5)];
T2_2=[0 x(2,4) x(2,2) x(2,6)];
T2_3=[0 x(2,5) x(2,6) x(2,3)];
%Load Coefficient matrix 3
a = [0 x(1,7)];
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
            hws.assignin('a', a);
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
bestP1=[Qe(1:3) We(1:3)];  
bestP2=[Qe(1) Qe(2); Qe(1) Qe(3); Qe(2) Qe(3)];
bestP3=[We(1) We(2); We(1) We(3); We(2) We(3)];
bestQ=norm(Qe);
bestG=Ge;
disp(bestG);
% x = 0.5*[10 10 10 1 1 1 5;
%     10 10 10 10 10 10 0];
while(true)
    vn = vn + 1*(rand(7,2)).*(pbest-x).' + 2*(rand(7,2)).*(gbest-x).';
    x = x + 1*vn.';
    T1_1=[0 x(1,1) x(1,4) x(1,5)];
    T1_2=[0 x(1,4) x(1,2) x(1,6)];
    T1_3=[0 x(1,5) x(1,6) x(1,3)];
    T2_1=[0 x(2,1) x(2,4) x(2,5)];
    T2_2=[0 x(2,4) x(2,2) x(2,6)];
    T2_3=[0 x(2,5) x(2,6) x(2,3)];
    a = [0 x(1,7)];
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
                hws.assignin('T1_1', T1_1);
                hws.assignin('T1_2', T1_2);
                hws.assignin('T1_3', T1_3);
                hws.assignin('T2_1', T2_1);
                hws.assignin('T2_2', T2_2);
                hws.assignin('T2_3', T2_3);
                hws.assignin('a', a);
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
        [bestP1,bestP2,bestP3,pbest,gbest,bestG,bestQ]=testE(bestP1,bestP2,bestP3,pbest,bestG,gbest,bestQ,x,Qe,We,Ge);
    else
        x = x - vn.';
    end
end