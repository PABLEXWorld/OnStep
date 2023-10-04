// -------------------------------------------------------------------------------------------------
// Pin map for the board used in the Carlos J. Neiman Observatory (with WeMos D1 R32)
// Based on the CNC Shield Version 3

// Note: SPI for TMC drivers: GPIO32 (MOSI), GPIO33 (SCK), GPIO15 (CS Axis1) on WeMos D1 R32 PCB are more difficult to wire into but optional. GPIO18 (CS Axis2) is on top.

#if defined(ESP32)

// Serial2 (SerialB) needs to be re-mapped to GPIO23 (TX) and GPIO5 (RX)
#define SERIAL_B_TX          23
#define SERIAL_B_RX           5

// The multi-purpose pins (Aux3..Aux8 can be analog pwm/dac if supported)
#define Aux2                OFF
#define Aux3                OFF
#define Aux4                OFF
#define Aux7                OFF
#define Aux8                OFF

// Misc. pins
#define AddonBootModePin    OFF
#define AddonResetPin       OFF

// The PEC index sense is a logic level input, resets the PEC index on rising edge then waits for 60 seconds before allowing another reset
#define PecPin              OFF
#define AnalogPecPin        OFF

// The status LED is a two wire jumper with a 10k resistor in series to limit the current to the LED
#define LEDnegPin            14     // Drain
#define LEDneg2Pin           17     // Drain
#define ReticlePin          OFF

// For a piezo buzzer
#define TonePin             OFF

// The PPS pin is a 3.3V logic input, OnStep measures time between rising edges and adjusts the internal sidereal clock frequency
#define PpsPin              OFF

#define LimitPin            OFF

// Axis1 RA/Azm step/dir driver
#define Axis1_EN            OFF     // Enable [must be low at boot]
#define Axis1_M0            OFF     // Microstep Mode 0 or SPI MOSI
#define Axis1_M1            OFF     // Microstep Mode 1 or SPI SCK
#define Axis1_M2            OFF     // Microstep Mode 2 or SPI CS
#define Axis1_M3            OFF     // SPI MISO/Fault
#define Axis1_STEP           12     // Step
#define Axis1_DIR            13     // Dir
#define Axis1_DECAY         OFF     // Decay mode
#define Axis1_HOME          OFF     // Sense home position

// Axis2 Dec/Alt step/dir driver
#define Axis2_EN         SHARED     // Enable pin control shared with Axis1
#define Axis2_M0            OFF     // Microstep Mode 0 or SPI MOSI
#define Axis2_M1            OFF     // Microstep Mode 1 or SPI SCK
#define Axis2_M2            OFF     // Microstep Mode 2 or SPI CS
#define Axis2_M3            OFF     // SPI MISO/Fault
#define Axis2_STEP           25     // Step
#define Axis2_DIR            26     // Dir
#define Axis2_DECAY         OFF     // Decay mode
#define Axis2_HOME          OFF     // Sense home position

// For rotator stepper driver
#define Axis3_EN         SHARED     // Enable pin control shared with Axis1
#define Axis3_STEP          OFF     // Step
#define Axis3_DIR           OFF     // Dir

// For focuser1 stepper driver
#define Axis4_EN         SHARED     // Enable pin control shared with Axis1
#define Axis4_STEP           19     // Step
#define Axis4_DIR            27     // Dir

// For focuser2 stepper driver
#define Axis5_EN         SHARED     // Enable pin control shared with Axis1
#define Axis5_STEP          OFF     // Step
#define Axis5_DIR           OFF     // Dir

// ST4 interface
#define ST4RAw              OFF     // ST4 RA- West [input only]
#define ST4DEs              OFF     // ST4 DE- South
#define ST4DEn              OFF     // ST4 DE+ North
#define ST4RAe              OFF     // ST4 RA+ East [input only]

#else
#error "Wrong processor for this configuration!"

#endif
