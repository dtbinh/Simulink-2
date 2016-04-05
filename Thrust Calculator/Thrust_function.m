w_rpm = linspace(0,9000,9000/25);
w_rads = (w_rpm/60)*2*pi;
v_inf = 25; %ms^-1
R = 22.86; %cm
rho = 1.225; %kg.m^3
a = 2*pi; %lift curve slope
b = 2; %rotors
figure;
T = 0;
for r = 0.1*22.86:0.01:R
    x = r/R;
    Cr_R = ((5623*x^6)/1000 - (2221*x^5)/100 + (173*x^4)/5 - (683*x^3)/25 + (1079*x^2)/100 - (813*x)/500 + 1987/10000)*(10^-2); %chord length (m*10^-2)
    Br_R = - (731*x^6)/20 + 138*x^5 - 210*x^4 + (1637*x^3)/10 - (3383*x^2)/50 + (643*x)/50 - 2003/10000; %rad
    gamma_c = (v_inf)./(w_rads.*(R*10^-2));
    sigma = (b*Cr_R)/(pi*R*10^-2);
    gamma = sqrt((sigma*a/16 - gamma_c/2).^2 + (sigma*a/8)*Br_R*x)-(sigma*a/16 - gamma_c/2);
    dT = a*b*Cr_R*(rho/2)*(w_rads.*r*10^-2).^2.*(Br_R - gamma);
    T = T + dT;
end
plot(w_rpm,T);