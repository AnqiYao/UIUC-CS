// full_machine: execute a series of MIPS instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clock   (input) - the clock signal
// reset   (input) - set to 1 to set all registers to zero, set to 0 for normal execution.

module full_machine(except, clock, reset);
    output      except;
    input       clock, reset;

	wire [31:0] inst, out, addr,data_in,data_out;  
	wire [31:0] PC, imm32, PC_1, rsData, rtData, B, rdData, nextPC, offS, branch_offset, jump, mem_read_in, mem_read_out, zeros, slt_out, ngf, lui_in, bl_in, bl_out, B_in, B_out, addm_out;
	wire [4:0] rsNum, rtNum, rdNum, rdest;  
	wire writeenable, rd_src, alu_src2,except, mem_read, word_we, byte_we, byte_load, lui, slt, addm, zero, negative, overflow;
	wire [2:0] alu_op;
	wire [1:0] control_type;
	wire [7:0] do;



	assign jump[31:28] = PC[31:28];
	assign jump[27:2] = inst[25:0];
	assign jump[1] = 0;
	assign jump[0] = 0;

	assign ngf[31:1] = zeros[31:1];
	assign ngf[0] = negative;
	assign lui_in[31:16] = inst[15:0];
	assign lui_in[15:0] = zeros[15:0];
	assign bl_in[31:8] = zeros[31:8];
	assign bl_in[7:0] = do;
	assign zeros = 32'b0;
	assign addr = out;
	
	
	register #(32) PC_reg(PC,nextPC,clock,1,reset);	
	instruction_memory im(inst[31:0],PC[31:2]);
	regfile rf (rsData, rtData, inst[25:21], inst[20:16], rdest, rdData, writeenable, clock, reset);
	mips_decode mip1(alu_op, writeenable, rd_src, alu_src2, except, control_type, mem_read, word_we, byte_we, byte_load, lui, slt, addm,inst[31:26],inst[5:0], zero);
	data_mem dm(data_out, addr, rtData, word_we, byte_we,clock,reset);


	alu32 #(32) a1 (PC_1, , , ,PC, 32'h4, 3'b010);
	alu32 #(32) a2 (offS, , , ,PC, branch_offset, 3'b010);
	alu32 #(32) a3 (out,overflow,zero,negative, rsData, B_out,alu_op);
	alu32 #(32) a4 (addm_out, , , ,rtData, data_out, 3'b010);

	assign imm32 = {{16{inst[15]}}, inst[15:0]};
	assign branch_offset[31:2] = imm32[29:0];
	assign branch_offset[1] = 0;
	assign branch_offset[0] = 0;
	
	mux2v #(5) m1 (rdest, inst[15:11], inst[20:16], rd_src);
	mux2v #(32) m2 (B_in, rtData,imm32, alu_src2); 
	mux4v #(32) m3 (nextPC, PC_1, offS, jump, rsData, control_type);
	mux2v #(32) m4 (slt_out, out, ngf, slt);
	mux2v #(32) m5 (bl_out, data_out, bl_in, byte_load);
	mux2v #(32) m6 (mem_read_out, slt_out, mem_read_in, mem_read);
	mux2v #(32) m7 (rdData, mem_read_out, lui_in, lui);
	mux2v #(32) m8 (mem_read_in, bl_out, addm_out, addm);
	mux2v #(32) m9 (B_out, B_in, zeros, addm);
	mux4v #(8) m10 (do, data_out[7:0], data_out[15:8], data_out[23:16], data_out[31:24], out[1:0]);
	

endmodule // full_machine
