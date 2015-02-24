/**
 * $Id: $
 *
 * @file rp.h
 * @brief Red Pitaya library API interface
 *
 * @Author Red Pitaya
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __RP_H
#define __RP_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>


/** @name Error codes
 *  Various error codes returned by the API.
 */
///@{

/** Success */
#define RP_OK     0
/** Failed to Open EEPROM Device */
#define RP_EOED   1
/** Failed to Open Memory Device */
#define RP_EOMD   2
/** Failed to Close Memory Device*/
#define RP_ECMD   3
/** Failed to Map Memory Device */
#define RP_EMMD   4
/** Failed to Unmap Memory Device */
#define RP_EUMD   5
/** Value Out Of Range */
#define RP_EOOR   6
/** LED Input Direction is not valid */
#define RP_ELID   7
/** Modifying Read Only field */
#define RP_EMRO   8
/** Writing to Input Pin is not valid */
#define RP_EWIP   9
/** Invalid Pin number */
#define RP_EPN    10
/** Uninitialized Input Argument */
#define RP_UIA    11
/** Failed to Find Calibration Parameters */
#define RP_FCA    12
/** Failed to Read Calibration Parameters */
#define RP_RCA    13
/** Buffer too small */
#define RP_BTS    14
/** Invalid parameter value */
#define RP_EIPV    15
/** Unsupported Feature */
#define RP_EUF    16
/** Data not normalized */
#define RP_ENN    17

///@}

/**
 * Type representing digital input output pins.
 */
typedef enum {
    RP_LED0,       //!< LED 0
    RP_LED1,       //!< LED 1
    RP_LED2,       //!< LED 2
    RP_LED3,       //!< LED 3
    RP_LED4,       //!< LED 4
    RP_LED5,       //!< LED 5
    RP_LED6,       //!< LED 6
    RP_LED7,       //!< LED 7
    RP_DIO0_P,     //!< DIO_P 0
    RP_DIO1_P,     //!< DIO_P 1
    RP_DIO2_P,     //!< DIO_P 2
    RP_DIO3_P,     //!< DIO_P 3
    RP_DIO4_P,     //!< DIO_P 4
    RP_DIO5_P,     //!< DIO_P 5
    RP_DIO6_P,     //!< DIO_P 6
    RP_DIO7_P,	   //!< DIO_P 7
    RP_DIO0_N,     //!< DIO_N 0
    RP_DIO1_N,     //!< DIO_N 1
    RP_DIO2_N,     //!< DIO_N 2
    RP_DIO3_N,     //!< DIO_N 3
    RP_DIO4_N,     //!< DIO_N 4
    RP_DIO5_N,     //!< DIO_N 5
    RP_DIO6_N,     //!< DIO_N 6
    RP_DIO7_N      //!< DIO_N 7
} rp_dpin_t;

/**
 * Type representing pin's high or low state (on/off).
 */
typedef enum {
    RP_LOW, //!< Low state
    RP_HIGH //!< High state
} rp_pinState_t;

/**
 * Type representing pin's input or output direction.
 */
typedef enum {
    RP_IN, //!< Input direction
    RP_OUT //!< Output direction
} rp_pinDirection_t;

/**
 * Type representing analog input output pins.
 */
typedef enum {
    RP_AOUT0,      //!< Analog output 0
    RP_AOUT1,      //!< Analog output 1
    RP_AOUT2,      //!< Analog output 2
    RP_AOUT3,      //!< Analog output 3
    RP_AIN0,       //!< Analog input 0
    RP_AIN1,       //!< Analog input 1
    RP_AIN2,       //!< Analog input 2
    RP_AIN3        //!< Analog input 3
} rp_apin_t;

/**
 * Type representing system health information.
 */
typedef enum {
    RP_TEMP_FPGA,  //!< FPGA temperature
    RP_VCC_PINT,   //!< VCC PINT
    RP_VCC_PAUX,   //!< VCC PAUX
    RP_VCC_BRAM,   //!< VCC BRAM
    RP_VCC_INT,    //!< VCC INT
    RP_VCC_AUX,    //!< VCC AUX
    RP_VCC_DDR     //!< VCC DDR
} rp_health_t;

