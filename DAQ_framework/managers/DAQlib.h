/*
 * This is the main header file to be included in order to use
 * the DAQ hardware or simulator.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This function is used to perform any necessary initialization for
 * the hardware module and/or the simulator.  It must be called
 * before any of the other functions can be used.  It also creates the
 * appropriate simulator window, depending on the value of setupNum.
 */
int setupDAQ(int setupNum);

/*
 * This function is used to read the given digital input channel,
 * returning a value of either 0 or 1.
 */
int digitalRead(int channel);

/*
 * This function is used to read the given analog input channel,
 * returns a voltage typically in the range [0V, 5V]
 */
double analogRead(int channel);

/*
 * This function is used to write a value to the given
 * digital output channel.  The value can be either 0 or 1.
 */
void digitalWrite(int channel, int val);

/*
 * This function is used to write the given 'data' to
 * the 7-segment LED display at 'position'.  Note that position
 * starts at zero from the right.
 */
void displayWrite(int data, int position);


/*
 * This function is used to determine whether the DAQ is available,
 * and if the user wishes to continue running the program.  It returns
 * TRUE only when the DAQ hardware or simulator is running and the control
 * window has not been quit by the user.  Once this function returns FALSE,
 * do not call any of the other DAQ-related functions.
 */
int continueSuperLoop(void);

/*
 * This function causes the DAQ to "sleep" for  a given amount of time in
 * milliseconds.  This is a cross-platform alternative to the Windows
 * Sleep() function or POSIX usleep() function.
 */
void delay(unsigned long ms);

/*
 * This function returns the time in milliseconds since the DAQ was
 * initialized.  It can be used in relative timing of events.
 */
unsigned long millis(void);

#ifdef __cplusplus
}
#endif