module pipelined_machine(clk, reset);
    input        clk, reset;

    wire [31:0]  PC;
    wire [31:2]  next_PC, PC_plus4, old_PC_plus4, PC_target;
    wire [31:0]  inst, old_inst;

    wire [31:0]  imm = {{ 16{inst[15]} }, inst[15:0] };  // sign-extended immediate
    wire [4:0]   rs = inst[25:21];
    wire [4:0]   rt = inst[20:16];
    wire [4:0]   rd = inst[15:11];
    wire [5:0]   opcode = inst[31:26];
    wire [5:0]   funct = inst[5:0];

    wire [4:0]   wr_regnum, old_wr_regnum;
    wire [2:0]   ALUOp, old_ALUOp;

    wire         RegWrite, old_RegWrite, BEQ, old_BEQ, ALUSrc, old_ALUSrc, MemRead, old_MemRead, MemWrite, old_MemWrite, MemToReg, old_MemToReg, RegDst, old_RegDst;
    wire         PCSrc, zero;
    wire [31:0]  rd1_data, old_rd1_data, rd2_data, old_rd2_data, old_old_rd2_data, B_data, alu_out_data, old_alu_out_data, load_data, wr_data;


    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(30, 30'h100000) PC_reg(PC[31:2], next_PC[31:2], clk, /* enable */not_stall, reset);

    assign PC[1:0] = 2'b0;  // bottom bits hard coded to 00
    adder30 next_PC_adder(old_PC_plus4, PC[31:2], 30'h1);
    adder30 target_PC_adder(PC_target, PC_plus4, imm[29:0]);
    mux2v #(30) branch_mux(next_PC, old_PC_plus4, PC_target, PCSrc);
    assign PCSrc = BEQ & zero;

    // DO NOT comment out or rename this module
    // or the test bench will break
    instruction_memory imem(old_inst, PC[31:2]);

    mips_decode decode(ALUOp, old_RegWrite, BEQ, ALUSrc, old_MemRead, old_MemWrite, old_MemToReg, RegDst,
                      opcode, funct);

    // DO NOT comment out or rename this module
    // or the test bench will break
    regfile rf (old_rd1_data, old_old_rd2_data,
               rs, rt, wr_regnum, wr_data,
               RegWrite, clk, reset);

    mux2v #(32) imm_mux(B_data, old_rd2_data, imm, ALUSrc);
    alu32 alu(old_alu_out_data, zero, ALUOp, rd1_data, B_data);

    // DO NOT comment out or rename this module
    // or the test bench will break
    data_mem data_memory(load_data, alu_out_data, rd2_data, MemRead, MemWrite, clk, reset);

    mux2v #(32) wb_mux(wr_data, alu_out_data, load_data, MemToReg);
    mux2v #(5) rd_mux(old_wr_regnum, rt, rd, RegDst);

//my code begins

	    register #(32, 32'd0) Register_1(inst, old_inst, clk, /*	 enable */not_stall, flush);
	    register #(30, 32'd0) Register_2(PC_plus4, old_PC_plus4, clk, /*	 enable */not_stall, flush);
	    register #(32, 32'd0) Register_3(alu_out_data, old_alu_out_data, clk, /*	 enable */1'b1, reset);
	    register #(5, 32'd0) Register_4(wr_regnum, old_wr_regnum, clk, /*	 enable */1'b1, reset);
	    register #(32, 32'd0) Register_5(rd2_data, old_rd2_data, clk, /*	 enable */1'b1, reset);
//	    register #(3, 32'd0) Register_6(ALUOp, old_ALUOp, clk, /*	 enable */1'b1, reset);
	    register #(1, 32'd0) Register_7(RegWrite, old_RegWrite, clk, /*	 enable */1'b1, reset);
//	    register #(1, 32'd0) Register_8(BEQ, old_BEQ, clk, /*	 enable */1'b1, reset);	
//	    register #(1, 32'd0) Register_9(ALUSrc, old_ALUSrc, clk, /*	 enable */1'b1, reset);
	    register #(1, 32'd0) Register_10(MemRead, old_MemRead, clk, /*	 enable */(1'b1 & not_stall), reset);
	    register #(1, 32'd0) Register_11(MemWrite, old_MemWrite, clk, /*	 enable */1'b1 , reset);
	    register #(1, 32'd0) Register_12(MemToReg, old_MemToReg, clk, /*	 enable */(1'b1 & not_stall), reset);
//	    register #(1, 32'd0) Register_13(RegDst, old_RegDst, clk, /*	 enable */1'b1, reset);

	    mux2v #(32) Fm1(rd1_data, old_rd1_data, alu_out_data, forwardA);
	    mux2v #(32)	Fm2(old_rd2_data, old_old_rd2_data, alu_out_data, forwardB);

	    wire forwardA, forwardB;
	    assign forwardA = (rs == wr_regnum) & RegWrite & (rs != 0); 
	    assign forwardB = (rt == wr_regnum) & RegWrite & (rs != 0);

	    wire stall, not_stall;
	    assign stall = ((rs == wr_regnum) & MemRead & ( wr_regnum!= 0 )) | ((rt == wr_regnum) & MemRead & ( wr_regnum != 0));
	    not no1(not_stall,stall);

	    wire flush;
	    assign flush = PCSrc | reset;


endmodule // pipelined_machine