#region VARIABLES
// CmdMessenger library available from https://github.com/dreamcat4/cmdmessenger
#include <CmdMessenger.h>

// Base64 library available from https://github.com/adamvr/arduino-base64
#include <Base64.h>

// Streaming4 library available from http://arduiniana.org/libraries/streaming/
#include <Streaming.h>

#include <Bounce.h>
#include "Pins.h"
// Mustnt conflict / collide with our message payload data. Fine if we use base64 library ^^ above
char field_separator = ',';
char command_separator = ';';

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);


//Pinball hardware
int noOfButtons=36;
Bounce buttons[]= Bounce[noOfButtons]; // Number of buttons

//Pinball Stuff;
int m_score, 
m_balls_in_game = 5,
m_current_ball,
m_players_in_game,
m_current_player;
boolean s_lites_rollover_top_left,
s_lites_rollover_top_right,
s_lites_outhole,
s_lites_ball_return_lane_left,
s_lites_ball_return_lane_right,
s_lites_on_yellow_bumpers,
s_lites_on_green_bumpers,
s_up_post,
s_lites_center_target,
s_start_button,
s_tilt,
s_game_running,;


// ------------------ C M D  L I S T I N G ( T X / R X ) ---------------------
// We can define up to a default of 50 cmds total, including both directions (send + recieve)
// and including also the first 4 default command codes for the generic error handling.
// If you run out of message slots, then just increase the value of MAXCALLBACKS in CmdMessenger.h
// Commands we send from the Arduino to be received on the PC

enum
{
  kCOMM_ERROR    = 000, // Lets Arduino report serial port comm error back to the PC (only works for some comm errors)
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // After opening the comm port, send this cmd 02 from PC to check arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd, or cmd not recognised
  kSEND_CMDS_END,       // Mustnt delete this line
};

messengerCallbackFunction messengerCallbacks[] = 
{
  hit_rollover_top_left, 			//4
  hit_rollover_top_right, 			//5
  hit_return_lane_left, 			//6
  hit_return_lane_right, 			//7
  hit_lites_ball_return_lane_left, 	        //8
  hit_lites_ball_return_lane_right,             //9
  hit_lites_on_yellow_bumpers, 		        //10
  hit_lites_on_green_bumpers, 		        //11
  hit_rubber_top_left, 				//12
  hit_rubber_top_right, 			//13
  hit_rubber_middle_left, 			//14
  hit_rubber_middle_right, 			//15
  hit_red_bumper, 			        //16
  hit_yellow_bumper_left, 			//17
  hit_yellow_bumper_right, 			//18
  hit_green_bumper_left, 			//19
  hit_green_bumper_right, 			//20
  hit_bumper_top_left, 				//21
  hit_bumper_top_right, 			//22
  hit_up_post_left, 				//23
  hit_up_post_right, 				//24
  hit_lites_center_target_left, 	        //25
  hit_lites_center_target_right, 	        //26
  hit_center_target, 				//27
  hit_outhole, 				        //28
  hit_slingshot_left, 				//29
  hit_slingshot_right, 				//30
  hit_flipper_left, 				//31
  hit_flipper_right, 				//32
  hit_down_post_left, 				//33
  hit_down_post_right, 				//34
  hit_score_100_field, 				//35
  hit_ball_out_of_field, 			//36
  hit_start_button, 				//37
  hit_tilt_1, 				        //38
  hit_tilt_2, 					//39
  hit_tilt_3, 					//40
  print_status,					//41 Prints out tons of shit and stuff
  NULL
};
#endregion
#region CALLBACK METHODS
void hit_rollover_top_left(){
  cmdMessenger.sendCmd(kACK,"Something hit rollover top left");
  if(s_lites_rollover_top_left) m_score += 3000;
  else m_score += 1000;
  printScore();
}
void hit_rollover_top_right(){
  cmdMessenger.sendCmd(kACK,"Something hit rollover top right");
  if(s_lites_rollover_top_right) m_score += 3000;
  else m_score += 1000;
  printScore();
}
void hit_return_lane_left(){
  cmdMessenger.sendCmd(kACK,"Something hit return lane left");
  if(s_lites_ball_return_lane_left){
	 s_lites_ball_return_lane_left = false;
	 triggerBallReturnLeft();
	}
  printScore();
}
void hit_return_lane_right(){
  cmdMessenger.sendCmd(kACK,"Something hit return lane right");
  if(s_lites_ball_return_lane_right){
	 s_lites_ball_return_lane_right = false;
	 triggerCloseGate();
	}
  printScore();
}
void hit_lites_ball_return_lane_left(){
  cmdMessenger.sendCmd(kACK,"Something hit lites ball return lane left");
  s_lites_ball_return_lane_left = true;
  printScore();
}
void hit_lites_ball_return_lane_right(){
  cmdMessenger.sendCmd(kACK,"Something hit lites ball return lane right");
  s_lites_ball_return_lane_right = true;
  printScore();
}
void hit_lites_on_yellow_bumpers(){
  cmdMessenger.sendCmd(kACK,"Something hit lites on yellow bumpers");
  s_lites_on_yellow_bumpers=true;
  printScore();
}
void hit_lites_on_green_bumpers(){
  cmdMessenger.sendCmd(kACK,"Something hit lites on green bumpers");
  s_lites_on_green_bumpers=true;
  printScore();
}
void hit_rubber_top_left(){
  cmdMessenger.sendCmd(kACK,"Something hit rubber top left");
  m_score += 10;
  printScore();
}
void hit_rubber_top_right(){
  cmdMessenger.sendCmd(kACK,"Something hit rubber top right");
  m_score += 10;
  printScore();
}

