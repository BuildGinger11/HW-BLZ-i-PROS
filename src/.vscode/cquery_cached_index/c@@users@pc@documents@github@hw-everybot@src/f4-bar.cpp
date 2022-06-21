#include "main.h"


// -Wing---------------------------------------------------------
pros::ADIDigitalOut Wing (6) ;
int wingState = 0 ;
int wingLock  = 0 ;
pros::ADIDigitalOut Tallmogo(4);
int TallState = 0;
int TallLock = 0;
void wing (bool position)
{
  Wing.set_value (position) ;
}
void tallMogo (bool position)
{
  Tallmogo.set_value (position) ;
}
pros::ADIDigitalIn wingLimiter (8) ;

bool wingHit = false ;

int getWingLimiter ()
{
  return (wingLimiter.get_value()) ;
}

void checkWingHit ()
{
  // begin drive forward @ max speed
  //chassis.~Drive() ;
// chassis.set_max_speed(127) ;
  printf("begin drive") ;

  int timer = 0 ;
  // while driving to mogo...
  while (getWingLimiter() == 1 && timer <= 100)
  {
    printf("while 1") ;
    timer ++ ;
    pros::delay(20) ;
  }
  while (getWingLimiter() == 0 && timer <= 100)
  {
    printf("while 2") ;
    timer ++ ;
    pros::delay(20) ;
  }
  while (getWingLimiter() == 1 && timer <= 100)
  {
    printf("while 3") ;
    timer ++ ;
    pros::delay(20) ;
  }
  // while hitting the mogo rim...
  while (getWingLimiter() == 0 && timer <= 100)
  {
    printf("while 4") ;
    timer ++ ;
    pros::delay(20) ;
  } // kicks out once wing grips onto mogo

  // retreat
  chassis.set_max_speed(-127) ;

}

// -Arm---------------------------------------------------------------


const int num_of_pos = 8; // Number of lift positions

const int num_of_lift_control = 6 ;
// max height for lift
const int maxHeight = 4000 ;

const int lift_heights[num_of_pos] = {0, 0, 700, 3400, 2100, 2100, 3400, maxHeight}; // Lift Positions
    // {ready, grab, allow intaking, above plat, on plat, release on plat, above plat}


// Driver Control Variables
int up_lock = 0;
int down_lock = 0;

int lift_state = 0 ; // was 1
int locked = 0 ;

int a_press = 0 ;


// bool b_lock = true ;
int b_press = 0 ;

int x_lock = 0 ;
//int XTimer = 0 ;

int resetTimer = 0 ;

pros::Motor lift(9); // motor


//lift mogo lock
pros::ADIDigitalOut sixLock(1);

void sixlock(bool position)
{
  sixLock.set_value(position);
}

void setLiftStart (int position)
{
  lift_state = position ;
}

int getLiftPos ()
{
  return lift_state ;
}

int liftMaxHeight ()
{
  return maxHeight ;
}

void set_lift(int input)  { lift = input; }

void zero_lift()    { lift.tare_position(); }
int  get_lift()     { return lift.get_position(); }
int  get_lift_vel() { return lift.get_actual_velocity(); }

void moveLift (int power)
{
  lift.move (power) ;
}

void set_lift_position(int target, int speed)
{
  //printf("Lift Position: %d \n", target);
  lift.move_absolute(target, speed);
}


void tareLift ()
{
  lift.tare_position() ;
}


// // int-eresting ints Owo
// int upButtonPress = 0 ;

///
// Driver Control
//  - when R1 is pressed, bring the lift up to new position in array
///
void
lift_control(void*) {
   //<-- when switch to drive mode, start here

  // move lift value up
  while(1)
  {
  // // manual override checkLockedMogo ()
  // if (master.get_digital(DIGITAL_UP))
  // {
  //   upButtonPress = 1 ;
  // }

  if (master.get_digital(DIGITAL_R1) && up_lock==0)
  {
    // If lift value is at max, bring it down to 0
    if(lift_state>=num_of_lift_control)
      lift_state = 0;
    // Otherwise, bring the lift value up
    else
      lift_state++;

    up_lock = 1;
  }

//  special position for platforming
  else if (master.get_digital(DIGITAL_A) && a_press == 0) {
     lift_state = 1;

    a_press = 1 ;

  }

  // reset lift if miss
  else if (master.get_digital(DIGITAL_B) && b_press == 0)
  {
    lift_state = 0 ;
    b_press = 1 ;
  }


  //actual motor moving stuff

    if(lift_state == 0)
    {

      set_lift_position(lift_heights[lift_state], 127) ;

      if (get_lift() < 20)
      {
        sixlock (false) ;
      }

    }
    else if (lift_state == 1)
    {
      // // claw in
      // claw(true) ;
      sixlock (true) ;
      set_lift_position(lift_heights[lift_state], 127) ;
    }
    else if (lift_state == 5)
    {
      set_lift_position(lift_heights[lift_state], 127) ;
      sixlock(false) ;
    }
    else if (lift_state == 6)
    {
      set_lift_position(lift_heights[lift_state], 127) ;
      // no sixlock
    }

    else
    {
      //actuate pneumatic
      sixlock(true);
      //move motor to pos
      set_lift_position(lift_heights[lift_state], 127);
    }



  if (!master.get_digital(DIGITAL_A))
  {
    a_press = 0 ;
  }
  if (!master.get_digital(DIGITAL_B))
  {
    b_press = 0 ;
  }
  if (!master.get_digital(DIGITAL_R1))
  {
    up_lock = 0 ;
  }


//maxHeightNerds button

  if (master.get_digital(DIGITAL_LEFT) && x_lock == 0)
  {
    lift_state = num_of_pos - 1 ;
    x_lock = 1 ;
  }
  if (!(master.get_digital(DIGITAL_LEFT)))
  {
    x_lock = 0 ;
  }

// reset lift if we are dumb
  if (master.get_digital(DIGITAL_Y))
  {
    moveLift(-127) ;
    // while (get_lift_vel() > 0 && resetTimer <= 150)
    // {
    //   moveLift(-127) ;
    //   resetTimer ++ ;
    // }
    tareLift() ;
  }
  else if (!master.get_digital(DIGITAL_Y))
  {
    resetTimer = 0 ;
  }


  // wing
  if (master.get_digital(DIGITAL_R2) && wingState == 0 && wingLock == 0)
  {
    //activate claw
    printf("open \n");
    wingState = 1 ;
    wing(false) ;
    wingLock = 1 ;
  }
  else if (master.get_digital(DIGITAL_R2) && wingState == 1 && wingLock == 0)
  {
    //deactivate claw
    wingState = 0 ;
    wing(true) ;
    wingLock = 1 ;
  }
  else if (!master.get_digital(DIGITAL_R2))
  {
    wingLock = 0 ;
  }


  if (master.get_digital(DIGITAL_UP) && TallState == 0 && TallLock == 0)
  {
    //activate tall mogo claw
    TallState = 1 ;
    tallMogo(false) ;
    TallLock = 1 ;
  }
  if (master.get_digital(DIGITAL_UP) && TallState == 1 && TallLock == 0)
  {
    //deactivate tall mogo claw
    TallState = 0 ;
    tallMogo(true) ;
    TallLock = 1 ;
  }
  else if (!master.get_digital(DIGITAL_UP))
  {
    TallLock = 0 ;
  }
  pros::delay (20) ;
  }
}
