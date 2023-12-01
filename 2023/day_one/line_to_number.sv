module line_to_number (
  input reg [7:0] input_char,
  input logic clk,
  output logic is_num_out,
  output logic[15:0] result_out
);

  logic is_number = 0;

  logic first_num_found = 0;
  logic [7:0] first_num = 0;
  logic [7:0] last_num  = 0;


  assign is_num_out = is_number;
  assign result_out = {first_num, last_num};

  initial begin

  end

  always_comb begin
    case (input_char)
      "1": is_number = 1;
      "2": is_number = 1;
      "3": is_number = 1;
      "4": is_number = 1;
      "5": is_number = 1;
      "6": is_number = 1;
      "7": is_number = 1;
      "8": is_number = 1;
      "9": is_number = 1;
      "0": is_number = 1;
      default: is_number = 0;
    endcase
  end

  always_ff @(posedge clk) begin
    if (is_number == 1) begin
      if (first_num_found == 0) begin
        first_num <= input_char;
        last_num <= input_char;
        first_num_found <= 1;
      end else begin
        last_num <= input_char;
      end
    end
  end

endmodule