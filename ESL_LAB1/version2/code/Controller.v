`timescale 1ns/1ps
`define bits 9
`define S0 3'b000
`define S1 3'b001
`define S2 3'b010
`define S3 3'b011
`define S4 3'b100
`define S5 3'b101

module Controller ( start, rst_n, clk, control);
    input start, rst_n, clk;
    output reg[15:0] control;
    reg [2:0] Current_State, Next_State;
	//reg [15:0] pipe1,pipe2,pipe3;
	//reg [15:0] control;

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) Current_State <= `S0;
        else Current_State <= Next_State;
    end
    
    always @(Current_State or start) begin
		case (Current_State)
		`S0:
		begin
			control = 16'b1_1_1_0_0_0_0_0_0_0_0_00_0_0_0;
			if(~start) Next_State = `S0;
			else Next_State = `S1;
		end
		`S1:
		begin
			control = 16'b0_0_0_1_1_1_0_0_0_0_0_01_0_0_0;
			Next_State = `S2;
		end
		`S2:
		begin
			control = 16'b0_0_0_1_1_0_1_1_0_0_0_10_0_0_0;
			Next_State = `S3;
		end
		`S3:
		begin
			control = 16'b0_0_0_1_1_1_1_1_1_0_0_11_1_0_1;
			Next_State = `S4;
		end
		`S4:
		begin
			control = 16'b0_0_0_0_0_0_1_1_0_1_0_00_0_1_1;
			Next_State = `S5;
		end
		`S5:
		begin
			control = 16'b0_0_0_0_0_0_0_0_0_0_1_00_0_0_0;
			Next_State = `S0;
		end
		default:
		begin
			control = 16'b0_0_0_0_0_0_0_0_0_0_1_00_0_0_0;
			Next_State = `S0;
		end
		endcase
    end
	/*
	always @(posedge clk) begin
		if(~rst_n) begin
			pipe1 <= 16'd0;
			pipe2 <= 16'd0;
			pipe3 <= 16'd0;
		end else begin
			pipe1 <= control;
			pipe2 <= pipe1;
			pipe3 <= pipe2;
		end
	end
	
	assign control = control | pipe3;
	*/
endmodule