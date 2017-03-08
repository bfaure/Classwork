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
// CREATED		"Wed Oct 05 15:21:00 2016"

module room(
	n,
	s,
	e,
	w,
	clk,
	v,
	r,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	win,
	d,
	sw
);


input wire	n;
input wire	s;
input wire	e;
input wire	w;
input wire	clk;
input wire	v;
input wire	r;
output wire	s0;
output wire	s1;
output wire	s2;
output wire	s3;
output wire	s4;
output wire	s5;
output wire	s6;
output wire	win;
output wire	d;
output wire	sw;

wire	SYNTHESIZED_WIRE_41;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_42;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_43;
wire	SYNTHESIZED_WIRE_5;
wire	SYNTHESIZED_WIRE_7;
wire	SYNTHESIZED_WIRE_9;
wire	SYNTHESIZED_WIRE_11;
wire	SYNTHESIZED_WIRE_13;
reg	SYNTHESIZED_WIRE_44;
wire	SYNTHESIZED_WIRE_15;
wire	SYNTHESIZED_WIRE_16;
wire	SYNTHESIZED_WIRE_17;
reg	DFF_inst;
reg	SYNTHESIZED_WIRE_45;
wire	SYNTHESIZED_WIRE_18;
wire	SYNTHESIZED_WIRE_19;
reg	SYNTHESIZED_WIRE_46;
reg	SYNTHESIZED_WIRE_47;
wire	SYNTHESIZED_WIRE_20;
wire	SYNTHESIZED_WIRE_22;
wire	SYNTHESIZED_WIRE_24;
reg	SYNTHESIZED_WIRE_48;
wire	SYNTHESIZED_WIRE_25;
reg	SYNTHESIZED_WIRE_49;
wire	SYNTHESIZED_WIRE_27;
wire	SYNTHESIZED_WIRE_30;
wire	SYNTHESIZED_WIRE_33;
wire	SYNTHESIZED_WIRE_36;
wire	SYNTHESIZED_WIRE_39;

assign	s0 = DFF_inst;
assign	s1 = SYNTHESIZED_WIRE_44;
assign	s2 = SYNTHESIZED_WIRE_45;
assign	s3 = SYNTHESIZED_WIRE_46;
assign	s4 = SYNTHESIZED_WIRE_47;
assign	s5 = SYNTHESIZED_WIRE_48;
assign	s6 = SYNTHESIZED_WIRE_49;
assign	win = SYNTHESIZED_WIRE_48;
assign	d = SYNTHESIZED_WIRE_49;
assign	sw = SYNTHESIZED_WIRE_46;
assign	SYNTHESIZED_WIRE_41 = 1;
assign	SYNTHESIZED_WIRE_42 = 1;




always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	DFF_inst <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	DFF_inst <= 1;
	end
else
	begin
	DFF_inst <= SYNTHESIZED_WIRE_1;
	end
end

assign	SYNTHESIZED_WIRE_43 =  ~r;

assign	SYNTHESIZED_WIRE_22 = SYNTHESIZED_WIRE_3 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_27 = SYNTHESIZED_WIRE_5 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_30 = SYNTHESIZED_WIRE_7 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_33 = SYNTHESIZED_WIRE_9 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_36 = SYNTHESIZED_WIRE_11 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_39 = SYNTHESIZED_WIRE_13 & SYNTHESIZED_WIRE_43;

assign	SYNTHESIZED_WIRE_15 = SYNTHESIZED_WIRE_44 & w;

assign	SYNTHESIZED_WIRE_1 = r | SYNTHESIZED_WIRE_15;

assign	SYNTHESIZED_WIRE_3 = SYNTHESIZED_WIRE_16 | SYNTHESIZED_WIRE_17;


assign	SYNTHESIZED_WIRE_16 = e & DFF_inst;

assign	SYNTHESIZED_WIRE_17 = n & SYNTHESIZED_WIRE_45;

assign	SYNTHESIZED_WIRE_5 = SYNTHESIZED_WIRE_18 | SYNTHESIZED_WIRE_19;

assign	SYNTHESIZED_WIRE_18 = s & SYNTHESIZED_WIRE_44;

assign	SYNTHESIZED_WIRE_19 = SYNTHESIZED_WIRE_46 & e;

assign	SYNTHESIZED_WIRE_7 = SYNTHESIZED_WIRE_45 & w;

assign	SYNTHESIZED_WIRE_9 = e & SYNTHESIZED_WIRE_45;

assign	SYNTHESIZED_WIRE_24 = SYNTHESIZED_WIRE_47 & v;

assign	SYNTHESIZED_WIRE_20 =  ~v;


assign	SYNTHESIZED_WIRE_25 = SYNTHESIZED_WIRE_20 & SYNTHESIZED_WIRE_47;


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_44 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_44 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_44 <= SYNTHESIZED_WIRE_22;
	end
end

assign	SYNTHESIZED_WIRE_11 = SYNTHESIZED_WIRE_24 | SYNTHESIZED_WIRE_48;

assign	SYNTHESIZED_WIRE_13 = SYNTHESIZED_WIRE_25 | SYNTHESIZED_WIRE_49;


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_45 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_45 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_45 <= SYNTHESIZED_WIRE_27;
	end
end


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_46 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_46 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_46 <= SYNTHESIZED_WIRE_30;
	end
end


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_47 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_47 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_47 <= SYNTHESIZED_WIRE_33;
	end
end


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_48 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_48 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_48 <= SYNTHESIZED_WIRE_36;
	end
end


always@(posedge clk or negedge SYNTHESIZED_WIRE_41 or negedge SYNTHESIZED_WIRE_42)
begin
if (!SYNTHESIZED_WIRE_41)
	begin
	SYNTHESIZED_WIRE_49 <= 0;
	end
else
if (!SYNTHESIZED_WIRE_42)
	begin
	SYNTHESIZED_WIRE_49 <= 1;
	end
else
	begin
	SYNTHESIZED_WIRE_49 <= SYNTHESIZED_WIRE_39;
	end
end


endmodule
