function out = doSplit (new_number)

  a = floor(new_number/2);
  b = ceil(new_number/2);

  out = [ '[' num2str(a) ',' num2str(b) ']' ];


endfunction
