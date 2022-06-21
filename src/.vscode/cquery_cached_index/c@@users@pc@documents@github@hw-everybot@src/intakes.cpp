#include "main.h"


// -mouth----------------------------------------------------------------------------

pros::Motor Conveyor(10) ; //<-- reversed

int power = 0;
int inputPower ;
void intake(int peee)
{
  // memorial to dru's code lmfao
  // peee = power;

  power = peee ;
  inputPower = peee ;
}
bool autonTask = true ;
void useAutonTask (bool input)
{
  autonTask = input ;
}
// int getPower ()
// {
//   return power ;
// }
void normalIntake (int power)
{
  Conveyor.move(power) ;
}

void intakeTask(void*)
{
  int prevpower = power;
  int timer = 0;
  int stucktime = 0;
  int banstucktime = 0;
  int startban = 0;
  bool jammed = false;

  while(true)
  {
    if (autonTask)
    {
      Conveyor.move(power);
    }

    // check if stopped - works maybe
    if(power != 0 && Conveyor.get_actual_velocity() == 0 && banstucktime >= 12 && !jammed)
    {
      stucktime++;
      if(stucktime >= 5)
        jammed = true;
    }

    // if stopped --> outtake
    if(jammed)
    {
      // printf("Velocity: %f \n%d \n", Conveyor.get_actual_velocity(), power);
      power = -127 ;
        timer++;
      // printf ("timer: %d\n", timer) ;
      if(timer >= 10) // 200 ms
      {
        jammed = false;
        // printf ("jammed: %d\n", jammed) ;
        banstucktime = 0;
        timer = 0;
        // printf ("timer: %d\n", timer) ;
        intake(inputPower) ;
      }
    }
    banstucktime++;

    prevpower = power;
    pros::delay(20);
  }
}

void Opt_intake(int power)
  {Conveyor.move(power);}
int getIntakePos ()
  {return Conveyor.get_position() ;}

// int crossThreshold = 0;
// bool lockedMogo ;
// bool checkLockedMogo ()
// {
//   if (getIntakePos() > 3000)
//   {
//     crossThreshold = 1 ;
//   }
//   if (crossThreshold == 1)
//   {
//     lockedMogo = true ;
//     return lockedMogo ;
//   }
//   else
//   {
//     lockedMogo = false ;
//     return lockedMogo ;
//   }
// }



void Intake_Control(void*)
{
  int timer = 0;
  int stucktime = 0;
  int banstucktime = 0;
  int startban = 0;
  bool count = false;
  while(true)
  {

    //printf("master: %d\n", master.get_digital(DIGITAL_L1));
    if(master.get_digital(DIGITAL_L1))
    {
     Opt_intake(127); // m ax: 127
     startban++;
    }

    else if(master.get_digital(DIGITAL_DOWN))
    {
     Opt_intake(-127);
     startban = 0;
    }
    else
    {
     Opt_intake(0);
     startban = 0;
    }
    if(master.get_digital(DIGITAL_L1) && Conveyor.get_actual_velocity() == 0 && banstucktime >= 12 && startban >= 15)
    {
      stucktime++;
      if(stucktime >= 5)
        count = true;
    }

    if(count)
    {
      //printf("Velocity: %f \n", Conveyor.get_actual_velocity());
      Opt_intake(-127);
        timer++;
      if(timer >= 21)
      {
        count = false;
        banstucktime = 0;
        timer = 0;
      }
    }
    banstucktime++;
//printf("Velocity: %f \n", Conveyor.get_actual_velocity());


  pros::delay(20);
  }
}
