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

time_id = tic ();

gridData = [];

%convert to Grid
for i = 1:length(txtread)
  line = txtread{i};
  
  for j = 1:length(line)
    gridData(i,j) = str2num(line(j));
  endfor

endfor


for x = 1:size(gridData)(1)
  for y = 1:size(gridData)(2)
    
    localMin_Grid(x,y) = localMin (gridData, y,x);
    
  endfor
  
endfor

gridData;
localMin_Grid;

risk = sum(gridData(localMin_Grid==1 )+1);


%Find basin edges
basin_grid = ~(gridData == 9) .*1;

[y,x] = find(localMin_Grid);
number_basins = length(x);

for basin = 2:number_basins
  xb = x(basin);
  yb = y(basin);
  
  done = false;
  basin_grid(yb, xb) = basin;
  while(done == false)
    [ty, tx] = find(basin_grid == basin);
    preCount = sum(sum(basin_grid==basin));
    for i = 1:length(tx)
      if(ty(i) < size(basin_grid)(1) )
        if(basin_grid(ty(i)+1, tx(i))) basin_grid(ty(i)+1, tx(i)) = basin; endif
      endif
      if(ty(i)-1 > 0 )
        if(basin_grid(ty(i)-1, tx(i))) basin_grid(ty(i)-1, tx(i)) = basin; endif
      endif
      if(tx(i) < size(basin_grid)(2) )
        if(basin_grid(ty(i),   tx(i)+1)) basin_grid(ty(i), tx(i)+1) = basin; endif
      endif
      if(tx(i)-1 > 0 )
        if(basin_grid(ty(i),   tx(i)-1)) basin_grid(ty(i), tx(i)-1) = basin; endif   
      endif
     
    endfor
    postCount = sum(sum(basin_grid==basin));
    
    if(preCount == postCount)
      %no change, stop growing
      done = true;
    endif
    
    
    
  endwhile
  

  
endfor

results = [];
for basin = 2:number_basins
  results = [results sum(sum(basin_grid == basin))];

endfor

a = sort(results)(end-2:end)

a(1)*a(2)*a(3)

toc(time_id)