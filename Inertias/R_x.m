function [Rx] = R_x(ph)
Rx=[1 0 0; 0 cos(ph) -sin(ph); 0 sin(ph) cos(ph)];
end