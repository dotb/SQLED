# SQLED
An Arduino LED class which supports fading LEDs

## Getting Started
First, configure the PWM pin connected to the LED
####Syntax####
        setup(pin_identifier)
        pin_identifier: the PWM pin connected to the LED.

####Example####
        setup(13);

Now you can fade the LED to a specific brightness over a configurable duration
####Syntax####
        anLED.fadeToBrightness(brightness_value, time_milliseconds);
        brightness_value: A value between 0 and 255, indicating the brightness of the LED.
        time_milliseconds: The amount of time taken to fade in milliseconds.

####Example####

        anLED.fadeToBrightness(128, 3000);
In the example above, the LED will fade to half it's available brightness over 3 seconds.

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
