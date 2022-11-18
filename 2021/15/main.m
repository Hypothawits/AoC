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

%convert to grid
for i = 1:length(txtread)
  line = txtread{i};
  
  for j = 1:length(line)
    gridData(i,j) = str2num(line(j));
  endfor

endfor

gridData

max_y = size(gridData)(1);
max_x = size(gridData)(2);

start_pos = [1,1];
end_pos = [max_y,max_x];

cPos = [1,1];

cX = cPos(1);
cY = cPos(2);

out = 0;
out = gridData(cY,cX) + moveSub(cY, cX, max_y, max_x, gridData, ' ', out);

##while ~all(cPos == end_pos)
##  cX = cPos(1);
##  cY = cPos(2);
##    
##    
##
##endwhile
