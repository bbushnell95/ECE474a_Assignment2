`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 31 23:03:03 2016
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

	wire [7:0] d, e;
	wire [15:0] f, g, xwire;

	wire na0, na1;

	ADD #(8) ADD_0(a, b, d);
	ADD #(8) ADD_1(a, c, e);
	COMP #(8) COMP_2(d, e, g[0], na0, na1);
	MUX2x1 #(8) MUX2x1_3(d, e, g[0], z);
	MUL #(16) MUL_4({a[7],8'b0,a[6:0]}, {c[7],8'b0,c[6:0]}, f);
	SUB #(16) SUB_5(f, {8'b0,d}, xwire);
	REG #(16) REG_6(xwire, clk, rst, x);

endmodule
