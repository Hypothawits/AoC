function [stepData, flash_count] = propFlash (stepData, flash_count)
  flash_index = (stepData > 9);
  flashCheck = any(any(flash_index));
  
  if(flashCheck)
    [r,c] = find(flash_index);
    stepData(r(1),c(1)) = -inf;
    stepData = increaseSurr (stepData,1, r,c);
    flash_count = flash_count +1;
    [stepData, flash_count] = propFlash (stepData, flash_count);
    stepData(r(1),c(1)) = 0;
    
    
  endif
endfunction
