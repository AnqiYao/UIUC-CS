#include <iostream>
#include <png.h>

#include "png.h"

int main() {
     
      PNG initial("in.png"); 
      size_t height = initial.height();
      size_t width = initial.width();
      PNG output( width, height);

      for (size_t yi = 0; yi < height; yi++) {
        for (size_t xi = 0; xi < width; xi++) {
	   *output(width-xi-1,height-yi-1) = *initial(xi,yi);
                  
          }
       } 
       
      output.writeToFile("out.png");        

      return 0;
}        
            
           
       
      
     

   
            

        
    
 
    
