// Copyright (C) 1991-2016 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, the Altera Quartus Prime License Agreement,
// the Altera MegaCore Function License Agreement, or other 
// applicable license agreement, including, without limitation, 
// that your use is for the sole purpose of programming logic 
// devices manufactured by Altera and sold by Altera or its 
// authorized distributors.  Please refer to the applicable 
// agreement for further details.

// PROGRAM		"Quartus Prime"
// VERSION		"Version 16.0.0 Build 211 04/27/2016 SJ Lite Edition"
// CREATED		"Wed Oct 05 14:46:11 2016"

module sword(
	clk,
	r,
	sw,
	v
);


input wire	clk;
input wire	r;
input wire	sw;
output wire	v;

wire	SYNTHESIZED_WIRE_11;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_12;
wire	SYNTHESIZED_WIRE_4;
wire	SYNTHESIZED_WIRE_6;
wire	SYNTHESIZED_WIRE_7;
reg	DFF_inst1;
reg	SYNTHESIZED_WIRE_13;
wire	SYNTHESIZED_WIRE_8;
wire	SYNTHESIZED_WIRE_9;
wire	SYNTHESIZED_WIRE_10;

assign	v = DFF_inst1;
assign	SYNTHESIZED_WIRE_11 = 1;
assign	SYNTHESIZED_WIRE_12 = 1;




always@(posedge clk or negedge SYNTHESIZED_WIRE_11 or negedge SYNTHESIZED_WIRE_12)
begin
if (!SYNTHESIZED_WIRE_11)
	begin
	SYNTHESIZED_WIRE_13 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_12)
	begin
	SYNTHESIZED_WIRE_13 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_13 <= SYNTHESIZED_WIRE_1;
	end
end


always@(posedge clk or negedge SYNTHESIZED_WIRE_11 or negedge SYNTHESIZED_WIRE_12)
begin
if (!SYNTHESIZED_WIRE_11)
	begin
	DFF_inst1 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_12)
	begin
	DFF_inst1 <= 1;
	end
else
	begin
	DFF_inst1 <= SYNTHESIZED_WIRE_4;
	end
end

assign	SYNTHESIZED_WIRE_1 = r | SYNTHESIZED_WIRE_6;


assign	SYNTHESIZED_WIRE_9 = SYNTHESIZED_WIRE_7 | DFF_inst1;

assign	SYNTHESIZED_WIRE_6 = SYNTHESIZED_WIRE_13 & SYNTHESIZED_WIRE_8;

assign	SYNTHESIZED_WIRE_8 =  ~sw;


assign	SYNTHESIZED_WIRE_4 = SYNTHESIZED_WIRE_9 & SYNTHESIZED_WIRE_10;

assign	SYNTHESIZED_WIRE_10 =  ~r;

assign	SYNTHESIZED_WIRE_7 = sw & SYNTHESIZED_WIRE_13;


endmodule
