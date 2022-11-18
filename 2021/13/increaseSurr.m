
function input = increaseSurr (input,indx, r,c)
  size_in = size(input);
  rMax = size_in(1);
  cMax = size_in(2);
 
  if (r(indx) > 1)
    input(r(indx)-1,c(indx)) +=1;
  endif
  if (r(indx) < rMax)
    input(r(indx)+1,c(indx)) +=1;
  endif
  if (c(indx) > 1)
    input(r(indx),c(indx)-1) +=1;
  endif
  if (c(indx) < cMax)
    input(r(indx),c(indx)+1) +=1;
  endif

  if (c(indx) < cMax) && (r(indx) < rMax)
      input(r(indx)+1,c(indx)+1) +=1;
  endif
  if (c(indx) < cMax) && (r(indx) > 1)
      input(r(indx)-1,c(indx)+1) +=1;
  endif
  if (c(indx) > 1) && (r(indx) < rMax)
      input(r(indx)+1,c(indx)-1) +=1;
  endif
  if (c(indx) > 1) && (r(indx) > 1)
      input(r(indx)-1,c(indx)-1)+=1;
  endif
  
endfunction
  
      
      
      
      
      
      
      