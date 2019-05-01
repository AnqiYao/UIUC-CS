// GCD datapath
module gcd_circuit(out, x_lt_y, x_ne_y, X, Y, x_sel, y_sel, x_en, y_en, output_en, clock, reset);
	output  [31:0] out;
	output  x_lt_y, x_ne_y;
	input	[31:0]	X, Y;
	input   x_sel, y_sel, x_en, y_en, output_en, clock, reset;
	
    // IMPLEMENT gcd_circuit HERE
	wire [31:0] w1,w2,w3,w4,w5,w6;

	mux2v m1(w1,X,w5,x_sel);
        mux2v m2(w2,Y,w6,y_sel);
       
        register r1(w3, w1, clock, x_en, reset);
	register r2(w4, w2, clock, y_en, reset);
	
	subtractor s1(w5,w3,w4);
	subtractor s2(w6,w4,w3);
       

	comparator c1(x_lt_y, x_ne_y, w3, w4);
	register r3(out,w3,clock,output_en,reset);
	
	


endmodule // gcd_circuit
