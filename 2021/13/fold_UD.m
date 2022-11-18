function out = fold_UD (gridData, y, max_y)
##  if(rem(max_y,2) == 0)
##  %is Even grid
##    spiltData_t = gridData(1:y     ,  :);
##    spiltData_b = gridData(y+1:end ,  :);
##    
##    
##    
##    spiltData_f = flipud(spiltData_b);
##    
##    out = spiltData_t | spiltData_f;
##  
##  else
  %is Odd grid
    spiltData_t = gridData(1:y-1    ,  :);
    spiltData_b = gridData(y+1:end  ,  :);
    
    
    
    spiltData_f = flipud(spiltData_b);
    
    out = spiltData_t | spiltData_f;
  
  
##  endif
  
  
  
endfunction
