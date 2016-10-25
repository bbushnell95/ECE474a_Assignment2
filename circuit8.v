`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Oct 25 13:43:49 2016
//Assignment: 2
//File: circuit8.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////


module circuit8(clk, rst, a, b, c, zero, z);
	input [63:0] a;
	input [63:0] b;
	input [63:0] c;
	input [63:0] zero;

	output [63:0] z;

	wire [63:0] e;
	wire [63:0] f;
	wire [63:0] g;
	wire [63:0] zwire;
	wire gEQz;


	SREG #(64) SREG_0(a, clk, rst, e);
	SREG #(64) SREG_1(c, clk, rst, f);
	SMOD #(64) SMOD_2(a, c, c, g);
	SCOMP #(1) SCOMP_3(g, zero, na0, na1, gEQz);
	SMUX2x1 #(64) SMUX2x1_4(e, f, gEQz, zwire);
	SREG #(64) SREG_5(zwire, clk, rst, z);

endmodule