void hit_rubber_middle_left(){
  cmdMessenger.sendCmd(kACK,"Something hit rubber middle left");
  m_score +=10;
  printScore();
}
void hit_rubber_middle_right(){
  cmdMessenger.sendCmd(kACK,"Something hit rubber middle right");
  m_score +=10;
  printScore();
}
void hit_red_bumper(){
  cmdMessenger.sendCmd(kACK,"Something hit red bumper");
  m_score +=10;
  printScore();
}
void hit_yellow_bumper_left(){
  cmdMessenger.sendCmd(kACK,"Something hit yellow bumper left");
  if(s_lites_on_yellow_bumpers) m_score += 100;
  else m_score += 10;
  printScore();
}
void hit_yellow_bumper_right(){
  cmdMessenger.sendCmd(kACK,"Something hit yellow bumper right");
  if(s_lites_on_yellow_bumpers) m_score += 100;
  else m_score += 10;
  printScore();
}
void hit_green_bumper_left(){
  cmdMessenger.sendCmd(kACK,"Something hit green bumper left");
  if(s_lites_on_green_bumpers) m_score += 100;
  else m_score += 10;
  printScore();
}
void hit_green_bumper_right(){
  cmdMessenger.sendCmd(kACK,"Something hit green bumper right");
  if(s_lites_on_green_bumpers) m_score += 100;
  else m_score += 10;
  printScore();
}
void hit_bumper_top_left(){
  cmdMessenger.sendCmd(kACK,"Something hit bumper top left");
  changeActiveLeft();
  printScore();
}
void hit_bumper_top_right(){
  cmdMessenger.sendCmd(kACK,"Something hit bumper top right");
  changeActiveRight();
  printScore();
}
void hit_up_post_left(){
  cmdMessenger.sendCmd(kACK,"Something hit up post left");
  s_up_post = true;
  triggerPostUp();
  printScore();
}
void hit_up_post_right(){
  cmdMessenger.sendCmd(kACK,"Something hit up post right");
  s_up_post = true;
  triggerPostUp();
  printScore();
}
void hit_lites_center_target_left(){
  cmdMessenger.sendCmd(kACK,"Something hit lites center target left");
  s_lites_center_target = true;
  printScore();
}
void hit_lites_center_target_right(){
  cmdMessenger.sendCmd(kACK,"Something hit lites center target right");
  s_lites_center_target = true;
  printScore();
}
void hit_center_target(){
  cmdMessenger.sendCmd(kACK,"Something hit center target");
  if(s_lites_center_target){
	  += m_center_target_score;
	  if(s_lites_ball_return_lane_right) triggerOpenGate();
  }
  printScore();
}
void hit_outhole(){
  cmdMessenger.sendCmd(kACK,"Something hit outhole");
  if(s_lites_outhole) m_score += 5000;
  else m_score += 500;
  triggerOuthole();
  printScore();
}
void hit_slingshot_left(){
  cmdMessenger.sendCmd(kACK,"Something hit slingshot left");
  m_score += 10;
  triggerSlingshotLeft();
  printScore();
}
void hit_slingshot_right(){
  cmdMessenger.sendCmd(kACK,"Something hit slingshot right");
  m_score += 10;
  triggerSlingshotRight();
  printScore();
}
void hit_flipper_left(){
  cmdMessenger.sendCmd(kACK,"Something hit flipper left");
  changeActiveLeft();
  printScore();
}
void hit_flipper_right(){
  cmdMessenger.sendCmd(kACK,"Something hit flipper right");
  changeActiveRight();
  printScore();
}
void hit_down_post_left(){
  cmdMessenger.sendCmd(kACK,"Something hit down post left");
  triggerPostDown();
  printScore();
}
void hit_down_post_right(){
  cmdMessenger.sendCmd(kACK,"Something hit down post right");
  triggerPostDown();
  printScore();
}
void hit_score_100_field(){
  cmdMessenger.sendCmd(kACK,"Something hit score 100 field");
  m_score += 100;
  printScore();
}
void hit_ball_out_of_field(){
  cmdMessenger.sendCmd(kACK,"Something hit ball out of field");
  if(m_current_player < m_players_in_game){
	  if(m_current_ball < m_balls_in_game){
		  m_current_player++;
		  
	}  
  printScore();
}
}
void hit_start_button(){
  cmdMessenger.sendCmd(kACK,"Something hit start button");
  triggerBallToLaunch()
  if(m_players_in_game <= 4) m_players_in_game++;
  triggerResetScore(); 
  printScore();
}
void hit_tilt_1(){
  cmdMessenger.sendCmd(kACK,"Something hit tilt 1");
  s_tilt = true;
  printScore();
}
void hit_tilt_2(){
  cmdMessenger.sendCmd(kACK,"Something hit tilt 2");
  s_tilt = true;
  printScore();
}
void hit_tilt_3(){
  cmdMessenger.sendCmd(kACK,"Something hit tilt 3");
  s_tilt = true;
  printScore();
}
void print_status(){
		cmdMessenger.sendCmd(kACK,"------ Status report -------");
		printScore();
		serial.print("s_lites_rollover_top_left: ");serial.println(s_lites_rollover_top_left);
		serial.print("s_lites_rollover_top_right: ");serial.println(s_lites_rollover_top_right);
		serial.print("s_lites_ball_return_lane_left: ");serial.println(s_lites_ball_return_lane_left);
		serial.print("s_lites_ball_return_lane_right: ");serial.println(s_lites_ball_return_lane_right);
		serial.print("s_lites_on_yellow_bumpers: ");serial.println(s_lites_on_yellow_bumpers);
		serial.print("s_up_post: ");serial.println(s_up_post);
		serial.print("s_lites_center_target: ");serial.println(s_lites_center_target);
		serial.print("s_start_button: ");serial.println(s_start_button);
		serial.print("s_tilt: ");serial.println(s_tilt);
}

