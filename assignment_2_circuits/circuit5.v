`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 31 18:31:47 2016
//Assignment: 2
//File: circuit5.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit5(clk, rst, a, b, c, z, x);
	input clk, rst;
	input [63:0] a, b, c;

	output [31:0] z, x;

	wire dLTe, dEQe, dEQe;
	wire [63:0] d, e, f, g, h, h, xrin, zrin, greg, hreg;

	wire na0, na1;
	wire na2, na3;

	ADD #(64) ADD_0(a, b, d);
	ADD #(64) ADD_1(a, c, e);
	SUB #(64) SUB_2(a, b, f);
	SCOMP #(64) SCOMP_3(d, e, na0, na1, dEQe);
	SCOMP #(64) SCOMP_4(d, e, na2, dLTe, na3);
	MUX2x1 #(64) MUX2x1_5(d, e, dLTe, g);
	MUX2x1 #(64) MUX2x1_6(g, f, dEQe, h);
	REG #(64) REG_7(g, clk, rst, greg);
	REG #(64) REG_8(h, clk, rst, hreg);
	SHL #(64) SHL_9(hreg, {63'b0,dLTe[0]}, xrin);
	SSHR #(64) SSHR_10(greg, {63'b0,dEQe[0]}, zrin);
	REG #(32) REG_11(xrin, clk, rst, x);
	REG #(32) REG_12(zrin, clk, rst, z);

endmodule
