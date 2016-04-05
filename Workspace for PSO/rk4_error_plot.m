function [e]=rk4_error_plot(Obd,Ob0,Qd,Qb0,k,a,If,tmax,step)
e=0;
t = 0;
Ob=Ob0;
Qb=Qb0;
figure;
hold on;
while t<tmax
    t = t + step;
    Oe=Obd-Ob;
    Qe=quatmultiply(quatinv(Qd),Qb);   
    Ork1 = dfb1(Obd,Ob,Qd,Qb,k,a,If);
    Ob1 = Ob + Ork1*step/2;
    Qb1 = Qb + (step/4)*(quatmultiply(Qb,[0 Ob1.']));
    Ork2 = dfb1(Obd,Ob1,Qd,Qb1,k,a,If);
    Ob2 = Ob + Ork2*step/2;
    Qb2 = Qb + (step/4)*(quatmultiply(Qb,[0 Ob2.']));
    Ork3 = dfb1(Obd,Ob2,Qd,Qb2,k,a,If);
    Ob3 = Ob + Ork3*step/2;
    Qb3 = Qb + (step/4)*(quatmultiply(Qb,[0 Ob3.']));
    Ork4 = dfb1(Obd,Ob3,Qd,Qb3,k,a,If);
    Ob4 = Ob + Ork4*step;
    Qb4 = Qb + (step/2)*(quatmultiply(Qb,[0 Ob4.']));
    Ob = Ob + (step/6)*(Ork1 + 2*Ork2 + 2*Ork3 + Ork4);
    Qb = quatnormalize((Qb1 + 2*Qb2 + 2*Qb3 + Qb4)/6);
    e = (abs((Qd(2:4)-Qb(2:4)).')+abs(Obd-Ob));
    scatter(t,norm(e));
    disp(Qb);
    disp(Ob);
    disp(e);
end
hold off;