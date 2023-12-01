module day #(parameter int PART = 1) (
    input reg [7:0] input_char,
    input logic clk,
    input [31:0] result_in,
    output [31:0] result_out
);

  integer tmp_result;
  assign result_out = tmp_result;

  initial begin
    tmp_result = 0;
  end

  always_ff @(posedge clk) begin
    // $display("before: %d", input_char);
    if (input_char == "(") begin
      tmp_result <= result_in +1;
    end
    if (input_char == ")") begin
      tmp_result <= result_in -1;
    end
    // $display("after: %d", result);
  end

endmodule
