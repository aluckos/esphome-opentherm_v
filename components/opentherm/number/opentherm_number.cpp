#include "opentherm_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *const TAG = "opentherm.number";

void OpenthermNumber::control(float value) {
  if (this->parent_ != nullptr && this->message_id_ != 0) {
    OpenthermData data;
    data.type = MessageType::WRITE_DATA;
    data.id = this->message_id_;
    data.u16((uint16_t)value); 
    
    // Używamy nowej metody, którą dodaliśmy do hub.h
    this->parent_->send_raw_message(data);
    this->publish_state(value);
    
    ESP_LOGD(TAG, "Wysłano nastawę OpenTherm ID %d: %.1f", this->message_id_, value);
  }
}

void OpenthermNumber::dump_config() {
  LOG_NUMBER(TAG, "OpenTherm Number", this);
  ESP_LOGCONFIG(TAG, "  Message ID: %u", this->message_id_);
}

}  // namespace opentherm
}  // namespace esphome
