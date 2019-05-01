`define STATUS_REGISTER 5'd12
`define CAUSE_REGISTER  5'd13
`define EPC_REGISTER    5'd14

module cp0(rd_data, EPC, TakenInterrupt,
           regnum, wr_data, next_pc, TimerInterrupt,
           MTC0, ERET, clock, reset);
    output [31:0] rd_data;
    output [29:0] EPC;
    output        TakenInterrupt;
    input   [4:0] regnum;
    input  [31:0] wr_data;
    input  [29:0] next_pc;
    input         TimerInterrupt, MTC0, ERET, clock, reset;
	wire [31:0] cause_register, status_register, de_out, epc_af, user_status;
	wire [29:0] epc_in;
	wire user_en, except_re, epc_en, not_status_register;

	assign cause_register[15] = TimerInterrupt;

	decoder32 d1(de_out, regnum, MTC0);
	assign user_en = de_out[12];
	assign epc_en  = TakenInterrupt | de_out[14];

	mux2v #(30) m1(epc_in, wr_data[31:2], next_pc, TakenInterrupt);
	assign except_re = reset | ERET;
	
	register r1 (user_status, wr_data, clock, user_en, reset);
	register #(30) r2 (EPC, epc_in, clock, epc_en, reset);
	dffe	 df1 (status_register[1], 1, clock, TakenInterrupt, except_re);
	assign epc_af[29:0] = EPC;
	assign epc_af[31:30] = 2'b0;
	assign cause_register[31:16] = 16'b0;
	assign cause_register[14:0] = 15'b0;
	assign status_register[31:16] = 16'b0;
	assign status_register[7:2] = 6'b0;
	assign status_register[15:8] = user_status[15:8];
	assign status_register[0] = user_status[0];

	not n1 (not_status_register, status_register[1]);
	assign TakenInterrupt = (cause_register[15] & status_register[15]) & (status_register[0] & not_status_register);
	assign rd_data = (status_register & {32{(regnum == 12)}}) | (cause_register & {32{(regnum == 13)}}) |(epc_af & {32{(regnum == 14)}});

endmodule
