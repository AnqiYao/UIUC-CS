// register: A register which may be reset to an arbirary value
//
// q      (output) - Current value of register
// d      (input)  - Next value of register
// clk    (input)  - Clock (positive edge-sensitive)
// enable (input)  - Load new value? (yes = 1, no = 0)
// reset  (input)  - Asynchronous reset    (reset = 1)
//
module register(q, d, clk, enable, reset);

    parameter
        width = 32,
        reset_value = 0;
 
    output [(width-1):0] q;
    reg    [(width-1):0] q;
    input  [(width-1):0] d;
    input                clk, enable, reset;
 
    always@(reset)
      if (reset == 1'b1)
        q <= reset_value;
 
    always@(posedge clk)
      if ((reset == 1'b0) && (enable == 1'b1))
        q <= d;

endmodule // register

module decoder2 (out, in, enable);
    input     in;
    input     enable;
    output [1:0] out;
 
    and a0(out[0], enable, ~in);
    and a1(out[1], enable, in);
endmodule // decoder2

module decoder4 (out, in, enable);
    input [1:0]    in;
    input     enable;
    output [3:0]   out;
    wire [1:0]    w_enable;

	decoder2 d1(w_enable,in[1],enable);
        decoder2 d2(out[1:0],in[0],w_enable[0]);
	decoder2 d3(out[3:2],in[0],w_enable[1]);
    // implement using decoder2's
    
endmodule // decoder4

module decoder8 (out, in, enable);
    input [2:0]    in;
    input     enable;
    output [7:0]   out;
    wire [1:0]    w_enable;
	
	decoder2 d1(w_enable, in[2], enable);
	decoder4 d2(out[7:4], in[1:0], w_enable[1]);
	decoder4 d3(out[3:0], in[1:0], w_enable[0]);	 
    // implement using decoder2's and decoder4's
 
endmodule // decoder8

module decoder16 (out, in, enable);
    input [3:0]    in;
    input     enable;
    output [15:0]  out;
    wire [1:0]    w_enable;

	decoder2 d1(w_enable, in[3], enable);
	decoder8 d2(out[15:8], in[2:0], w_enable[1]);
	decoder8 d3(out[7:0], in[2:0], w_enable[0]);

	
    // implement using decoder2's and decoder8's
 
endmodule // decoder16

module decoder32 (out, in, enable);
    input [4:0]    in;
    input     enable;
    output [31:0]  out;
    wire [1:0]    w_enable;
 
	decoder2 d1(w_enable, in[4], enable);
	decoder16 d2(out[31:16], in[3:0], w_enable[1]);
	decoder16 d3(out[15:0], in[3:0], w_enable[0]);
    // implement using decoder2's and decoder16's
 
endmodule // decoder32

module mips_regfile (rd1_data, rd2_data, rd1_regnum, rd2_regnum, 
             wr_regnum, wr_data, writeenable, 
             clock, reset);

    output [31:0]  rd1_data, rd2_data;
    input   [4:0]  rd1_regnum, rd2_regnum, wr_regnum;
    input  [31:0]  wr_data;
    input          writeenable, clock, reset;
	wire [31:0] w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28,w29,w30,w31,w32;
	decoder32 d1(w0, wr_regnum, writeenable);
	register r1(w1, wr_data, clock,w0[0],reset);
	register r2(w2, wr_data, clock,w0[1],reset);
	register r3(w3, wr_data, clock,w0[2],reset);
	register r4(w4, wr_data, clock,w0[3],reset);
	register r5(w5, wr_data, clock,w0[4],reset);
	register r6(w6, wr_data, clock,w0[5],reset);
	register r7(w7, wr_data, clock,w0[6],reset);
	register r8(w8, wr_data, clock,w0[7],reset);
	register r9(w9, wr_data, clock,w0[8],reset);
	register r10(w10, wr_data, clock,w0[9],reset);
	register r11(w11, wr_data, clock,w0[10],reset);
	register r12(w12, wr_data, clock,w0[11],reset);
	register r13(w13, wr_data, clock,w0[12],reset);
	register r14(w14, wr_data, clock,w0[13],reset);	
	register r15(w15, wr_data, clock,w0[14],reset);
	register r16(w16, wr_data, clock,w0[15],reset);
	register r17(w17, wr_data, clock,w0[16],reset);
	register r18(w18, wr_data, clock,w0[17],reset);
	register r19(w19, wr_data, clock,w0[18],reset);
	register r20(w20, wr_data, clock,w0[19],reset);
	register r21(w21, wr_data, clock,w0[20],reset);
	register r22(w22, wr_data, clock,w0[21],reset);
	register r23(w23, wr_data, clock,w0[22],reset);
	register r24(w24, wr_data, clock,w0[23],reset);
	register r25(w25, wr_data, clock,w0[24],reset);
	register r26(w26, wr_data, clock,w0[25],reset);
	register r27(w27, wr_data, clock,w0[26],reset);
	register r28(w28, wr_data, clock,w0[27],reset);
	register r29(w29, wr_data, clock,w0[28],reset);
	register r30(w30, wr_data, clock,w0[29],reset);
	register r31(w31, wr_data, clock,w0[30],reset);
	register r32(w32, wr_data, clock,w0[31],reset);
	
	mux32v m1(rd1_data,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28,w29,w30,w31,w32 ,rd1_regnum);
	mux32v m2(rd2_data,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28,w29,w30,w31,w32 ,rd2_regnum);
	
    // build a register file!
    
endmodule // mips_regfile

