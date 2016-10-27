`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Thu Oct 27 13:11:45 2016
//Assignment: 2
//File: circuit3_output.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit3_output(clk, rst, a, b, c, d, e, f, g, h, sa, avg);
	input clk, rst;
	input [7:0] sa;
	input [15:0] a, b, c, d, e, f, g, h;

	output [15:0] avg;

	wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;

	SADD #(32) SADD_0({a[15],16'b0,a[14:0]}, {b[15],16'b0,b[14:0]}, l00);
	SADD #(32) SADD_1({c[15],16'b0,c[14:0]}, {d[15],16'b0,d[14:0]}, l01);
	SADD #(32) SADD_2({e[15],16'b0,e[14:0]}, {f[15],16'b0,f[14:0]}, l02);
	SADD #(32) SADD_3({g[15],16'b0,g[14:0]}, {h[15],16'b0,h[14:0]}, l03);
	SADD #(32) SADD_4(l00, l01, l10);
	SADD #(32) SADD_5(l02, l03, l11);
	SADD #(32) SADD_6(l10, l11, l2);
	SSHR #(32) SSHR_7(l2, {sa[7],24'b0,sa[6:0]}, l2div2);
	SSHR #(32) SSHR_8(l2div2, {sa[7],24'b0,sa[6:0]}, l2div4);
	SSHR #(32) SSHR_9(l2div4, {sa[7],24'b0,sa[6:0]}, l2div8);
	SREG #(16) SREG_10(l2div8, clk, rst, avg);

endmodule
