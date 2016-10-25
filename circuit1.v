`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 24 22:31:52 2016
//Assignment: 2
//File: circuit1.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////


module circuit1(clk, rst, a, b, c, z, x);
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

	wire na0 na1;

	SADD #(TODO) SADD_0(a, b, d);
	SADD #(TODO) SADD_1(a, c, e);
	SCOMP_gt #(TODO) SCOMP_gt_2(d, e, g);
	MUX2x1 #(TODO) MUX2x1_3(g, d, e, z);
	SMUL #(TODO) SMUL_4(a, c, z);
	SUB #(TODO) SUB_5(f, d, d, z);
	SREG #(TODO) SREG_6(xwire, x);

endmodule
