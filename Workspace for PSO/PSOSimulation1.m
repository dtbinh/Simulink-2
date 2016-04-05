%Constants
If=[0.0052 0 0;0 0.0052 0; 0 0 0.0082]; %intertia matrix
tmax = 120; %max testing time
h=0.1;  %time step
%Starting Coefficients to be optimized
k0 = 0.1*[-0.5726 -0.5149 -0.4233];
a0 = 0.1*[-0.7900 -0.5528 -0.1993];
x = [k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)].';
%Desired settling points
Qd=[1 0 0 0];
Obd=[0 0 0].';
%Initial Velocity Condition
Ob0=[1 0 1].';
%Single Iteration error
Ge = 0; %Sets Global Error
Qe = 0; %Sets local Quat Error
We = 0; %Sets local Vel Error
%Starting points for PSO algorithm
pbest=[k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)].';
gbest=[k0(1) k0(2) k0(3) a0(1) a0(2) a0(3)].';
vn = 0.1*[0.1 0.1 0.1 0.1 0.1 0.1].';

for psi = 20:80:180
    rpsi = deg2rad(psi);
    for theta = 20:80:180
        rtheta = deg2rad(theta);
        for rho = 20:80:180
            rrho = deg2rad(rho);
            Rb0 = [rpsi rtheta rrho].'; %creates starting euler angles (rad)
            Qb0=angle2quat(Rb0(1),Rb0(2),Rb0(3)); %converts to quaternion
            k=If*[k0(1) 0 0; 0 k0(2) 0; 0 0 k0(3)];
            a=If*[a0(1) 0 0; 0 a0(2) 0; 0 0 a0(3)];
            [ge,qe,we] = rk4(Obd,Ob0,Qd,Qb0,k,a,If,tmax,h);
            Ge = Ge + ge;
            Qe = Qe + qe;
            We = We + we;
        end
    end
end
bestP=[Qe(1:3) We(1:3)];
bestG=Ge;
while(true);
    k=If*[x(1) 0 0; 0 x(2) 0; 0 0 x(3)];
    a=If*[x(4) 0 0; 0 x(5) 0; 0 0 x(6)];
    Ge = 0; %Sets Global Error
    Qe = 0; %Sets local Quat Error
    We = 0; %Sets local angular rate error
    %iterates through possible starting positions
    for psi = 20:80:180
        rpsi = deg2rad(psi);
        for theta = 20:80:180
            rtheta = deg2rad(theta);
            for rho = 20:80:180
                rrho = deg2rad(rho);
                Rb0 = [rpsi rtheta rrho].'; %creates starting euler angles (rad)
                Qb0=angle2quat(Rb0(1),Rb0(2),Rb0(3)); %converts to quaternion
                [ge,qe,we] = rk4(Obd,Ob0,Qd,Qb0,k,a,If,tmax,h);
                Ge = Ge + ge;
                Qe = Qe + qe;
                We = We + we;
            end
        end
    end
    [pbest,bestP,gbest,bestG] = testE(bestP,pbest,bestG,gbest,x,Qe,We,Ge);
    vn = vn + 0.2*(rand(6,1)).*(pbest-x) + 2*(rand(6,1)).*(gbest-x);
    x = x + 0.1*vn;    
    disp(Ge);
    disp(x);
end


%while t<600
%    t = t + h;
%    Oe=Obd-Ob;
%    Qe=quatmultiply(quatinv(Qd),Qb);   
%    tau = -(k/If)*(Oe)-(a/If)*(Qe(2:4).');
%    Ork1 = dfb1(Obd,Ob,Qd,Qb,k,a,If);
%    Ob1 = Ob + Ork1*h/2;
%    Qb1 = Qb + (h/4)*(quatmultiply(Qb,[0 Ob1.']));
%    Ork2 = dfb1(Obd,Ob1,Qd,Qb1,k,a,If);
%    Ob2 = Ob + Ork2*h/2;
%    Qb2 = Qb + (h/4)*(quatmultiply(Qb,[0 Ob2.']));
%    Ork3 = dfb1(Obd,Ob2,Qd,Qb2,k,a,If);
%    Ob3 = Ob + Ork3*h/2;
%    Qb3 = Qb + (h/4)*(quatmultiply(Qb,[0 Ob3.']));
%    Ork4 = dfb1(Obd,Ob3,Qd,Qb3,k,a,If);
%    Ob4 = Ob + Ork4*h;
%    Qb4 = Qb + (h/2)*(quatmultiply(Qb,[0 Ob4.']));
%    Ob = Ob + (h/6)*(Ork1 + 2*Ork2 + 2*Ork3 + Ork4);
%    Qb = (Qb1 + 2*Qb2 + 2*Qb3 + Qb4)/6;
%    e = (abs((Qd(2:4)-Qb(2:4)).')+abs(Obd-Ob));
%    scatter(t,norm(e));
%    disp(e);
%end
%hold off;
    