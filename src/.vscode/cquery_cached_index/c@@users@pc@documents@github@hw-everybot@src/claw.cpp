#include "main.h"

int timer = 0;


// -Claw (under conveyor)-------------------------------------------
pros::ADIDigitalOut Claw (5);


int claw_state = 0 ;
int clawLock = 0 ;

void claw (bool position)
{
  Claw.set_value (position) ;
}

// -Claw Lift (arm)-------------------------------------------------

pros::ADIDigitalOut ClawLift (2) ;

void clawLift (bool position)
{
  ClawLift.set_value (position) ;
}
void doubleclaw(bool position)
{
  claw(position);
  pros::delay(500);
  clawLift(position);
}

// void clawGrab (bool position)
// {
//   claw (position) ;
// }
// void clawDrop (bool position)
// {
//   claw (position) ;
//   clawLift(position) ;
// }

bool clawop = true ;
void setClawOp (bool boolean)
{
  clawop = boolean ;
}

void
clawControl(void*) {
   //<-- when switch to drive mode, start here

   while (1)
   {
     // activate MogoClaw
     if ( master.get_digital(DIGITAL_L2) && claw_state == 0 && clawLock == 0)
     {
       timer = 0 ;
       //activate claw
       printf("open \n");
       claw_state = 1 ;
       clawLift(false) ;
       clawLock = 1 ;
     }
     else if (master.get_digital(DIGITAL_L2) && claw_state == 1 && clawLock == 0)
     {
       timer = 0 ;
       //grab with claw
       claw_state = 0 ;
       claw(true) ;
       clawLock = 1 ;
     }
     else if (!master.get_digital(DIGITAL_L2))
     {
       clawLock = 0 ;
       timer ++ ;
       
      if (clawop && claw_state == 0 && timer > 20)
        clawLift(true) ;
      else if (clawop && claw_state == 1 && timer > 25)
        claw(false) ;
      // else
      //   clawLift (false) ;
     }

    pros::delay(20) ;
   }

}
