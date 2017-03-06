function [ h ] = height( t )
h=-4.9.*t.^2 + 125.*t + 500;
h(h<0) = 0;