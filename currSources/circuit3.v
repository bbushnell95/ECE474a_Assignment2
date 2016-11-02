`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Nov  1 16:09:10 2016
//Assignment: 2
//File: circuit3.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit3(clk, rst, a, b, c, d, e, f, g, h, sa, avg);
	input clk, rst;
	input signed [7:0] sa;
	input signed [15:0] a, b, c, d, e, f, g, h;

	output signed [15:0] avg;

	wire signed [31:0] l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;

	ADD #(32) ADD_0({{16{a[15]}},a}, {{16{b[15]}},b}, l00);
	ADD #(32) ADD_1({{16{c[15]}},c}, {{16{d[15]}},d}, l01);
	ADD #(32) ADD_2({{16{e[15]}},e}, {{16{f[15]}},f}, l02);
	ADD #(32) ADD_3({{16{g[15]}},g}, {{16{h[15]}},h}, l03);
	ADD #(32) ADD_4(l00, l01, l10);
	ADD #(32) ADD_5(l02, l03, l11);
	ADD #(32) ADD_6(l10, l11, l2);
	SSHR #(32) SSHR_7(l2, {{24{sa[7]}},sa}, l2div2);
	SSHR #(32) SSHR_8(l2div2, {{24{sa[7]}},sa}, l2div4);
	SSHR #(32) SSHR_9(l2div4, {{24{sa[7]}},sa}, l2div8);
	REG #(16) REG_10(l2div8, clk, rst, avg);

endmodule
