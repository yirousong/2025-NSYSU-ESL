`timescale 1ns/1ps
`define bits 9

module Datapath ( inportR, inportG, inportB, control, clk, rst_n, outportY, outportU, outportV );
    input [`bits-1:0] inportR, inportG, inportB;
    input [15:0] control;
    input clk, rst_n;
    output [`bits-1:0] outportY, outportU, outportV;
    wire [`bits-1:0] R1, R2, R3, R4, R5, R6, R7, R8;
    wire [`bits-1:0] M1_OUT, M2_OUT, M3_OUT;
    wire [`bits-1:0] Fmul1, Fmul2, Fmul3;
    wire [`bits-1:0] Fadd1, Fadd2, Fadd3;
    wire [26:0] data;

    Register r1( .D(inportR), .reset(rst_n), .clk(clk), .load(control[15:15]), .Q(R1) );
    Register r2( .D(inportG), .reset(rst_n), .clk(clk), .load(control[14:14]), .Q(R2) );
    Register r3( .D(inportB), .reset(rst_n), .clk(clk), .load(control[13:13]), .Q(R3) );
    Register r4( .D(Fmul1), .reset(rst_n), .clk(clk), .load(control[12:12]), .Q(R4) );
    Register r5( .D(Fmul2), .reset(rst_n), .clk(clk), .load(control[11:11]), .Q(R5) );
    Register r6( .D(M1_OUT), .reset(rst_n), .clk(clk), .load(control[10:10]), .Q(R6) );
    Register r7( .D(Fadd1), .reset(rst_n), .clk(clk), .load(control[9:9]), .Q(R7) );
    Register r8( .D(M2_OUT), .reset(rst_n), .clk(clk), .load(control[8:8]), .Q(R8) );
    Register r9( .D(Fadd2), .reset(rst_n), .clk(clk), .load(control[7:7]), .Q(outportY) );
    Register r10( .D(Fadd2), .reset(rst_n), .clk(clk), .load(control[6:6]), .Q(outportU) );
    Register r11( .D(Fadd2), .reset(rst_n), .clk(clk), .load(control[5:5]), .Q(outportV) );

    ROM FU1 ( .clk(clk), .addr(control[4:3]), .data(data) );

    MUX2 M1 ( .A(Fmul3), .B(Fadd3), .S(control[2:2]), .Y(M1_OUT) );
    MUX2 M2 ( .A(Fmul3), .B(Fadd3), .S(control[1:1]), .Y(M2_OUT) );
    MUX2 M3 ( .A(R8), .B(R6), .S(control[0:0]), .Y(M3_OUT) );

    Mul MU1 ( .A(R1), .B(data[26:18]), .Mul(Fmul1) );
    Mul MU2 ( .A(R2), .B(data[17:9]), .Mul(Fmul2) );
    Mul MU3 ( .A(R3), .B(data[8:0]), .Mul(Fmul3) );

    Add AD1 ( .A(R4), .B(R5), .Add(Fadd1) );
    Add AD2 ( .A(M3_OUT), .B(R7), .Add(Fadd2) );
    Add AD3 ( .A(R8), .B(9'b010000000), .Add(Fadd3) );
endmodule
