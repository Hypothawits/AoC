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

backup_copy = txtread;

%convert to Grid
for i = 1:length(txtread)
  line = txtread{i};
  
  for j = 1:length(line)
    gridData(i,j) = str2num(line(j));
  endfor

endfor
disp("input");
disp(gridData);

stepData = gridData;

flash_count = 0;

for (stepNum = 1:200)
  #disp(["step:" , num2str(stepNum)])
  #increment by 9
  stepData = step(stepData);

  #check for flash numbers
  [stepData, flash_count] = propFlash (stepData, flash_count);
  
endfor

flash_count

#reset Data
stepNum = 1;
stepData = gridData;
flash_count = 0;
all_flash = false;

while( all_flash == false)
  #disp(["step:" , num2str(stepNum)])
  #increment by 9
  stepData = step(stepData);

  #check for flash numbers
  [stepData, flash_count] = propFlash (stepData, flash_count);
  
  %Part two:
  all_flash = all(all(stepData == 0));
  if(all_flash)
    disp(["All Flash: ", num2str(stepNum)]);
  endif

   stepNum +=1;
endwhile



