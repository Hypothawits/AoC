clear;
fid = fopen ("test.txt");
##fid = fopen ("input.txt");
% save full lines into a new file if only chars inside

% Read in data (line by line)
i = 1;
lineRead = true;
while (lineRead)
  newLine = fgetl (fid);
    
  if (newLine == -1)
    lineRead = false;
  else
    txtread{i} = newLine;
    i = i+1;
  end
end
fclose (fid);

backup_copy = txtread;
time_id = tic ();

% proccess inputs
game_input = txtread{1};
game_input = strsplit (game_input, ',');
game_input = cellfun(@str2num, game_input);

game_boards = txtread{2:end};



game_boards = strsplit(game_boards, ' ');




board_group = cellfun(@isempty, game_boards)
number_of_boards = sum(board_group)

for board_num = 1:number_of_boards
  start_ = board_num +1 + 5*(board_num-1);
  end_ = start_ +3;
  boards{board_num} = game_boards(start_:end_)
endfor

 boards_score =  boards;

 boards{1}{1}
cell2mat(boards{1})

%play game

for round = 1:length(game_input)
  this_round = game_input(round);
  
endfor















toc(time_id)




