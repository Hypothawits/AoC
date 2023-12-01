`timescale 1ns / 1ps

module tb_day;

  localparam int Part = 2;  // Which part of the puzzle to run
  localparam int T = 10;  // clock period in ns
  localparam int TextSize = 5+1;

  localparam int TEST = 0;

  logic clk;
  logic rst;

  int fd;  // file descriptor

  reg [0:TextSize-1][7:0] line_reg;
  string line_str;
  integer code = 1;

  // initial begin
  //   result = 0;
  // end
  string str_queue[$];
  string str_out_queue[$];

  logic [7:0] my_char;

  // Read file
  initial begin
    // string input_string;
    if (TEST == 1) begin
      if (Part == 1) begin
        fd = $fopen("./input_test.txt", "r");
      end else begin
        fd = $fopen("./input_test_p2.txt", "r");
      end
    end else begin
      fd = $fopen("./input.txt", "r");
    end

    if (fd != 0) begin
      $display("INFO: Input Opened");
    end else begin
      $display("ERROR: File Open Failed");
    end

    // Read whole file
    // code = $fgets(line_reg, fd);
    // $display("%s", line_reg);

    // Read one line
    // code = $fscanf(fd, "%s\n", line_str);
    // $display("%s", line_str);

  end

  int tmp_str_to_int = 0;
  int final_result = 0;

  initial begin
    clk = 1'b0; // start low
    rst = 1'b1; // start high to pull active low

    while (code != -1) begin
      code = $fscanf(fd, "%s\n", line_str);
      // $display("code: %d", code);

      if (code == 1) begin
        str_queue.push_back(line_str);
      end
    end

    $display("Number of Lines: %d", $size(str_queue));

    if (TEST == 1) begin
      foreach (str_queue[i]) begin
        $display("queue: %d: %s", i, str_queue[i]);
      end
    end



    foreach (str_queue[i]) begin
      //loop through each line
      line_str = str_queue[i];
      // $display("%s", line_str);

      //reset the internal state
      rst = 1'b0;
      #(T) rst = 1'b1;

      for(int j = 0; j < $size(line_str); j++) begin
        //loop through each char
          input_char = line_str[j];
          #(T);
          // $display("%s", line_str[j]);
      end

      #(T);
      str_out_queue.push_back(result_out);
      $display("%s : %s", line_str, result_out);

    end

    if (TEST == 1) begin
      foreach (str_out_queue[i]) begin
        $display("results: %d: %s", i, str_out_queue[i]);
      end
    end

    foreach (str_out_queue[i]) begin
      tmp_str_to_int = str_out_queue[i].atoi();
      final_result = final_result + tmp_str_to_int;
      // $display("Final Result: %d",final_result);
    end


    $display("Final Result: %d",final_result);
    // part 2 results:
    // 55631 too high!
    // 13625 too low!
    // 13625
    $display("Finished Normally");
    $finish;
  end


  // Clock
  always begin
    clk = #(T / 2) ~clk;
  end

  reg [7:0] input_char;
  logic is_num_out;
  logic [15:0] result_out;

  day #( .PART(Part) ) dut (
      .clk(clk),
      .rst(rst),
      .input_char(input_char),
      .is_num_out(is_num_out),
      .result_out(result_out)
  );

  int i = 0;
  always @(posedge clk) begin
    //  $display("i:%d, char:%s, is_num: %d, result:%s", i, line_str[i], is_num_out, result_out);
    //  input_char = line_str[i];
    //  i = i + 1;
    // result_in = result_out;
    // if (result_in == -1) begin
    //   $display("first basement: %d", i-1);
    // end
  end
  always @(negedge clk) begin

  end

  // sets up time and signal dumping
  initial begin
    $timeformat(-9, 1, " ns", 8);
    $dumpfile("day.vcd");
    $dumpvars(0, tb_day);
  end

  // Set max time until simulation finish (number of cycles)
  initial begin
    #(1000000) $display("ERROR: Run out of Simulation");
    $finish;
  end

  final begin
    $fclose(fd);
    // $display("final result: %d", result_out);
    $display("File Length chars: %d", TextSize);
    $display("Clock Cycles: %d", i);
  end

endmodule  // counter_tb
