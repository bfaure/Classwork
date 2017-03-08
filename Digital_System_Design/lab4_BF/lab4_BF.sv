
// Brian Faure
// lab4_BF.sv

module lab4_BF(input logic clk,
               input logic reset,
               input logic left,right,
               output logic la,lb,lc,ra,rb,rc);

  // Creating state encoding struct
  typedef enum logic [5:0] {S0 = 6'b000000,
                            S1 = 6'b001000,
                            S2 = 6'b011000,
                            S3 = 6'b111000,
                            S4 = 6'b000100,
                            S5 = 6'b000110,
                            S6 = 6'b000111} statetype;
  
  // Creating two statetype objects
  statetype state, nextstate;
  
  // State register, triggered by either the clock or reset
  always_ff @(posedge clk, posedge reset)
    begin
      if (reset) 	state <= S0;		
      else			state <= nextstate;
    end
  
  // Next state logic
  always_comb
    begin
      
      case (state)
        S0:
          begin
          	if (left & ~reset) 			nextstate <= S4;
            else if (right & ~reset) 	nextstate <= S1;
            else						nextstate <= S0;
          end
        S1:
           begin
             if (~reset)				nextstate <= S2;
             else						nextstate <= S0;
           end
        S2:
          begin
            if (~reset)					nextstate <= S3;
            else						nextstate <= S0;
          end
        S3:
          begin
            if (~reset & right)			nextstate <= S1;
            else						nextstate <= S0;
          end
        S4:
          begin
            if (~reset)					nextstate <= S5;
            else						nextstate <= S0;
          end
        S5:
          begin
            if (~reset)					nextstate <= S6;
            else						nextstate <= S0;
          end
        S6:
          begin
            if (~reset & left)			nextstate <= S4;
            else						nextstate <= S0;
          end
        default:
          begin
            nextstate <= S0;
          end
      endcase 
    end

  // Output logic
  assign la = (state==S4 | state==S5 | state==S6);
  assign lb = (state==S5 | state==S6);
  assign lc = (state==S6);
  
  assign ra = (state==S1 | state==S2 | state==S3);
  assign rb = (state==S2 | state==S3);
  assign rc = (state==S3);
  
endmodule
  