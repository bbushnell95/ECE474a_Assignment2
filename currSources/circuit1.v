`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Nov  1 14:32:07 2016
//Assignment: 2
//File: circuit1.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit1(clk, rst, a, b, c, z, x);
	input clk, rst;
	input signed [7:0] a, b, c;

	output signed [7:0] z;
	output signed [15:0] x;

	wire signed [7:0] d, e;
	wire signed [15:0] f, g, xwire;

	wire na0, na1;

	ADD #(8) ADD_0(a, b, d);
	ADD #(8) ADD_1(a, c, e);
	SCOMP #(8) SCOMP_2(d, e, g[0], na0, na1);
	MUX2x1 #(8) MUX2x1_3(d, e, g[0], z);
	MUL #(16) MUL_4({{8{a[7]}},a}, {{8{c[7]}},c}, f);
	SUB #(16) SUB_5(f, {{8{d[7]}},d}, xwire);
	REG #(16) REG_6(xwire, clk, rst, x);

endmodule
