#include "opentherm_number.h"

namespace esphome {
namespace opentherm {

static const char *const TAG = "opentherm.number";

void OpenthermNumber::control(float value) {
  this->publish_state(value);

  // Zapisywanie stanu, jeśli włączone
  if (this->restore_value_)
    this->pref_.save(&value);

  // Logika wysyłania komendy OpenTherm
  if (this->is_any_number_ && this->parent_ != nullptr) {
    // Brink zwykle przyjmuje wartości jako u16 (np. 0-100 dla wentylacji)
    uint16_t data = (uint16_t)value;
    
    // Wrzucamy zapytanie do kolejki huba
    this->parent_->enqueue_request(OpenThermMessage(
        OpenThermMessageType::WRITE_DATA,
        (OpenThermMessageID)this->message_id_,
        data
    ));
    
    ESP_LOGD(TAG, "Wysłano WRITE_DATA ID %d, Wartość: %u", this->message_id_, data);
  } else {
    ESP_LOGW(TAG, "Próba zmiany wartości, ale nie ustawiono msg_id lub brak połączenia z hubem!");
  }
}

void OpenthermNumber::setup() {
  float value;
  if (!this->restore_value_) {
    value = this->initial_value_;
  } else {
    this->pref_ = global_preferences->make_preference<float>(this->get_preference_hash());
    if (!this->pref_.load(&value)) {
      if (!std::isnan(this->initial_value_)) {
        value = this->initial_value_;
      } else {
        value = this->traits.get_min_value();
      }
    }
  }
  this->publish_state(value);
}

void OpenthermNumber::dump_config() {
  LOG_NUMBER("", "OpenTherm Number", this);
  ESP_LOGCONFIG(TAG,
                "  Restore value: %s", YESNO(this->restore_value_));
  ESP_LOGCONFIG(TAG,
                "  Initial value: %.2f", this->initial_value_);
  if (this->is_any_number_) {
    ESP_LOGCONFIG(TAG, "  Message ID: %d (Any Number Mode)", this->message_id_);
  }
}

}  // namespace opentherm
}  // namespace esphome
