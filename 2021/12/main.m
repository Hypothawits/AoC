function out = main()

clear;
fid = fopen ("test.txt");
##fid = fopen ("input.txt");
% save full lines into a new file if only chars inside
cell2mat

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

##for i = 1:length(txtread)
  bgn = txtread{1}( 1:find(txtread{1} == '-')-1   );
  ext = txtread{1}( find(txtread{1} == '-')+1:end );

  isStart(bgn);
  isStart(ext);
  
  isEnd(bgn);
  isEnd(ext);
  
##endfor


endfunction





function out = contains(list, test)
  out =any( cell2mat(list) == test );  
endfunction

function out = isEnd(input)
  out = all(input=='end');
endfunction

function out = isStart(input)
  out = all(input=='start');
endfunction