Virtual Display / Framebuffer Display for Adafruit GFX Library
--------------------------------------------------------------

Quick and dirty variable size 1-Bit Adafruit framebuffer display class
which implements a virtual display / framebuffer with either 
horizontal/row byte arrangement or vertical/column byte arrangement.

Can be used for debugging by printing the frambuffer via serial 
using function "displaySerial()" or for implementing dedicated 
display device classes. Therefore you can access the framebuffer via the
variable "buffer" which size is "bufferSize". You may also implement the 
function "display()" for that.

I couldn't find a proper guide for how to implement a custom class for
Adafruit GFX library, so I just tried... I have no idea if all features
work properly...