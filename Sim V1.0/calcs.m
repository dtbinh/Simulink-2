Z = deg2rad(0);
Y = deg2rad(-45);
X = deg2rad(30);
%syms X;
%syms Y;
%syms Z;
z = Z;
y = Y;
x = X;

rz = [ cos(z) sin(z) 0; -sin(z) cos(z) 0; 0 0 1];
ry = [cos(y) 0 -sin(y); 0 1 0; sin(y) 0 cos(y)];
rx = [1 0 0; 0 cos(x) sin(x); 0 -sin(x) cos(x)];

Qx = [cos(x/2) sin(x/2) 0 0];
Qy = [cos(y/2) 0 sin(y/2) 0];
Qz = [cos(z/2) 0 0 sin(z/2)];
R =  rz*ry*rx;

Qb = quatmultiply(Qx,quatmultiply(Qy,Qz ));
Qbi = quatinv(Qb);
T = [0 0 0 5.347];
t = [0 0 5.347];
Tp = quatmultiply(Qbi,quatmultiply(T,Qb));
disp(Tp);
disp((R)*(t).');