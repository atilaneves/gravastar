#include "CGrav.hpp"
#include "CGravMenu.hpp"
#include "CGravOptions.hpp"
#include <stdio.h>


bool gDebug = false;


int main(int argc, char *argv[]) {
  if(argc > 1) gDebug = true;
  CGrav grav; //initialise things
  CGravOptions options;
  CGravMenu menu(options);

  menu.Run();
  return 0;
}


END_OF_MAIN() //allegro needs this
