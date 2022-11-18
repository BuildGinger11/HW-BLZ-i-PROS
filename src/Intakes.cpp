#include "main.h"

// -mouth----------------------------------------------------------------------------

pros::Motor Conveyor(16);  //<-- reversed

void set_intake(int power) { Conveyor.move(power); }

void Intake_Control(void *) {
  while (true) {
    // printf("master: %d\n", master.get_digital(DIGITAL_L1));
    if (master.get_digital(DIGITAL_L1)or master.get_digital(DIGITAL_R1 )) {
      set_intake(127);  // m ax: 127
    } else if (master.get_digital(DIGITAL_L2)) {
      set_intake(-127);
    } else {
      set_intake(0);
    }

    pros::delay(20);
  }
}
