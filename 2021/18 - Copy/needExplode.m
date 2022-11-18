function [out idx] = needExplode (input)
 %count number of open brackets
 % input = '[[[[1,1],[2,2]],[3,3]],[4,4]]';
 % input = '[[[[[1,1],[2,2]],[3,3]],[4,4]],[5,5]]';
 
  isNumber = ~(input == '[' | input == ']' | input == ',');
  start_bracket_pair = isNumber & [isNumber(3:end) [0 0]];
  
  index_pairs = find(start_bracket_pair);

  for j = 1:length(index_pairs)
    pair_start = index_pairs(j);
    
    out=false;
    idx = 0;
    
    a = input(1:pair_start) == '[';
    b = input(1:pair_start) == ']';
    count = 0;
    for i = 1:length(a)
      count += ( a(i) - b(i) );
      if count >4
        out = true;
        idx = pair_start;
        return;
        break;
      endif
    endfor

  endfor
  

  
  
  

endfunction
