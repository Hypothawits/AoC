
function out = score2 (y)

  switch y
    case ')'
      out = 1;
      return;
    case ']'
      out = 2;
      return;
    case '}'
      out = 3;
      return;
    case '>'
      out = 4;
      return;
      
  endswitch


endfunction
