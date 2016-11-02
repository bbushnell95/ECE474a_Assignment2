`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Nov  1 16:09:36 2016
//Assignment: 2
//File: circuit6.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit6(clk, rst, a, b, c, d, e, f, g, h, num, avg);
	input clk, rst;
	input signed [15:0] a, b, c, d, e, f, g, h, num;

	output signed [15:0] avg;

	wire signed [15:0] r1, r2, r3, r4, r5, r6, r7, avgwire;
	wire signed [31:0] t1, t2, t3, t4, t5, t6, t7;

	ADD #(32) ADD_0({{16{a[15]}},a}, {{16{b[15]}},b}, t1);
	REG #(16) REG_1(t1, clk, rst, r1);
	ADD #(32) ADD_2({{16{r1[15]}},r1}, {{16{c[15]}},c}, t2);
	REG #(16) REG_3(t2, clk, rst, r2);
	ADD #(32) ADD_4({{16{r2[15]}},r2}, {{16{d[15]}},d}, t3);
	REG #(16) REG_5(t3, clk, rst, r3);
	ADD #(32) ADD_6({{16{r3[15]}},r3}, {{16{e[15]}},e}, t4);
	REG #(16) REG_7(t4, clk, rst, r4);
	ADD #(32) ADD_8({{16{r4[15]}},r4}, {{16{f[15]}},f}, t5);
	REG #(16) REG_9(t5, clk, rst, r5);
	ADD #(32) ADD_10({{16{r5[15]}},r5}, {{16{g[15]}},g}, t6);
	REG #(16) REG_11(t6, clk, rst, r6);
	ADD #(32) ADD_12({{16{r6[15]}},r6}, {{16{h[15]}},h}, t7);
	REG #(16) REG_13(t7, clk, rst, r7);
	SDIV #(16) SDIV_14(r7, num, avgwire);
	REG #(16) REG_15(avgwire, clk, rst, avg);

endmodule
