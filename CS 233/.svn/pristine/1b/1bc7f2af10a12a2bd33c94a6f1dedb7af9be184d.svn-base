module decoder_test;
    reg [5:0] opcode, funct;

    initial begin
        $dumpfile("decoder.vcd");
        $dumpvars(0, decoder_test);

             opcode = `OP_OTHER0; funct = `OP0_ADD; // try addition
        # 10 opcode = `OP_OTHER0; funct = `OP0_SUB; // try subtraction
	# 10 opcode = `OP_OTHER0; funct = `OP0_AND;
	# 10 opcode = `OP_OTHER0; funct = `OP0_OR;
	# 10 opcode = `OP_OTHER0; funct = `OP0_NOR; //line 5
	# 10 opcode = `OP_OTHER0; funct = `OP0_XOR; //line 6
	# 10 opcode = `OP_ADDI; funct = `OP0_SLL;
	# 10 opcode = `OP_ANDI; funct = `OP0_SLL;
	# 10 opcode = `OP_ORI; funct = `OP0_SLL;
	# 10 opcode = `OP_XORI; funct = `OP0_SLL;
	# 10 opcode = `OP_OTHER0; funct = `OP0_MTLO;
	# 10 opcode = `OP_ORI; funct = `OP0_XOR;
	# 10 opcode = `OP_OTHER0; funct = `OP0_SLL;
        // add more tests here!

        # 10 $finish;
    end

    // use gtkwave to test correctness
    wire [2:0] alu_op;
    wire       writeenable, rd_src, alu_src2, except;
    mips_decode decoder(alu_op, writeenable, rd_src, alu_src2, except,
                        opcode, funct);
	
	    initial
        $monitor("At time %2t, opcode_in = %d funct_in = %d writtenable = %d rd_src = %d alu_src2 =%d except =%d alu_op =%d",
                 $time, opcode, funct, writeenable, rd_src, alu_src2, except, alu_op);

endmodule // decoder_test
