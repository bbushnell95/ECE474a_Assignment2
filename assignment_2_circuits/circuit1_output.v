`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Oct 25 13:09:41 2016
//Assignment: 2
//File: circuit1_output.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////


module circuit1_output(clk, rst, a, b, c, z, x);
	input [7:0] a;
	input [7:0] b;
	input [7:0] c;

	output [7:0] z;
	output [15:0] x;

	wire [7:0] d;
	wire [7:0] e;
	wire [15:0] f;
	wire [15:0] g;
	wire [15:0] xwire;

	wire na0, na1;

	SADD #(8) SADD_0(a, b, d);
	SADD #(8) SADD_1(a, c, e);
	SCOMP #(16) SCOMP_2(d, e, g, na0, na1);
	SMUX2x1 #(8) SMUX2x1_3(d, e, g, z);
	SMUL #(8) SMUL_4(a, c, z);
	SSUB #(8) SSUB_5(f, d, d, z);
	SREG #(16) SREG_6(xwire, clk, rst, x);

endmodule
