
// Brian Faure
// alu.sv

module alu(input logic signed [31:0] 	a, b,
           input logic [2:0]			f,
           output logic signed [31:0]	y,
           output logic					zero);
  
  // Creating state encodings
  typedef enum logic [2:0] {s0 = 3'b000, // A AND B
                            s1 = 3'b001, // A OR B
                            s2 = 3'b010, // A + B
                            s3 = 3'b011, // not used
                            s4 = 3'b100, // A AND B'
                            s5 = 3'b101, // A OR B'
                            s6 = 3'b110, // A - B
                            s7 = 3'b111}  // SLT (Set less than)
  statetype;
  
  // Logic to create outputs based on input f
  always_comb
    begin
      
      // Break down execution by operation type
      case(f)
        
        // A AND B
        s0:
          begin
            $display("Performing A AND B");
            y <= a & b;
            
          end
        
        // A OR B
        s1:
          begin
            $display("Performing A OR B");
            y <= a | b;
            
          end
        
        // A + B
        s2: 
          begin
            $display("Performing A + B");
            y <= a + b;
            
          end
        
        // not used
        s3:
          begin
            $display("Encoding not used");
            y <= a;
            
          end
        
        // A AND B'
        s4:
          begin
            $display("Performing A AND B'");
            y <= a & ~b;
            
          end
        
        // A OR B'
        s5:
          begin
            $display("Performing A OR B'");
            y <= a | ~b;
            
          end
        
        // A - B
        s6:
          begin
            $display("Performing A - B");
            y<= a - b;
            
          end
        
        // SLT (set less than)
        s7:
          begin
            $display("Performing SLT");
            y <= a < b;
            
          end
        
        default:
          begin
            $display("Default operation");
            y <= a;
            
          end
      endcase  
    end
  
  // Hook up zero output to be true if the output is zero
  assign zero = (y == 32'b0);
  
endmodule
           
