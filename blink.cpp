
//************************************
//*                                  *
//*  Katelyn Biesiadecki             *
//*  January 25, 2017                *
//*                                  *
//*  Blinky                          *
//*                                  *
//*  This program will turn an LED   *
//*  (digital pin 13) on and off     *
//*  every second.                   *
//*                                  *
//************************************

void setup() 
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}

