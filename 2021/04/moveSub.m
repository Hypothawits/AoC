

function out = moveSub (cY, cX, max_y, max_x,  gridData, prevPos, out)
  if all([cY cX] == [max_y max_x])
    out +=gridData(cY,cX);
    return;
  endif
  
  
  R = L = U = D = 99;
  %Possible Moves
  if(cX < max_x)
    R = gridData(cY,cX+1)
  endif
  if(cX > 1)
    L = gridData(cY,cX-1)
  endif
  if(cY < max_y)
    U = gridData(cY+1,cX) 
  endif
  if(cY > 1)
    D = gridData(cY-1,cX)
  endif
  
  temp = [R L U D]
  temp = temp(temp < 99); %remove invalid options
  
  move_R_score = sum( R > temp );
  move_L_score = sum( L > temp );
  move_U_score = sum( U > temp );
  move_D_score = sum( D > temp );
  
  temp = [move_R_score move_L_score move_U_score move_D_score]
  
  
  temp = temp .+ 99 .* [ (prevPos == 'R') (prevPos == 'L') (prevPos == 'U') (prevPos == 'D')];
  temp == min(temp)  
  
  
  move = [temp == min(temp)]
  move_R = move(1)
  move_L = move(2) 
  move_U = move(3)
  move_D = move(4)
  
  if  move_U
    out += gridData(cY,cX) + moveSub(cY+1, cX, max_y, max_x, gridData, 'D');
        
  elseif move_R
    out += gridData(cY,cX) + moveSub(cY, cX+1, max_y, max_x, gridData, 'L');
    
  elseif move_D
    out += gridData(cY,cX) + moveSub(cY-1, cX, max_y, max_x, gridData, 'U');
    
  elseif move_L
    out += gridData(cY,cX) + moveSub(cY, cX-1, max_y, max_x, gridData, 'R');
    
  endif
endfunction
