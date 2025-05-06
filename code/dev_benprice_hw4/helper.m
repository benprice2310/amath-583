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

% Matrix A (float)
A = [ -2.47834, -0.0789192, -0.0400073;
       6.09025,    6.5666,   -8.83365;
      -2.76896,  0.562423,   -1.90952 ];

% Matrix B (float)
B = [  7.59057,  -1.75305,  -6.24973;
       1.19836,   1.52262,   3.75935;
      -3.82986,  -5.09745,  -3.13731 ];

% Matrix C (float) BEFORE
C = [ -191.827,   45.3647,   113.025;
              770.122,   380.881,   124.872;
             -84.8745,   119.258,   246.992 ];

a = 3;
b = 2;

C = a * A * B + b * C

%% Problem 3
clearvars;
close all;
clc;

% % C++ OUTPUT
% 
% === A Poor Man's Builder ===
% Mon May  5 12:56:33 PDT 2025
% 
% Cleaning up...
% ./p3.clean:4: no matches found: xprob*
% Cleaned up
% 
% Compiling sources with -fPIC...
% Compiled sources
% 
% Creating shared library...
% Built shared object library
% 40 -rwxr-xr-x@ 1 benprice  staff  16752 May  5 12:56 libmatrix_utils.so
% 
% Linking executable...
% Done. Built program binary:
% 152 -rwxr-xr-x@ 1 benprice  staff  74152 May  5 12:56 xproblem3
% 
% ...
% === Problem 3: Matrix Class Demonstration ===
% 
% Matrix A:
%          1         2         3
%         -4         0       5.5
%       3.14     -2.71         0
% 
% Transpose of A:
%          1        -4      3.14
%          2         0     -2.71
%          3       5.5         0
% 
% Matrix B:
%        0.5        -1         2
%          3       1.5      -2.5
%          0         4         1
% 
% Matrix C = A + B:
%        1.5         1         5
%         -1       1.5         3
%       3.14      1.29         1
% 
% Matrix D = A * B:
%        6.5        14         0
%         -2        26      -2.5
%      -6.56    -7.205    13.055
% 
% Infinity norm of matrix C: 7.5
% (venv3.13) benprice@Bens-MacBook-Pro problem3 % 

A = [1         2         3
     -4         0       5.5
     3.14     -2.71         0];

% Transpose of A:
%          1        -4      3.14
%          2         0     -2.71
%          3       5.5         0

B = [0.5        -1         2
     3       1.5      -2.5
     0         4         1];

% Matrix C = A + B:
%        1.5         1         5
%         -1       1.5         3
%       3.14      1.29         1

% Matrix D = A * B:
%        6.5        14         0
%         -2        26      -2.5
%      -6.56    -7.205    13.055

A
B
C = A + B
D = A * B

norm(C, inf)


%% Problem 6
clearvars;
close all;
clc;


A = [     1,     2,     3
         -4,     0,   5.5
       3.14, -2.71,     0];

coder.rowMajor
A(1,3)

coder.columnMajor
A(3,1)