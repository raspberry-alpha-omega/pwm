#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define BITS 6
#define TICK_US 250

#define N_CHANNELS 8

extern int usleep(int usecs);

int levels[N_CHANNELS];
int state[N_CHANNELS];

void switch_on(int channel) {
	if (!state[channel]) {
		digitalWrite(channel, LOW);
		state[channel] = 1;
	}
}

void switch_off(int channel) {
	if (state[channel]) {
		digitalWrite(channel, HIGH);
		state[channel] = 0;
	}
}

void wait(int ticks) {
	usleep(ticks * TICK_US);
}

void emit() {
  int bit;
  int power;
  int channel;

  for (bit = 0; bit < BITS; ++bit) {
    power = 1 << bit;
    for (channel = 0; channel < N_CHANNELS; ++channel) {
      if ((levels[channel] & power) > 0) {
        switch_on(channel);
      } else {
        switch_off(channel);
      }
    }
    wait(power);
  }
}

void setup(int argc, char**argv, int* channels) {
	wiringPiSetup();
  for (int i = 0; i < N_CHANNELS; ++i) {
	  pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
		state[i] = 0;
		
		if (i < argc-1)
	    channels[i] = atoi(argv[i+1]);
		else
			channels[i] = 0;
  }
}


int main(int argc, char**argv) {
  setup(argc, argv, levels);
  pinMode(0, OUTPUT);

  for (;;) {
    emit();
  }
}

