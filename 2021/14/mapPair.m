## Copyright (C) 2021 ijz67398
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} mapPair (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: ijz67398 <ijz67398@TE6WILDRIDINGS>
## Created: 2021-12-14

function out = mapPair (pair_list, result_list, a,b)
  out = -1;
  
  for i = 1:length(pair_list)
    check1 = (pair_list{i}(1) == a);
    check2 = (pair_list{i}(2) == b);
    
    if(check1 && check2)
      out = result_list(i);
      return;    
    endif
    
  endfor


endfunction