typedef enum {
    RP_WAVEFORM_SINE,       //!< Wave form sine
    RP_WAVEFORM_SQUARE,     //!< Wave form square
    RP_WAVEFORM_TRIANGLE,   //!< Wave form triangle
    RP_WAVEFORM_RAMP_UP,    //!< Wave form sawtooth (/|)
    RP_WAVEFORM_RAMP_DOWN,  //!< Wave form reversed sawtooth (|\)
    RP_WAVEFORM_DC,         //!< Wave form dc
    RP_WAVEFORM_PWM,        //!< Wave form pwm
    RP_WAVEFORM_ARBITRARY   //!< Use defined wave form
} rp_waveform_t;

typedef enum {
    RP_GEN_MODE_CONTINUOUS, //!< Continuous signal generation
    RP_GEN_MODE_BURST,      //!< Signal is generated N times, wher N is defined with rp_GenBurstCount method
    RP_GEN_MODE_STREAM      //!< User can continuously write data to buffer
} rp_gen_mode_t;


typedef enum {
    RP_GEN_TRIG_SRC_INTERNAL = 1,   //!< Internal trigger source
    RP_GEN_TRIG_SRC_EXT_PE = 2,     //!< External trigger source positive edge
	RP_GEN_TRIG_SRC_EXT_NE = 3,     //!< External trigger source negative edge
    RP_GEN_TRIG_GATED_BURST     //!< External trigger gated burst
} rp_trig_src_t;

/**
 * Type representing Input/Output channels.
 */
typedef enum {
    RP_CH_1, //!< Channel A
    RP_CH_2  //!< Channel B
} rp_channel_t;

/**
 * Type representing acquire signal sampling rate.
 */
typedef enum {
    RP_SMP_125M,     //!< Sample rate 125Msps; Buffer time length 131us; Decimation 1
    RP_SMP_15_625M,  //!< Sample rate 15.625Msps; Buffer time length 1.048ms; Decimation 8
    RP_SMP_1_953M,   //!< Sample rate 1.953Msps; Buffer time length 8.388ms; Decimation 64
    RP_SMP_122_070K, //!< Sample rate 122.070ksps; Buffer time length 134.2ms; Decimation 1024
    RP_SMP_15_258K,  //!< Sample rate 15.258ksps; Buffer time length 1.073s; Decimation 8192
    RP_SMP_1_907K    //!< Sample rate 1.907ksps; Buffer time length 8.589s; Decimation 65536
} rp_acq_sampling_rate_t;


/**
 * Type representing decimation used at acquiring signal.
 */
typedef enum {
    RP_DEC_1,     //!< Sample rate 125Msps; Buffer time length 131us; Decimation 1
    RP_DEC_8,     //!< Sample rate 15.625Msps; Buffer time length 1.048ms; Decimation 8
    RP_DEC_64,    //!< Sample rate 1.953Msps; Buffer time length 8.388ms; Decimation 64
    RP_DEC_1024,  //!< Sample rate 122.070ksps; Buffer time length 134.2ms; Decimation 1024
    RP_DEC_8192,  //!< Sample rate 15.258ksps; Buffer time length 1.073s; Decimation 8192
    RP_DEC_65536  //!< Sample rate 1.907ksps; Buffer time length 8.589s; Decimation 65536
} rp_acq_decimation_t;


/**
 * Type representing different trigger sources used at acquiring signal.
 */
typedef enum {
    RP_TRIG_SRC_DISABLED, //!< Trigger is disabled
    RP_TRIG_SRC_NOW,      //!< Trigger triggered now (immediately)
    RP_TRIG_SRC_CHA_PE,   //!< Trigger set to Channel A threshold positive edge
    RP_TRIG_SRC_CHA_NE,   //!< Trigger set to Channel A threshold negative edge
    RP_TRIG_SRC_CHB_PE,   //!< Trigger set to Channel B threshold positive edge
    RP_TRIG_SRC_CHB_NE,   //!< Trigger set to Channel B threshold negative edge
    RP_TRIG_SRC_EXT_PE,   //!< Trigger set to external trigger positive edge (DIO0_P pin)
    RP_TRIG_SRC_EXT_NE,   //!< Trigger set to external trigger negative edge (DIO0_P pin)
    RP_TRIG_SRC_AWG_PE,   //!< Trigger set to arbitrary wave generator application positive edge
    RP_TRIG_SRC_AWG_NE    //!< Trigger set to arbitrary wave generator application negative edge
} rp_acq_trig_src_t;


/**
 * Type representing different trigger states.
 */
typedef enum {
    RP_TRIG_STATE_TRIGGERED, //!< Trigger is triggered/disabled
    RP_TRIG_STATE_WAITING,   //!< Trigger is set up and waiting (to be triggered)
} rp_acq_trig_state_t;


