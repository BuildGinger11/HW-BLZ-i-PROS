#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 110;  // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                              // If this is 127 and the robot tries to heading correct, it's only correcting by
                              // making one side slower.  When this is 87%, it's correcting by making one side
                              // faster and one side slower, giving better heading correction.
const int TURN_SPEED = 90;
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


void Han_Solo(){

flywheel(120);
pros::delay(2500);
set_intake(110);
set_topintake(0);

//get roller
chassis.set_drive_pid(3, 90);
chassis.wait_drive();

set_intake(0);

chassis.set_drive_pid(-12, 90);
pros::delay(100);
set_intake(-127);
set_topintake(-127);
pros::delay(150);
set_intake(0);
set_topintake(0);
chassis.wait_drive();

//get in shooting position
chassis.set_turn_pid(-12, 80);
chassis.wait_drive();

//shoot two discs
set_indexer(OUT);
set_topintake(127);
set_intake(127);
pros::delay(110);
flywheel(123);
pros::delay(700);
set_topintake(50);;
set_indexer(IN);
set_intake(0);

// get another disc
chassis.set_drive_pid(8, 90);
chassis.wait_drive();

pros::delay(400);

chassis.set_turn_pid(-131, 80);
chassis.wait_drive();

set_intake(127);
chassis.set_drive_pid(20, 80);
chassis.wait_drive();

chassis.set_drive_pid(44.5, 60);
chassis.wait_drive();
flywheel(85);
pros::delay(500);

// get to shooting position
chassis.set_turn_pid(-44.9, 70);
chassis.wait_drive();
set_intake(0);

chassis.set_drive_pid(-12.2, 80);
chassis.wait_drive();

//shoot discs!!
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(150);
  flywheel(96);
  set_intake(127);
  pros::delay(700);

  set_indexer(IN);
  set_intake(0);
  set_topintake(0);
  pros::delay(300);

//go to roller
chassis.set_drive_pid(12, 80);
chassis.wait_drive();

/*
chassis.set_turn_pid(-136, 90);
chassis.wait_drive();

//intake and outtake discs on the way
flywheel(127);
set_indexer(OUT);
set_intake(127);
set_topintake(127);
chassis.set_drive_pid(64, 120);
pros::delay(1100);
chassis.wait_drive();

//turn roller!
chassis.set_turn_pid(-90, 100);
chassis.wait_drive();

set_intake(90);
chassis.set_drive_pid(4.5, 115);
chassis.wait_drive();
set_intake(0);
*/
/*
//turn and shoot two discs
chassis.set_drive_pid(-7, 100);
chassis.wait_drive();

chassis.set_turn_pid(-83, 90);
chassis.wait_drive();

set_indexer(OUT);
set_topintake(127);
pros::delay(500);
flywheel(99);
pros::delay(700);

flywheel(95);
set_intake(127);

pros::delay(950);

set_indexer(IN);
set_intake(0);
set_topintake(0);
*/

}

void help_me_ObiWan () {

chassis.set_drive_pid(25, 90);
chassis.wait_drive();

chassis.set_turn_pid(90, 90);
chassis.wait_drive();

set_intake(90);

chassis.set_drive_pid(11, 90);
pros::delay(75);
set_intake(0);

}








//=================================================================================================================

//=================================================================================================================

//=================================================================================================================



