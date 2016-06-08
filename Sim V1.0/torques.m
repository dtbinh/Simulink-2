%torques
syms wx;
syms Ixx;
syms Iyy;
syms Izz;
syms rot;
W = [0 0 0; 0 0 wx; 0 -wx 0];
I = [Ixx 0 0; 0 Iyy 0; 0 0 Izz];
R = [0 0 rot].';
disp (W*I*R);