/**
 * Calibration parameters, stored in the EEPROM device
 */
typedef struct {
    uint32_t fe_ch1_fs_g_hi; //!< High gain front end full scale voltage, channel A
    uint32_t fe_ch2_fs_g_hi; //!< High gain front end full scale voltage, channel B
    uint32_t fe_ch1_fs_g_lo; //!< Low gain front end full scale voltage, channel A
    uint32_t fe_ch2_fs_g_lo; //!< Low gain front end full scale voltage, channel B
    int32_t  fe_ch1_dc_offs; //!< Front end DC offset, channel A
    int32_t  fe_ch2_dc_offs; //!< Front end DC offset, channel B
    uint32_t be_ch1_fs;      //!< Back end full scale voltage, channel A
    uint32_t be_ch2_fs;      //!< Back end full scale voltage, channel B
    int32_t  be_ch1_dc_offs; //!< Back end DC offset, channel A
    int32_t  be_ch2_dc_offs; //!< Back end DC offset, on channel B
} rp_calib_params_t;

/** @name General
 */
///@{


/**
 * Initializes the library. It must be called first, before any other library method.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_Init();

/**
 * Releases the library resources. It must be called last, after library is not used anymore. Typically before
 * application exits.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_Release();

/**
* Resets all modules. Typically calles after rp_Init()
* application exits.
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_Reset();

/**
 * Retrieves the library version number
 * @return Library version
 */
const char* rp_GetVersion();

/**
 * Returns calibration settings.
 * These calibration settings are populated only once from EEPROM at rp_Init().
 * Each rp_GetCalibrationSettings call returns the same cached setting values.
 * @return Calibration settings
 */
rp_calib_params_t rp_GetCalibrationSettings();

/**
 * Returns textual representation of error code.
 * @param errorCode Error code returned from API.
 * @return Textual representation of error given error code.
 */
const char* rp_GetError(int errorCode);

///@}

/** @name Digital Input/Output
 */
///@{

/**
* Sets digital pins to default values. Pins DIO1_P - DIO7_P, RP_DIO0_N - RP_DIO7_N are set al OUTPUT and to LOW. LEDs are set to LOW/OFF
*/
int rp_DpinReset();

/**
 * Sets digital input output pin state.
 * @param pin    Digital input output pin.
 * @param state  High/Low state that will be set at the given pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_DpinSetState(rp_dpin_t pin, rp_pinState_t state);

/**
 * Gets digital input output pin state.
 * @param pin    Digital input output pin.
 * @param state  High/Low state that is set at the given pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_DpinGetState(rp_dpin_t pin, rp_pinState_t* state);

/**
 * Sets digital input output pin direction. LED pins are already automatically set to the output direction,
 * and they cannot be set to the input direction. DIOx_P and DIOx_N are must set either output or input direction
 * before they can be used. When set to input direction, it is not allowed to write into these pins.
 * @param pin        Digital input output pin.
 * @param direction  In/Out direction that will be set at the given pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_DpinSetDirection(rp_dpin_t pin, rp_pinDirection_t direction);

/**
 * Gets digital input output pin direction.
 * @param pin        Digital input output pin.
 * @param direction  In/Out direction that is set at the given pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_DpinGetDirection(rp_dpin_t pin, rp_pinDirection_t* direction);

///@}

/** @name Analog Input/Output
 */
///@{


/**
* Sets analog pins to default values. Output pins are set to 0 V.
*/
int rp_ApinReset();


/**
 * Gets value from analog pin in volts.
 * @param pin    Analog pin.
 * @param value  Value on analog pin in volts
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_ApinGetValue(rp_apin_t pin, float* value);

/**
 * Gets raw value from analog pin.
 * @param pin    Analog pin.
 * @param value  Raw value on analog pin
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_ApinGetValueRaw(rp_apin_t pin, uint32_t* value);

/**
 * Sets value in volts on analog output pin.
 * @param pin    Analog output pin.
 * @param value  Value in volts to be set on given output pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_ApinSetValue(rp_apin_t pin, float value);

/**
 * Sets raw value on analog output pin.
 * @param pin    Analog output pin.
 * @param value  Raw value to be set on given output pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_ApinSetValueRaw(rp_apin_t pin, uint32_t value);

/**
 * Gets range in volts on specific pin.
 * @param pin      Analog input output pin.
 * @param min_val  Minimum value in volts on given pin.
 * @param max_val  Maximum value in volts on given pin.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_ApinGetRange(rp_apin_t pin, float* min_val,  float* max_val);


/** @name Acquire
 */
