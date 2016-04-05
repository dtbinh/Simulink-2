function [bestP1,bestP2,bestP3,pbest,gbest,bestG,bestQ] = testE(bestP1,bestP2,bestP3,pbest,bestG,gbest,bestQ,x,Qe,We,Ge)
%T1_1 T1_2 T1_3 Diagonal
pbest(1,1:3)=(bestP1(1:3)>=Qe).*x(1,1:3)+(1-(bestP1(1:3)>Qe)).*pbest(1,1:3);
bestP1(1:3)=(bestP1(1:3)>=Qe).*Qe + (1-(bestP1(1:3)>Qe)).*bestP1(1:3);
%T1_12 positive definite skew elements
disp(x);
pbest(1,4)=isequal((bestP2(1,1:2)>=[Qe(1) Qe(2)]),[1 1])*x(1,4)+(1-isequal((bestP2(1,1:2)>=[Qe(1) Qe(2)]),[1 1]))*pbest(1,4);
bestP2(1,1:2)=isequal((bestP2(1,1:2)>=[Qe(1) Qe(2)]),[1 1]).*[Qe(1) Qe(2)]+(1-isequal((bestP2(1,1:2)>[Qe(1) Qe(2)]),[1 1])).*bestP2(1,1:2);
%T1_13 positive definite skew elements
pbest(1,5)=isequal((bestP2(2,1:2)>=[Qe(1) Qe(3)]),[1 1])*x(1,5)+(1-isequal((bestP2(2,1:2)>=[Qe(1) Qe(3)]),[1 1]))*pbest(1,5);
bestP2(2,1:2)=isequal((bestP2(2,1:2)>=[Qe(1) Qe(3)]),[1 1]).*[Qe(1) Qe(3)]+(1-isequal((bestP2(2,1:2)>[Qe(1) Qe(3)]),[1 1])).*bestP2(2,1:2);
%T1_23 positive definite skew elements
pbest(1,6)=isequal((bestP2(3,1:2)>=[Qe(2) Qe(3)]),[1 1])*x(1,6)+(1-isequal((bestP2(3,1:2)>=[Qe(2) Qe(3)]),[1 1]))*pbest(1,6);
bestP2(3,1:2)=isequal((bestP2(3,1:2)>=[Qe(2) Qe(3)]),[1 1]).*[Qe(2) Qe(3)]+(1-isequal((bestP2(3,1:2)>[Qe(2) Qe(3)]),[1 1])).*bestP2(3,1:2);
%T2_1 T2_2 T2_3 Diagonal
pbest(2,1:3)=(bestP1(4:6)>=We).*x(2,1:3)+(1-(bestP1(4:6)>We)).*pbest(2,1:3);
bestP1(4:6)=(bestP1(4:6)>=We).*We + (1-(bestP1(4:6)>We)).*bestP1(4:6);
%T2_12 positive definite skew elements
pbest(2,4)=isequal((bestP3(1,1:2)>=[We(1) We(2)]),[1 1])*x(2,4)+(1-isequal((bestP3(1,1:2)>=[We(1) We(2)]),[1 1]))*pbest(2,4);
bestP3(1,1:2)=isequal((bestP3(1,1:2)>=[We(1) We(2)]),[1 1]).*[We(1) We(2)]+(1-isequal((bestP3(1,1:2)>[We(1) We(2)]),[1 1])).*bestP3(1,1:2);
%T2_13 positive definite skew elements
pbest(2,5)=isequal((bestP3(2,1:2)>=[We(1) We(3)]),[1 1])*x(2,5)+(1-isequal((bestP3(2,1:2)>=[We(1) We(3)]),[1 1]))*pbest(2,5);
bestP3(2,1:2)=isequal((bestP3(2,1:2)>=[We(1) We(3)]),[1 1]).*[We(1) We(3)]+(1-isequal((bestP3(2,1:2)>[We(1) We(3)]),[1 1])).*bestP3(2,1:2);
%T2_23 positive definite skew elements
pbest(2,6)=isequal((bestP3(3,1:2)>=[We(2) We(3)]),[1 1])*x(2,6)+(1-isequal((bestP3(3,1:2)>=[We(2) We(3)]),[1 1]))*pbest(2,6);
bestP3(3,1:2)=isequal((bestP3(3,1:2)>=[We(2) We(3)]),[1 1]).*[We(2) We(3)]+(1-isequal((bestP3(3,1:2)>[We(2) We(3)]),[1 1])).*bestP3(3,1:2);

%a scalar
if norm(Qe)<bestQ;
    bestQ=norm(Qe);
    disp(bestQ);
    pbest(1,7)=x(1,7);
end
%Global best
if norm(Ge)<norm(bestG);
    bestG=Ge;
    disp(bestG);
    gbest=x;
end
end