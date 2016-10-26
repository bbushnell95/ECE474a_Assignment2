`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Wed Oct 26 03:22:58 2016
//Assignment: 2
//File: circuit8.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////


module circuit8(clk, rst, a, b, c, zero, z);
	input clk, rst;
	input [63:0] a, b, c, zero;

	output [63:0] z;

	wire gEQz;
	wire [63:0] e, f, g, zwire;

	wire na0, na1;

	SDEC #(64) SDEC_0(a, e);
	SINC #(64) SINC_1(c, f);
	SMOD #(64) SMOD_2(a, c, g);
	SCOMP #(64) SCOMP_3(g, zero, na0, na1, gEQz);
	SMUX2x1 #(64) SMUX2x1_4(e, f, gEQz, zwire);
	SREG #(64) SREG_5(zwire, clk, rst, z);

endmodule
