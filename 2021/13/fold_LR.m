function out = fold_LR (gridData, x, max_x)
##  if(rem(max_x,2) == 0)
##  %is even grid
##    spiltData_l = gridData(: , 1:x-1);
##    spiltData_r = gridData(: , x:end );
##    
##    spiltData_f = fliplr(spiltData_r);
##    
##    out = spiltData_l | spiltData_f;
##  else
  %is odd grid
    spiltData_r = gridData(: , x+1:end);
    spiltData_l = gridData(: , 1:x-1);
    
    
    spiltData_f = fliplr(spiltData_r);
    
    out = spiltData_l | spiltData_f;
##  endif
  

endfunction
