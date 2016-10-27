`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Thu Oct 27 14:04:57 2016
//Assignment: 2
//File: circuit2.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit2(clk, rst, a, b, c, z, x);
	input clk, rst;
	input [31:0] a, b, c;

	output [31:0] z, x;

	wire dLTe, dEQe;
	wire [31:0] d, e, f, g, h, zwire, xwire;

	wire na0, na1;
	wire na2, na3;

	SADD #(32) SADD_0(a, b, d);
	SADD #(32) SADD_1(a, c, e);
	SSUB #(32) SSUB_2(a, b, f);
	SCOMP #(32) SCOMP_3(d, e, na0, na1, dEQe);
	SCOMP #(32) SCOMP_4(d, e, na2, dLTe, na3);
	SMUX2x1 #(32) SMUX2x1_5(d, e, dLTe, g);
	SMUX2x1 #(32) SMUX2x1_6(g, f, dEQe, h);
	SSHL #(32) SSHL_7(g, {31'b0,dLTe[0]}, xwire);
	SSHR #(32) SSHR_8(h, {31'b0,dEQe[0]}, zwire);
	SREG #(32) SREG_9(xwire, clk, rst, x);
	SREG #(32) SREG_10(zwire, clk, rst, z);

endmodule
