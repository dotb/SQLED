# SQLED
An Arduino LED class which supports fading LEDs

## Usage
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
