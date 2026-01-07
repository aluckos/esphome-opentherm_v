#pragma once

#include "esphome/components/number/number.h"
#include "esphome/core/preferences.h"
#include "esphome/core/log.h"
#include "esphome/components/opentherm/input.h"
#include "opentherm_component.h" // Potrzebne do komunikacji z hubem

namespace esphome {
namespace opentherm {

class OpenthermNumber : public number::Number, public Component, public OpenthermInput {
 protected:
  void control(float value) override;
  void setup() override;
  void dump_config() override;

  float initial_value_{NAN};
  bool restore_value_{false};
  
  // NOWE POLA DLA ANY_NUMBER
  uint8_t message_id_{0}; 
  bool is_any_number_{false};

  ESPPreferenceObject pref_;
  OpenthermComponent *parent_; // Wskaźnik do głównego huba OT

 public:
  void set_parent(OpenthermComponent *parent) { parent_ = parent; }
  void set_min_value(float min_value) override { this->traits.set_min_value(min_value); }
  void set_max_value(float max_value) override { this->traits.set_max_value(max_value); }
  void set_initial_value(float initial_value) { initial_value_ = initial_value; }
  void set_restore_value(bool restore_value) { this->restore_value_ = restore_value; }
  
  // Metody do konfiguracji "any_number"
  void set_message_id(uint8_t msg_id) { 
    this->message_id_ = msg_id; 
    this->is_any_number_ = true;
  }
};

}  // namespace opentherm
}  // namespace esphome
