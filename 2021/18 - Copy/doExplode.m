
function input = doExplode (input, idx)
  %input = result
  %idx
  % '[ [5,6],3]'
  % '[ 3, [5,6]]'
  
  
  
  
  
  
  b_start = idx;
  b_end = b_start + find(input(b_start:end) == ']')(1) -2;
  
  
  A = input(b_start:b_end);
  L_number = str2num(A(1:find(A == ',')-1 ) )    ;
  R_number = str2num(A( find(A == ',')+1:end ) ) ;

  isNumber = ~(input == '[' | input == ']' | input == ',');
  
  is_number_left_of_explode = any(isNumber(1:b_start-1));
  is_number_right_of_explode = any(isNumber(b_end+1:end));
  
  

  
  
  if is_number_left_of_explode
    %find first number to left and add L_number to it
    next_number_index = find(isNumber(1:b_start-1))(end);
    next_number = str2num(input(next_number_index));
    new_number = next_number + L_number;
    
    if new_number <10
      input(next_number_index) = num2str(new_number);
    else
##      input(b_start:b_end)
      new_str = doSplit(new_number);
      input = [input(1:next_number_index-1) new_str input(next_number_index+1:end)];
      
      % Recalc Helper arrays
      b_start += 4; %  inserted 5 chars'[z,x]'
      b_end += 4;
##      input(b_start:b_end)
      
      isNumber = ~(input == '[' | input == ']' | input == ',');
      is_number_left_of_explode = any(isNumber(1:b_start-1));
      is_number_right_of_explode = any(isNumber(b_end+1:end));
    endif
    
  endif
  
  if is_number_right_of_explode
    %find first number to right and add R_number to it
    next_number_index = b_end + find(isNumber(b_end+1:end))(1);
    next_number = str2num(input(next_number_index));
    new_number = next_number + R_number;
    
    if new_number <10
      input(next_number_index) = num2str(new_number);
    else
##      input(b_start:b_end)
      new_str = doSplit(new_number);
      input = [input(1:next_number_index-1) new_str input(next_number_index+1:end)];
      
      % Recalc Helper arrays
      %b_start += 4; %  inserted 5 chars'[z,x]'
      %b_end += 4;
##      input(b_start:b_end)
      
      isNumber = ~(input == '[' | input == ']' | input == ',');
      is_number_left_of_explode = any(isNumber(1:b_start-1));
      is_number_right_of_explode = any(isNumber(b_end+1:end));
    endif
    
  endif
  
  input = [input(1:b_start-2) '0' input(b_end+2:end)];
  
  %remove pair from input
  

  %check if split
  
endfunction
