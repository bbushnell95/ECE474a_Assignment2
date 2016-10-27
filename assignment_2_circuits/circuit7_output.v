`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Thu Oct 27 13:34:02 2016
//Assignment: 2
//File: circuit7_output.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit7_output(clk, rst, a, b, c, d, zero, z);
	input clk, rst;
	input [63:0] a, b, c, d, zero;

	output [63:0] z;

	wire gEQz;
	wire [63:0] e, f, g, zwire;

	wire na0, na1;

	SDIV #(64) SDIV_0(a, b, e);
	SDIV #(64) SDIV_1(c, d, f);
	SMOD #(64) SMOD_2(a, b, g);
	SCOMP #(64) SCOMP_3(g, zero, na0, na1, gEQz);
	SMUX2x1 #(64) SMUX2x1_4(e, f, gEQz, zwire);
	SREG #(64) SREG_5(zwire, clk, rst, z);

endmodule
