close all;
clearvars;
clc;

lb = -5;
ub = 5;

m = 5;
n = 3;
p = 4;

% A = randi([lb, ub], m, p);
% B = randi([lb, ub], p, n);
% C = randi([lb, ub], m, n);

A = [-4    -5     1    -4;
    -4    -1    -2    -4;
    -1     0    -1    -1;
     4    -1    -5    -3;
     3     2     5     0];

B = [-2     3     5;
     5    -3    -1;
     5    -1     5;
    -5     1    -2];

C = [2    -4     1;
     2    -4     4;
     0     5     2;
     2    -4    -3;
     2    -5    -1];

a = 7;
b = 8;

C = a * A * B + b * C