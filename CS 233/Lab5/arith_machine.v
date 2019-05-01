// arith_machine: execute a series of arithmetic instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clock  (input)  - the clock signal
// reset  (input)  - set to 1 to set all registers to zero, set to 0 for normal execution.

module arith_machine(except, clock, reset);
    output      except;
    input       clock, reset;

 	
 	wire [31:0] inst;  
	wire [31:0] PC;  
	wire [31:0] PC_1, imm32;
	wire [4:0] rsNum, rtNum, rdNum, rdest;
	wire [31:0] rsData, rtData, B, rdData;
	wire writtenable, rd_src, alu_src2;
	wire  [2:0] alu_op;





    register #(32) PC_reg(PC, PC_1, clock, 1, reset);
    alu32 a1(PC_1, , , ,PC, 32'h4, 3'b010);

    instruction_memory im(inst, PC[31:2]);

    mux2v #(5) m1(rdest,inst[15:11],inst[20:16],rd_src);

    regfile rf ( rsData, rtData, inst[25:21], inst[20:16], rdest, rdData, writtenable, clock, reset);

    mips_decode mip1(alu_op, writtenable, rd_src, alu_src2, except, inst[31:26], inst[5:0]);

    assign imm32 = {{16{inst[15]}}, inst[15:0]};

    mux2v m2(B,rtData,imm32,alu_src2);

    alu32 a2(rdData, , , ,rsData, B, alu_op);

endmodule // arith_machine
