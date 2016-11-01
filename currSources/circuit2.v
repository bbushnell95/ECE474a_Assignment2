`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 31 23:03:07 2016
//Assignment: 2
//File: circuit2.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit2(clk, rst, a, b, c, z, x);
	input clk, rst;
	input signed [31:0] a, b, c;

	output signed [31:0] z, x;

	wire dLTe, dEQe;
	wire [31:0] d, e, f, g, h, zwire, xwire;

	wire na0, na1;
	wire na2, na3;

	ADD #(32) ADD_0(a, b, d);
	ADD #(32) ADD_1(a, c, e);
	SUB #(32) SUB_2(a, b, f);
	COMP #(32) COMP_3(d, e, na0, na1, dEQe);
	COMP #(32) COMP_4(d, e, na2, dLTe, na3);
	MUX2x1 #(32) MUX2x1_5(d, e, dLTe, g);
	MUX2x1 #(32) MUX2x1_6(g, f, dEQe, h);
	SHL #(32) SHL_7(g, {31'b0,dLTe}, xwire);
	SHR #(32) SHR_8(h, {31'b0,dEQe}, zwire);
	REG #(32) REG_9(xwire, clk, rst, x);
	REG #(32) REG_10(zwire, clk, rst, z);

endmodule
