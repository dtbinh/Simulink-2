function [pbest,bestP,gbest,bestG] = testE_PD_Diagonal(bestP,pbest,bestG,gbest,x,Qe,We,Ge)
if Qe(1)<bestP(1);
    bestP(1)=Qe(1);
    pbest(1)=x(1);
end
if Qe(2)<bestP(2);
    bestP(2)=Qe(2);
    pbest(2)=x(2);
end
if Qe(3)<bestP(3);
    bestP(3)=Qe(3);
    pbest(3)=x(3);
end
if We(1)<bestP(4);
    bestP(4)=We(1);
    pbest(4)=x(4);
end
if We(2)<bestP(5);
    bestP(5)=We(2);
    pbest(5)=x(5);
end
if We(3)<bestP(6);
    bestP(6)=We(3);
    pbest(6)=x(6);
end
if norm(Ge)<norm(bestG);
    bestG=Ge;
    disp(bestG);
    gbest=x;
end
end