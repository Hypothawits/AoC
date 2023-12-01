`timescale 1ns / 1ps

module tb_day;

  localparam int Part = 1;  // Which part of the puzzle to run
  localparam int T = 10;  // clock period in ns
  localparam int TextSize = 7001;

  logic clk;

  int fd;  // file descriptor

  reg [0:TextSize-1][7:0] line_reg;
  string line_str;
  integer code;

  // initial begin
  //   result = 0;
  // end


  // Read file
  initial begin
    // string input_string;
    fd = $fopen("./input.txt", "r");

    if (fd) begin
      $display("INFO: Input Opened");
    end else begin
      $display("ERROR: File Open Failed");
    end

    code = $fgets(line_reg, fd);
    // $display("%s", line_reg);

    // $display("%s", line_reg[0]);
    // line_str.itoa("5");

  end

  initial begin
    clk = 1'b0;
    result_in = 0;
  end


  // Clock
  always begin
    clk = 1'b0;
    #(T / 2);
    clk = 1'b1;
    #(T / 2);
  end

  reg [7:0] input_char;

  integer result_in;
  integer result_out;

  day #( .PART(1) ) dut (
      .clk(clk),
      .input_char(input_char),
      .result_in(result_in),
      .result_out(result_out)
  );

  int i = 0;
  always @(posedge clk) begin
    // $display("i:%d, char:%s, result:%d", i, line_reg[i], result_out);
    // input_char = line_reg[i];
    // i = i + 1;
    // result_in = result_out;
    // if (result_in == -1) begin
    //   $display("first basement: %d", i-1);
    // end
  end
    always @(negedge clk) begin
    // $display("i:%d, char:%s, result:%d", i, line_reg[i], result_out);
    input_char = line_reg[i];
    i = i + 1;
    result_in = result_out;
  end


  initial begin
    $timeformat(-9, 1, " ns", 8);
    // $monitor("time=%t clk=%b", $time, clk);
    $dumpfile("day.vcd");
    $dumpvars(0, tb_day);
  end

  // Set time until simulation finish (number of cycles)
  initial begin
    #((TextSize * T)+T/2) $finish;
  end

  final begin
    $fclose(fd);
    $display("final result: %d", result_out);
    $display("File Length chars: %d", TextSize);
    $display("Clock Cycles: %d", i);
  end

endmodule  // counter_tb
