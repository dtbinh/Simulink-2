function [bestP1,bestP2,pbest,gbest,bestG] = testE(bestP1,bestP2,pbest,bestG,gbest,x,Ge)
%C1_1 C1_2 C1_3 Diagonal
pbest(1:3)=(bestP1(1:3)>=Ge(1:3)).*x(1:3)+(1-(bestP1(1:3)>Ge(1:3))).*pbest(1:3);
bestP1(1:3)=(bestP1(1:3)>=Ge(1:3)).*Ge(1:3) + (1-(bestP1(1:3)>Ge(1:3))).*bestP1(1:3);
%C1_12 positive definite skew elements
pbest(4)=isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1])*x(4)+(1-isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1]))*pbest(4);
bestP2(1,1:2)=isequal((bestP2(1,1:2)>=[Ge(1) Ge(2)]),[1 1]).*[Ge(1) Ge(2)]+(1-isequal((bestP2(1,1:2)>[Ge(1) Ge(2)]),[1 1])).*bestP2(1,1:2);
%C1_13 positive definite skew elements
pbest(5)=isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1])*x(5)+(1-isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1]))*pbest(5);
bestP2(2,1:2)=isequal((bestP2(2,1:2)>=[Ge(1) Ge(3)]),[1 1]).*[Ge(1) Ge(3)]+(1-isequal((bestP2(2,1:2)>[Ge(1) Ge(3)]),[1 1])).*bestP2(2,1:2);
%C1_23 positive definite skew elements
pbest(6)=isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1])*x(6)+(1-isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1]))*pbest(6);
bestP2(3,1:2)=isequal((bestP2(3,1:2)>=[Ge(2) Ge(3)]),[1 1]).*[Ge(2) Ge(3)]+(1-isequal((bestP2(3,1:2)>[Ge(2) Ge(3)]),[1 1])).*bestP2(3,1:2);
%Global best
if norm(Ge)<norm(bestG);
    bestG=norm(Ge);
    disp(bestG);
    gbest=x;
end
end