clear;
%fid = fopen ("test.txt");
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

txtread{1}

openChars = ['{' '[' '(' '<'];
closeChars = ['}' ']' ')' '>'];


isOpener (txtread{1}(1))
isCloser (txtread{1}(1))



total_score = 0;
corrupt_line_indx = [];
for (line = 1:length(txtread))
pos = 1;
corp = false;

while ( pos < length(txtread{line}))

  x = txtread{line}(pos);
  y = txtread{line}(pos+1);
  
  if(isOpener (x) & isCloser(y))
    #disp ("Could be a pair")
    switch (x)
      case '{'
        if(y != '}')
          corp = true;
          disp(['corrupt: ', txtread{line}]);
          
          total_score = total_score+score(y);
          corrupt_line_indx = [corrupt_line_indx, line];
          break
        endif
        #Remove pair from list
        txtread{line}(pos+1) = [];
        txtread{line}(pos) = [];
        #Reset position to start
        pos = 0;
      case '['
        if(y != ']')
          corp = true;
          disp(['corrupt: ',txtread{line}]);
          total_score = total_score+score(y);
          corrupt_line_indx = [corrupt_line_indx, line];
          break
        endif
        #Remove pair from list
        txtread{line}(pos+1) = [];
        txtread{line}(pos) = [];
        #Reset position to start
        pos = 0;
      case '('
        if(y != ')')
          corp = true;
          disp(['corrupt: ', txtread{line}]);
          total_score = total_score+score(y);
          corrupt_line_indx = [corrupt_line_indx, line];
          break
        endif
        #Remove pair from list
        txtread{line}(pos+1) = [];
        txtread{line}(pos) = [];
        #Reset position to start
        pos = 0;
        
      case '<'
        if(y != '>')
          corp = true;
          disp(['corrupt: ', txtread{line}]);
          total_score = total_score+score(y);
          corrupt_line_indx = [corrupt_line_indx, line];
          break
        endif
        #Remove pair from list
        txtread{line}(pos+1) = [];
        txtread{line}(pos) = [];
        #Reset position to start
        pos = 0;
    endswitch
    txtread{line};
  endif
  
  pos = pos +1;  
endwhile

  disp("End of Line Checks");
  #txtread{line}
endfor

disp(["Part 1: ", num2str(total_score) ]);
corrupt_line_indx
incomplete_lines = backup_copy;

incomplete_lines(corrupt_line_indx) = [];
txtread(corrupt_line_indx) = [];

incomplete_lines
disp("init")
txtread

for i = 1:length(txtread)
  txtread{i} = fliplr(txtread{i});
endfor

disp("flip")
txtread


for i = 1:length(txtread)
  for x = 1:length(txtread{i})
    txtread{i}(x) = flipBra(txtread{i}(x));
  endfor
endfor

disp("Swapped")
txtread
total_score =  zeros(1,length(txtread));

for i = 1:length(txtread)
  for x = 1:length(txtread{i})
    total_score(i) = total_score(i)*5 + score2(txtread{i}(x));
  endfor
endfor
disp("Result")
sorted_total = sort(total_score);
disp(sorted_total(  ceil(length(total_score)/2)     ))




