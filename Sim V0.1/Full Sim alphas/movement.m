function out = movement(t,e0)
x0 = e0(1);
y0 = e0(2);
out = zeros(2,1);
out(1) = x0 + 2*t;
out(2) = y0 + 2*t^2;
end
