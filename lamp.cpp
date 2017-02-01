
//************************************
//*                                  *
//*  Katelyn Biesiadecki             *
//*  January 31, 2017                *
//*                                  *
//*  Mouse Lamp                      *
//*                                  *
//*  This program will toggle an LED *
//*  when a button is pressed.       *
//*                                  *
//************************************

const int BUTTON_PIN = 2;
const int LED_PIN = 13;
int buttonState = 0;
boolean pressed = false;

void setup() 
{
	pinMode(LED_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
}

void loop() 
{
	buttonState = digitalRead(BUTTON_PIN);

	if (buttonState == HIGH && !pressed) {
		pressed = true;
		digitalWrite(LED_BUILTIN, HIGH);
	} else if (buttonState == HIGH && pressed) {
		pressed = false;
		digitalWrite(LED_BUILTIN, LOW);
	}
}

