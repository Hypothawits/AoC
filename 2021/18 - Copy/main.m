clear;
fid = fopen ("test.txt");
##fid = fopen ("input.txt");
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

backup_copy = txtread;


result = txtread{1};

for i = 2:length(txtread)
  
  B = txtread{i}
  result = sumList(result, B)
  
  [explode idx] = needExplode (result)
  while(explode)
    result = doExplode (result, idx)
    %explode again?
    [explode idx] = needExplode (result)
    result(idx-1:idx+3)
  endwhile
  
endfor

result
##test = '[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]'
##
##[explode idx] = needExplode (test)
##result = doExplode (test, idx)
##
##[explode idx] = needExplode (result)
##result = doExplode (result, idx)















