`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/31/2016 10:31:01 PM
// Design Name: 
// Module Name: test_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

//module circuit1(clk, rst, a, b, c, z, x);
module test_tb();
    reg [63:0] a_tb, b_tb, c_tb, d_tb, zero_tb;
    reg Clk_tb, Rst_tb;
    wire [63:0] z_tb;
    
    circuit7 comp(Clk_tb, Rst_tb, a_tb, b_tb, c_tb, d_tb, zero_tb, z_tb);
    
    always begin
        Clk_tb <= 0;
        #10;
        Clk_tb <= 1;
        #10;
    end
    
    initial begin
        Rst_tb <= 1;
        #10 Rst_tb <= 0;
        #10;
        a_tb <= 9;
        b_tb <= 87;
        c_tb <= 78;
        d_tb <= 31;
        zero_tb <= 57;
        
        #10;
    end



endmodule
