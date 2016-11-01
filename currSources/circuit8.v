`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Nov  1 15:26:15 2016
//Assignment: 2
//File: circuit8.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit8(clk, rst, a, b, c, zero, z);
	input clk, rst;
	input signed [63:0] a, b, c, zero;

	output signed [63:0] z;

	wire signed gEQz;
	wire signed [63:0] e, f, g, zwire;

	wire na0, na1;

	DEC #(64) DEC_0(a, e);
	INC #(64) INC_1(c, f);
	SMOD #(64) SMOD_2(a, c, g);
	SCOMP #(64) SCOMP_3(g, zero, na0, na1, gEQz);
	MUX2x1 #(64) MUX2x1_4(e, f, gEQz, zwire);
	REG #(64) REG_5(zwire, clk, rst, z);

endmodule
