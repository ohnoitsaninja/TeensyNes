/*
The MIT License (MIT)
Copyright (c) 2016 Logan McCandless
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef nesController_h
#define nesController_h
#include <stdint.h> 
#include <arduino.h>
class nesController {   // buttonOffset will shift the gamepad buttons up by 8*buttonOffset
  public:              // for multiple nes controllers on a single usb joystick interface 
    nesController(uint8_t clockPin, uint8_t latchPin, uint8_t dataPin, uint8_t buttonOffset=0);
    void read();
  private:
    uint8_t _Clock; 
    uint8_t _Latch; 
    uint8_t _Data;
    uint8_t _buttonOffset;
    bool processButton(uint8_t);
};

#endif
