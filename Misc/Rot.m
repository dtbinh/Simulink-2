function Rl = Rot(Z,Y,X)
    Rz = [cos(Z) -sin(Z) 0; sin(Z) cos(Z) 0; 0 0 1];
    Ry = [cos(Y) 0 sin(Y); 0 1 0; -sin(Y) 0 cos(Y)];
    Rx= [1 0 0; 0 cos(X) -sin(X); 0 sin(X) cos(X)];
    Rl = Rz*Ry*Rx;
end