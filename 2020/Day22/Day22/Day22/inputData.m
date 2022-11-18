function [p1_out,p2_out] = inputData(use_test)
%INPUTDATA Summary of this function goes here
%   Detailed explanation goes here

p1_test = [9 2 6 3 1];
p2_test = [5 8 4 7 10];

p1_data = [27 29 30 44 50 5 33 47 34 38 36 4 2 18 24 16 32 21 17 9 3 22 41 31 23];
p2_data = [25 1 15 46 6 13 20 12 10 14 19 37 40 26 43 11 48 45 49 28 35 7 42 39 8];

if use_test
    p1_out = p1_test;
    p2_out = p2_test;
else
    p1_out = p1_data;
    p2_out = p2_data;
end

end

