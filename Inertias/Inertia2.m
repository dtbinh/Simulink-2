%syms lam;
lam = deg2rad(35);
%syms eta;
eta = deg2rad(35);
%syms sig;
sig = deg2rad(0);
Rx = [1 0 0; 0 cos(lam) -sin(lam); 0 sin(lam) cos(lam)];
Tx = [1 0 0; 0 cos(-lam) -sin(-lam); 0 sin(-lam) cos(-lam)];
Ry = [cos(eta) 0 sin(eta); 0 1 0; -sin(eta) 0 cos(eta)];
Ty = [cos(-eta) 0 sin(-eta); 0 1 0; -sin(-eta) 0 cos(-eta)];
Rz = [cos(sig) -sin(sig) 0; sin(sig) cos(sig) 0; 0 0 1];
Tz = [cos(-sig) -sin(-sig) 0; sin(-sig) cos(-sig) 0; 0 0 1];
%%
%Inner inertia at CG aligned with XYZ
I_inner_cg=[585.10692885 -0.33559145 -2.44256622; -0.33559145 1960.92699148 0.81486827; -2.44256622 0.81486827 2139.83661274];
cg_inner = (10^(-3))*[-1.4000931 -0.0428028 -1.9417366].'; 
m_inner = 99*(10^(-3));
body = (10^(-3))*[-195.16 0 0].';
% Inertia TRANSLATED to M center
I_inner = I_inner_cg+(10^(7))*m_inner*(dot(cg_inner,cg_inner)*eye(3)-(cg_inner*(cg_inner.')));
% Inertia ROTATED by eta & lambda
I_inner_prime = (Ry*Rx)*I_inner*((Rx*Ry).');
disp(vpa(I_inner_prime,8));
%CG ROTATED about X & Y
cg_inner_prime = Rz*Ry*Rx*cg_inner;
% Inertia TRANSLATED to O center
d_inner_body = body - cg_inner_prime;
I_inner_body = I_inner_prime + (10^(7))*m_inner*(dot(d_inner_body,d_inner_body)*eye(3)-(d_inner_body*(d_inner_body.')));
disp(vpa(I_inner_body,6));
% Inertia TRANSFORMED by eta & lambda
I_inner_body_prime = (Tz*Ty*Tx)*I_inner_body*(Tx.')*(Ty.')*(Tz.');
disp(vpa(I_inner_body_prime,8));
%I_middle=[3024.3030 0.0253 406.8425; 0.0253 8791.1608 0.0143; 406.8425 0.0143 11579.8541];
%cg_middle= [-47 -3.74 -2.13].'; 
%I_m=I_m2+Rx*I_m1*(inv(Rx));
%I_mm = Rz*Ry*I_m*(inv(Ry))*(inv(Rz));
%%
%I_mm = [3590.31 92.32 269.00; 92.32	9531.69 11.47; 269.00 11.47 12504.24];
%m=0.201;
%Lm1 = ([195.2 0 0]).*10^(-3);
%Lm1 = ([170.6 1.9 2.8]).*10^(-3);
%Lm1 = ([24.5 1.9 -2.8]).*10^(-3);
%I_mb=I_mm + 10^(7)*m*(dot(Lm1,Lm1)*eye(3)-Lm1.'*(Lm1));
%disp(vpa(I_mb,8));
%Lm2= ([-195.2 0 0]).*10^(-3);%([-170.6 1.9 -2.8]).*10^(-3);
%I_mb1 = I_mm+10^(7)*m*(dot(Lm2,Lm2)*eye(3)-Lm2.'*(Lm2));
%disp(vpa(I_mb1,8));
%Id = [3613.14426 736.01988	-691.19813; 736.01988 68062.54543 0.91148; -691.19813 0.91148 71026.41742];
%d = (Id-I_mb);
%pd = norm(d/Id);
%disp(pd);
%I_b = [183677.46 -0.42 -4.46; -0.42 183554.97 -10.41; -4.46 -10.41 360077.62];

%Lmb = ([-195.161 0 0].').*10^(-3);
%m = 201*10^(-3);
%
%disp(vpa(I_mb,6));