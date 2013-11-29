/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
void setupEncoders();

#ifdef FAKE_ODOMETRY
void updateFakeOdometry(unsigned char moving, long lastMotorCommand, double left_tpf, double right_tpf);
#endif
