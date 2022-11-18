## Copyright (C) 2021 tsecc
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
## @deftypefn {} {@var{retval} =} score (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: tsecc <tsecc@DESKTOP-F62I9SQ>
## Created: 2021-12-12

function out = score (y)

  switch y
    case ')'
      out = 3;
      return;
    case ']'
      out = 57;
      return;
    case '}'
      out = 1197;
      return;
    case '>'
      out = 25137;
      return;
      
  endswitch


endfunction
