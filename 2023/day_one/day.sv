module day #(parameter int PART = 1) (
    input reg [7:0] input_char,
    input logic clk,
    input logic rst,
    output logic is_num_out,
    output logic[15:0] result_out
);

  logic is_number = 0;
  logic char_found_flag;
  logic [7:0] char_num;
  logic first_num_found;
  logic [7:0] first_num;
  logic [7:0] last_num;


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

  check_for_number cfn_inst(
      .input_char(input_char),
      .clk(clk),
      .rst(rst),
      .char_found_flag(char_found_flag),
      .num_out(char_num)
  );

  always_ff @(posedge clk or negedge rst or posedge char_found_flag) begin

    if (rst == 0) begin
      // is_number = 0;
      first_num_found <= 0;
      first_num <= " ";
      last_num <= " ";

    end else begin
      if (is_number == 1) begin
        if (first_num_found == 0) begin
          first_num <= input_char;
          last_num <= input_char;
          first_num_found <= 1;
        end else begin
          last_num <= input_char;
        end
      end

      if (PART == 2) begin
        if (char_found_flag == 1) begin
          if (first_num_found == 0) begin
            first_num <= char_num;
            last_num <= char_num;
            first_num_found <= 1;
          end else begin
            last_num <= char_num;
          end
        end
      end

    end



  end

endmodule
