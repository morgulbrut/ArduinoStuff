// CmdMessenger library available from https://github.com/dreamcat4/cmdmessenger
#include <CmdMessenger.h>

// Base64 library available from https://github.com/adamvr/arduino-base64
#include <Base64.h>

// Streaming4 library available from http://arduiniana.org/libraries/streaming/
#include <Streaming.h>

#include "Pins.h"
// Mustnt conflict / collide with our message payload data. Fine if we use base64 library ^^ above
char field_separator = ',';
char command_separator = ';';



// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);


//Pinball Stuff;

int m_score;
boolean s_green,s_yellow,s_center, s_post, s_outhole, s_rollover_left, s_rollover_right, s_return_left, s_return_right;

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
  hitYellowOn,            // 004 in this example
  hitGreenOn,             // 005 in this example
  hitPostEn,              // 006 in this example
  hitPostDis,             // 007 in this example
  hitCenterEn,            // 008 in this example
  hitRolloverLeft,        // 008 in this example
  hitRolloverRight,       // 010 in this example
  hitBumperRed,           // 011 in this example
  hitBumperYellow,        // 012 in this example
  hitBumperGreen,         // 013 in this example
  hitBumper,              // 014 in this example
  startGame,              // 015 in this example
  NULL
};
// Its also possible (above ^^) to implement some symetric commands, when both the Arduino and
// PC / host are using each other's same command numbers. However we recommend only to do this if you
// really have the exact same messages going in both directions. Then specify the integers (with '=')


// ------------------ C A L L B A C K  M E T H O D S -------------------------


void hitYellowOn()
{
  cmdMessenger.sendCmd(kACK,"Ball hits yellow on");
  s_yellow = true;  
  printScore();

}

void   hitGreenOn()
{
  cmdMessenger.sendCmd(kACK,"Ball hits green on");
  s_green = true;  
  printScore();
}


void hitPostEn()
{
  cmdMessenger.sendCmd(kACK,"Ball hits post on");
  s_post = true;  
  printScore();
}


void hitPostDis()
{
  cmdMessenger.sendCmd(kACK,"Ball hits post on"); 
  s_post = false;  
  printScore();
}


void hitCenterEn()
{
  cmdMessenger.sendCmd(kACK,"Ball hits center target on");
  s_center = true;   
  printScore();
}


void hitRolloverLeft()
{
  cmdMessenger.sendCmd(kACK,"Ball rolls over left rollover"); 
  if(s_rollover_left) m_score += 5000;
  else m_score +=1000;  
  printScore();
}


void hitRolloverRight()
{
  cmdMessenger.sendCmd(kACK,"Ball rolls over right rollover");
  if(s_rollover_right) m_score += 5000;
  else m_score +=1000;
  printScore();
}


void hitBumperRed()
{
  cmdMessenger.sendCmd(kACK,"Ball hit red bumper");
  m_score +=10;  
  printScore();
}


void hitBumperYellow()
{
  cmdMessenger.sendCmd(kACK,"Ball hit yellow bumper");
  if(s_yellow) m_score += 100;
  else m_score +=10;  
  printScore();
}


void   hitBumperGreen()
{
  cmdMessenger.sendCmd(kACK,"Ball hit green bumper");
  if(s_yellow) m_score += 100;
  else m_score +=10;     
  printScore();
}


void   hitBumper()
{
  cmdMessenger.sendCmd(kACK,"Ball hit bumper");  
  changeActive();
  printScore();
}


void   startGame()
{
  cmdMessenger.sendCmd(kACK,"Game started");
  m_score=0;
  changeActive();  
  printScore();
}


// ------------------ D E F A U L T  C A L L B A C K S -----------------------

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

// ------------------ E N D  C A L L B A C K  M E T H O D S ------------------



// ------------------ S E T U P ----------------------------------------------

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
  
  changeActive();
  // blink
  pinMode(13, OUTPUT);
}


// ------------------ M A I N ( ) --------------------------------------------

// Timeout handling
long timeoutInterval = 2000; // 2 seconds
long previousMillis = 0;
int counter = 0;

void timeout()
{
  // blink
  if (counter % 2)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  counter ++;
}  

void loop() 
{
  // Process incoming serial data, if any
  cmdMessenger.feedinSerialData();

  // handle timeout function, if any
  if (  millis() - previousMillis > timeoutInterval )
  {
    timeout();
    previousMillis = millis();
  }

  // Loop.
}


//---------------------------- PINBALL STUFF-----------
void printScore(){
  Serial.print("Score: ");
  Serial.println(m_score);
}

void changeActive(){
  if(s_outhole){
    s_rollover_left = false;
    s_rollover_right = true;
    s_outhole = false;
  }
  else if(s_rollover_left){
    s_rollover_left = false;
    s_rollover_right = false;
    s_outhole = true;
  }
  else if(s_rollover_right){
    s_rollover_left = true;
    s_rollover_right = false;
    s_outhole = false;
  }
  else{
    s_rollover_left = true;
    s_rollover_right = false;
    s_outhole = false;
  }
}


