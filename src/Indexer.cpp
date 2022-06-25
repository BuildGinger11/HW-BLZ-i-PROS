#include "main.h"

pros::Motor Indexer(5, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

int rotations() { return Indexer.get_position(); }
void indexer(int power) { Indexer.move(power); }

bool pressed = false;
bool rotation = false;
int FinalDegrees = 0;

void Index_Control(void *) {
  int target = 160;
  while (1) {
    if (master.get_digital_new_press(DIGITAL_R1) && get_flywheel() != 0) {
      printf("inmaster \n");
      Indexer.move_absolute(target, 200);
      pros::delay(350);
      Indexer.move_absolute(0, 200);
    }

    pros::delay(20);
  }
}
