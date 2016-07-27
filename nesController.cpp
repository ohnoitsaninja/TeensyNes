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

#include "nesController.h"

nesController::nesController(uint8_t pClock, uint8_t pLatch, uint8_t pData, uint8_t buttonOffset) {
  _Clock = pClock;
  _Latch = pLatch;
  _Data = pData;
  _buttonOffset = buttonOffset;
  pinMode(_Clock, OUTPUT);
  pinMode(_Latch, OUTPUT);
  pinMode(_Data, INPUT);
  digitalWrite(_Latch, LOW);
  digitalWrite(_Clock, LOW);
}

bool nesController::processButton(uint8_t k) {
  static byte buttons;
  bool buttonStatus = (buttons >> k)&1;
  if (buttonStatus != digitalRead(_Data)) {
#ifdef USBjoystick_h_
    Joystick.button(1 + k + (_buttonOffset<<3), buttonStatus);
#endif
    buttons ^= 1 << k;
#ifdef debugOut
    Serial.printf("%s button #%i\n",  buttonStatus ? "released" : "pressed", k);
#endif
    return true;
  }
  return false;
}

void nesController::read() {
  digitalWriteFast(_Latch, HIGH);
  digitalWriteFast(_Latch, LOW);
  uint8_t i = 0;
  if (nesController::processButton(i)) return;
  i++;
  for (; i < 8; i++) {
    digitalWriteFast(_Clock, LOW);
    digitalWriteFast(_Clock, HIGH);
    delayMicroseconds(1);
    if (nesController::processButton(i)) return;
  }
}

