#include "CAllegro.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>


CAllegro::CAllegro() {

  if(allegro_init() != 0) {
      fprintf(stderr, "\n*** Error: could not initialise allegro ***\n\n");
  }
  if (install_keyboard() != 0)
    fprintf(stderr, "\n*** Error: keyboard not initialised ***\n\n");
  if (install_timer() != 0)
    fprintf(stderr, "\n*** Error: timer not initialised ***\n\n");

  // Voice reservation must happen before install_sound().
  reserve_voices(32, -1);

  // Allegro 4 negotiates an unsigned 16-bit format through Arch's "default"
  // ALSA PCM, which results in silence with PipeWire. The explicit PipeWire
  // PCM negotiates signed 16-bit samples correctly.
#ifdef __linux__
  set_config_string("sound", "alsa_device", "pipewire");
#endif
  int soundResult = install_sound(DIGI_ALSA, MIDI_NONE, nullptr);
  if (soundResult != 0) {
#ifdef __linux__
    set_config_string("sound", "alsa_device", "default");
    soundResult = install_sound(DIGI_ALSA, MIDI_NONE, nullptr);
#endif
  }
  if (soundResult != 0)
    soundResult = install_sound(DIGI_AUTODETECT, MIDI_NONE, nullptr);
  if (soundResult != 0) {
    fprintf(stderr, "\n*** Error: sound not initialised: %s ***\n\n",
            allegro_error);
  }
  install_joystick(JOY_TYPE_AUTODETECT);
  set_display_switch_mode(SWITCH_PAUSE); //to be able to alt tab

  srand(time(nullptr));
}


CAllegro::~CAllegro() {
  allegro_exit();
}
