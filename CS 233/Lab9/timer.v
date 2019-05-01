module timer(TimerInterrupt, TimerAddress, cycle,
             address, data, MemRead, MemWrite, clock, reset);
    output        TimerInterrupt, TimerAddress;
    output [31:0] cycle;
    input  [31:0] address, data;
    input         MemRead, MemWrite, clock, reset;
	wire Acknowledge, TimerRead, TimerWrite, w1, w2, new_en, new_re;
	wire [31:0] data_out_1, data_out_2, data_1;
    // complete the timer circuit here
	
	
	assign w1 = (address == 32'hffff006c);
	assign w2 = (address == 32'hffff001c);


	assign TimerRead = (address == 32'hffff001c) & MemRead;
	assign TimerWrite = (address == 32'hffff001c) & MemWrite;
	assign Acknowledge = (address == 32'hffff006c) & MemWrite;
	
	or o1 (TimerAddress, w1, w2); 

	register #(32,32'hffffffff) r1(data_out_1, data, clock, TimerWrite, reset);
	register r2(data_out_2, data_1, clock, 1, reset);
		
	alu32 a1(data_1, , , `ALU_ADD, data_out_2, 32'b1);
	assign new_en = (data_out_1 == data_out_2);
	assign new_re = (Acknowledge | reset);  
	
	dffe d3(TimerInterrupt, 1'b1, clock, new_en, new_re);
	
	tristate t1 (cycle, data_out_2 ,TimerRead);

    // HINT: make your interrupt cycle register reset to 32'hffffffff
    //       (using the reset_value parameter)
    //       to prevent an interrupt being raised the very first cycle
endmodule