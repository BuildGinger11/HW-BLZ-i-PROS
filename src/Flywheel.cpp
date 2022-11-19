#include "main.h"

pros::Motor Flywheel(17, true); //no true
pros::Motor Flywheel2(15); //true

std::vector<int> speeds = {0, 81, 63}; // {0, 127, 115, 110, 95};
bool speed = false;

void flywheel(int power) {
  Flywheel.move(power);
  Flywheel2.move(power);
}

int flywheel_index = 0;
void set_flywheel(int input) { flywheel_index = input; }
int get_flywheel() { return flywheel_index; }

void Flywheel_Control(void *) {
  while (true) {
    if (master.get_digital_new_press(DIGITAL_R2)) {
      flywheel_index++;
      if (flywheel_index >= speeds.size())
        flywheel_index = 0;
    }
    flywheel(speeds[flywheel_index]);

    pros::delay(20);
  }
}
