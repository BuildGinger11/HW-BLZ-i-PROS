#include "main.h"


pros::Motor Flywheel(9);
pros::Motor Flywheel2(10, true);

int speeds[2] = {80, 127};
bool speed = false;

void flywheel (int power)
{
  Flywheel.move(power);
  Flywheel2.move(power);
}

void Flywheel_Control (void*)
{
 while(true)
 {
   if(master.get_digital(DIGITAL_R2))
   {
     speed = !speed;
   }
   if(speed)
   {
     flywheel(speeds[0]);
   }
   else
   {
     flywheel(speeds[1]);
   }
  pros::delay(20);
 }
}
