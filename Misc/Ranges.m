T = [0 0 1].';
X = -pi:0.01:pi;
Y = -pi:0.01:pi;
Z = pi/4;%[pi/4 3/4*pi 5/4*pi 7/4*pi];
i = 0;
for Y = -pi:pi/10:pi
    i=i+1;
    for X = -pi:pi/10:pi
        RL = Rot(Z,Y,X);
        Tp=RL*T;
        disp('T');
        disp(Tp); 
        disp('X');
        disp(X);
        disp('Y');
        disp(Y);
    end
end

