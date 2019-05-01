// 00 - AND, 01 - OR, 10 - NOR, 11 - XOR
module logicunit(out, A, B, control);
    output      out;
    input       A, B;
    input [1:0] control;
    wire	w1,w2,w3,w4;
 /*  
    not n1(w1,control[0]);
    not n2(w2,control[1]);
    not n3(not_A,A);
    not n4(not_B,B);
      
    //test for and
    and a1(w3,A,B,w1,w2);


    //test for xor
    xor x1(w4,control[0],control[1]);
    xor x2(w5,A,B);
    and a2(w6,w4,w5);


    //test for nor
    and a3(w7,control[1],w1);
    and a4(w8,not_A,not_B);
    and a5(w9,w7,w8);

    //test for or
    or o1(w10,A,B);
    and a6(w11,control[0],w2);
    and a7(w12,w10,w11);

    or o2(out,w3,w6,w9,w12);
  */
  and a1(w1,A,B);
  or o1(w2,A,B);
  nor n1(w3,A,B);
  xor x1(w4,A,B);


  mux4 m1(out,w1,w2,w3,w4,control[1:0]);


        
    

endmodule // logicunit
