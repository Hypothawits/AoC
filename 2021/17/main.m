clear;
##target area: x=102..157, y=-146..-90
##target.x = 20:30;
##target.y = -10:-5;
target.x = 102:157;
target.y = -146:-90;

pos.x = 0;
pos.y = 0;

velocity.x = 7;
velocity.y = 2;

valid_velocities = {};

####velocity_y = velocity.y:-1:-10
####pos_x = velocity_y .+2
##
##
check = true;

innit_velocity = velocity;
store_max_valid_y = [];
for y = -146:1:250
##  for x = 14:1:150
  for x = 14:1:157

    velocity.x = x;
    velocity.y = y;
    
    pos.x = 0;
    pos.y = 0;
    
    innit_velocity = velocity;
    check = true;
    temp_store_max_y = 0;
    while check == true;
      [pos, velocity] = step(pos, velocity);
      
      if (pos.y > temp_store_max_y) temp_store_max_y = pos.y; endif
      
      if( any(target.x == pos.x) && any(target.y == pos.y) )
        %found valid velocity
        check = false;
        valid_velocities{ length(valid_velocities) +1 } = innit_velocity;
        store_max_valid_y = [store_max_valid_y temp_store_max_y];
      elseif (all(target.x < pos.x) || all(target.y > pos.y))
        %invalid velocity found
        check = false;
      endif
      
    endwhile

  endfor
endfor
##store_max_valid_y
max(store_max_valid_y)
%516 too low
length(store_max_valid_y)
##function out = step (pos, velocity)
##  pos.x += velocity.x;
##  pos.y += velocity.y;
##  
##  velocity.x += (velocity.x > 0)*-1 + (velocity.x < 0)*1;
##  velocity.y += -1;
##
##endfunction
