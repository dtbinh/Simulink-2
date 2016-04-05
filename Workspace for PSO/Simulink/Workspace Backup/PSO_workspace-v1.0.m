k0=[1 1 1];
a0=[1 1 1];
%persistent x vn K1 K2 K3 a1 a2 a3 pbest gbest bestG bestP
%First run through
x = [k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)];
%x = [0.8902    1.0944    1.0888    0.8863    0.7622    0.9760];
vn = [0.1 0.1 0.1 0.1 0.1 0.1].';
K1=[0 x(1) 0 0];
K2=[0 0 x(2) 0];
K3=[0 0 0 x(3)];
a1=[0 x(4) 0 0];
a2=[0 0 x(5) 0];
a3=[0 0 0 x(6)];
[Out]=sim('PSO','ReturnWorkspaceOutputs', 'on','SrcWorkspace','current');
pbest=x;
gbest=x;
Qe=Out.get('Qe');
bestP=[Qe(1:3) We(1:3)];
Ge=Out.get('Ge');
bestG=Ge;
disp(x);
while(true)
    vn = vn + 0.1*(rand(6,1)).*(pbest-x).' + 0.2*(rand(6,1)).*(gbest-x).';
    x = x + 0.1*vn.';
    disp(x);
    K1=[0 x(1) 0 0];
    K2=[0 0 x(2) 0];
    K3=[0 0 0 x(3)];
    a1=[0 x(4) 0 0];
    a2=[0 0 x(5) 0];
    a3=[0 0 0 x(6)];
    %hws = Simulink.ModelWorkspace;
    hws = get_param(bdroot, 'modelworkspace');
    hws.DataSource = 'MAT-File';
    hws.FileName = 'co-effs';
    hws.assignin('K1', K1);
    hws.assignin('K2', K2);
    hws.assignin('K3', K3);
    hws.assignin('a1', a1);
    hws.assignin('a2', a2);
    hws.assignin('a3', a3);
    hws.saveToSource;
    hws.reload;
    try
        [Out]=sim('PSO','ReturnWorkspaceOutputs', 'on','SrcWorkspace','base');  
    catch ME
        if (strcmp(ME.identifier,'Simulink:Engine:DerivNotFinite'))
            disp('Null');
        end
        if (strcmp(ME.identifier,'SL_SERVICES:utils:UNDEFINED_ID'))
            break;
        end
    end
    Ge=Out.get('Ge');
    Qe=Out.get('Qe');
    We=Out.get('We');
    [pbest,bestP,gbest,bestG]=testE(bestP,pbest,bestG,gbest,x,Qe,We,Ge);
end