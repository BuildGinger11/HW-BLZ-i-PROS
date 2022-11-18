
/*
#include "main.h"

pros::Motor slider(13, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

int rotations() { return slider.get_position(); }
void set_slider(int power) { slider.move(power); }

bool pressed = false;
bool rotation = false;
int FinalDegrees = 0;

void Slider_Control(void *) {
  int speed = 200;
  while (1) {
    if (master.get_digital_new_press(DIGITAL_R1) && get_flywheel() != 0) {
      printf("inmaster \n");
      slider.move_absolute(-2000, speed);
      pros::delay(2000);
      slider.move_absolute(0, speed);
    }

    pros::delay(20);
  }
}
*/
