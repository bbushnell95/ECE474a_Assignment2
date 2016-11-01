`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
//Students: Brett Bushnell (Undergrad), Matt Dzurick (Grad)
//Date Created: Mon Oct 31 19:10:43 2016
//Assignment: 2
//File: circuit6.v
//Description: A netlist behavior circuit implementation
//
//////////////////////////////////////////////////////////////////////////////////

module circuit6(clk, rst, a, b, c, d, e, f, g, h, num, avg);
	input clk, rst;
	input [15:0] a, b, c, d, e, f, g, h, num;

	output [15:0] avg;

	wire [15:0] r1, r2, r3, r4, r5, r6, r7, r7, avgwire;
	wire [31:0] t1, t2, t3, t4, t5, t6, t7;

	ADD #(32) ADD_0({a[15],16'b0,a[14:0]}, {b[15],16'b0,b[14:0]}, t1);
	REG #(16) REG_1(t1, clk, rst, r1);
	ADD #(32) ADD_2({r1[15],16'b0,r1[14:0]}, {c[15],16'b0,c[14:0]}, t2);
	REG #(16) REG_3(t2, clk, rst, r2);
	ADD #(32) ADD_4({r2[15],16'b0,r2[14:0]}, {d[15],16'b0,d[14:0]}, t3);
	REG #(16) REG_5(t3, clk, rst, r3);
	ADD #(32) ADD_6({r3[15],16'b0,r3[14:0]}, {e[15],16'b0,e[14:0]}, t4);
	REG #(16) REG_7(t4, clk, rst, r4);
	ADD #(32) ADD_8({r4[15],16'b0,r4[14:0]}, {f[15],16'b0,f[14:0]}, t5);
	REG #(16) REG_9(t5, clk, rst, r5);
	ADD #(32) ADD_10({r5[15],16'b0,r5[14:0]}, {g[15],16'b0,g[14:0]}, t6);
	REG #(16) REG_11(t6, clk, rst, r6);
	ADD #(32) ADD_12({r6[15],16'b0,r6[14:0]}, {h[15],16'b0,h[14:0]}, t7);
	REG #(16) REG_13(t7, clk, rst, r7);
	SDIV #(16) SDIV_14(r7, num, avgwire);
	REG #(16) REG_15(avgwire, clk, rst, avg);

endmodule
