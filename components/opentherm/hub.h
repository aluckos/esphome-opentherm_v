#pragma once

#include <vector>
#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include "opentherm.h"

#ifdef OPENTHERM_USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif

#ifdef OPENTHERM_USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif

#ifdef OPENTHERM_USE_SWITCH
#include "esphome/components/opentherm/switch/opentherm_switch.h"
#endif

#ifdef OPENTHERM_USE_OUTPUT
#include "esphome/components/opentherm/output/opentherm_output.h"
#endif

#ifdef OPENTHERM_USE_NUMBER
#include "esphome/components/opentherm/number/opentherm_number.h"
#endif

#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "opentherm_macros.h"

namespace esphome {
namespace opentherm {

static const uint8_t REPEATING_MESSAGE_ORDER = 255;
static const uint8_t INITIAL_UNORDERED_MESSAGE_ORDER = 254;

// OpenTherm component for ESPHome
class OpenthermHub : public Component {
 protected:
  // Communication pins for the OpenTherm interface
  InternalGPIOPin *in_pin_, *out_pin_;
  // The OpenTherm interface
  std::unique_ptr<OpenTherm> opentherm_;

  OPENTHERM_SENSOR_LIST(OPENTHERM_DECLARE_SENSOR, )

  OPENTHERM_BINARY_SENSOR_LIST(OPENTHERM_DECLARE_BINARY_SENSOR, )

  OPENTHERM_SWITCH_LIST(OPENTHERM_DECLARE_SWITCH, )

  OPENTHERM_NUMBER_LIST(OPENTHERM_DECLARE_NUMBER, )

  OPENTHERM_OUTPUT_LIST(OPENTHERM_DECLARE_OUTPUT, )

  OPENTHERM_INPUT_SENSOR_LIST(OPENTHER
