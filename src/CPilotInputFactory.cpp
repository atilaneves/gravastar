#include "CPilotInputFactory.hpp"
#include "CPilotInputOptions.hpp"
#include "CPilotInputKey.hpp"
#include "CPilotInputJoy.hpp"
#include <stdio.h>
#include <stdlib.h>


CPilotInput* CPilotInputFactory::CreateInput(const CPilotInputOptions&
					     options) {

  if(options.Type() == "Keyboard")
    return new CPilotInputKey(options);
  else if(options.Type() == "Joystick") {
    return new CPilotInputJoy(options);
  }
  else {
    fprintf(stderr, "Unknown input type %s\n", options.Type().c_str());
    exit(1);
  }

}
