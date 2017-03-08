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
// CREATED		"Wed Sep 14 19:40:00 2016"

module lab2_BF(
	SW,
	HEX0
);


input wire	[3:0] SW;
output wire	[6:0] HEX0;

wire	D0;
wire	D0_Negated;
wire	D1;
wire	D1_Negated;
wire	D2;
wire	D2_Negated;
wire	D3;
wire	D3_Negated;
wire	Sa;
wire	Sb;
wire	Sc;
wire	Sd;
wire	Se;
wire	Sf;
wire	Sg;
wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_2;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_4;
wire	SYNTHESIZED_WIRE_5;
wire	SYNTHESIZED_WIRE_6;
wire	SYNTHESIZED_WIRE_7;
wire	SYNTHESIZED_WIRE_8;
wire	SYNTHESIZED_WIRE_9;
wire	SYNTHESIZED_WIRE_10;
wire	SYNTHESIZED_WIRE_11;
wire	SYNTHESIZED_WIRE_12;
wire	SYNTHESIZED_WIRE_13;
wire	SYNTHESIZED_WIRE_14;
wire	SYNTHESIZED_WIRE_15;
wire	SYNTHESIZED_WIRE_16;
wire	SYNTHESIZED_WIRE_17;
wire	SYNTHESIZED_WIRE_18;
wire	SYNTHESIZED_WIRE_19;
wire	SYNTHESIZED_WIRE_20;
wire	SYNTHESIZED_WIRE_21;
wire	SYNTHESIZED_WIRE_22;
wire	SYNTHESIZED_WIRE_23;
wire	SYNTHESIZED_WIRE_24;
wire	SYNTHESIZED_WIRE_25;

assign	SYNTHESIZED_WIRE_23 = 0;



assign	D0_Negated =  ~D0;

assign	D1_Negated =  ~D1;

assign	SYNTHESIZED_WIRE_2 = D3_Negated & D2_Negated & D1;

assign	Sf = SYNTHESIZED_WIRE_0 | SYNTHESIZED_WIRE_1 | SYNTHESIZED_WIRE_2 | SYNTHESIZED_WIRE_3;

assign	SYNTHESIZED_WIRE_4 = D3_Negated & D2 & D1_Negated;

assign	SYNTHESIZED_WIRE_5 = D2_Negated & D1_Negated & D0;

assign	SYNTHESIZED_WIRE_6 = D3_Negated & D0;

assign	Se = SYNTHESIZED_WIRE_4 | SYNTHESIZED_WIRE_5 | SYNTHESIZED_WIRE_6;

assign	SYNTHESIZED_WIRE_7 = D2_Negated & D1_Negated & D0;

assign	SYNTHESIZED_WIRE_10 = D2 & D1 & D0;

assign	SYNTHESIZED_WIRE_8 = D3 & D2_Negated & D1 & D0_Negated;

assign	SYNTHESIZED_WIRE_9 = D3_Negated & D2 & D1_Negated & D0_Negated;

assign	D2_Negated =  ~D2;

assign	Sd = SYNTHESIZED_WIRE_7 | SYNTHESIZED_WIRE_8 | SYNTHESIZED_WIRE_9 | SYNTHESIZED_WIRE_10;

assign	SYNTHESIZED_WIRE_12 = D3_Negated & D2_Negated & D1 & D0_Negated;

assign	SYNTHESIZED_WIRE_11 = D3 & D2 & D1;

assign	SYNTHESIZED_WIRE_13 = D3 & D2 & D0_Negated;

assign	Sc = SYNTHESIZED_WIRE_11 | SYNTHESIZED_WIRE_12 | SYNTHESIZED_WIRE_13;

assign	Sa = SYNTHESIZED_WIRE_14 | SYNTHESIZED_WIRE_15 | SYNTHESIZED_WIRE_16 | SYNTHESIZED_WIRE_17;

assign	SYNTHESIZED_WIRE_18 = D3_Negated & D2 & D1_Negated & D0;

assign	SYNTHESIZED_WIRE_20 = D3 & D2 & D0_Negated;

assign	SYNTHESIZED_WIRE_19 = D3 & D1 & D0;

assign	SYNTHESIZED_WIRE_21 = D3 & D2 & D1;

assign	D3_Negated =  ~D3;

assign	SYNTHESIZED_WIRE_22 = D2 & D1 & D0_Negated;

assign	SYNTHESIZED_WIRE_14 = D3 & D2 & D1_Negated;

assign	SYNTHESIZED_WIRE_17 = D2 & D1_Negated & D0_Negated;

assign	SYNTHESIZED_WIRE_15 = D3 & D2_Negated & D1 & D0;

assign	SYNTHESIZED_WIRE_16 = D3_Negated & D2_Negated & D1_Negated & D0;

assign	Sb = SYNTHESIZED_WIRE_18 | SYNTHESIZED_WIRE_19 | SYNTHESIZED_WIRE_20 | SYNTHESIZED_WIRE_21 | SYNTHESIZED_WIRE_22 | SYNTHESIZED_WIRE_23;


assign	SYNTHESIZED_WIRE_25 = D3_Negated & D2_Negated & D1_Negated;

assign	SYNTHESIZED_WIRE_24 = D3_Negated & D2 & D1 & D0;

assign	Sg = SYNTHESIZED_WIRE_24 | SYNTHESIZED_WIRE_25;

assign	SYNTHESIZED_WIRE_0 = D3 & D2 & D1_Negated;

assign	SYNTHESIZED_WIRE_3 = D3_Negated & D1 & D0;

assign	SYNTHESIZED_WIRE_1 = D3_Negated & D2_Negated & D0;

assign	D3 = SW[3];
assign	HEX0[6] = Sg;
assign	HEX0[5] = Sf;
assign	HEX0[4] = Se;
assign	HEX0[3] = Sd;
assign	HEX0[2] = Sc;
assign	HEX0[1] = Sb;
assign	HEX0[0] = Sa;
assign	D0 = SW[0];
assign	D1 = SW[1];
assign	D2 = SW[2];
assign	D3 = SW[3];

endmodule
