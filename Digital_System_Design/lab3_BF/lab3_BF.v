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
// CREATED		"Wed Oct 05 15:21:18 2016"

module lab3_BF(
	n,
	s,
	e,
	w,
	clk,
	reset,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	d,
	win
);


input wire	n;
input wire	s;
input wire	e;
input wire	w;
input wire	clk;
input wire	reset;
output wire	s0;
output wire	s1;
output wire	s2;
output wire	s3;
output wire	s4;
output wire	s5;
output wire	s6;
output wire	d;
output wire	win;

wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;





room	b2v_inst(
	.n(n),
	.s(s),
	.e(e),
	.w(w),
	.v(SYNTHESIZED_WIRE_0),
	.r(reset),
	.clk(clk),
	.s0(s0),
	.s1(s1),
	.s2(s2),
	.s3(s3),
	.s4(s4),
	.s5(s5),
	.s6(s6),
	.d(d),
	.win(win),
	.sw(SYNTHESIZED_WIRE_1));


sword	b2v_inst2(
	.sw(SYNTHESIZED_WIRE_1),
	.r(reset),
	.clk(clk),
	.v(SYNTHESIZED_WIRE_0));


endmodule
