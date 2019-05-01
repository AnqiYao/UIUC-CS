/**
 * @file
 * Contains the implementation of the countOnes function.
 */

unsigned sumup(unsigned input){
      int right = input & 0b01010101;
      int left = input & 0b10101010;
      int output1 = (left>>1)+right;
      int right1 = output1 & 0b00110011;
      int left1 = output1 & 0b11001100;
      int output2 = (left1>>2) + right1;
      int result = 0;
      result += (output2>>4) + (output2&0b00001111);
      return result;
}

unsigned countOnes(unsigned input) {
      return sumup(input)+sumup(input>>8)+sumup(input>>16)+sumup(input>>24);
}