void rogue_one(){

//get match load
set_indexer(OUT);
pros::delay(300);
flywheel(-69);
set_topintake(-60);
set_intake(-30);
pros::delay(400);
set_intake(0);
pros::delay(900);
set_indexer(IN);
flywheel(79);
set_topintake(40);
set_intake(0);
pros::delay(900);

// back up and turn
chassis.set_drive_pid(8, 80);
chassis.wait_drive();

chassis.set_turn_pid(-91.5, 80);
chassis.wait_drive();

// shoot 3 discs
set_indexer(OUT);
set_topintake(127);
pros::delay(300);
set_flywheel(83);
set_intake(127);
pros::delay(950);

set_indexer(IN);
set_intake(0);
set_topintake(0);

//get back to match load position
chassis.set_drive_pid(-1.9, 90);
chassis.wait_drive();

chassis.set_turn_pid(-1, 80);
chassis.wait_drive();

chassis.set_drive_pid(-10.4, 70);

//get match load
set_indexer(OUT);
pros::delay(300);
flywheel(-60);
set_topintake(-50);
set_intake(-25);
pros::delay(800);
set_intake(0);
pros::delay(2100);
set_indexer(IN);
flywheel(77);
set_topintake(40);
set_intake(0);
pros::delay(900);

// back up and turn
chassis.set_drive_pid(8, 80);
chassis.wait_drive();

chassis.set_turn_pid(-91.5, 80);
chassis.wait_drive();

// shoot another 3 discs x1
set_indexer(OUT);
set_topintake(127);
pros::delay(300);
set_flywheel(79);
set_intake(127);
pros::delay(950);

set_indexer(IN);
set_intake(0);
set_topintake(0);

//get back to match load position
chassis.set_drive_pid(-1.9, 90);
chassis.wait_drive();

chassis.set_turn_pid(-1, 80);
chassis.wait_drive();

chassis.set_drive_pid(-11, 70);

//get match load
set_indexer(OUT);
pros::delay(300);
flywheel(-63);
set_topintake(-50);
set_intake(-25);
pros::delay(900);
set_intake(0);
pros::delay(2000);
set_indexer(IN);
flywheel(77);
set_topintake(30);
set_intake(0);
pros::delay(900);

// back up and turn
chassis.set_drive_pid(8, 80);
chassis.wait_drive();

chassis.set_turn_pid(-91.5, 80);
chassis.wait_drive();

// shoot another 3 discs x2
set_indexer(OUT);
set_topintake(127);
pros::delay(300);
set_flywheel(79);
set_intake(127);
pros::delay(950);

set_indexer(IN);
set_intake(0);
set_topintake(0);

//get to roller #1
chassis.set_turn_pid(-86, 80);
chassis.wait_drive();

chassis.set_drive_pid(39, 90);
chassis.wait_drive();

chassis.set_turn_pid(-183, 80);
chassis.wait_drive();

//turn roller
set_intake(90);
pros::delay(400);

chassis.set_drive_pid(6, 90);
chassis.wait_drive();
pros::delay(300);

//drive to roller #2
chassis.set_drive_pid(-23, 70);
chassis.wait_drive();

chassis.set_turn_pid(-90, 80);
chassis.wait_drive();

set_intake(90);
chassis.set_drive_pid(18, 80);
set_topintake(40);
chassis.wait_drive();
pros::delay(400);

//back away
chassis.set_drive_pid(-11, 90);
chassis.wait_drive();

chassis.set_swing_pid(LEFT_SWING, 45, 80);
chassis.wait_drive();

flywheel(81);
//collect 3 discs
set_intake(127);
set_topintake(40);
chassis.set_drive_pid(66, 90);
chassis.wait_drive();

chassis.set_drive_pid(-10, 100);
chassis.wait_drive();

//get in position to shoot
chassis.set_turn_pid(135, 80);
chassis.wait_drive();

//shoot!!
set_indexer(OUT);
set_topintake(127);
pros::delay(300);
flywheel(80);
set_intake(127);
pros::delay(1150);

set_indexer(IN);
set_intake(0);
set_topintake(40);
flywheel(96);

//get next 3 discs
chassis.set_turn_pid(43, 80);
chassis.wait_drive();
set_intake(127);

chassis.set_drive_pid(34, 88);
chassis.wait_drive();

set_intake(127);
chassis.set_drive_pid(19, 100);
chassis.wait_drive();

//get to shooting position
chassis.set_turn_pid(93, 90);
chassis.wait_drive();

//shoot!!
set_indexer(OUT);
set_intake(115);
set_topintake(127);
pros::delay(300);
flywheel(940);
set_intake(127);
pros::delay(1100);

set_indexer(IN);
set_intake(0);
set_topintake(0);

//go do roller #3
chassis.set_drive_pid(17, 100);
chassis.wait_drive();

chassis.set_turn_pid(0, 90);
chassis.wait_drive();

set_intake(90);
pros::delay(200);

chassis.set_drive_pid(13, 100);
chassis.wait_drive();
pros::delay(300);

//do roller #4
chassis.set_drive_pid(-13, 90);
chassis.wait_drive();

chassis.set_turn_pid(90, 90);
chassis.wait_drive();

set_intake(90);
chassis.set_drive_pid(26, 100);
chassis.wait_drive();
pros::delay(300);

//get in position for expansion
chassis.set_drive_pid(-20, 1000);
chassis.wait_drive();

chassis.set_turn_pid(43, 80);
chassis.wait_drive();

chassis.set_drive_pid(8, 120);
chassis.wait_drive();

//shoot expansion!!
set_expansion(UP);

}


void speed_test(){

//speed 1 - 105rpm
  flywheel(105);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);


//speed 2 - 110rpm
  flywheel(110);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);

//speed 3 - 115rpm
  flywheel(115);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);

//speed 4 - 120pm
  flywheel(120);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);

//speed 5 - 125rpm
  flywheel(125);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);


}

void speed_test2(){

/*
//speed 1 - 118rpm
  flywheel(118);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);
  set_topintake(40);
*/

//speed 2 - 119rpm
  flywheel(119);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);
  set_topintake(40);

/*
//speed 3 - 120rpm
  flywheel(120);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);
  pros::delay(4000);
  set_indexer(IN);
  set_topintake(40);

//speed 4 - 121pm
  flywheel(121);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);
  set_topintake(40);

//speed 5 - 122rpm
  flywheel(122);
  pros::delay(4000);
  set_indexer(OUT);
  set_topintake(127);
  pros::delay(6000);
  flywheel(-20);
  set_topintake(-20);;
  pros::delay(4000);
  set_indexer(IN);
  set_topintake(40);
*/
}
