module gcd_control(done, x_sel, y_sel, x_en, y_en, output_en, go, x_lt_y, x_ne_y, clock, reset);
	output	x_sel, y_sel, x_en, y_en, output_en, done;
	input	go, x_lt_y, x_ne_y;
	input	clock, reset;

	// IMPLEMENT YOUR STATE MACHINE HERE
	wire sG_next, sG, sX_next, sX, sY_next, sY, sT_next, sT, sWait_next, sWait, sWait1_next, sWait1, sTX, sTY, sT_nextX, sT_nextY, done_next;

	assign sWait_next = (~go|reset|(sTX & ~go)|(sTY & ~go) & ~reset);
	assign sWait1_next = ((sWait & go) & ~reset)|~go;
	assign sG_next = ((go & sWait1 )|(sG & ~x_lt_y & x_ne_y)) & ~reset;
	assign sT_nextX = ((sG & ~x_lt_y & x_ne_y)|(sTY & ~x_lt_y & x_ne_y)|(sTX & ~x_lt_y & x_ne_y)) & ~reset;
	assign sT_nextY = ((sG & x_lt_y & x_ne_y)|(sTX & x_lt_y & x_ne_y)|(sTY & x_lt_y & x_ne_y)) & ~reset;
	assign sX_next = ((sTX & ~sTY & ~sT)| (sTY & x_lt_y & x_ne_y)) & ~reset;
	assign sY_next = ((sTY & ~sTX & ~sT)| (sTX & ~x_lt_y & x_ne_y)) & ~reset;
	assign sT_next = ((sG & ~x_ne_y)|(sTX & ~x_ne_y)|(sTY & ~x_ne_y)) & ~reset;

	dffe d0(sG, sG_next, clock, 1'b1, reset);
	dffe d1(sX, sX_next, clock, 1'b1, reset);
	dffe d2(sY, sY_next, clock, 1'b1, reset);
	dffe d6(sTX, sT_nextX,  clock, 1'b1, reset);
	dffe d7(sTY, sT_nextY,  clock, 1'b1, reset);
	dffe d3(sT, sT_next, clock, 1'b1, reset);
	dffe d4(sWait, sWait_next, clock, 1'b1, reset);
	dffe d5(sWait1, sWait1_next, clock, 1'b1, reset);
	dffe d8(done_next, done, clock, 1'b1, reset);

	assign x_sel = sTX;
	assign y_sel = sTY;
	assign x_en = (x_sel & ~x_lt_y)|sWait1;
	assign y_en = (y_sel & x_lt_y)|sWait1;
	assign output_en = (sG & ~x_ne_y)|(sTX & ~x_ne_y)|(sTY & ~x_ne_y)|(sT & ~x_ne_y);
	assign done = (sT | (done_next & go));

endmodule //GCD_control
