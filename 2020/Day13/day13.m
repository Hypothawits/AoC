clear;
filename = "test.txt";
inputLines = splitlines(fileread(filename));

input_data = {};


leavingTime = str2double( inputLines{1} );
bus_data = inputLines{2};

bus_data = split(bus_data,',');

bus_data = string(bus_data);

mask = bus_data == 'x';
bus_data = bus_data(~mask);
bus_data = str2double(bus_data);
% bus_data = sort(bus_data);

a = leavingTime ./ bus_data
b = a - floor(a)

c = max(b)

%for line_num=1:length(inputLines)
%    line = inputLines{line_num};
%    
%    disp(line) 
%end

% part 1


result = "no result yet!";
disp("part 1")
disp( result )

