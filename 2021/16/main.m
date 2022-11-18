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

a = transpose(txtread{1});
binary_stream_in = dec2bin(hex2dec(a));
binary_stream_in = transpose(binary_stream_in);
binary_stream_in = reshape(binary_stream_in, 1,4*length(binary_stream_in));

length_of_binary_in = length(binary_stream_in);

p_num = 1;
pos = 1;
while (pos <length_of_binary_in)
  

  packet{p_num}.version   = bin2dec(binary_stream_in(pos:pos+2));
  packet{p_num}.id        = bin2dec(binary_stream_in(pos+3:pos+5));
  packet{p_num}.length_id = bin2dec(binary_stream_in(pos+6:pos+6));
  if (packet{p_num}.length_id) 
    % id = 1
    packet{p_num}.length = 11;
    packet{p_num}.num_sub_packets = bin2dec(binary_stream_in(8:8+packet{p_num}.length-1));
    packet{p_num}.length_of_sub_packets = packet{p_num}.length * packet{p_num}.num_sub_packets;
    data_start = 8+packet{p_num}.length-1;
    packet{p_num}.data = binary_stream_in(data_start:data_start+packet{p_num}.length_of_sub_packets);
    packet_end = data_start+packet{p_num}.length_of_sub_packets;
    pos += (18 + packet{p_num}.length_of_sub_packets);
  else
    % id = 0
    packet{p_num}.length = 15;
    packet{p_num}.length_of_sub_packets = bin2dec(binary_stream_in(8:8+packet{p_num}.length-1));
    %packet{1}.num_sub_packets = packet{1}.length_of_sub_packets / packet{1}.length;
    data_start = 8+packet{p_num}.length-1;
    packet{p_num}.data = binary_stream_in(data_start:data_start+packet{p_num}.length_of_sub_packets);
    packet_end = data_start+packet{p_num}.length_of_sub_packets;
    pos += (22 + packet{p_num}.length_of_sub_packets);
  endif  


  p_num +=1;

endwhile
























