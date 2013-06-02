#include "CPilotInputFactory.hpp"
#include "CPilotInputOptions.hpp"
#include "CPilotInputKey.hpp"
#include "CPilotInputJoy.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;


CPilotInput* CPilotInputFactory::CreateInput(const CPilotInputOptions& options) {

    if(options.Type() == "Keyboard")
        return new CPilotInputKey(options);
    else if(options.Type() == "Joystick") {
        return new CPilotInputJoy(options);
    } else {
        cerr << "Unknown input type: " << options.Type() << endl;
        exit(1);
    }

}
