%syms lam;
lam = deg2rad(0);
%syms eta;
eta = deg2rad(0);
%syms sig;
sig = deg2rad(0);
Rx = [1 0 0; 0 cos(lam) -sin(lam); 0 sin(lam) cos(lam)];
Tx = [1 0 0; 0 cos(-lam) -sin(-lam); 0 sin(-lam) cos(-lam)];
Ry = [cos(eta) 0 sin(eta); 0 1 0; -sin(eta) 0 cos(eta)];
Ty = [cos(-eta) 0 sin(-eta); 0 1 0; -sin(-eta) 0 cos(-eta)];
Rz = [cos(sig) -sin(sig) 0; sin(sig) cos(sig) 0; 0 0 1];
Tz = [cos(-sig) -sin(-sig) 0; sin(-sig) cos(-sig) 0; 0 0 1];
%Net body inertia at body center of mass
%   Lxx = 18201862.469	Lxy = -43.611	Lxz = -803.054
%	Lyx = -43.611	Lyy = 18189616.533	Lyz = -1774.833
%	Lzx = -803.054	Lzy = -1774.833	Lzz = 36007757.692
%Body inertia at center of mass [g.mm^2]
I_b = [18201862.469 -43.611 -803.054; -43.611 18189616.533 -1774.833; -803.054 -1774.833 36007757.692];
%Center of body mass relative to origin [mm]
z = -[-0.03084 -0.06314 -14.26938].';
%Mass of body
m_body= 814.7;
I_bm = eye(3).*(I_b + m_body*(dot(z,z)*eye(3)-(z*z.')))+(1-eye(3)).*(I_b + m_body*(dot(z,z)*eye(3)+(z*z.')));
disp(vpa(I_bm,8));
%Net Inertia at body center
%	Ixx = 1865124.59	Ixy = 1097559.37	Ixz = -130022.59
%	Iyx = 1097559.37	Iyy = 6285551.52	Iyz = -41774.03
%	Izx = -130022.59	Izy = -41774.03	Izz = 8103496.66

%Net Inertia at motor module center
%   Ixx = 1865124.59	Ixy = 274.90	Ixz = 40684.50
%	Iyx = 274.90	Iyy = 930236.74	Iyz = -41774.03
%	Izx = 40684.50	Izy = -41774.03	Izz = 2748181.88

%Damping Inertia at body center
%   Ixx = 2411388.43	Ixy = 891311.35	Ixz = 1465803.62
%   Iyx = 891311.35	Iyy = 3392536.08	Iyz = 504032.03
%   Izx = 1465803.62	Izy = 504032.03	Izz = 4082917.76
%Inner Inertia at rotational center (g.cm^2)
%	Lxx = 585.10692885	Lxy = -0.33559145	Lxz = -2.44256622
%	Lyx = -0.33559145	Lyy = 1960.92699148	Lyz = 0.81486827
%	Lzx = -2.44256622	Lzy = 0.81486827	Lzz = 2139.83661274
%Middle Inertia at rotational center (g.cm^2)
%	Ixx = 3024.3030	Ixy = 0.0253	Ixz = 406.8425
%	Iyx = 0.0253	Iyy = 8791.1608	Iyz = 0.0143
%	Izx = 406.8425	Izy = 0.0143	Izz = 11579.8541
%%
%Inner Ring
%%
%Inner inertia at its center of mass [g.mm^2]
I_ci = [58510.69288464 -33.55914455	-244.25662227; -33.55914455	196092.69914818	81.48682740; -244.25662227 81.48682740 213983.66127405];
%C.I position relative t
ci = [-1.40009309 -0.04280281 -1.94173659].';
%C.I rotated about rotational center
cip = Rx*(ci);
%inner ring mass [g]
m_inner = 99;
%Inner inertia rotated at center of mass aligned with Body Frame [g.mm^2]
I_cip = ([0 1 0; 1 0 1; 0 1 0]).*(Rx*(I_ci)*(Rx.'))+([1 0 1; 0 1 0; 1 0 1]).*(Tx*(I_ci)*(Tx.'));
%Inner inertia at rotational center, aligned with Body frame [g.mm^2]
I_i = eye(3).*(I_cip + m_inner*(dot(cip,cip)*eye(3)-(cip*cip.')))+(1-eye(3)).*(I_cip + m_inner*(dot(cip,cip)*eye(3)+(cip*cip.')));
%%
%Middle Ring
%%
%Middle inertia at its center of mass [g.mm^2]
I_cm = [299657.4162	17931.7784	23270.6394; 17931.7784	652484.2871	1387.2864; 23270.6394 1387.2864 931272.7166];
%C.M Position relative to rotational center [mm]
cm = -[46.9966 -3.7402 3.6326].'; 
%C.M rotated about rotational center [mm]
cmp = Ry*cm;
%middle ring mass [g]
m_middle = 102;
%Middle inertia rotated at center of mass aligned with Body Frame [g.mm^2]
I_cmp = ([0 1 0; 1 0 1; 0 1 0]).*(Ry*(I_cm)*(Ry.'))+([1 0 1; 0 1 0; 1 0 1]).*(Ty*(I_cm)*(Ty.'));
%Middle inertia at rotational center, aligned with Body Frame [g.mm^2]
I_m = eye(3).*(I_cmp + m_middle*(dot(cmp,cmp)*eye(3)-(cmp*cmp.')))+(1-eye(3)).*(I_cmp + m_middle*(dot(cmp,cmp)*eye(3)+(cmp*cmp.')));
%Distance to body center, [m]
B = [-195.1614 0 0].';
R = B - cmp;
%Middle inertia at body center
I_mb = eye(3).*(I_cmp + m_middle*(dot(R,R)*eye(3)-(R*R.')))+(1-eye(3)).*(I_cmp + m_middle*(dot(R,R)*eye(3)+(R*R.')));
%disp(vpa(simplify(I_mb(2,2)),8));
%disp(vpa(I_mb,8));
eth = 0:0.1:4*pi;
out = 102.0.*(47.136782.*cos((2*pi-eth) - 0.07714157) - 195.1614).*(46.9966.*cos(eth) + 3.6326.*sin(eth) - 195.1614) - 4807.9517.*sin((2*pi-eth) - 0.07714157).*(3.6326.*cos(eth) - 46.9966.*sin(eth)) + 652484.29;
%plot(eth,out);