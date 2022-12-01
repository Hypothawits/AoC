function [explode need_explode_pairs] = needExplode (input)
 %count number of open brackets
 % input = '[[[[1,1],[2,2]],[3,3]],[4,4]]';
 % input = '[[[[[1,1],[2,2]],[3,3]],[4,4]],[5,5]]';
 
  isNumber = ~(input == '[' | input == ']' | input == ',');
  start_bracket_pair = isNumber & [isNumber(3:end) [0 0]];
  
  index_pairs = find(start_bracket_pair);
  need_explode_pairs = [];
  
  for j = 1:length(index_pairs)
    pair_start = index_pairs(j);
    
    idx = 0;
    
    a = input(1:pair_start) == '[';
    b = input(1:pair_start) == ']';
    
    c = sum((a .* 1) - (b .* 1));
    if c > 4
      idx = pair_start;
      need_explode_pairs = [need_explode_pairs pair_start];
    endif

  endfor
  
  explode = (length(need_explode_pairs) > 0);
  
  
  

endfunction
