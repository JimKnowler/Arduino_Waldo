#ifndef ARDUINO_WALDO_H
#define ARDUINO_WALDO_H

// TODO: add timeout, such that if host doesn't respond after 'n' seconds then the arduino client restarts and waits for a connection
// TODO: perhaps we should have a special character that can be used to flush the serial port connection at any time.
//       - the device can send this when it times out and effectively restart the serial communication.
//       - perhaps it could be associated with a unique ID, that the host can acknowledge and reply with to confirm that the 
//         connection has been successfully reset.

/**
 * @class Waldo
 * @brief Arduino client library for Waldo
 * 
 */
class Waldo 
{
public:
    Waldo();
    ~Waldo();
    /**
     * @brief Initialise Waldo library
     *
     * @note The Waldo library takes ownership of the serial port, and uses it to 
     *       communicate with the host.  
     * 
     *       When using the Waldo library, you must not call any other functions on the Serial 
     *       port, such as Serial.println(), because this interferes with how Waldo communicates
     *       with the host.
     * 
     *       When using the Waldo library, you must keep the Serial Monitor closed in Arduino IDE, 
     *       because this interferes with how Waldo communicates with the host.      
     *       
     */
    void setup();
  
    /**
     * @brief Add an analog input, such as a potentiometer
     * 
     * @param label Name of this input
     * @param pin The Analog Arduino Pin that the input is connected to (e.g. A0)
     */
    void add_input_analog(const char* label, int pin);

    /**
     * @brief Add a digial input, such as a button
     * 
     * @param label Name of this input
     * @param pin The Digital Arduino Pin that the input is connected to (e.g. D0)
     */
    void add_input_digital(const char* label, int pin);
  
    /**
     * @brief Function to be called from Arduino loop() function
     * 
     * @note This functions sends updates for all inputs to the host, and manages 
     *       flow control of the serial port.
     */
    void loop();
};
  
#endif