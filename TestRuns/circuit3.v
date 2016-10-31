`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Sun Oct 30 19:29:46 2016
//Assignment: 2
//File: circuit3.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit3(clk, rst, a, b, c, d, e, f, g, h, sa, avg);
	input clk, rst;
	input [7:0] sa;
	input [15:0] a, b, c, d, e, f, g, h;

	output [15:0] avg;

	wire [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;

	ADD #(32) ADD_0({a[15],16'b0,a[14:0]}, {b[15],16'b0,b[14:0]}, l00);
	ADD #(32) ADD_1({c[15],16'b0,c[14:0]}, {d[15],16'b0,d[14:0]}, l01);
	ADD #(32) ADD_2({e[15],16'b0,e[14:0]}, {f[15],16'b0,f[14:0]}, l02);
	ADD #(32) ADD_3({g[15],16'b0,g[14:0]}, {h[15],16'b0,h[14:0]}, l03);
	ADD #(32) ADD_4(l00, l01, l10);
	ADD #(32) ADD_5(l02, l03, l11);
	ADD #(32) ADD_6(l10, l11, l2);
	SSHR #(32) SSHR_7(l2, {sa[7],24'b0,sa[6:0]}, l2div2);
	SSHR #(32) SSHR_8(l2div2, {sa[7],24'b0,sa[6:0]}, l2div4);
	SSHR #(32) SSHR_9(l2div4, {sa[7],24'b0,sa[6:0]}, l2div8);
	REG #(16) REG_10(l2div8, clk, rst, avg);

endmodule
