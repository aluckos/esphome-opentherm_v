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

  uint8_t message_id_{0}; 
  OpenthermHub *parent_{nullptr};

 public:
  void set_parent(OpenthermHub *parent) { parent_ = parent; }
  void set_message_id(uint8_t msg_id) { this->message_id_ = msg_id; }
};

}  // namespace opentherm
}  // namespace esphome
