function [Rz] = R_z(ps)
cs = cos(ps);
ss = sin(ps);
Rz = [cs -ss 0; ss cs 0; 0 0 1];
