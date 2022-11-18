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


grid = zeros(1000, 1000);

for i = 1:length(txtread)
##  txtread{i};
  
  bgn = txtread{i}( 1:find(txtread{i} == '-')-1   );
  ext = txtread{i}( find(txtread{i} == '-')+2:end );

  f_x = str2num(bgn(1:find(bgn == ',')-1 ) )    ;
  f_y = str2num(bgn( find(bgn == ',')+1:end ) ) ;
  e_x = str2num(ext(1:find(ext == ',') -1 ) )   ;
  e_y = str2num(ext( find(ext == ',')+1:end ) ) ;

  if(f_x > e_x)
    x_sel = f_x:-1:e_x;
  else
    x_sel = f_x:e_x;
  endif 
  
  if(f_y > e_y)
    y_sel = f_y:-1:e_y;
  else
    y_sel = f_y:e_y;
  endif
  
  linear_index = (y_sel .* length(grid)) .+ x_sel .+1;
  
  
  
  
  vert = (f_x == e_x);
  hoz = (f_y == e_y);
    

  if(vert || hoz)
    grid(linear_index) += 1;
  endif
  

  
endfor

##grid
## 20271 was part 2
transpose(grid);
sum(sum(grid >= 2))









