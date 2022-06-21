#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



void testerAuton()
{
  TallMogoClaw();
}



void wingGrab ()
{
  // pneuLift(true) ; // was true
  // pneuLiftLock(false) ;
  sixlock(false) ;

  wing(true) ;
  // printf("testLine \n") ;
  // chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_drive_pid(54, 127) ;

  pros::delay(500) ;

    printf("begin drive \n") ;

    int timer = 0 ;
    while (getWingLimiter() == 0 && timer <= 100)
    { // not pressed - drive to mogo
      printf("while 2\n") ;
      timer ++ ;
      pros::delay(20) ;
    }
    while (getWingLimiter() == 1 && timer <= 100)
    { // pressed - hits mogo
      chassis.set_max_speed(-127) ;
      printf("while 3\n") ;
      timer ++ ;
      pros::delay(20) ;
    }

  set_lift_position(0, 127) ;
  chassis.set_drive_pid(-40, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  wing(false) ;
  pros::delay(250) ;
  // grab mogo
  chassis.set_drive_pid(7, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  // chassis.set_turn_pid(90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_swing_pid(LEFT_SWING, 45, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // // grab
  // pneuLiftLock (true) ;
  // pros::delay(500) ;
  // pneuLift(true) ;

  chassis.set_drive_pid(10, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  sixlock(true) ;
  pros::delay(250) ;
}

void wingTurn ()
{
  // pneuLift(true) ; // was true
  // pneuLiftLock(false) ;
  sixlock(false) ;

  wing(true) ;
  // printf("testLine \n") ;
  // chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_drive_pid(50, 127) ;

  pros::delay(500) ;

    printf("begin drive \n") ;

    int timer = 0 ;
    while (getWingLimiter() == 0 && timer <= 100)
    { // not pressed - drive to mogo
      printf("while 2\n") ;
      timer ++ ;
      pros::delay(20) ;
    }
    while (getWingLimiter() == 1 && timer <= 100)
    { // pressed - hits mogo
      chassis.set_swing_pid(RIGHT_SWING, 90, 127) ;
      printf("while 3\n") ;
      timer ++ ;
      pros::delay(20) ;
    }

  // checkWingHit() ;
  set_lift_position(0, 127) ;
  chassis.set_swing_pid(RIGHT_SWING, 90, 127) ;
  // chassis.set_turn_pid(90, 127) ; // tip that mf
  chassis.wait_drive() ;

  // pick up
  wing(false) ;
  pros::delay(250) ;

  //chassis.set_swing_pid(LEFT_SWING, 140, DRIVE_SPEED) ;
  chassis.set_turn_pid(95, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  chassis.set_drive_pid(30, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  sixlock(true) ;

  // chassis.set_swing_pid(LEFT_SWING, 180, DRIVE_SPEED) ;

}

void wingAWPFull ()
{
  // pneuLift(true) ; // was true
  // pneuLiftLock(false) ;
  sixlock(false) ;

  wing(true) ;
  // printf("testLine \n") ;
  // chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_drive_pid(50, 127) ;

  pros::delay(500) ;

    printf("begin drive \n") ;

    int timer = 0 ;
    while (getWingLimiter() == 0 && timer <= 100)
    { // not pressed - drive to mogo
      printf("while 2\n") ;
      timer ++ ;
      pros::delay(20) ;
    }
    while (getWingLimiter() == 1 && timer <= 100)
    { // pressed - hits mogo
      chassis.set_max_speed(-127) ;
      printf("while 3\n") ;
      timer ++ ;
      pros::delay(20) ;
    }

  // checkWingHit() ;
  set_lift_position(0, 127) ;
  chassis.set_drive_pid(-40, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  wing(false) ;
  pros::delay(250) ;
  // grab mogo
  chassis.set_drive_pid(7, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  // chassis.set_turn_pid(90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_swing_pid(LEFT_SWING, 45, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // // grab
  // pneuLiftLock (true) ;
  // pros::delay(500) ;
  // pneuLift(true) ;

// score AWP
  chassis.set_drive_pid(10, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  sixlock(true) ;
  pros::delay(250) ;

  chassis.set_turn_pid(-89, DRIVE_SPEED) ; // was -90
  chassis.wait_drive() ;

  // rush ally goal
  claw(false) ;
  set_lift_position(700, DRIVE_SPEED) ;
  chassis.set_drive_pid(-89, DRIVE_SPEED/1.2) ; // was -88, was DRIVE_SPEED
  chassis.wait_drive() ;

  claw(true) ;
  pros::delay(500) ;
  intake(127) ;

  chassis.set_drive_pid(10, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // face ringRow
  chassis.set_turn_pid(0, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // get ringRow
  chassis.set_drive_pid(24, DRIVE_SPEED/3) ;
  chassis.wait_drive() ;

  // retreat
  chassis.set_drive_pid(-30, DRIVE_SPEED) ;
  chassis.wait_drive() ;


}

void bamboozlerRight ()
{
  //pneuLift(true) ;

  // into position
  chassis.set_drive_pid(20, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_turn_pid(-45, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(100, DRIVE_SPEED) ;
  chassis.wait_drive() ;
}


void fullAWPTall ()
{
// -v2--------------------------starts right side
    // set up subsystems
    claw(false) ;
    sixlock(false) ;
    set_lift_position(-5, 100) ;
  // fake out for short neut + get tall
    chassis.set_drive_pid(30, DRIVE_SPEED) ; // was 20
    chassis.wait_until(20) ;
    // face tall
    chassis.set_turn_pid(-50, DRIVE_SPEED) ; // was -45
    chassis.wait_drive () ;
    chassis.set_drive_pid(36, DRIVE_SPEED) ;
    chassis.wait_drive() ;
    // grab tall
    sixlock(true) ;
    pros::delay(250) ;
    set_lift_position(500, 100) ;

  // return for ally
    // retreat
    chassis.set_drive_pid(-56, DRIVE_SPEED) ; // was -58
    chassis.wait_drive() ;
    // face ally
    chassis.set_swing_pid(LEFT_SWING, -100, DRIVE_SPEED) ; // was -90
    chassis.wait_until(-90) ;
    // turn for ally
    chassis.set_drive_pid(-8, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    claw(true) ;
    intake(127) ;
    pros::delay(150) ;


  // grab next ally + score
    // head to ally2
    chassis.set_turn_pid(-90, DRIVE_SPEED) ;
    chassis.wait_drive() ;
    // drive and drop
    chassis.set_drive_pid(107, DRIVE_SPEED) ; // was 100
    chassis.wait_until(50) ;
    claw(false) ;
    intake(0) ;

    chassis.wait_drive() ;

    // // face ally
    // chassis.set_turn_pid(-45, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    // // into the goal
    // chassis.set_drive_pid(-24, DRIVE_SPEED) ;
    // chassis.wait_drive() ;

    // grab ally2
    chassis.set_turn_pid(0, DRIVE_SPEED) ;
    chassis.wait_drive() ;
    chassis.set_drive_pid(-15, DRIVE_SPEED) ;
    chassis.wait_drive() ;
    chassis.set_swing_pid(LEFT_SWING, -45, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    claw(true) ;
    intake(127) ;

    // grab ring group
    chassis.set_drive_pid(24, DRIVE_SPEED) ;
    chassis.wait_drive() ;
    // face ringGroup
    chassis.set_turn_pid(60, DRIVE_SPEED) ; // was 50
    chassis.wait_drive() ;
    // grab and retreat
    chassis.set_drive_pid(35, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    chassis.set_drive_pid(-40, 127) ;

// -v1--------------------------------------------------------------
    // // prep subsystems
    // wing (false) ; // make sure our setup isnt dumb
    //
    // claw(false) ;
    // set_lift_position(-5, 100) ;
    //
    // // into ally1
    // chassis.set_drive_pid(-6, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // drop ring + temp grab
    // claw(true) ;
    //
    // pros::delay(250) ;
    // //claw(false) ;
    //
    //
    // // set lift pos
    // set_lift_position(250, 100) ;
    // sixlock(false) ;
    //
    // chassis.set_swing_pid(LEFT_SWING, 135, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // turn around to face tall mogo
    // chassis.set_turn_pid(130, DRIVE_SPEED) ; // was 135
    // chassis.wait_drive() ;
    //
    // intake(127) ;
    // // drive to neut
    // chassis.set_drive_pid(55, DRIVE_SPEED/2) ; // was 70
    // chassis.wait_until(40) ; // was 60
    // set_lift_position(0, 127) ;
    // chassis.wait_drive() ;
    // // pick up
    // sixlock(true) ;
    // pros::delay(250) ;
    //
    // set_lift_position(500, DRIVE_SPEED) ;
    // // face ringGroup
    // chassis.set_turn_pid(270, TURN_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // drive thru ringGroup & into zone
    // chassis.set_drive_pid(25, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // drop ally1
    // chassis.set_turn_pid(180, TURN_SPEED) ;
    // chassis.wait_drive() ;
    //
    // claw(false) ;
    //
    // // drive to ally2
    // chassis.set_drive_pid(10, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // chassis.set_turn_pid(10, TURN_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // back up into ally2
    // chassis.set_drive_pid(-55, DRIVE_SPEED) ; // was -50
    // chassis.wait_drive() ;
    //
    // claw(true) ;
    //
    // // face ringRow + intake
    // // chassis.set_turn_pid(90, DRIVE_SPEED) ;
    // chassis.set_swing_pid(LEFT_SWING, 90, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // ringTake
    // chassis.set_drive_pid(30, DRIVE_SPEED) ;
    // chassis.wait_drive() ;
    //
    // // retreat back into zone
    // chassis.set_drive_pid(-40, 127) ;


}

void TallMogoWing()
{

  // printf("testLine \n") ;
  // chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  //sixlock(false) ;
  //claw(false) ;

  wing(true) ;
  chassis.set_drive_pid(41, 127);//54
  set_lift_position(1000, 100);
  pros::delay(1000);
  set_lift_position(-5, 100);
  // pros::delay(500) ;
  //
  //   printf("begin drive \n") ;
  //
  //   int timer = 0 ;
  //   while (getWingLimiter() == 0 && timer <= 100)
  //   { // not pressed - drive to mogo
  //     printf("while 2\n") ;
  //     timer ++ ;
  //     pros::delay(20) ;
  //   }
  chassis.set_drive_pid(-22, 127);
  pros::delay(1000);
  //chassis.set_swing_pid(LEFT_SWING, -20, 127);
  //chassis.wait_drive();
  wing(false);
  sixlock(false);
  pros::delay(500);
  chassis.set_swing_pid(LEFT_SWING, 14, 100);
  chassis.wait_drive();
  chassis.set_drive_pid(15, 60);
  chassis.wait_drive();
  sixlock(true);
  pros::delay(400);
  chassis.set_drive_pid(-12, 100);
  chassis.wait_drive();
  chassis.set_swing_pid(LEFT_SWING, -53, 110);
  chassis.wait_drive() ;
  doubleclaw(false) ;
  chassis.set_drive_pid(-27, 80); // was -40
  chassis.wait_drive();
  set_lift_position(1000, 100);
  doubleclaw(true);
  chassis.set_turn_pid(40, 100);
  chassis.wait_drive();
  intake(127);
  chassis.set_drive_pid(42, 50);
  chassis.wait_drive();
  chassis.set_drive_pid(-47, 127);
  chassis.wait_drive() ;

}
void TallMogoClaw()
{

  // printf("testLine \n") ;
  // chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  //sixlock(false) ;
  //claw(false) ;

  sixlock(false) ;
  chassis.set_drive_pid(10, 127);//54
  set_lift_position(2000, 127);
  pros::delay(1500);
  set_lift_position(-5, 100);
  chassis.set_drive_pid(40, 100);
  chassis.wait_drive();
  sixlock(true);
  pros::delay(200);
  // pros::delay(500) ;
  //
  //   printf("begin drive \n") ;
  //
  //   int timer = 0 ;
  //   while (getWingLimiter() == 0 && timer <= 100)
  //   { // not pressed - drive to mogo
  //     printf("while 2\n") ;
  //     timer ++ ;
  //     pros::delay(20) ;
  //   }
  chassis.set_drive_pid(-22, 127);
  pros::delay(1000);
  //chassis.set_swing_pid(LEFT_SWING, -20, 127);
  //chassis.wait_drive();
  chassis.set_swing_pid(LEFT_SWING, -53, 110);
  chassis.wait_drive() ;
  doubleclaw(false) ;
  chassis.set_drive_pid(-27, 80); // was -40
  chassis.wait_drive();
  set_lift_position(1000, 100);
  doubleclaw(true);
  chassis.set_turn_pid(40, 100);
  chassis.wait_drive();
  intake(127);
  chassis.set_drive_pid(42, 50);
  chassis.wait_drive();
  chassis.set_drive_pid(-47, 127);
  chassis.wait_drive() ;

}
void rightneut()
{
  set_lift_position(-5, 100) ;
  doubleclaw(false);
  chassis.set_drive_pid(35, 127) ;//54
    wing(true) ;
  chassis.wait_until(27);
  chassis.set_drive_pid(-28, 127);
  chassis.wait_until(-27);
    wing(false);
    sixlock(false);
    pros::delay(300);
  chassis.set_swing_pid(LEFT_SWING, 17, 100);
  chassis.wait_drive();
  chassis.set_drive_pid(20, 60);
  chassis.wait_until(15);
  sixlock(true);
  chassis.wait_drive();
  pros::delay(200);
  chassis.set_drive_pid(-5, 110);
  chassis.wait_drive();
  set_lift_position(1000, 127);
  chassis.set_turn_pid(-88, 110);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, 110);
  chassis.wait_drive();
  doubleclaw(true);
  chassis.set_drive_pid(5, 100);
  chassis.wait_drive();
  chassis.set_turn_pid(0, 100);
  chassis.wait_drive();
  intake(127);
  chassis.set_drive_pid(42, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(-47, 127);

}

void Tallsmallneut()
{
  set_lift_position(-5, 100) ;
  doubleclaw(false);
  sixlock(false);
  chassis.set_drive_pid(35, 127) ;//54
    wing(true) ;
  chassis.wait_until(27);
  chassis.set_turn_pid(125, 80);
  chassis.wait_drive();
    wing(false);
    pros::delay(300);
  chassis.set_turn_pid(302, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(35, 127);
  chassis.wait_drive();
  sixlock(true);
  pros::delay(300);
  chassis.set_drive_pid(-55, 127);
  chassis.wait_drive();
}

void tallnuetfake()
{
  set_lift_position(-5, 100) ;
  doubleclaw(false);
  sixlock(false);
  chassis.set_drive_pid(20, 127) ;
  chassis.wait_drive();
  chassis.set_turn_pid(-41, 110);
  chassis.wait_drive();
  chassis.set_drive_pid(33, 90);
  chassis.wait_until(32);
  chassis.set_drive_pid(5, 40);
  chassis.wait_drive();
  sixlock(true);
  pros::delay(300);
  chassis.set_drive_pid(-47, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, 110);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, 110);
  chassis.wait_drive();
  doubleclaw(true);
  chassis.set_drive_pid(5, 100);
  chassis.wait_drive();
  set_lift_position(-1000, 100);
  chassis.set_turn_pid(0, 100);
  chassis.wait_drive();
  intake(127);
  chassis.set_drive_pid(42, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(-47, 127);

}
// -preWing Collection----------------------------------------------------


void neutRushAndAllyLeft ()
{

  sixlock(false) ;
  wing(true) ;

  chassis.set_drive_pid(35, 127) ;
  chassis.wait_until(29) ; // was 28


  set_lift_position(-5, 127) ;
  chassis.set_drive_pid(-43, DRIVE_SPEED) ;
  chassis.wait_until(-37) ; // was -36
  wing(false) ;

  chassis.wait_drive() ;

  chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  chassis.wait_drive() ;


  doubleclaw(false) ;
  chassis.set_drive_pid(-16, DRIVE_SPEED) ; // -13
  chassis.wait_drive() ;


  // grab
  doubleclaw(true) ;

  chassis.set_swing_pid(LEFT_SWING, 25, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  //chassis.set_drive_pid(31, DRIVE_SPEED) ;
  chassis.set_drive_pid(26, DRIVE_SPEED/1.25) ;
  chassis.wait_drive() ;

  sixlock(true) ;
  pros::delay(250) ;
  set_lift_position(700, 100) ;
  intake(127) ;

  chassis.set_turn_pid(80, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(40, DRIVE_SPEED/2) ;
  chassis.wait_drive() ;

}


void winPointAuton () // need test
{
  // prep subsystems
  doubleclaw(false) ;
  set_lift_position(-5, 100) ;
  pros::delay(500) ;

  // into ally
  chassis.set_drive_pid(-6, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // grab
  doubleclaw(true) ;

  // raise lift to prepare for intaking
  set_lift_position(400, 100) ;

  chassis.set_swing_pid(LEFT_SWING, 115, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  //chassis.set_drive_pid(31, DRIVE_SPEED) ;
  chassis.set_drive_pid(26, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  chassis.set_turn_pid(180, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // drive to ally
  intake (127) ;
  chassis.set_drive_pid(67, DRIVE_SPEED/2.5) ; // was 70
  chassis.wait_until(55) ;

  intake(0) ;
  doubleclaw(false) ;

  chassis.wait_drive() ;

  chassis.set_turn_pid(25, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(-28, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // grab + score on ally
  doubleclaw(true) ;

// grab ring row + intake
  chassis.set_drive_pid(5, DRIVE_SPEED) ;
  chassis.wait_drive() ;
  // face neut
  chassis.set_turn_pid(90, DRIVE_SPEED) ; // was 60
  chassis.wait_drive() ;
  intake(127) ;

  chassis.set_drive_pid(30, DRIVE_SPEED/1.75) ;
  chassis.wait_drive() ;
  chassis.set_drive_pid(-35, DRIVE_SPEED) ;
  chassis.wait_drive() ;

}


void wingAndSwingLeftNeutAndTall () // need test
{
  sixlock(false) ;
  doubleclaw(false) ;
  wing(true) ;

  chassis.set_drive_pid(35, 127) ;
  chassis.wait_until(27) ;


  set_lift_position(-5, 127) ;


    chassis.set_swing_pid(RIGHT_SWING, 90, 127) ;
    chassis.wait_drive() ;

    wing(false) ;

    chassis.set_turn_pid(58, DRIVE_SPEED) ; // was 60
    chassis.wait_drive() ;

    chassis.set_drive_pid(70, DRIVE_SPEED) ;
    chassis.wait_until(60) ;

    sixlock(true) ;
    chassis.wait_drive() ;

    set_lift_position(500, DRIVE_SPEED) ;

    chassis.set_drive_pid(-60, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    chassis.set_turn_pid(90, DRIVE_SPEED) ;
    chassis.wait_drive() ;

}

void scoopEnemyZoneRight ()
{
  doubleclaw(false) ;
  sixlock(false) ;
  set_lift_position(300, 100) ;

  chassis.set_drive_pid(-24, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  doubleclaw(true) ;

  chassis.set_drive_pid(12, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  intake(127) ;

  chassis.set_turn_pid(140, DRIVE_SPEED) ; // was 135
  chassis.wait_drive() ;

  chassis.set_drive_pid(65, DRIVE_SPEED/2) ; // was 60
  chassis.wait_drive() ;

  chassis.set_turn_pid(57, DRIVE_SPEED) ; // was 45
  chassis.wait_drive() ;

  wing(true) ;

  chassis.set_drive_pid(90, DRIVE_SPEED/3) ;
  chassis.wait_until(85) ;

  set_lift_position(-5, 100) ;

  chassis.wait_drive () ;

  sixlock(true) ;
  pros::delay(250) ;
  set_lift_position(300, 100) ;

  chassis.set_turn_pid(-33, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(70, DRIVE_SPEED/2) ;
  chassis.wait_drive() ;
}

// -preWing Collection----------------------------------------------------

void noKickStand ()
{
  // sixlock prep
  sixlock(false) ;
  //rush short neut
  //rush short neut
  chassis.set_drive_pid(48, DRIVE_SPEED) ; // was 41

  // // slow down for end
  //  chassis.wait_until(30) ;
  //  chassis.set_max_speed(DRIVE_SPEED/1.5) ;
  // pick up
  chassis.wait_until(45) ;

  //chassis.wait_drive() ;

  sixlock(true) ;
  //pros::delay(500) ;
  // intake(127) ;

  chassis.wait_drive() ;

  //intake(127) ;

  chassis.set_drive_pid(-54, DRIVE_SPEED) ; // was -47
  chassis.wait_drive() ;

  chassis.set_turn_pid(-100, DRIVE_SPEED) ; // was -90
  chassis.wait_drive() ;

  // back into ally
  chassis.set_drive_pid(-16, DRIVE_SPEED) ; // -13
  chassis.wait_drive() ;


  //  set_lift_position(liftMaxHeight(), 100) ;
  // grab
  claw(true) ;
  pros::delay(500) ;

  claw(false) ;

  chassis.set_drive_pid(20, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_turn_pid(-145, DRIVE_SPEED) ; // was -45
  chassis.wait_drive() ;

  // get out
  chassis.set_drive_pid(-26, DRIVE_SPEED) ; // was -29
  chassis.wait_drive() ;


  // face ally
  chassis.set_turn_pid(-100, DRIVE_SPEED) ; // was 0
  chassis.wait_drive() ;

  // set lift to prepare for intaking
  set_lift_position(250, 100) ;

  // drive to ally
  chassis.set_drive_pid(-88, DRIVE_SPEED) ; // -90
  chassis.wait_drive() ;

  // grab + score on ally
  claw(true) ;
  intake(127) ;
  pros::delay(500) ;

  // chassis.set_turn_pid(90, DRIVE_SPEED) ;
  // chassis.wait_drive() ;
  chassis.set_drive_pid(40, DRIVE_SPEED) ;
  chassis.wait_drive() ;
}


void semiGamerRight()
{
  sixlock(false) ;
  //rush short neut
  chassis.set_drive_pid(40, DRIVE_SPEED) ;
  //chassis.wait_until(5) ;
  // // drop intake lift
  // intakeLock(true) ;
  // pros::delay(100) ;
  // intakeLock(false) ;
  // finish drive

  chassis.wait_until(37) ;
  // pick up
  sixlock(true) ;

  chassis.wait_drive() ;


  chassis.set_drive_pid(-24, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_turn_pid(-90, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  //set_lift_position(1700, 100) ;

  chassis.set_drive_pid(-20, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // grab ally
  claw (true) ;
  pros::delay(500) ;

  set_lift_position(700, DRIVE_SPEED) ;

  chassis.set_drive_pid(10, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // turn to face rings
  chassis.set_turn_pid(0, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // pick up rigns

  intake(127) ;

  chassis.set_drive_pid(30, DRIVE_SPEED/5) ;
  chassis.wait_drive() ;

  // retreat
  chassis.set_drive_pid(-40, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  // drop??
  claw(false) ;
//
}

void semiGamerLeft ()
{
  sixlock(false) ;

  claw(false) ;
  clawLift(false) ;

  //rush short neut
  chassis.set_drive_pid(41, DRIVE_SPEED) ;

  // // slow down for end
  //  chassis.wait_until(30) ;
  //  chassis.set_max_speed(DRIVE_SPEED/1.5) ;
  // pick up
  chassis.wait_until(38) ;

  //chassis.wait_drive() ;

  sixlock(true) ;
  set_lift_position(-10, 100) ;
  //pros::delay(500) ;
  // intake(127) ;

  chassis.wait_drive() ;

  // turn
  // chassis.set_turn_pid(5, DRIVE_SPEED) ; // was 10
  // chassis.wait_drive() ;

  // back up
  chassis.set_drive_pid(-47, DRIVE_SPEED) ; // was -45
  chassis.wait_drive() ;

  chassis.set_turn_pid(-90, DRIVE_SPEED) ; // was -80
  chassis.wait_drive() ;


  chassis.set_drive_pid(-16, DRIVE_SPEED) ; // -13
    chassis.wait_drive() ;


    // grab
    claw(true) ;
    clawLift(true) ;
    pros::delay(500) ;
    intake(127) ;


    set_lift_position(700, 100) ;

    // // escape
    // chassis.set_drive_pid(5, DRIVE_SPEED) ;
    // chassis.wait_drive() ;

    //chassis.set_turn_pid(10, DRIVE_SPEED) ;
    chassis.set_swing_pid(LEFT_SWING, 0, DRIVE_SPEED) ;
    chassis.wait_drive() ;


    //intake(-127) ;

    //chassis.set_drive_pid(31, DRIVE_SPEED) ;
    chassis.set_drive_pid(28, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    //intake(127) ;

    chassis.set_turn_pid(80, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    //normalIntake (127) ;
    chassis.set_drive_pid(30, DRIVE_SPEED) ;
    chassis.wait_drive() ;

    //claw(false) ;


}

void skillAuton()
{
  sixlock(false) ;
  set_lift_position(-5, 100) ;

  chassis.set_drive_pid(24, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_turn_pid(90, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(48, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_turn_pid(0, DRIVE_SPEED) ;
  chassis.wait_drive() ;

  chassis.set_drive_pid(48, DRIVE_SPEED/3) ;
  chassis.wait_drive() ;

  sixlock(true) ;

  tallMogo(true) ;
}
// {
//
//       // sets all subsystems into ready positions
//         set_lift_position(-75, DRIVE_SPEED) ;
//         sixlock(false) ;
//         claw(false) ;
//         // pros::delay(500) ;
//
//       // grab ally mogo
//         // drive backwards
//         chassis.set_drive_pid(-6, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//         // grab mogo
//         claw(true) ;
//         pros::delay(500) ;
//
//       // grab neut mogo
//         chassis.set_swing_pid(ez::LEFT_SWING, 100, SWING_SPEED);
//         chassis.wait_drive();
//
//         // lower lift
//         set_lift_position(-75, 100) ;
//
//         // rush
//         chassis.set_drive_pid(46, DRIVE_SPEED) ;
//
//         chassis.wait_until(26) ;
//         chassis.set_max_speed(DRIVE_SPEED/1.5) ;
//
//         chassis.wait_drive() ;
//
//         //grab
//         pros::delay(150) ;
//         sixlock(true) ;
//         pros::delay(250) ;
//
//       // pringle sweeper
//         // prep lift
//         set_lift_position(700, 100) ;
//         // reverse into position
//         chassis.set_drive_pid(-21, DRIVE_SPEED) ; // was -17
//         chassis.wait_drive() ;
//
//         chassis.set_turn_pid(177, DRIVE_SPEED) ; // was 180
//         chassis.wait_drive() ;
//
//
//         // pick up home row rings (10)
//         intake(90) ; // <-- turns on intakes for rest of auton
//
//
//         chassis.set_drive_pid(51, DRIVE_SPEED) ; // was 48
//         chassis.wait_drive() ;
//
//       // platform neut
//         // // turn off intake
//         // intake(0) ;
//         // raise lift
//         set_lift_position(1700, 100) ;
//
//         // might not need
//         // align with platform
//         chassis.set_drive_pid(-13, DRIVE_SPEED) ; // was -10
//         chassis.wait_drive() ;
//
//
//         // turn to face
//         chassis.set_turn_pid(280, DRIVE_SPEED) ; // was 275
//         chassis.wait_drive() ;
//         // into the platform
//         chassis.set_drive_pid(22, DRIVE_SPEED) ; // was 20
//         chassis.wait_drive() ;
//         // lower lift
//         set_lift_position(1050, 100) ;
//         pros::delay(500) ;
//         // drop mogo
//         sixlock(false) ;
//         pros::delay(250) ;
//         // back out and raise lift
//         set_lift_position(1700, 100) ;
//         pros::delay(250) ;
//         chassis.set_drive_pid(-15, DRIVE_SPEED) ; // was -10
//         chassis.wait_drive() ;
//
//       // grab and platform tall neut
//
//         // // align
//         // chassis.set_drive_pid(-5, DRIVE_SPEED) ;
//         // chassis.wait_drive() ;
//
//         // face tall neut
//         set_lift_position(-75, DRIVE_SPEED) ;
//         chassis.set_turn_pid(96, DRIVE_SPEED) ; // was 93
//         chassis.wait_drive() ;
//         // grab
//         chassis.set_drive_pid(19, DRIVE_SPEED/1.75) ; // ws 17 / was DRIVE_SPEED
//         chassis.wait_drive() ;
//         sixlock(true) ;
//         pros::delay(250) ;
//         // lift & turn
//         set_lift_position(1700, DRIVE_SPEED) ;
//         // pros::delay(750) ;
//         chassis.set_turn_pid(250, DRIVE_SPEED/2) ; // was 260
//         chassis.wait_drive() ;
//         // drive forward
//         chassis.set_drive_pid(15, DRIVE_SPEED/1.5) ;
//         chassis.wait_drive() ;
//
//       // platform tall neut
//         // set_lift_position(1700, DRIVE_SPEED) ;
//         // pros::delay(750) ;
//         chassis.set_turn_pid(270, DRIVE_SPEED/2) ;
//         chassis.wait_drive() ;
//         chassis.set_drive_pid(25, DRIVE_SPEED/1.5) ; // was 32
//         chassis.wait_drive() ;
//         // lower
//         set_lift_position(1100, 100) ;
//         pros::delay(1000) ;
//         //drop
//         sixlock(false) ;
//         pros::delay(500) ;
//         // back out
//         set_lift_position(1700, 100) ;
//         chassis.set_drive_pid(-5, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//       // grab ally
//         // face
//         chassis.set_turn_pid(180, DRIVE_SPEED) ; // was 178
//         chassis.wait_drive () ;
//
//
//         // prep lift & intake
//         set_lift_position(-75, 100) ;
//
//         // drive to ally
//         chassis.set_drive_pid(70, DRIVE_SPEED/1.2) ; // was 50 ;was DRIVE_SPEED
//         //chassis.wait_drive() ;
//
//         pros::delay(3000) ;
//
//         // grab
//         sixlock(true) ;
//         pros::delay(250) ;
//
//       // pringles and traveling to other side
//         set_lift_position(400, 100) ;
//         // chassis.set_drive_pid(-5, DRIVE_SPEED) ;
//         // chassis.wait_drive() ;
//
// // skipped---------------------------
// /*
// cant be:
// build (tested driver)
// code (dry runs are fine)
// hardware fine dry rns and driver
//
// */
//         chassis.set_turn_pid(90, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//         // intake(80) ;
//         // pringle pick up + drive to other side
//
//         chassis.set_drive_pid(62, DRIVE_SPEED/1.2) ; // was 62, was DRIVE_SPEED
//         chassis.wait_drive() ;
//
// // -----------------------------------------
//
//       // ring intake + plat ally goals
//         chassis.set_turn_pid(0, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//         set_lift_position(1700, 50) ;
//
//         //align in front of platform
//         chassis.set_drive_pid(59, DRIVE_SPEED/1.4) ; // was 57, was DRIVE_SPEED
//         chassis.wait_drive() ;
//
//         // face platform
//         chassis.set_turn_pid(90, DRIVE_SPEED) ; // was -270
//         chassis.wait_drive() ;
//
//         // plat ally1
//         chassis.set_drive_pid(22, DRIVE_SPEED) ; // was 16
//         chassis.wait_drive() ;
//
//         set_lift_position(1100, DRIVE_SPEED) ;
//         pros::delay(250) ;
//         sixlock(false) ;
//         pros::delay(250) ;
//
//         // get out
//         set_lift_position(1700, 100) ;
//         chassis.set_drive_pid(-20, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//       // plat ally2
//         // drop goal and lower lift
//         set_lift_position(0, 100) ;
//         claw(false) ;
//         chassis.set_drive_pid(12, DRIVE_SPEED) ; // was 11
//         chassis.wait_drive() ;
//
//         // turn around
//         chassis.set_turn_pid(-90, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//         // drive into
//         chassis.set_drive_pid(15, DRIVE_SPEED) ; // was 12
//         chassis.wait_drive() ;
//         sixlock(true) ;
//         pros::delay(250) ;
//
//         set_lift_position(1700, 100) ;
//         // face plat
//         chassis.set_turn_pid(110, TURN_SPEED) ; // was DRIVE_SPEED
//         chassis.wait_drive() ;
//         // drive into - problem line
//         chassis.set_drive_pid(26, DRIVE_SPEED) ; // was 25
//         pros::delay(1000) ;
//         // lower and plat
//         set_lift_position(1100, 100) ;
//         pros::delay(500) ;
//         sixlock(false) ;
//
//         // escape
//         set_lift_position(1700, 100) ;
//         chassis.set_drive_pid(-10, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//       // grab + plat neut
//         // face
//         chassis.set_turn_pid(220, DRIVE_SPEED) ; // was 222
//         chassis.wait_drive() ;
//
//         // lower lift
//         set_lift_position(0, 127) ;
//         //set_lift_position(300, 127) ;
//         chassis.set_drive_pid(50, DRIVE_SPEED) ; // was 42
//         chassis.wait_until(27) ; // was 25
//         chassis.set_max_speed(DRIVE_SPEED/1.5) ;
//         chassis.wait_drive() ;
//
//         // pick up neut
//         sixlock(true) ;
//         pros::delay(250) ;
//
//         // turn + go back to plat
//         set_lift_position(1500, 100) ;
//         chassis.set_turn_pid(53, DRIVE_SPEED) ; // was 55
//         chassis.wait_drive() ;
//
//         // drive to plat
//         chassis.set_drive_pid(59, DRIVE_SPEED) ; // was 59
//         chassis.wait_drive() ;
//         // // face plat
//         // chassis.set_turn_pid(87, DRIVE_SPEED) ; // was 90
//         // chassis.wait_drive() ;
//         // // drive in
//         // chassis.set_drive_pid(10, DRIVE_SPEED) ; // was 10
//         // chassis.wait_drive() ;
//
//         set_lift_position(1100, 100) ;
//         pros::delay(500) ;
//         sixlock(false) ;
//         pros::delay(250) ;
//
//         // escape
//         set_lift_position(1700, 100) ;
//         chassis.set_drive_pid(-6, DRIVE_SPEED) ; // was -7 , -5
//         chassis.wait_drive() ;
//       // grab ally goal
//         chassis.set_turn_pid(0, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//         set_lift_position(0, 100) ; // was 100
//         // pros::delay(500) ;
//
//         // into the wall
//         chassis.set_drive_pid(69, DRIVE_SPEED/1.2) ; // was 69
//
//         // chassis.wait_until(30) ;
//         // set_lift_position(0, 100) ;
//
//         pros::delay(3000); // was 3000
//
//
//         sixlock(true) ;
//         pros::delay(250) ;
//
//       // speed run plat
//         chassis.set_turn_pid(-117, DRIVE_SPEED) ; // was -115
//         chassis.wait_drive() ;
//
//         set_lift_position(1400, 100) ;
//         chassis.set_drive_pid(105, DRIVE_SPEED) ;
//         chassis.wait_drive() ;
//
//         // drop
//         sixlock(false) ;
//         pros::delay(250) ;
//
//         chassis.set_drive_pid(-20, DRIVE_SPEED) ;
//
// }

void blank ()
{}
