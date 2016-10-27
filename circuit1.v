`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Wed Oct 26 20:01:42 2016
//Assignment: 2
//File: circuit1.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////


module circuit1(clk, rst, a, b, c, z, x);
	input clk, rst;
	input [7:0] a, b, c;

	output [7:0] z;
	output [15:0] x;

	wire [7:0] d, e;
	wire [15:0] f, g, xwire;

	wire na0, na1;

	SADD #(8) SADD_0(a, b, d);
	SADD #(8) SADD_1(a, c, e);
	SCOMP #(8) SCOMP_2(d, e, g, na0, na1);
	SMUX2x1 #(8) SMUX2x1_3(d, e, g, z);
	SMUL #(16) SMUL_4(a, c, f);
	SSUB #(16) SSUB_5(f, d, xwire);
	SREG #(16) SREG_6(xwire, clk, rst, x);

endmodule
