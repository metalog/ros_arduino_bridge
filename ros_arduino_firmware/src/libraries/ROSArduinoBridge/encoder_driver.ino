/* *************************************************************
   Encoder definitions
   
   Add a "#if defined" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#if defined ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }

  void setupEncoders() {}

#elif defined DFROBOT_SEN0038
  long coder[2] = {0,0};

  void setupEncoders()
  {
#ifndef FAKE_ODOMETRY
    pinMode(2, INPUT);
    digitalWrite(2, HIGH);       // turn on pullup resistor
    pinMode(3, INPUT);
    digitalWrite(3, HIGH);       // turn on pullup resistor
    attachInterrupt(LEFT, LwheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 2
    attachInterrupt(RIGHT, RwheelSpeed, CHANGE);   //init the interrupt mode for the digital pin 3
#endif
  }

  void LwheelSpeed()
  {
      coder[LEFT] ++;  //count the left wheel encoder interrupts
  }

  void RwheelSpeed()
  {
      coder[RIGHT] ++; //count the right wheel encoder interrupts
  }

  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    return coder[i];
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    coder[i] = 0;
  }

#ifdef FAKE_ODOMETRY
  void updateFakeOdometry(unsigned char moving, long lastMotorCommand, double left_tpf, double right_tpf)
  {
    unsigned long timeframe;
    if(moving)
    {
      timeframe = millis() - lastMotorCommand;
      coder[LEFT]  = timeframe * left_tpf / 1000 + 0.5;
      coder[RIGHT] = timeframe * right_tpf / 1000 + 0.5;
    }
  }
#endif
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