///@{

/**
 * Sets the decimation used at acquiring signal. There is only a set of pre-defined decimation
 * values which can be specified. See the #rp_acq_decimation_t enum values.
 * @param decimation Specify one of pre-defined decimation values
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetDecimation(rp_acq_decimation_t decimation);

/**
 * Gets the decimation used at acquiring signal. There is only a set of pre-defined decimation
 * values which can be specified. See the #rp_acq_decimation_t enum values.
 * @param decimation Returns one of pre-defined decimation values which is currently set.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDecimation(rp_acq_decimation_t* decimation);

/**
 * Gets the decimation factor used at acquiring signal in a numerical form. Although this method returns an integer
 * value representing the current factor of the decimation, there is only a set of pre-defined decimation
 * factor values which can be returned. See the #rp_acq_decimation_t enum values.
 * @param decimation Returns decimation factor value which is currently set.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDecimationFactor(uint32_t* decimation);

/**
 * Sets the sampling rate for acquiring signal. There is only a set of pre-defined sampling rate
 * values which can be specified. See the #rp_acq_sampling_rate_t enum values.
 * @param sampling_rate Specify one of pre-defined sampling rate value
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetSamplingRate(rp_acq_sampling_rate_t sampling_rate);

/**
 * Gets the sampling rate for acquiring signal. There is only a set of pre-defined sampling rate
 * values which can be returned. See the #rp_acq_sampling_rate_t enum values.
 * @param sampling_rate Returns one of pre-defined sampling rate value which is currently set
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetSamplingRate(rp_acq_sampling_rate_t* sampling_rate);

/**
 * Gets the sampling rate for acquiring signal in a numerical form in Hz. Although this method returns a float
 * value representing the current value of the sampling rate, there is only a set of pre-defined sampling rate
 * values which can be returned. See the #rp_acq_sampling_rate_t enum values.
 * @param sampling_rate returns currently set sampling rate in Hz
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetSamplingRateHz(float* sampling_rate);

/**
 * Enables or disables averaging of data between samples.
 * Data between samples can be averaged by setting the averaging flag in the Data decimation register.
 * @param enabled When true, the averaging is enabled, otherwise it is disabled.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetAveraging(bool enabled);

/**
 * Returns information if averaging of data between samples is enabled or disabled.
 * Data between samples can be averaged by setting the averaging flag in the Data decimation register.
 * @param enabled Set to true when the averaging is enabled, otherwise is it set to false.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetAveraging(bool *enabled);

/**
 * Sets the trigger source used at acquiring signal. When acquiring is started,
 * the FPGA waits for the trigger condition on the specified source and when the condition is met, it
 * starts writing the signal to the buffer.
 * @param source Trigger source.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetTriggerSrc(rp_acq_trig_src_t source);

/**
 * Gets the trigger source used at acquiring signal. When acquiring is started,
 * the FPGA waits for the trigger condition on the specified source and when the condition is met, it
 * starts writing the signal to the buffer.
 * @param source Currently set trigger source.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerSrc(rp_acq_trig_src_t* source);

/**
 * Returns the trigger state. Either it is waiting for a trigger to happen, or it has already been triggered.
 * By default it is in the triggered state, which is treated the same as disabled.
 * @param state Trigger state
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerState(rp_acq_trig_state_t* state);

/**
 * Sets the number of decimated data after trigger written into memory.
 * @param decimated_data_num Number of decimated data. It must not be higher than the ADC buffer size.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetTriggerDelay(int32_t decimated_data_num);

/**
 * Returns current number of decimated data after trigger written into memory.
 * @param decimated_data_num Number of decimated data.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerDelay(int32_t* decimated_data_num);

/**
 * Sets the amount of decimated data in nanoseconds after trigger written into memory.
 * @param time_ns Time in nanoseconds. Number of ADC samples within the specified
 * time must not be higher than the ADC buffer size.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetTriggerDelayNs(int64_t time_ns);

/**
 * Returns the current amount of decimated data in nanoseconds after trigger written into memory.
 * @param time_ns Time in nanoseconds.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerDelayNs(int64_t* time_ns);

/**
 * Sets the trigger threshold value in volts. Makes the trigger when ADC value crosses this value.
 * @param voltage Threshold value for the channel
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetTriggerLevel(float voltage);

/**
 * Gets currently set trigger threshold value in volts
 * @param voltage Current threshold value for the channel
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerLevel(float* voltage);

/**
 * Sets the trigger threshold hysteresis value in volts.
 * Value must be outside to enable the trigger again.
 * @param voltage Threshold hysteresis value for the channel
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetTriggerHyst(float voltage);

/**
 * Gets currently set trigger threshold hysteresis value in volts
 * @param voltage Current threshold hysteresis value for the channel
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetTriggerHyst(float* voltage);

/**
 * Sets the acquire gain state. The gain should be set to the same value as it is set on the Red Pitaya
 * hardware by the LV/HV gain jumpers. LV = 1V; HV = 20V.
 * @param channel Channel A or B
 * @param state High or Low state
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqSetGain(rp_channel_t channel, rp_pinState_t state);

/**
 * Returns the currently set acquire gain state in the library. It may not be set to the same value as
 * it is set on the Red Pitaya hardware by the LV/HV gain jumpers. LV = 1V; HV = 20V.
 * @param channel Channel A or B
 * @param state Currently set High or Low state in the library.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetGain(rp_channel_t channel, rp_pinState_t* state);

/**
 * Returns the currently set acquire gain in the library. It may not be set to the same value as
 * it is set on the Red Pitaya hardware by the LV/HV gain jumpers. Returns value in Volts.
 * @param channel Channel A or B
 * @param voltage Currently set gain in the library. 1.0 or 20.0 Volts
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetGainV(rp_channel_t channel, float* voltage);

/**
 * Returns current position of ADC write pointer.
 * @param pos Write pointer position
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetWritePointer(uint32_t* pos);

/**
 * Returns position of ADC write pointer at time when trigger arrived.
 * @param pos Write pointer position
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetWritePointerAtTrig(uint32_t* pos);

/**
 * Starts the acquire. Signals coming from the input channels are acquired and written into memory.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqStart();

/**
 * Resets the acquire writing state machine.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqReset();

/**
 * Normalizes the ADC buffer position. Returns the modulo operation of ADC buffer size...
 * @param pos position to be normalized
 * @return Normalized position (pos % ADC_BUFFER_SIZE)
 */
