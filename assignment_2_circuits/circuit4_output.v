`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Thu Oct 27 13:26:41 2016
//Assignment: 2
//File: circuit4_output.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit4_output(clk, rst, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, final);
	input clk, rst;
	input [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	output [31:0] final;

	wire [31:0] t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;

	SADD #(32) SADD_0({a[7],24'b0,a[6:0]}, {b[7],24'b0,b[6:0]}, t1);
	SADD #(32) SADD_1(t1, {c[7],24'b0,c[6:0]}, t2);
	SADD #(32) SADD_2(t2, {d[7],24'b0,d[6:0]}, t3);
	SADD #(32) SADD_3(t3, {e[7],24'b0,e[6:0]}, t4);
	SADD #(32) SADD_4(t4, {f[7],24'b0,f[6:0]}, t5);
	SADD #(32) SADD_5(t5, {g[7],24'b0,g[6:0]}, t6);
	SADD #(32) SADD_6(t6, {h[7],24'b0,h[6:0]}, t7);
	SADD #(32) SADD_7(t7, {i[7],24'b0,i[6:0]}, t8);
	SADD #(32) SADD_8(t8, {j[7],24'b0,j[6:0]}, t9);
	SADD #(32) SADD_9(t9, {l[7],24'b0,l[6:0]}, t10);
	SADD #(32) SADD_10(t10, {m[7],24'b0,m[6:0]}, t11);
	SADD #(32) SADD_11(t11, {n[7],24'b0,n[6:0]}, t12);
	SADD #(32) SADD_12(t12, {o[7],24'b0,o[6:0]}, t13);
	SADD #(32) SADD_13(t13, {p[7],24'b0,p[6:0]}, t14);
	SREG #(32) SREG_14(t14, clk, rst, final);

endmodule
