// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op      (output) - control signal to be sent to the ALU
// writeenable (output) - should a new value be captured by the register file
// rd_src      (output) - should the destination register be rd (0) or rt (1)
// alu_src2    (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except      (output) - set to 1 when the opcode/funct combination is unrecognized
// opcode      (input)  - the opcode field from the instruction
// funct       (input)  - the function field from the instruction
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, opcode, funct);
    output [2:0] alu_op;
    output       writeenable, rd_src, alu_src2, except;
    input  [5:0] opcode, funct;
	wire w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;


	assign w1 = (opcode == 6'b0);
	assign rd_src = ~w1;
	assign alu_src2 = ~w1;
	assign w2 = (opcode == 6'b1000);
	assign w3 = (opcode == 6'b1100);
	assign w4 = (opcode == 6'b1101);
	assign w5 = (opcode == 6'b1110);
	assign w6 = (funct == 6'b100000);
	assign w7 = (funct == 6'b100010);
	assign w8 = (funct == 6'b100100);
	assign w9 = (funct == 6'b100101);
	assign w10 = (funct == 6'b100111);
	assign w11 = (funct == 6'b100110);
	assign alu_op[0] = (w1&(w7|w9|w11))|w4|w5;
	assign alu_op[1] = w2|w5|((w6|w7|w10|w11)&w1);
	assign alu_op[2] = w3|w4|w5|((w8|w9|w10|w11)&w1);
	assign writeenable = (w1 & (w6|w7|w8|w9|w10|w11))|w2|w3|w4|w5;
	assign except = ~writeenable;	


endmodule // mips_decode