uint32_t rp_AcqGetNormalizedDataPos(uint32_t pos);

/**
 * Returns the ADC buffer in raw units from start to end position.
 *
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param start_pos Starting position of the ADC buffer to retrieve.
 * @param end_pos Ending position of the ADC buffer to retrieve.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @param buffer_size Length of input buffer. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t *buffer_size);

/**
 * Returns the ADC buffer in Volt units from start to end position.
 *
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param start_pos Starting position of the ADC buffer to retrieve.
 * @param end_pos Ending position of the ADC buffer to retrieve.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @param buffer_size Length of input buffer. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t *buffer_size);

/**
 * Returns the ADC buffer in raw units from specified position and desired size.
 * Output buffer must be at least 'size' long.
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param pos Starting position of the ADC buffer to retrieve.
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer);

/**
 * Returns the ADC buffer in raw units from the oldest sample to the newest one.
 * Output buffer must be at least 'size' long.
 * CAUTION: Use this method only when write pointer has stopped (Trigger happened and writing stopped).
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);

/**
 * Returns the latest ADC buffer samples in raw units.
 * Output buffer must be at least 'size' long.
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);

/**
 * Returns the ADC buffer in Volt units from specified position and desired size.
 * Output buffer must be at least 'size' long.
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param pos Starting position of the ADC buffer to retrieve
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer);

/**
 * Returns the ADC buffer in Volt units from the oldest sample to the newest one.
 * Output buffer must be at least 'size' long.
 * CAUTION: Use this method only when write pointer has stopped (Trigger happened and writing stopped).
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer);

/**
 * Returns the latest ADC buffer samples in Volt units.
 * Output buffer must be at least 'size' long.
 * @param channel Channel A or B for which we want to retrieve the ADC buffer.
 * @param size Length of the ADC buffer to retrieve. Returns length of filled buffer. In case of too small buffer, required size is returned.
 * @param buffer The output buffer gets filled with the selected part of the ADC buffer.
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer);


int rp_AcqGetBufSize(uint32_t* size);

/* Deep averagning functions */
int rp_DeepAvgStart();
int rp_SetDeepAvgCount(uint32_t count);
int rp_SetDeepAvgShift(uint32_t shift);
int rp_SetDeepDataSeqLen(uint32_t len);
int rp_SetDeepAvgDebTim(uint32_t deb_t);

