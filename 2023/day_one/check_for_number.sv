module check_for_number (
  input reg [7:0] input_char,
  input logic clk,
  input logic rst,
  output logic [7:0] num_out,
  output logic char_found_flag
);

  logic is_number = 0;

  logic first_num_found = 0;
  logic [7:0] first_num = 0;
  logic [7:0] last_num  = 0;

  // typedef enum {O,ON,ONE,
  //               T,TW,TWO,
  //               NONE} num_state_e;

  typedef enum {O,ON,ONE,
                T,TW,TWO,
                TH,THR,THRE,THREE,
                F,FO,FOU,FOUR,
                FI,FIV,FIVE,
                S,SI,SIX,
                SE,SEV,SEVE,SEVEN,
                E,EI,EIG,EIGH,EIGHT,
                N,NI,NIN,NINE,
                // Z,ZE,ZER,ZERO,
                NONE} num_state_e;

  num_state_e current_state = NONE;

  always_ff @( negedge clk ) begin
    char_found_flag <= 0;
  end

  always_ff @(posedge clk or negedge rst) begin
    if (rst == 0) begin
      current_state <= NONE;
    end else begin

      case (current_state)
        O:      begin
            case (input_char)
              "n": current_state <= ON;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              // "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        ON:     begin
            case (input_char)
              "e": begin
                current_state <= ONE;
                char_found_flag <= 1;
                num_out <= "1";
              end
              "i": current_state <= NI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        ONE:    begin
            case (input_char)
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        T:      begin
            case (input_char)
              "w": current_state <= TW;
              "h": current_state <= TH;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        TW:     begin
            case (input_char)
              "o":  begin
                current_state <= TWO;
                char_found_flag <= 1;
                num_out <= "2";
              end

              // "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        TWO:    begin
            case (input_char)
              "n": current_state <= ON;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              // "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        TH:     begin
            case (input_char)
              "r": current_state <= THR;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        THR:    begin
            case (input_char)
              "e": current_state <= THRE;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        THRE:   begin
            case (input_char)
              "e": begin
                current_state <= THREE;
                char_found_flag <= 1;
                num_out <= "3";
              end
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        THREE:  begin
            case (input_char)
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        F:      begin
            case (input_char)
              "o": current_state <= FO;
              "i": current_state <= FI;

              // "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FO:     begin
            case (input_char)
              "u": current_state <= FOU;
              "n": current_state <= ON;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              // "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FOU:    begin
            case (input_char)
              "r": begin
                current_state <= FOUR;
                char_found_flag <= 1;
                num_out <= "4";
              end

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FOUR:   begin
            case (input_char)
              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FI:     begin
            case (input_char)
              "v": current_state <= FIV;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FIV:    begin
            case (input_char)
              "e": begin
                current_state <= FIVE;
                num_out <= "5";
                char_found_flag <= 1;
              end
              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        FIVE:   begin
            case (input_char)
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        S:      begin
            case (input_char)
              "i": current_state <= SI;
              "e": current_state <= SE;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SI:     begin
            case (input_char)
              "x": begin
                current_state <= SIX;
                char_found_flag <= 1;
                num_out <= "6";
              end

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SIX:    begin
            case (input_char)
              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SE:     begin
            case (input_char)
              "v": current_state <= SEV;
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SEV:    begin
            case (input_char)
              "e": current_state <= SEVE;


              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SEVE:   begin
            case (input_char)
              "n": begin
                current_state <= SEVEN;
                char_found_flag <= 1;
                num_out <= "7";
              end
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              // "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        SEVEN:  begin
            case (input_char)
              "i": current_state <= NI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        E:      begin
            case (input_char)
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        EI:     begin
            case (input_char)
              "g": current_state <= EIG;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        EIG:    begin
            case (input_char)
              "h": current_state <= EIGH;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        EIGH:   begin
            case (input_char)
              "t": begin
                current_state <= EIGHT;
                char_found_flag <= 1;
                num_out <= "8";
              end

              "o": current_state <= O;
              // "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        EIGHT:  begin
            case (input_char)
              "w": current_state <= TW;
              "h": current_state <= TH;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        N:      begin
            case (input_char)
              "i": current_state <= NI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        NI:     begin
            case (input_char)
              "n": current_state <= NIN;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              // "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        NIN:    begin
            case (input_char)
              "e": begin
                current_state <= NINE;
                char_found_flag <= 1;
                num_out <= "9";
              end
              "i": current_state <= NI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              // "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        NINE:   begin
            case (input_char)
              "i": current_state <= EI;

              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        // Z:      begin
        //     case (input_char)
        //       "e": current_state <= ZE;

        //       "o": current_state <= O;
        //       "t": current_state <= T;
        //       "f": current_state <= F;
        //       "s": current_state <= S;
        //       // "e": current_state <= E;
        //       "n": current_state <= N;
        //       "z": current_state <= Z;
        //       default: current_state <= NONE;
        //     endcase
        //   end
        // ZE:     begin
        //     case (input_char)
        //       "r": current_state <= ZER;
        //       "i": current_state <= EI;

        //       "o": current_state <= O;
        //       "t": current_state <= T;
        //       "f": current_state <= F;
        //       "s": current_state <= S;
        //       // "e": current_state <= E;
        //       "n": current_state <= N;
        //       "z": current_state <= Z;
        //       default: current_state <= NONE;
        //     endcase
        //   end
        // ZER:    begin
        //     case (input_char)
        //       "o": begin
        //         current_state <= ZERO;
        //         char_found_flag <= 1;
        //         num_out <= "0";
        //       end

        //       // "o": current_state <= O;
        //       "t": current_state <= T;
        //       "f": current_state <= F;
        //       "s": current_state <= S;
        //       "e": current_state <= E;
        //       "n": current_state <= N;
        //       "z": current_state <= Z;
        //       default: current_state <= NONE;
        //     endcase
        //   end
        // ZERO:   begin
        //     case (input_char)
        //       "n": current_state <= ON;

        //       "o": current_state <= O;
        //       "t": current_state <= T;
        //       "f": current_state <= F;
        //       "s": current_state <= S;
        //       "e": current_state <= E;
        //       // "n": current_state <= N;
        //       "z": current_state <= Z;
        //       default: current_state <= NONE;
        //     endcase
        //   end
        NONE:   begin
            num_out <= " ";
            case (input_char)
              "o": current_state <= O;
              "t": current_state <= T;
              "f": current_state <= F;
              "s": current_state <= S;
              "e": current_state <= E;
              "n": current_state <= N;
              // "z": current_state <= Z;
              default: current_state <= NONE;
            endcase
          end
        default: current_state <= NONE;
      endcase

    end

  end

endmodule
