#include "main.h"


pros::Motor Flywheel(9);
pros::Motor Flywheel2(10, true);

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
     flywheel(127);
   }
   else
   {
     flywheel(0);
   }
  pros::delay(20);
 }
}
