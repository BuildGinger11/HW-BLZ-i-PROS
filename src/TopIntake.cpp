#include "main.h"

// -mouth----------------------------------------------------------------------------

pros::Motor topintake(19);  //<-- reversed
int indexer1 = 0;
bool indexer = true;
pros::ADIDigitalOut indexer2('F');

void set_topintake(int power) { topintake.move(power); }

void set_indexer(bool input)
{
  indexer2.set_value(input);
}

void TopIntake_Control(void *b) {
  while (true) {
    // printf("master: %d\n", master.get_digital(DIGITAL_L1));
    if (master.get_digital(DIGITAL_R1)&& get_flywheel() != 0)
     {
      set_topintake(127);  // m ax: 127
    }
     else {
      set_topintake(30);
    }

    pros::delay(60);
  }
}

void
Indexer_Control(void *b){
  //toggle for lock4
  while(1)
  {
    if (master.get_digital(DIGITAL_R1) && indexer) {
    indexer = false;
    set_indexer(OUT);
    pros::delay(3000);
    set_indexer(IN);

   }
     else if (!master.get_digital(DIGITAL_R1)) { indexer = true; }
  }

}
