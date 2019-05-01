/**
 * @file
 * Contains the implementation of the extractMessage function.
 */

#include <iostream> // might be useful for debugging
#include <assert.h>
#include "extractMessage.h"

using namespace std;

char *extractMessage(const char *message_in, int length) {


   // length must be a multiple of 8
   assert((length % 8) == 0);

   // allocate an array for the output
   char *message_out = new char[length];
	// TODO: write your code here


   for(int i = 0; i < length; i+=8){
         if(i>=length) break;
           int temp = i;
      for(int j = i; j < temp+8 ; j++){
           if (j%8==0)          
           message_out[j] = (char) ( (message_in[temp]&0x01) | (message_in[temp+1]&0x01)<<1 | (message_in[temp+2]&0x01)<<2 | (message_in[temp+3]&0x01)<<3 | (message_in[temp+4]&0x01)<<4 | (message_in[temp+5]&0x01)<<5 | (message_in[temp+6]&0x01)<<6 | (message_in[temp+7]&0x01)<<7);
           else if (j%8==1)
           message_out[j] = (char) ( (message_in[temp]&0x02)>>1 | (message_in[temp+1]&0x02) | (message_in[temp+2]&0x02)<<1 | (message_in[temp+3]&0x02)<<2 | (message_in[temp+4]&0x02)<<3 | (message_in[temp+5]&0x02)<<4 | (message_in[temp+6]&0x02)<<5 | (message_in[temp+7]&0x02)<<6);
           else if (j%8==2)
           message_out[j] = (char) ( (message_in[temp]&0x04)>>2 | (message_in[temp+1]&0x04)>>1 | (message_in[temp+2]&0x04) | (message_in[temp+3]&0x04)<<1 | (message_in[temp+4]&0x04)<<2 | (message_in[temp+5]&0x04)<<3 | (message_in[temp+6]&0x04)<<4 | (message_in[temp+7]&0x04)<<5);
           else if (j%8==3)
           message_out[j] = (char) ( (message_in[temp]&0x08)>>3 | (message_in[temp+1]&0x08)>>2 | (message_in[temp+2]&0x08)>>1 | (message_in[temp+3]&0x08) | (message_in[temp+4]&0x08)<<1 | (message_in[temp+5]&0x08)<<2 | (message_in[temp+6]&0x08)<<3 | (message_in[temp+7]&0x08)<<4);
	   else if (j%8==4)
           message_out[j] = (char) ( (message_in[temp]&0x10)>>4 | (message_in[temp+1]&0x10)>>3 | (message_in[temp+2]&0x10)>>2 | (message_in[temp+3]&0x10)>>1 | (message_in[temp+4]&0x10) | (message_in[temp+5]&0x10)<<1 | (message_in[temp+6]&0x10)<<2 | (message_in[temp+7]&0x10)<<3);
           else if (j%8==5)
           message_out[j] = (char) ( (message_in[temp]&0x20)>>5 | (message_in[temp+1]&0x20)>>4 | (message_in[temp+2]&0x20)>>3 | (message_in[temp+3]&0x20)>>2 | (message_in[temp+4]&0x20)>>1 | (message_in[temp+5]&0x20) | (message_in[temp+6]&0x20)<<1 | (message_in[temp+7]&0x20)<<2);
           else if (j%8==6)
           message_out[j] = (char) ( (message_in[temp]&0x40)>>6 | (message_in[temp+1]&0x40)>>5 | (message_in[temp+2]&0x40)>>4 | (message_in[temp+3]&0x40)>>3 | (message_in[temp+4]&0x40)>>2 | (message_in[temp+5]&0x40)>>1 | (message_in[temp+6]&0x40) | (message_in[temp+7]&0x40)<<1);
           else if (j%8==7)
           message_out[j] = (char) ( (message_in[temp]&0x80)>>7 | (message_in[temp+1]&0x80)>>6 | (message_in[temp+2]&0x80)>>5 | (message_in[temp+3]&0x80)>>4 | (message_in[temp+4]&0x80)>>3 | (message_in[temp+5]&0x80)>>2 | (message_in[temp+6]&0x80)>>1 | (message_in[temp+7]&0x80));
           
            cout<< message_out[j]<<endl;
           }
       
       }
               
	return message_out;
}
