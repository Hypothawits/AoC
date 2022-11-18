clear;
##fid = fopen ("test.txt");
fid = fopen ("input.txt");
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

input_map = txtread{1};
input_image = [];
for i = 3:length(txtread)
  input_image = [input_image ; txtread{i}];
endfor

input_map = input_map == '#';
input_image = input_image == '#';
original_image = input_image;

[y,x] = size(input_image);
bigger_image = zeros(y+4, x+4);
binary_map = [256 128 64; 32 16 8; 4 2 1];

num_step = 50;
infinate_void_value = 0;
for step = 1:num_step
  
  [y,x] = size(input_image);
  bigger_image = ones(y+4, x+4) .* infinate_void_value;
  next_image   = ones(y+4, x+4) .* infinate_void_value;
  
  %Copy input into bigger frame
  bigger_image(3:end-2, 3:end-2) = input_image;
  
  
  %Loop over squares
  for x = 2:(length(bigger_image)-1)
    for y = 2:(length(bigger_image)-1)
      test_square = get3by3(bigger_image, y,x);
      idx = sum(sum(test_square .* binary_map));
      new_pixel = input_map(idx+1);
      
      next_image(x,y) = new_pixel;
      
      
    endfor
  endfor
  
  %deal with the "trick" =(
  if input_map(1)
    first_pixel = input_map(1);
    last_pixel = input_map(length(input_map));
    
    if next_image(1,1) == first_pixel
      %replace edge with last pixel
      next_image(1,:)  = last_pixel;
      next_image(end,:)= last_pixel;
      next_image(:,1)  = last_pixel;
      next_image(:,end)= last_pixel;
      
      infinate_void_value = last_pixel;
      
    else
      %replace edge with first pixel
      next_image(1,:)  = first_pixel;
      next_image(end,:)= first_pixel;
      next_image(:,1)  = first_pixel;
      next_image(:,end)= first_pixel;
      
      infinate_void_value = first_pixel;
    endif
  endif
  
  
  
  %copy the new image to the input
  input_image = next_image;
  
  
  
endfor


sum(sum(input_image))



% infinite in all directions...
## the first value of the decode is 1
## the last value of the decode is 0
## so the infinite space oscilates between 1 and zero...
## on every step...


%part2 in 192.904s












toc(time_id)
