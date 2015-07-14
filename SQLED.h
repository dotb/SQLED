//
//  SQLED.h
//  
//
//  Created by Bradley Clayton on 7/30/12.
//  Copyright (c) 2012 Squarepolka. All rights reserved.
//

#ifndef SQLED_h
#define SQLED_h

#include "Arduino.h"
#include "SQSchedularProtocol.h"

class SQLED : public SQSchedularProtocol
{
public:
    SQLED();
    virtual void setup(int ledPin);
    virtual void turnOn();
    virtual void turnOff();
    virtual void fadeToBrightness(int brightness, long duration);
    virtual void setBrightness(int value, long duration);
    virtual float currentVal();
    
    #pragma mark - SQSchedularDelegate Methods
    virtual unsigned int executionInterval();
    virtual void loop();
    
    boolean isFading;
    boolean isPulsing;
    
private:
    int _ledPin;
    
    float _currentVal;
    float _fadeStartVal;
    float _fadeEndVal;
    long _fadeStartTime;
    long _fadeEndTime;
};

#endif