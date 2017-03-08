
// Brian Faure
// lab8_BF.sv


module lab8_BF #( parameter N=8, parameter M=3 )
  
  ( input logic [N-1:0] 	input_bits,
   input logic [M-1:0]	shift_pattern,
   output logic [N-1:0]	output_bits
  );
  
  wire [N-1:0] buffer [M-1:1];
  
  assign buffer[2] = shift_pattern[2] ? {input_bits[3:0], input_bits[7:4]} : input_bits;
  assign buffer[1] = shift_pattern[1] ? {buffer[2][1:0], buffer[2][7:2]} : buffer[2];
  assign output_bits = shift_pattern[0] ? {buffer[1][0], buffer[1][7:1]} : buffer[1];
  
endmodule


/*
module lab8_BF #( parameter N=16, parameter M=4 )
  
  ( input logic [N-1:0] 	input_bits,
   input logic [M-1:0]	shift_pattern,
   output logic [N-1:0]	output_bits
  );
  
  wire [N-1:0] buffer [M-1:1];
  
  assign buffer[3] = shift_pattern[3] ? {input_bits[7:0], input_bits[15:8]} : input_bits;
  assign buffer[2] = shift_pattern[2] ? {buffer[3][3:0], buffer[3][15:4]} : buffer[3];
  assign buffer[1] = shift_pattern[1] ? {buffer[2][1:0], buffer[2][15:2]} : buffer[2];
  assign output_bits = shift_pattern[0] ? {buffer[1][0], buffer[1][15:1]} : buffer[1];
  
endmodule

module lab8_BF #(parameter N=64, parameter M=6)
  (
    input logic [N-1:0]		input_bits,
    input logic [M-1:0]		shift_pattern,
    output logic [N-1:0]	output_bits
  );
  
  wire [63:0] buffer [5:1];
  
  assign buffer[5] = shift_pattern[5] 	? {input_bits[31:0], input_bits[63:32]}	: input_bits;
  assign buffer[4] = shift_pattern[4] 	? {buffer[5][15:0], buffer[5][63:16]} 	: buffer[5];
  assign buffer[3] = shift_pattern[3] 	? {buffer[4][7:0], buffer[4][63:8]}		: buffer[4];
  assign buffer[2] = shift_pattern[2] 	? {buffer[3][3:0], buffer[3][63:4]}		: buffer[3];
  assign buffer[1] = shift_pattern[1] 	? {buffer[2][1:0], buffer[2][63:2]}		: buffer[2];
  assign output_bits = shift_pattern[0]	? {buffer[1][0], buffer[1][63:1]}		: buffer[1];
  
endmodule
*/
  