//
//  SQLED.cpp
//  
//
//  Created by Bradley Clayton on 7/30/12.
//  Copyright (c) 2012 Squarepolka. All rights reserved.
//


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