int rp_GetDeepAvgCount(uint32_t *count);
int rp_GetDeepAvgShift(uint32_t *shift);
int rp_GetDeepDataSeqLen(uint32_t *len);
int rp_GetDeepAvgDebTim(uint32_t *deb_t);

int acq_GetDeepAvgTriggerState(rp_acq_trig_src_t *source);


/** @name Health
 */
///@{


/**
 * Gets data about system health like temperature
 * @param sensor   From witch sensor the data is read
 * @param value    The returned value
 * @return If the function is successful, the return value is RP_OK.
 * If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
 */
int rp_HealthGetValue(rp_health_t sensor, float* value);


/** @name Generate
*/
///@{



/**
* Sets generate to default values.
*/
int rp_GenReset();

/**
* Enables output
* @param channel Channel A or B which we want to enable
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenOutEnable(rp_channel_t channel);

/**
* Disables output
* @param channel Channel A or B which we want to disable
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenOutDisable(rp_channel_t channel);

/**
* Sets channel signal peak to peak amplitude.
* @param channel Channel A or B which we want to enable
* @param amplitude Amplitude of the generated signal. From 0 to max value. Max amplitude is 1
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenAmp(rp_channel_t channel, float amplitude);

/**
* Sets DC offset of the signal. signal = signal + DC_offset
* @param channel Channel A or B which we want to enable
* @param offset DC offset of the generated signal. Max offset is 2
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenOffset(rp_channel_t channel, float offset);

/**
* Sets channel signal frequency
* @param channel Channel A or B which we want to enable
* @param frequency Frequency of the generated signal in Hz
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenFreq(rp_channel_t channel, float frequency);

/**
* Sets channel signal phase. This shifts the signal in time
* @param channel Channel A or B which we want to enable
* @param phase Phase in degrees of the generated signal. From 0 deg to 180 deg
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenPhase(rp_channel_t channel, float phase);

/**
* Sets channel signal form. This determines how the signal looks
* @param channel Channel A or B which we want to enable
* @param form Wave form of the generated signal [SINE, SQUARE, TRIANGLE, SAWTOOTH, PWM, DC, ARBITRARY]
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenWaveform(rp_channel_t channel, rp_waveform_t type);

/**
* Sets user defined wave form
* @param channel Channel A or B which we want to enable
* @param waveform Use defined wave form, where min is -1V an max is 1V
* @param length Length of waveform
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenArbWaveform(rp_channel_t channel, float* waveform, uint32_t length);

/**
* Sets duty cycle of PWM signal
* @param channel Channel A or B which we want to enable
* @param ratio Ratio betwen the time when signal in HIGH vs the time when signal is LOW.
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenDutyCycle(rp_channel_t channel, float ratio);

/**
* Sets geenration mode
* @param channel Channel A or B which we want to enable
* @param mode Type of signal generation (CONTINUOUS, BURST, STREAM)
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenMode(rp_channel_t channel, rp_gen_mode_t mode);

/**
* Sets number of generated waveforms in a burst.
* @param channel Channel A or B which we want to enable
* @param num Number of generated waveforms. If -1 a continuous signal will be generated.
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenBurstCount(rp_channel_t channel, int num);


/**
* Sets number of burst repetitions. This determines how many bursts will be generated.
* @param channel Channel A or B which we want to enable
* @param repetitions Number of generated bursts. If -1, infinite bursts will be generated.
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenBurstRepetitions(rp_channel_t channel, int repetitions);


/**
* Sets the time/period of one burst in micro seconds. Period must be equal or greater then the time of one burst.
* If it is greater than the difference will be the delay between two consequential bursts.
* @param channel Channel A or B which we want to enable
* @param period Time in micro seconds
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenBurstPeriod(rp_channel_t channel, uint32_t period);

/**
* Sets trigger source
* @param channel Channel A or B which we want to enable
* @param src Trigger source (INTERNAL, EXTERNAL)
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenTriggerSource(rp_channel_t channel, rp_trig_src_t src);

/**
* Sets Trigger for specified channel/channels
* @param channel Channel A or B which we want to enable
* @param mask Mask determines channel: 1->ch1, 2->ch2, 3->ch1&ch2
* @return If the function is successful, the return value is RP_OK.
* If the function is unsuccessful, the return value is any of RP_E* values that indicate an error.
*/
int rp_GenTrigger(int mask);

///@}

#ifdef __cplusplus
}
#endif

#endif //__RP_H
