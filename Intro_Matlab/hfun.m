function [h] = hfun(t)
h = 2.13.*t.^2 - 0.0013.*t.^4 + 0.000034.*t.^4.751;
h(h<0)=0;

