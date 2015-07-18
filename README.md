# SQLED
An Arduino LED class which supports fading LEDs

## Usage
###Configure the PWM pin connected to the LED###
####Syntax####
        setup(pin_identifier)
        pin_identifier: the PWM pin connected to the LED.

####Example####
        setup(13);

###Fade the LED to a configurable brightness over a configurable duration###
####Syntax####
        anLED.fadeToBrightness(brightness_value, time_milliseconds);
        brightness_value: A value between 0 and 255, indicating the brightness of the LED.
        time_milliseconds: The amount of time taken to fade in milliseconds.

####Example####
Fading an led to half it's available brightness over 3 seconds.
        anLED.fadeToBrightness(128, 3000);

###Example Sketch###
    #include <SQLED.h>
    SQLED anLED;

    void setup() 
    {
      anLED.setup(13);
    }
    
    void loop() 
    {
      anLED.loop();
      // Fade between on and off.
      if (!anLED.isFading)
      {
        if (anLED.currentVal() <= 0)
        {
          anLED.fadeToBrightness(255, 3000);
        }
        else
        {
          anLED.fadeToBrightness(0, 3000);
        }
      }
    }
