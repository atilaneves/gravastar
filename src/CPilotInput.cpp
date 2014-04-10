#include "CPilotInput.hpp"
#include <assert.h>


std::vector<std::string> CPilotInput::sNames{"Left", "Right", "Thrust", "Weapon",
                                             "Special", "Super", "Start"};

bool CPilotInput::IsOn(const std::string& which) const {
    if(which == "Left")    return Left();
    else if(which == "Right")   return Right();
    else if(which == "Thrust")  return Thrust();
    else if(which == "Weapon")  return Weapon();
    else if(which == "Special") return Special();
    else if(which == "Super")   return Super();
    else if(which == "Start")   return Start();
    assert(0); //should never get here
    return false;
}
