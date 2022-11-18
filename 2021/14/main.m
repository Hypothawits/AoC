clear;
##fid = fopen ("test.txt");
fid = fopen ("input.txt");
% save full lines into a new file if only chars inside

% Read in data (line by line)
i = 1;
lineRead = true;
while (lineRead)
  newLine = fgetl (fid);
    
  if (newLine == -1)
    lineRead = false;
  else
    txtread{i} = newLine;
    i = i+1;
  end
end
fclose (fid);

start_input = txtread{1}

txtread(2) = [];
txtread(1) = [];


backup_copy = txtread;

for i = 1:length(txtread)
  input_list{i}.pair = txtread{i}(1:2);
  input_list{i}.insert = txtread{i}(7);
  input_list{i}.next_1 = [txtread{i}(1) txtread{i}(7)];
  input_list{i}.next_2 = [txtread{i}(7) txtread{i}(2)] ;
  input_list{i}.count = 0;
endfor

%map char to index
map = cell(length(input_list), 2);

for i = 1:length(input_list)
  pair1 = input_list{i}.next_1;
  pair2 = input_list{i}.next_2;
  
  for j = 1:length(input_list)
    does1_match = all(input_list{j}.pair == pair1);
    does2_match = all(input_list{j}.pair == pair2);
    if(does1_match)
      input_list{i}.next_1 = j;
    endif
    if(does2_match)
      input_list{i}.next_2 = j;
    endif
  endfor


endfor

%setting up starting pairs
for i = 2:length(start_input)
  pair = start_input(i-1:i)
  
  %find the matching pair in the list
  for j = 1:length(input_list)
    does_match = all(input_list{j}.pair == pair)
    if(does_match)
      input_list{j}.count +=1 ;
      break;
    endif
  endfor
endfor
%%%% %%%% %%%%

out = zeros(1,10); %results
for i = 1:length(start_input)
  start_input(i)  
  out = keepScore(start_input(i), 1, out);
endfor


%do the hard bit
steps = 40;
for s = 1:steps
  
  in_copy = input_list;
  
  for i = 1:length(input_list)
    input_list{i};
    in_copy{  input_list{i}.next_1  }.count += 1*input_list{i}.count;
    in_copy{  input_list{i}.next_2  }.count += 1*input_list{i}.count;
    if(input_list{i}.count>0)
      in_copy{i}.count -=1*input_list{i}.count; %the current input is split
    endif
    out = keepScore(input_list{i}.insert, input_list{i}.count, out);
    
  endfor
  input_list = in_copy;
  
endfor

out
[' '; '   S   ' 'V   ' 'F   ' 'P   ' 'B   ' 'O   ' 'K   ' 'N   ' 'H   ' 'C                                                 .']


out2 = out(out > 0);

min(out2)
max(out2)

out2 = max(out2) - min(out2)

x = 0

##newLine = start_input;
##inputLine = newLine;
##
##steps = 10;
##newLine;
##for s = 1:steps
##  
##  for i = length(inputLine):-1:2
##    a = inputLine(i-1);
##    b = inputLine(i);
##    
##    out = mapPair(pair_list, result_list, a,b);
##    newLine = [newLine(1:i-1) out{1}  newLine(i:end)];
##    
##  endfor
##  newLine;
##  inputLine = newLine;
##endfor
##
##results = [ sum( newLine == 'S') sum( newLine == 'V') sum( newLine == 'F') sum( newLine == 'P') sum( newLine == 'B') sum( newLine == 'O') sum( newLine == 'K') sum( newLine == 'N') sum( newLine == 'H') sum( newLine == 'C')]
##
##results = results(results >0)
##
##min(results)
##max(results)
##
##out = max(results) - min(results)