#endregion 
#region DEFAULT CALLBACKS

void arduino_ready()
{
  // In response to ping. We just send a throw-away Acknowledgement to say "im alive"
  cmdMessenger.sendCmd(kACK,"Arduino ready");
}

void unknownCmd()
{
  // Default response for unknown commands and corrupt messages
  cmdMessenger.sendCmd(kERR,"Unknown command");
}
#endregion
#region SETUP
void attach_callbacks(messengerCallbackFunction* callbacks)
{
  int i = 0;
  int offset = kSEND_CMDS_END;
  while(callbacks[i])
  {
    cmdMessenger.attach(offset+i, callbacks[i]);
    i++;
  }
}

void setup() 
{
  // Listen on serial connection for messages from the pc
  // Serial.begin(57600);  // Arduino Duemilanove, FTDI Serial
  Serial.begin(115200); // Arduino Uno, Mega, with AT8u2 USB

  // cmdMessenger.discard_LF_CR(); // Useful if your terminal appends CR/LF, and you wish to remove them
  cmdMessenger.print_LF_CR();   // Make output more readable whilst debugging in Arduino Serial Monitor

  // Attach default / generic callback methods
  cmdMessenger.attach(kARDUINO_READY, arduino_ready);
  cmdMessenger.attach(unknownCmd);

  // Attach my application's user-defined callback methods
  attach_callbacks(messengerCallbacks);

  arduino_ready();
    s_lites_rollover_top_left = false;
    s_lites_outhole = true;
    s_lites_rollover_top_right = false;
  //changeActiveRight();
  
  // buttons
  for(int i = 0; i <= noOfButtons; i++){
	  buttons[i] = Bounce(i+B_ROLLOVER_TOP_LEFT, 5);
	  pinMode(i+B_ROLLOVER_TOP_LEFT, INPUT);
  }
}
#endregion 
#region MAIN

