
function out = localMin (gridData, x,y)
  out = 1;
  if(x<size(gridData)(2))
    a = gridData(y,x) > gridData(y,x+1);
    if(a) out = 0; end
  end
  if(x>1)
    b = gridData(y,x) > gridData(y,x-1);
    if(b) out = 0; end
  end
  if (y <size(gridData)(1))
    c = gridData(y,x) > gridData(y+1,x);
    if(c) out = 0; end
  end
  if(y>1)
    d = gridData(y,x) > gridData(y-1,x);
    if(d) out = 0; end
  end
  
endfunction
