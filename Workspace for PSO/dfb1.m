function [rK4]=dfb1(od,ob,qd,qb,k,a,If)
qe = quatmultiply(quatinv(qd),qb);
rK4=-(k/If)*(od-ob)-(a/If)*(qe(2:4).');
