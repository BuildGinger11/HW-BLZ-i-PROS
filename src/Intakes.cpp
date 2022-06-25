#include "main.h"

// -mouth----------------------------------------------------------------------------

pros::Motor Conveyor(16);  //<-- reversed

void intakes(int power) { Conveyor.move(power); }

void Intake_Control(void *) {
  while (true) {
    // printf("master: %d\n", master.get_digital(DIGITAL_L1));
    if (master.get_digital(DIGITAL_L1)) {
      intakes(127);  // m ax: 127
    } else if (master.get_digital(DIGITAL_L2)) {
      intakes(-127);
    } else {
      intakes(0);
    }

    pros::delay(20);
  }
}
