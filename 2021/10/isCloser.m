function out = isCloser (input)
  closeChars = ['}' ']' ')' '>'];
  out = any(closeChars == input);
endfunction
