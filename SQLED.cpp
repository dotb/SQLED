/*
Copyright (c) 2015, Bradley Clayton
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of SQLED nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "SQLED.h"

SQLED::SQLED()
{
    isFading = false;
    isPulsing = false;
}

void SQLED::setup(int ledPin)
{
    _ledPin = ledPin;
    _currentVal = 0;
    pinMode(_ledPin, OUTPUT);
    this->fadeToBrightness(0, 0);
}

void SQLED::turnOn()
{
    this->fadeToBrightness(255, 0);
}

void SQLED::turnOff()
{
    this->fadeToBrightness(0, 0);
}

void SQLED::fadeToBrightness(int brightness, long duration)
{
    _fadeStartTime = millis();
    _fadeEndTime = _fadeStartTime + duration;
    _fadeStartVal = _currentVal;
    _fadeEndVal = brightness;
    isFading = true;
}

void SQLED::setBrightness(int value, long duration)
{
    // Only adjust brighness of LED if it is on
    if (_currentVal > 0)
    {
        fadeToBrightness(value, duration);
    }
}

float SQLED::currentVal()
{
    return _currentVal;
}

#pragma mark - SQSchedularDelegate Methods
unsigned int SQLED::executionInterval()
{
    return 0;
}

// Clock events
void SQLED::loop()
{
    long timeNow = millis();
    if (timeNow < _fadeEndTime)
    {
        _currentVal = map(timeNow, _fadeStartTime, _fadeEndTime, _fadeStartVal, _fadeEndVal);
    }
    else
    {
        _currentVal = _fadeEndVal; // Ensure we finish on the final value
        isFading = false;
        if (isPulsing && _currentVal >= 255)
        {
            fadeToBrightness(0, _fadeEndTime - _fadeStartTime);
        }
        else if (isPulsing && _currentVal <= 0)
        {
            fadeToBrightness(255, _fadeEndTime - _fadeStartTime);
        }
    }
    
    if (_currentVal != analogRead(_ledPin))
    {
        analogWrite(_ledPin, _currentVal);
    }
}


