<<<<<<< HEAD
%Z = deg2rad(45);
%Y = deg2rad(0);
%X = deg2rad(45);
syms Z;
syms Y;
=======
Z = deg2rad(135);
%Y = deg2rad(13.26);
%X = deg2rad(34.54);
>>>>>>> f17598eb5f945231693a7e142a7f5c7dcc58359e
syms X;
syms Y;
%syms Z;
syms Tt;
<<<<<<< HEAD
x = deg2rad(45);
y = deg2rad(0);
z = deg2rad(0);
%rz = [ cos(z) -sin(z) 0; sin(z) cos(z) 0; 0 0 1];
%ry = [cos(y) 0 sin(y); 0 1 0; -sin(y) 0 cos(y)];
%rx = [1 0 0; 0 cos(x) -sin(x); 0 sin(x) cos(x)];
Qx = [cos(x/2) sin(x/2) 0 0];
Qy = [cos(y/2) 0 sin(y/2) 0];
Qz = [cos(z/2) 0 0 sin(z/2)];
Qb = quatmultiply(Qz,quatmultiply(Qy,Qx));
Qbi = quatinv(Qb);
T = [0 0 0 -1];
Tp = quatmultiply(Qbi,quatmultiply(T,Qb));
disp(Tp);
=======
x = X;
y = Y;
z = Z;
rz = [ cos(z) -sin(z) 0; sin(z) cos(z) 0; 0 0 1];
ry = [cos(y) 0 sin(y); 0 1 0; -sin(y) 0 cos(y)];
rx = [1 0 0; 0 cos(x) -sin(x); 0 sin(x) cos(x)];
T = [0 0 Tt].';
disp((rx*ry*rz).'*T);%*(T));
>>>>>>> f17598eb5f945231693a7e142a7f5c7dcc58359e
