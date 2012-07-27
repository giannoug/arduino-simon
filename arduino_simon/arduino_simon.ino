#define CHOICES  4    // This defines the number of LEDs and buttons. Simon has 4!
#define STEPS    50   // 50 steps. Increase it if you find the game easy (highly unlikely).

int leds[] = {
	2, 3, 4, 5}; // LED pin definitions.
int buttons[] = {
	8, 9, 10, 11}; // Button pin definitions.

void setup() {
	for (int i = 0; i < CHOICES; i++) {
		pinMode(leds[i], OUTPUT); // Each LED pin is set as an output.

		pinMode(buttons[i], INPUT); // Each button as an input,
		digitalWrite(buttons[i], HIGH); // with internal pullup.
	}

	randomSeed(analogRead(0));
}

void loop() {
	int steps[STEPS];
	unsigned long time = 500; // Initial time between each "step". Decreases everytime the user correctly recreates the pattern.

	for (int i = 0; i < STEPS; i++) {
		steps[i] = random(CHOICES); // A random step (0-3).

		// Shows all the steps, until now.
		for (int j = 0; j <= i; j++) {
			lightLedForMs(steps[j], time);
		}

		// Check if user reproduces them correctly.
		for (int j = 0; j <= i; j++) {
			int button = getButton();

			if (button == steps[j]) {
				lightLedForMs(steps[j], 250);
			}
			else {
				gameover();
			}
		}

		time -= 10; // Time is reduced by 10ms between each round.
		delay(1000);
	}
}

// When the game is over, the reset button on the Arduino board has to be pressed.
void gameover() {
	while (1) {
		for (int i = 0; i < 4; i++) {
			int led = leds[i];
			digitalWrite(led, !digitalRead(led));
		}
		delay(100);
	}
}

void lightLedForMs(int led, unsigned long ms) {
	digitalWrite(leds[led], HIGH);
	delay(ms);
	digitalWrite(leds[led], LOW);
	delay(ms);
}

int getButton() {
	while (1) {
		for (int i = 0; i < CHOICES; i++) {
			if (!digitalRead(buttons[i])) {
				return i;
			}
		}
	}
}
