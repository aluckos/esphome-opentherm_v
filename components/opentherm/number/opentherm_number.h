#pragma once

#include "esphome/components/number/number.h"
#include "esphome/core/component.h"
#include "../hub.h" 

namespace esphome {
namespace opentherm {

class OpenthermHub; 

class OpenthermNumber : public number::Number, public Component {
 protected:
  void control(float value) override;
  void dump_config() override;
  void setup() override; // Dodano deklarację setup

  uint8_t message_id_{0}; 
  float initial_value_{NAN}; // Dodano zmienną dla początkowej wartości
  bool restore_value_{false}; // Dodano zmienną dla przywracania stanu
  OpenthermHub *parent_{nullptr};

 public:
  void set_parent(OpenthermHub *parent) { parent_ = parent; }
  void set_message_id(uint8_t msg_id) { this->message_id_ = msg_id; }
  void set_initial_value(float initial_value) { initial_value_ = initial_value; }
  void set_restore_value(bool restore_value) { restore_value_ = restore_value; }
};

}  // namespace opentherm
}  // namespace esphome
