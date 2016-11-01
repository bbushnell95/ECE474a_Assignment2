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

module test_tb();
    reg signed [7:0] a_tb;
    reg [15:0] b_tb;
    reg Clk_tb, Rst_tb;
    wire signed [31:0] c_tb;
    
    mixedcircuit2 comp(Clk_tb, Rst_tb, a_tb, b_tb, c_tb);

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
        a_tb <= -7;
        b_tb <= 1;
        
        #10;
    end



endmodule
