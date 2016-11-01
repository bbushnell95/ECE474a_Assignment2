`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Tue Nov  1 15:25:31 2016
//Assignment: 2
//File: circuit4.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit4(clk, rst, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);
	input clk, rst;
	input signed [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	output signed [31:0] final;

	wire signed [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;

	ADD #(32) ADD_0({{24{a[7]}},a}, {{24{b[7]}},b}, t1);
	ADD #(32) ADD_1(t1, {{24{c[7]}},c}, t2);
	ADD #(32) ADD_2(t2, {{24{d[7]}},d}, t3);
	ADD #(32) ADD_3(t3, {{24{e[7]}},e}, t4);
	ADD #(32) ADD_4(t4, {{24{f[7]}},f}, t5);
	ADD #(32) ADD_5(t5, {{24{g[7]}},g}, t6);
	ADD #(32) ADD_6(t6, {{24{h[7]}},h}, t7);
	ADD #(32) ADD_7(t7, {{24{i[7]}},i}, t8);
	ADD #(32) ADD_8(t8, {{24{j[7]}},j}, t9);
	ADD #(32) ADD_9(t9, {{24{l[7]}},l}, t10);
	ADD #(32) ADD_10(t10, {{24{m[7]}},m}, t11);
	ADD #(32) ADD_11(t11, {{24{n[7]}},n}, t12);
	ADD #(32) ADD_12(t12, {{24{o[7]}},o}, t13);
	ADD #(32) ADD_13(t13, {{24{p[7]}},p}, t14);
	REG #(32) REG_14(t14, clk, rst, final);

endmodule
