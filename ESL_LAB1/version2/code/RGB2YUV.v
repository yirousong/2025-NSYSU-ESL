`timescale 1ns/1ps
`define bits 9

module RGB2YUV (start, clk, rst_n, inportR, inportG, inportB, outportY, outportU, outportV);
    input start, clk, rst_n;
    input [`bits-1:0] inportR, inportG, inportB;
    output [`bits-1:0] outportY, outportU, outportV;
    wire [15:0] control;
    
    Controller Controller( .start(start), .rst_n(rst_n), .clk(clk), .control(control) );
    Datapath Datapath( .inportR(inportR), .inportG(inportG), .inportB(inportB), .control(control), .clk(clk),
    .rst_n(rst_n), .outportY(outportY), .outportU(outportU), .outportV(outportV)  );
endmodule
