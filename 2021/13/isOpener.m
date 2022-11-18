
function out = isOpener (input)
  openChars = ['{' '[' '(' '<'];
  out = any(openChars == input);
  
endfunction
