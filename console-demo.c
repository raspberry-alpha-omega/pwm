#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS 4
#define STEP 1000

#define N_CHANNELS 16
#define N_CYCLES 5

extern int usleep(int usecs);

int levels[N_CHANNELS];
int nchannels = 0;
int state[N_CHANNELS];
char history[N_CHANNELS][(1 << BITS) * N_CYCLES + 1];
int hi;

int setup(int argc, char**argv, int* channels) {
  int ret = 0;
  for (ret = 0; ret < argc-1; ++ret) {
    channels[ret] = atoi(argv[ret+1]);
  }

  printf("running %d cycles of %d channels\n", N_CYCLES, ret);
  return ret;
}

void switch_on(int channel) {
  state[channel] = 1;
}

void switch_off(int channel) {
  state[channel] = 0;
}

void wait(int ticks) {
  int i;
  int channel;
  for (i = 0; i < ticks; ++i) {
    for (channel = 0; channel < nchannels; ++channel) {
      history[channel][hi] = state[channel] ? '^' : '_';
    }
    usleep(STEP);
    ++hi;
  }
}

void emit() {
  int bit;
  int power;
  int channel;

  for (bit = 0; bit < BITS; ++bit) {
    power = 1 << bit;
    for (channel = 0; channel < nchannels; ++channel) {
      if ((levels[channel] & power) > 0) {
        switch_on(channel);
      } else {
        switch_off(channel);
      }
    }
    wait(power);
  }
}

void describe() {
  int channel;
  for (channel = 0; channel < nchannels; ++channel) {
    history[channel][hi] = 0;
    puts(history[channel]);
  }
  putchar('\n');
}

int main(int argc, char**argv) {
  int cycle;

  nchannels = setup(argc, argv, levels);

  hi = 0;
  for (cycle = 0; cycle < N_CYCLES; ++cycle) {
    emit();
  }
  describe();
}

