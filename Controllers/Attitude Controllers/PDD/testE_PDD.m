function [bestP1,bestP2,pbest,gbest,bestG] = testE_PDD(bestP1,bestP2,pbest,bestG,gbest,x,Qe,We,Ge)
%T1_1 T1_2 T1_3 Diagonal
pbest(1,1:3)=(bestP1(1:3)>=Ge).*x(1,1:3)+(1-(bestP1(1:3)>Ge)).*pbest(1,1:3);
bestP1(1:3)=(bestP1(1:3)>=Ge).*Ge + (1-(bestP1(1:3)>Ge)).*bestP1(1:3);
%T1_12 positive definite skew elements
pbest(1,4)=isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1])*x(1,4)+(1-isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1]))*pbest(1,4);
bestP2(1,1:2)=isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1]).*[Ge(1) Ge(2)]+(1-isequal((bestP2(1,1:2)>[Ge(1) Ge(2)]),[1 1])).*bestP2(1,1:2);
%T1_13 positive definite skew elements
pbest(1,5)=isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1])*x(1,5)+(1-isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1]))*pbest(1,5);
bestP2(2,1:2)=isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1]).*[Ge(1) Ge(3)]+(1-isequal((bestP2(2,1:2)>[Ge(1) Ge(3)]),[1 1])).*bestP2(2,1:2);
%T1_23 positive definite skew elements
pbest(1,6)=isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1])*x(1,6)+(1-isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1]))*pbest(1,6);
bestP2(3,1:2)=isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1]).*[Ge(2) Ge(3)]+(1-isequal((bestP2(3,1:2)>[Ge(2) Ge(3)]),[1 1])).*bestP2(3,1:2);
%T2:(1,1) T2:(2,2) T2:(3,3) Diagonal
pbest(2,1:3)=(bestP1(4:6)>=We).*x(2,1:3)+(1-(bestP1(4:6)>We)).*pbest(2,1:3);
bestP1(4:6)=(bestP1(4:6)>=We).*We + (1-(bestP1(4:6)>We)).*bestP1(4:6);
%T3:(1,1) T3:(2,2) T3:(3,3) Diagonal
pbest(2,4:6)=(bestP1(7:9)>=Qe).*x(2,4:6)+(1-(bestP1(7:9)>Qe)).*pbest(2,4:6);
bestP1(7:9)=(bestP1(7:9)>=Qe).*Qe + (1-(bestP1(7:9)>Qe)).*bestP1(7:9);
%Global best
if norm(Ge)<norm(bestG);
    bestG=Ge;
    disp(bestG);
    gbest=x;
end
end