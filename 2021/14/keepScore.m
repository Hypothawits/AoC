function out = keepScore (char_in, val, out)

  switch char_in
    case 'S'
      out(1) += val;
    case 'V'
      out(2) += val;
    case 'F'
      out(3) += val;
    case 'P'
      out(4) += val;
    case 'B'
      out(5) += val;
    case 'O'
      out(6) += val;
    case 'K'
      out(7) += val;
    case 'N'
      out(8) += val;
    case 'H'
      out(9) += val;
    case 'C'
      out(10) += val;
  endswitch




endfunction

##for i = 1:length(input_list)
##  number = input_list{i}.count
##  
##  switch input_list{i}.pair(1)
##    case 'S'
##      out(1) = number;
##    case 'V'
##      out(2) = number;
##    case 'F'
##      out(3) = number;
##    case 'P'
##      out(4) = number;
##    case 'B'
##      out(5) = number;
##    case 'O'
##      out(6) = number;
##    case 'K'
##      out(7) = number;
##    case 'N'
##      out(8) = number;
##    case 'H'
##      out(9) = number;
##    case 'C'
##      out(10) = number;
##  endswitch
##  
##  switch input_list{i}.pair(2)
##    case 'S'
##      out(1) = number;
##    case 'V'
##      out(2) = number;
##    case 'F'
##      out(3) = number;
##    case 'P'
##      out(4) = number;
##    case 'B'
##      out(5) = number;
##    case 'O'
##      out(6) = number;
##    case 'K'
##      out(7) = number;
##    case 'N'
##      out(8) = number;
##    case 'H'
##      out(9) = number;
##    case 'C'
##      out(10) = number;
##  endswitch
##  
##endfor