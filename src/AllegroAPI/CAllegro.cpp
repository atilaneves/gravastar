#include "CAllegro.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>


CAllegro::CAllegro() {

  assert(allegro_init() == 0);
  install_keyboard();
  install_timer();
  reserve_voices(32, -1);
  if (install_sound(DIGI_AUTODETECT, MIDI_NONE, nullptr) != 0)
    fprintf(stderr, "\n*** Error: sound not initialised ***\n\n");
  install_joystick(JOY_TYPE_AUTODETECT);
  set_display_switch_mode(SWITCH_PAUSE); //to be able to alt tab

  srand(time(nullptr));
}


CAllegro::~CAllegro() {
  allegro_exit();
}
