#include  "rgbapixel.h"

#include<cstdint>
using std::uint8_t;
RGBAPixel:: RGBAPixel() : red(255), green(255),blue(255),alpha(255)
{
     /*do nothing */
}

RGBAPixel:: RGBAPixel(uint8_t r, uint8_t g, uint8_t b)
                     : red(r), green(g) , blue(b),alpha(255)
{
                        /*do nothing*/
}

