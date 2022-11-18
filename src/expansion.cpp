#include "main.h"


//Driver Control Variables
bool expansion = true;
int expansion1 = 0;
pros::ADIDigitalOut expansion2('B');


void set_expansion(bool input)
{
  if(input == UP)
  expansion2.set_value(true);
  if(input ==DOWN)
  expansion2.set_value(false);
}


void
Expansion_Control(void *b){

while (true) {
  //toggle for lock4
  if (master.get_digital(DIGITAL_RIGHT) && expansion) {
    expansion = false;
    set_expansion(UP);

  }
  else if (!master.get_digital(DIGITAL_RIGHT))
  set_expansion(DOWN);

  }
}