void loop() 
{
  cmdMessenger.feedinSerialData();
	
  buttonHandling();
	
}

void printScore(){
  Serial.print("Score: ");
  Serial.println(m_score);
}

void changeActiveRight(){
  if(s_lites_rollover_top_left){
    s_lites_rollover_top_left = false;
    s_lites_outhole = true;
    s_lites_rollover_top_right = false;
  }
  else if(s_lites_outhole){
    s_lites_rollover_top_left = false;
    s_lites_outhole = false;
    s_lites_rollover_top_right = true;
  } 
  else if(s_lites_rollover_top_right){
    s_lites_rollover_top_left = true;
    s_lites_outhole = false;
    s_lites_rollover_top_right = false;
  }
  else{
    s_lites_rollover_top_left = true;
    s_lites_outhole = false;
    s_lites_rollover_top_right = false;
  }
}

void changeActiveLeft(){
  if(s_lites_rollover_top_left){
    s_lites_rollover_top_left = false;
    s_lites_outhole = false;
    s_lites_rollover_top_right = true;
  }
  else if(s_lites_outhole){
    s_lites_rollover_top_left = true;
    s_lites_outhole = false;
    s_lites_rollover_top_right = false;
  } 
  else if(s_lites_rollover_top_right){
    s_lites_rollover_top_left = false;
    s_lites_outhole = true;
    s_lites_rollover_top_right = false;
  }
  else{
    s_lites_rollover_top_left = true;
    s_lites_outhole = false;
    s_lites_rollover_top_right = false;
  }
}
#endregion
#region HARDWARE
void triggerBallReturnLeft(){}
void triggerOpenGate(){}
void triggerCloseGate(){}
void triggerOuthole(){}
void triggerPostUp(){}
void triggerPostDown(){}
void triggerSlingshotLeft(){}
void triggerSlingshotRight(){}
void triggerFlipperLeft(){}
void triggerFlipperRight(){}
void triggerBallToLaunch(){}
void triggerResetScore(){}
void buttonHandling(){
   if (buttons[B_ROLLOVER_TOP_LEFT-4].update() ) {
		if (buttons[B_ROLLOVER_TOP_LEFT-4].read() == HIGH) {
			hit_rollover_top_left();
     }
   }
   if (buttons[B_ROLLOVER_TOP_RIGHT-4].update() ) {
		if (buttons[B_ROLLOVER_TOP_RIGHT-4].read() == HIGH) {
			hit_rollover_top_right();
     }
   }
   if (buttons[B_RETURN_LANE_LEFT-4].update() ) {
		if (buttons[B_RETURN_LANE_LEFT-4].read() == HIGH) {
			hit_return_lane_left();
     }
   }
   if (buttons[B_RETURN_LANE_RIGHT-4].update() ) {
		if (buttons[B_RETURN_LANE_RIGHT-4].read() == HIGH) {
			hit_return_lane_right();
     }
   }
   if (buttons[B_LITES_BALL_RETURN_LANE_LEFT-4].update() ) {
		if (buttons[B_LITES_BALL_RETURN_LANE_LEFT-4].read() == HIGH) {
			hit_lites_ball_return_lane_left();
     }
   }
   if (buttons[B_LITES_BALL_RETURN_LANE_RIGHT-4].update() ) {
		if (buttons[B_LITES_BALL_RETURN_LANE_RIGHT-4].read() == HIGH) {
			hit_lites_ball_return_lane_right();
     }
   }
   if (buttons[B_LITES_ON_YELLOW_BUMPERS-4].update() ) {
		if (buttons[B_LITES_ON_YELLOW_BUMPERS-4].read() == HIGH) {
			hit_lites_on_yellow_bumpers();
     }
   }
   if (buttons[B_LITES_ON_GREEN_BUMPERS-4].update() ) {
		if (buttons[B_LITES_ON_GREEN_BUMPERS-4].read() == HIGH) {
			hit_lites_on_green_bumpers();
     }
   }
   if (buttons[B_RUBBER_TOP_LEFT-4].update() ) {
		if (buttons[B_RUBBER_TOP_LEFT-4].read() == HIGH) {
			hit_rubber_top_left();
     }
   }
   if (buttons[B_RUBBER_TOP_RIGHT-4].update() ) {
		if (buttons[B_RUBBER_TOP_RIGHT-4].read() == HIGH) {
			hit_rubber_top_right();
     }
   }
   if (buttons[B_RUBBER_MIDDLE_LEFT-4].update() ) {
		if (buttons[B_RUBBER_MIDDLE_LEFT-4].read() == HIGH) {
			hit_rubber_middle_left();
     }
   }
   if (buttons[B_RUBBER_MIDDLE_RIGHT-4].update() ) {
		if (buttons[B_RUBBER_MIDDLE_RIGHT-4].read() == HIGH) {
			hit_rubber_middle_right();
     }
   }
   if (buttons[B_RED_BUMPER-4].update() ) {
		if (buttons[B_RED_BUMPER-4].read() == HIGH) {
			hit_red_bumper();
     }
   }
   if (buttons[B_YELLOW_BUMPER_LEFT-4].update() ) {
		if (buttons[B_YELLOW_BUMPER_LEFT-4].read() == HIGH) {
			hit_yellow_bumper_left();
     }
   }
   if (buttons[B_YELLOW_BUMPER_RIGHT-4].update() ) {
		if (buttons[B_YELLOW_BUMPER_RIGHT-4].read() == HIGH) {
			hit_yellow_bumper_right();
     }
   }
   if (buttons[B_GREEN_BUMPER_LEFT-4].update() ) {
		if (buttons[B_GREEN_BUMPER_LEFT-4].read() == HIGH) {
			hit_green_bumper_left();
     }
   }
   if (buttons[B_GREEN_BUMPER_RIGHT-4].update() ) {
		if (buttons[B_GREEN_BUMPER_RIGHT-4].read() == HIGH) {
			hit_green_bumper_right();
     }
   }
   if (buttons[B_BUMPER_TOP_LEFT-4].update() ) {
		if (buttons[B_BUMPER_TOP_LEFT-4].read() == HIGH) {
			hit_bumper_top_left();
     }
   }
   if (buttons[B_BUMPER_TOP_RIGHT-4].update() ) {
		if (buttons[B_BUMPER_TOP_RIGHT-4].read() == HIGH) {
			hit_bumper_top_right();
     }
   }
   if (buttons[B_UP_POST_LEFT-4].update() ) {
		if (buttons[B_UP_POST_LEFT-4].read() == HIGH) {
			hit_up_post_left();
     }
   }
   if (buttons[B_UP_POST_RIGHT-4].update() ) {
		if (buttons[B_UP_POST_RIGHT-4].read() == HIGH) {
			hit_up_post_right();
     }
   }
   if (buttons[B_LITES_CENTER_TARGET_LEFT-4].update() ) {
		if (buttons[B_LITES_CENTER_TARGET_LEFT-4].read() == HIGH) {
			hit_lites_center_target_left();
     }
   }
   if (buttons[B_LITES_CENTER_TARGET_RIGHT-4].update() ) {
		if (buttons[B_LITES_CENTER_TARGET_RIGHT-4].read() == HIGH) {
			hit_lites_center_target_right();
     }
   }
   if (buttons[B_CENTER_TARGET-4].update() ) {
		if (buttons[B_CENTER_TARGET-4].read() == HIGH) {
			hit_center_target();
     }
   }
   if (buttons[B_OUTHOLE-4].update() ) {
		if (buttons[B_OUTHOLE-4].read() == HIGH) {
			hit_outhole();
     }
   }
   if (buttons[B_SLINGSHOT_LEFT-4].update() ) {
		if (buttons[B_SLINGSHOT_LEFT-4].read() == HIGH) {
			hit_slingshot_left();
     }
   }
   if (buttons[B_SLINGSHOT_RIGHT-4].update() ) {
		if (buttons[B_SLINGSHOT_RIGHT-4].read() == HIGH) {
			hit_slingshot_right();
     }
   }
   if (buttons[B_FLIPPER_LEFT-4].update() ) {
		if (buttons[B_FLIPPER_LEFT-4].read() == HIGH) {
			hit_flipper_left();
     }
   }
   if (buttons[B_FLIPPER_RIGHT-4].update() ) {
		if (buttons[B_FLIPPER_RIGHT-4].read() == HIGH) {
			hit_flipper_right();
     }
   }
   if (buttons[B_DOWN_POST_LEFT-4].update() ) {
		if (buttons[B_DOWN_POST_LEFT-4].read() == HIGH) {
			hit_down_post_left();
     }
   }
   if (buttons[B_DOWN_POST_RIGHT-4].update() ) {
		if (buttons[B_DOWN_POST_RIGHT-4].read() == HIGH) {
			hit_down_post_right();
     }
   }
   if (buttons[B_SCORE_100_FIELD-4].update() ) {
		if (buttons[B_SCORE_100_FIELD-4].read() == HIGH) {
			hit_score_100_field();
     }
   }
   if (buttons[B_BALL_OUT_OF_FIELD-4].update() ) {
		if (buttons[B_BALL_OUT_OF_FIELD-4].read() == HIGH) {
			hit_ball_out_of_field();
     }
   }
   if (buttons[B_START_BUTTON-4].update() ) {
		if (buttons[B_START_BUTTON-4].read() == HIGH) {
			hit_start_button();
     }
   }
   if (buttons[B_TILT_1-4].update() ) {
		if (buttons[B_TILT_1-4].read() == HIGH) {
			hit_tilt_1();
     }
   }
   if (buttons[B_TILT_2-4].update() ) {
		if (buttons[B_TILT_2-4].read() == HIGH) {
			hit_tilt_2();
     }
   }
   if (buttons[B_TILT_3-4].update() ) {
		if (buttons[B_TILT_3-4].read() == HIGH) {
			hit_tilt_3();
     }
   }
}
#endregion
