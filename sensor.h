#ifndef SENSOR_H_
#define SENSOR_H_

#include <cocoos.h>

#ifdef __cplusplus ////
extern "C" {
#endif ////

/*
 * Sensor interface
 * Used by tasks to access a sensor
 * An example could be an i2c connected sensor. The sensor driver
 * could signal the event in the tx interrupt when new data is available,
 * or return 1 in the poll() function.
 */
 
//// For Arduino: Break into SensorInfo, Control_Info_t structs for easier initialisation in C++
/**
* Information interface
*/
typedef struct {
  /**
   *  Name of the sensor
   */
  const char* name;

  /**
   *  Event signaled by driver when new data available
   *  Should be set by the application during startup using the init() function
   */
  Evt_t *event;

  /*
   * Sensor id
   * Could be used as message id. Should be set by the init() method.
   */
  uint8_t id;

  /**
   *  Minimum polling period, set to 0 if polling is not used
   *  If we know that a sensor is updated every second, it would be
   *  meaningless to poll it more often. Set the period_ms to indicate
   *  a suitable minimum period.
   */
  uint16_t period_ms;

  /**
   *  Poll for new data
   *  @return 1 if new data available, 0 otherwise
   */
  uint8_t (*poll)(void);

  /**
   * Get sensor data
   * @param buf, pointer to output buffer
   * @param size, size of buffer
   * @return number of bytes copied
   */
  uint8_t (*data)(uint8_t *buf, uint8_t size);  // receive max size bytes into buf

} SensorInfo;
////

////
/**
 * Control interface
 */
typedef struct {
  /**
   * Initialize sensor
   * Should be called during main startup
   *
   * @param id, an unique id for the sensor
   * @param event, event that should be signaled. Set to 0 if not used.
   * @param period_ms, minimum polling time, set to 0 if not used.
   */
  void (*init)(uint8_t id, Evt_t *event, uint16_t period_ms);

  /**
   * Set sensor to measure next channel
   */
  void (*next_channel)(void);

  /**
   * Set sensor to measure previous channel
   */
  void (*prev_channel)(void);
} SensorControl;
////
  
typedef struct {
  /**
   * Information interface
   */
  SensorInfo info; ////

  /**
   * Control interface
   */
  SensorControl control; ////
} Sensor;

void debug(const char *s); ////

#ifdef __cplusplus ////
}
#endif ////

#endif /* SENSOR_H_ */
