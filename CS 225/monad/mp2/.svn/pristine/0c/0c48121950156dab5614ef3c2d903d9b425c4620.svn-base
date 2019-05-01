#include "image.h"

void Image::flipleft(){
  RGBAPixel *leftside;
  RGBAPixel *rightside; 
  RGBAPixel *temp = new RGBAPixel();
 for(size_t x=0;x<this->width()/2;x++){
    for(size_t y=0;y<this->height();y++){
        leftside = this->operator()(x,y);
        rightside = this->operator()(this->width()-x-1,y);
        *temp = *leftside;
        *leftside = *rightside;
        *rightside = *temp;
     }
   } 
      
     delete temp;
} 

void Image::adjustbrightness(int r,int g,int b){
  
  for(size_t x=0;x<this->width();x++){
    for(size_t y=0;y<this->height();y++){
       
            if(this->operator()(x,y)->red +r >255)
                this->operator()(x,y)-> red = 255;
            else if (this->operator()(x,y)-> red +r <0)
                this->operator()(x,y)-> red = 0;
            else
                (this->operator()(x,y))-> red += r ;
       
            if(this->operator()(x,y)-> green +g> 255)
                this->operator()(x,y)-> green = 255;
            else if(this->operator()(x,y)-> green +g <0)
                this->operator()(x,y)-> green =0;
           else
             (this->operator()(x,y))-> green += g;
            
            if(this->operator()(x,y)-> blue +b >255)
                this->operator()(x,y)-> blue = 255;
            else if(this->operator()(x,y)-> blue +b <0)
                this->operator()(x,y)-> blue =0;
            else 
              (this->operator()(x,y))-> blue += b; 
        }
      }
}



void Image::invertcolors(){
 for(size_t x=0;x<this->width();x++){
    for(size_t y=0;y<this->height();y++){
        (this->operator()(x,y))-> red = 255 - (this->operator()(x,y))-> red ;
        (this->operator()(x,y))-> green = 255 - (this->operator()(x,y))-> green ;
        (this->operator()(x,y))-> blue = 255 - (this->operator()(x,y))-> blue ;
      }
    }
}






