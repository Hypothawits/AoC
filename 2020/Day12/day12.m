clear;
filename = "input.txt";
inputLines = splitlines(fileread(filename));

input_data = {};

coords.x = 0;
coords.y = 0;

boat.heading = 'E';
boat.pos = coords;




for line_num=1:length(inputLines)
    line = inputLines{line_num};
    
    disp(line) 
     
    intruction = line(1);
    distance = str2double( line(2:length(line)) );
   
    input_data{line_num} = {intruction, distance}; %#ok<SAGROW>
end

% part 1
for i=1:length(inputLines)
    
    intruction = input_data{i}{1};
    distance   = input_data{i}{2};
    
    if     intruction == 'N'
        % Move North by number
        boat.pos.x = boat.pos.x + distance;
    elseif intruction == 'S'
        % Move South by number
        boat.pos.x = boat.pos.x - distance;
    elseif intruction == 'E'
        % Move East by number
        boat.pos.y = boat.pos.y + distance;
    elseif intruction == 'W'
        % Move West by number
        boat.pos.y = boat.pos.y - distance;
    elseif intruction == 'L'
        % Turn Left by degrees
         if     boat.heading == 'N'
            if distance == 90
                boat.heading = 'W';
            elseif distance == 180
                boat.heading = 'S';
            elseif distance == 270
                boat.heading = 'E';
            end
            
        elseif boat.heading == 'S'
            if distance == 90
                boat.heading = 'E';
            elseif distance == 180
                boat.heading = 'N';
            elseif distance == 270
                boat.heading = 'W';
            end
            
            
        elseif boat.heading == 'E'
            if distance == 90
                boat.heading = 'N';
            elseif distance == 180
                boat.heading = 'W';
            elseif distance == 270
                boat.heading = 'S';
            end
            
            
        elseif boat.heading == 'W'
            if distance == 90
                boat.heading = 'S';
            elseif distance == 180
                boat.heading = 'E';
            elseif distance == 270
                boat.heading = 'N';
            end
            
            
        end
        
        
        
    elseif intruction == 'R'
        % Turn Right by degrees
        if     boat.heading == 'N'
            if distance == 90
                boat.heading = 'E';
            elseif distance == 180
                boat.heading = 'S';
            elseif distance == 270
                boat.heading = 'W';
            end
            
        elseif boat.heading == 'S'
            if distance == 90
                boat.heading = 'W';
            elseif distance == 180
                boat.heading = 'N';
            elseif distance == 270
                boat.heading = 'E';
            end
            
            
        elseif boat.heading == 'E'
            if distance == 90
                boat.heading = 'S';
            elseif distance == 180
                boat.heading = 'W';
            elseif distance == 270
                boat.heading = 'N';
            end
            
            
        elseif boat.heading == 'W'
            if distance == 90
                boat.heading = 'N';
            elseif distance == 180
                boat.heading = 'E';
            elseif distance == 270
                boat.heading = 'S';
            end
            
            
        end
        
       
       
    elseif intruction == 'F'
        % Move Heading by number
        if     boat.heading == 'N'
            boat.pos.x = boat.pos.x + distance;
        elseif boat.heading == 'S'
            boat.pos.x = boat.pos.x - distance;
        elseif boat.heading == 'E'
            boat.pos.y = boat.pos.y + distance;
        elseif boat.heading == 'W'
            boat.pos.y = boat.pos.y - distance;
        end
    else
        disp("somethings gone wrong!")
    end
end

disp("part 1")
disp( abs(boat.pos.x) + abs(boat.pos.y) )


% reset and create waypoint
 % relative to the boat
waypoint.pos.x = +1;
waypoint.pos.y = +10;

coords.x = 0;
coords.y = 0;

boat.heading = 'E';
boat.pos = coords;

% part 2
for i=1:length(inputLines)
    
    intruction = input_data{i}{1};
    distance   = input_data{i}{2};
    
    if     intruction == 'N'
        % Move North by number
        waypoint.pos.x = waypoint.pos.x + distance;
        
    elseif intruction == 'S'
        % Move South by number
        waypoint.pos.x = waypoint.pos.x - distance;
        
    elseif intruction == 'E'
        % Move East by number
        waypoint.pos.y = waypoint.pos.y + distance;
        
    elseif intruction == 'W'
        % Move West by number
        waypoint.pos.y = waypoint.pos.y - distance;
        
    elseif intruction == 'L'
        % Turn Left by degrees
        [angle,R] = cart2pol(waypoint.pos.x,waypoint.pos.y);
        angle = angle - deg2rad(distance);
        [waypoint.pos.x,waypoint.pos.y] = pol2cart(angle,R);
                
    elseif intruction == 'R'
        % Turn Right by degrees
        [angle,R] = cart2pol(waypoint.pos.x,waypoint.pos.y);
        angle = angle + deg2rad(distance);
        [waypoint.pos.x,waypoint.pos.y] = pol2cart(angle,R);
        
    elseif intruction == 'F'
        % Move to waypoint a number of times
        for i = 1:distance
            boat.pos.x = boat.pos.x + waypoint.pos.x;
            boat.pos.y = boat.pos.y + waypoint.pos.y;
        end
    else
        disp("somethings gone wrong!")
    end
end

disp("part 2")
disp( abs(boat.pos.x) + abs(boat.pos.y) )