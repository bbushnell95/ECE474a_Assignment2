`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 31 23:03:14 2016
//Assignment: 2
//File: circuit4.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit4(clk, rst, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);
	input clk, rst;
	input signed [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	output signed [31:0] final;

	wire [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;

	ADD #(32) ADD_0({a[7],24'b0,a[6:0]}, {b[7],24'b0,b[6:0]}, t1);
	ADD #(32) ADD_1(t1, {c[7],24'b0,c[6:0]}, t2);
	ADD #(32) ADD_2(t2, {d[7],24'b0,d[6:0]}, t3);
	ADD #(32) ADD_3(t3, {e[7],24'b0,e[6:0]}, t4);
	ADD #(32) ADD_4(t4, {f[7],24'b0,f[6:0]}, t5);
	ADD #(32) ADD_5(t5, {g[7],24'b0,g[6:0]}, t6);
	ADD #(32) ADD_6(t6, {h[7],24'b0,h[6:0]}, t7);
	ADD #(32) ADD_7(t7, {i[7],24'b0,i[6:0]}, t8);
	ADD #(32) ADD_8(t8, {j[7],24'b0,j[6:0]}, t9);
	ADD #(32) ADD_9(t9, {l[7],24'b0,l[6:0]}, t10);
	ADD #(32) ADD_10(t10, {m[7],24'b0,m[6:0]}, t11);
	ADD #(32) ADD_11(t11, {n[7],24'b0,n[6:0]}, t12);
	ADD #(32) ADD_12(t12, {o[7],24'b0,o[6:0]}, t13);
	ADD #(32) ADD_13(t13, {p[7],24'b0,p[6:0]}, t14);
	REG #(32) REG_14(t14, clk, rst, final);

endmodule
