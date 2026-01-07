#include "hub.h"
#include "esphome/core/helpers.h"

#include <string>

namespace esphome {
namespace opentherm {

static const char *const TAG = "opentherm";

namespace message_data {
// ... (zachowaj wszystkie funkcje parse_ i write_ bez zmian) ...
bool parse_flag8_lb_0(OpenthermData &data) { return read_bit(data.valueLB, 0); }
bool parse_flag8_lb_1(OpenthermData &data) { return read_bit(data.valueLB, 1); }
bool parse_flag8_lb_2(OpenthermData &data) { return read_bit(data.valueLB, 2); }
bool parse_flag8_lb_3(OpenthermData &data) { return read_bit(data.valueLB, 3); }
bool parse_flag8_lb_4(OpenthermData &data) { return read_bit(data.valueLB, 4); }
bool parse_flag8_lb_5(OpenthermData &data) { return read_bit(data.valueLB, 5); }
bool parse_flag8_lb_6(OpenthermData &data) { return read_bit(data.valueLB, 6); }
bool parse_flag8_lb_7(OpenthermData &data) { return read_bit(data.valueLB, 7); }
bool parse_flag8_hb_0(OpenthermData &data) { return read_bit(data.valueHB, 0); }
bool parse_flag8_hb_1(OpenthermData &data) { return read_bit(data.valueHB, 1); }
bool parse_flag8_hb_2(OpenthermData &data) { return read_bit(data.valueHB, 2); }
bool parse_flag8_hb_3(OpenthermData &data) { return read_bit(data.valueHB, 3); }
bool parse_flag8_hb_4(OpenthermData &data) { return read_bit(data.valueHB, 4); }
bool parse_flag8_hb_5(OpenthermData &data) { return read_bit(data.valueHB, 5); }
bool parse_flag8_hb_6(OpenthermData &data) { return read_bit(data.valueHB, 6); }
bool parse_flag8_hb_7(OpenthermData &data) { return read_bit(data.valueHB, 7); }
uint8_t parse_u8_lb(OpenthermData &data) { return data.valueLB; }
uint8_t parse_u8_hb(OpenthermData &data) { return data.valueHB; }
int8_t parse_s8_lb(OpenthermData &data) { return (int8_t) data.valueLB; }
int8_t parse_s8_hb(OpenthermData &data) { return (int8_t) data.valueHB; }
uint16_t parse_u16(OpenthermData &data) { return data.u16(); }
uint16_t parse_u8_lb_60(OpenthermData &data) { return data.valueLB * 60; }
uint16_t parse_u8_hb_60(OpenthermData &data) { return data.valueHB * 60; }
int16_t parse_s16(OpenthermData &data) { return data.s16(); }
float parse_f88(OpenthermData &data) { return data.f88(); }

void write_flag8_lb_0(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 0, value); }
void write_flag8_lb_1(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 1, value); }
void write_flag8_lb_2(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 2, value); }
void write_flag8_lb_3(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 3, value); }
void write_flag8_lb_4(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 4, value); }
void write_flag8_lb_5(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 5, value); }
void write_flag8_lb_6(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 6, value); }
void write_flag8_lb_7(const bool value, OpenthermData &data) { data.valueLB = write_bit(data.valueLB, 7, value); }
void write_flag8_hb_0(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 0, value); }
void write_flag8_hb_1(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 1, value); }
void write_flag8_hb_2(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 2, value); }
void write_flag8_hb_3(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 3, value); }
void write_flag8_hb_4(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 4, value); }
void write_flag8_hb_5(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 5, value); }
void write_flag8_hb_6(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 6, value); }
void write_flag8_hb_7(const bool value, OpenthermData &data) { data.valueHB = write_bit(data.valueHB, 7, value); }
void write_u8_lb(const uint8_t value, OpenthermData &data) { data.valueLB = value; }
void write_u8_hb(const uint8_t value, OpenthermData &data) { data.valueHB = value; }
void write_s8_lb(const int8_t value, OpenthermData &data) { data.valueLB = (uint8_t) value; }
void write_s8_hb(const int8_t value, OpenthermData &data) { data.valueHB = (uint8_t) value; }
void write_u16(const uint16_t value, OpenthermData &data) { data.u16(value); }
void write_s16(const int16_t value, OpenthermData &data) { data.s16(value); }
void write_f88(const float value, OpenthermData &data) { data.f88(value); }
}  // namespace message_data

OpenthermData OpenthermHub::build_request_(MessageId request_id) const {
  OpenthermData data;
  data.type = 0;
  data.id = request_id;
  data.valueHB = 0;
  data.valueLB = 0;

  if (request_id == MessageId::STATUS) {
    bool const ch_enabled = this->ch_enable && OPENTHERM_READ_ch_enable && OPENTHERM_READ_t_set > 0.0;
    bool const dhw_enabled = this->dhw_enable && OPENTHERM_READ_dhw_enable;
    bool const cooling_enabled =
        this->cooling_enable && OPENTHERM_READ_cooling_enable && OPENTHERM_READ_cooling_control > 0.0;
    bool const otc_enabled = this->otc_active && OPENTHERM_READ_otc_active;
    bool const ch2_enabled = this->ch2_active && OPENTHERM_READ_ch2_active && OPENTHERM_READ_t_set_ch2 > 0.0;
    bool const summer_mode_is_active = this->summer_mode_active && OPENTHERM_READ_summer_mode_active;
    bool const dhw_blocked = this->dhw_block && OPENTHERM_READ_dhw_block;

    data.type = MessageType::READ_DATA;
    data.valueHB = ch_enabled | (dhw_enabled << 1) | (cooling_enabled << 2) | (otc_enabled << 3) | (ch2_enabled << 4) |
                   (summer_mode_is_active << 5) | (dhw_blocked << 6);

    return data;
  }

  // --- START MODYFIKACJI BRINK TSP 52/53 ---
  if (request_id == MessageId::HVAC_IDX_TSP) {
    static bool flip_tsp = false;
    data.type = MessageType::READ_DATA;
    data.id = request_id;
    data.valueHB = flip_tsp ? 53 : 52; // Naprzemiennie prosimy o Low Byte (52) i High Byte (53)
    data.valueLB = 0;
    flip_tsp = !flip_tsp;
    return data;
  }
  // --- KONIEC MODYFIKACJI ---

  switch (request_id) {
    OPENTHERM_SWITCH_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_WRITE_MESSAGE, OPENTHERM_MESSAGE_WRITE_ENTITY, ,
                                      OPENTHERM_MESSAGE_WRITE_POSTSCRIPT, )
    OPENTHERM_NUMBER_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_WRITE_MESSAGE, OPENTHERM_MESSAGE_WRITE_ENTITY, ,
                                      OPENTHERM_MESSAGE_WRITE_POSTSCRIPT, )
    OPENTHERM_OUTPUT_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_WRITE_MESSAGE, OPENTHERM_MESSAGE_WRITE_ENTITY, ,
                                      OPENTHERM_MESSAGE_WRITE_POSTSCRIPT, )
    OPENTHERM_INPUT_SENSOR_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_WRITE_MESSAGE, OPENTHERM_MESSAGE_WRITE_ENTITY, ,
                                            OPENTHERM_MESSAGE_WRITE_POSTSCRIPT, )
    OPENTHERM_SETTING_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_WRITE_MESSAGE, OPENTHERM_MESSAGE_WRITE_SETTING, ,
                                       OPENTHERM_MESSAGE_WRITE_POSTSCRIPT, )
    default:
      break;
  }

  switch (request_id) {
    OPENTHERM_SENSOR_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_READ_MESSAGE, OPENTHERM_IGNORE, , , )
    default:
      break;
  }
  switch (request_id) {
    OPENTHERM_BINARY_SENSOR_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_READ_MESSAGE, OPENTHERM_IGNORE, , , )
    default:
      break;
  }

  ESP_LOGE(TAG, "Tried to create a request with unknown id %d. This should never happen.", request_id);
  return {};
}

OpenthermHub::OpenthermHub() : Component(), in_pin_{}, out_pin_{} {}

void OpenthermHub::process_response(OpenthermData &data) {
  ESP_LOGD(TAG, "Received OpenTherm response with id %d (%s)", data.id,
           this->opentherm_->message_id_to_str((MessageId) data.id));
  this->opentherm_->debug_data(data);

  // --- START MODYFIKACJI ODBIORU BRINK TSP ---
  if (data.id == MessageId::HVAC_IDX_TSP) {
    static uint8_t brink_temp_lb = 0;
    if (data.valueHB == 52) {
      brink_temp_lb = data.valueLB;
      ESP_LOGD(TAG, "Odebrano TSP 52 (Low Byte): %d", brink_temp_lb);
    } else if (data.valueHB == 53) {
      uint16_t full_flow = ((uint16_t)data.valueLB << 8) | brink_temp_lb;
      ESP_LOGD(TAG, "Odebrano TSP 53 (High Byte): %d -> Pełny przepływ: %d m3/h", data.valueLB, full_flow);
      // Przekazujemy wynik do sensora flow_rate jeśli istnieje
      if (this->flow_rate_sensor_ != nullptr) {
        this->flow_rate_sensor_->publish_state((float)full_flow);
      }
    }
    return; // Kończymy procesowanie dla tego ID
  }
  // --- KONIEC MODYFIKACJI ---

  switch (data.id) {
    OPENTHERM_SENSOR_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_RESPONSE_MESSAGE, OPENTHERM_MESSAGE_RESPONSE_ENTITY, ,
                                      OPENTHERM_MESSAGE_RESPONSE_POSTSCRIPT, )
  }
  switch (data.id) {
    OPENTHERM_BINARY_SENSOR_MESSAGE_HANDLERS(OPENTHERM_MESSAGE_RESPONSE_MESSAGE, OPENTHERM_MESSAGE_RESPONSE_ENTITY, ,
                                             OPENTHERM_MESSAGE_RESPONSE_POSTSCRIPT, )
  }
}

// ... (reszta metod setup, loop, itp. pozostaje bez zmian) ...
void OpenthermHub::setup() {
  this->opentherm_ = make_unique<OpenTherm>(this->in_pin_, this->out_pin_);
  if (!this->opentherm_->initialize()) {
    ESP_LOGE(TAG, "Failed to initialize OpenTherm protocol.");
    this->mark_failed();
    return;
  }
  this->add_repeating_message(MessageId::STATUS);
  this->write_initial_messages_(this->messages_);
  this->message_iterator_ = this->messages_.begin();
}

void OpenthermHub::on_shutdown() { this->opentherm_->stop(); }

void OpenthermHub::write_initial_messages_(std::vector<MessageId> &target) {
  std::vector<std::pair<MessageId, uint8_t>> sorted;
  std::copy_if(this->configured_messages_.begin(), this->configured_messages_.end(), std::back_inserter(sorted),
               [](const std::pair<MessageId, uint8_t> &pair) { return pair.second < REPEATING_MESSAGE_ORDER; });
  std::sort(sorted.begin(), sorted.end(),
            [](const std::pair<MessageId, uint8_t> &a, const std::pair<MessageId, uint8_t> &b) {
              return a.second < b.second;
            });
  target.clear();
  std::transform(sorted.begin(), sorted.end(), std::back_inserter(target),
                 [](const std::pair<MessageId, uint8_t> &pair) { return pair.first; });
}

void OpenthermHub::write_repeating_messages_(std::vector<MessageId> &target) {
  target.clear();
  for (auto const &pair : this->configured_messages_) {
    if (pair.second == REPEATING_MESSAGE_ORDER) {
      target.push_back(pair.first);
    }
  }
}

void OpenthermHub::loop() {
  if (this->sync_mode_) { this->sync_loop_(); return; }
  auto cur_time = millis();
  auto const cur_mode = this->opentherm_->get_mode();
  if (this->handle_error_(cur_mode)) return;
  switch (cur_mode) {
    case OperationMode::IDLE:
      this->check_timings_(cur_time);
      if (this->should_skip_loop_(cur_time)) break;
      this->start_conversation_();
      break;
    case OperationMode::SENT:
      this->opentherm_->listen();
      break;
    case OperationMode::RECEIVED:
      this->read_response_();
      break;
    default: break;
  }
}

bool OpenthermHub::handle_error_(OperationMode mode) {
  switch (mode) {
    case OperationMode::ERROR_PROTOCOL: this->handle_protocol_error_(); return true;
    case OperationMode::ERROR_TIMEOUT: this->handle_timeout_error_(); return true;
    case OperationMode::ERROR_TIMER: this->handle_timer_error_(); return true;
    default: return false;
  }
}

void OpenthermHub::sync_loop_() {
  if (!this->opentherm_->is_idle()) return;
  auto cur_time = millis();
  this->check_timings_(cur_time);
  if (this->should_skip_loop_(cur_time)) return;
  this->start_conversation_();
  if (this->handle_error_(this->opentherm_->get_mode())) return;
  if (!this->spin_wait_(1150, [&] { return this->opentherm_->is_active(); })) { this->stop_opentherm_(); return; }
  if (this->handle_error_(this->opentherm_->get_mode())) return;
  this->opentherm_->listen();
  if (!this->spin_wait_(1150, [&] { return this->opentherm_->is_active(); })) { this->stop_opentherm_(); return; }
  if (this->handle_error_(this->opentherm_->get_mode())) return;
  this->read_response_();
}

void OpenthermHub::check_timings_(uint32_t cur_time) {
  if (this->last_conversation_start_ > 0 && (cur_time - this->last_conversation_start_) > 1150) {
    ESP_LOGW(TAG, "%d ms elapsed since last convo...", (int)(cur_time - this->last_conversation_start_));
  }
}

bool OpenthermHub::should_skip_loop_(uint32_t cur_time) const {
  return (this->last_conversation_end_ > 0 && (cur_time - this->last_conversation_end_) < 100);
}

void OpenthermHub::start_conversation_() {
  if (this->message_iterator_ == this->messages_.end()) {
    if (this->sending_initial_) {
      this->sending_initial_ = false;
      this->write_repeating_messages_(this->messages_);
    }
    this->message_iterator_ = this->messages_.begin();
  }
  auto request = this->build_request_(*this->message_iterator_);
  this->before_send_callback_.call(request);
  ESP_LOGD(TAG, "Sending request with id %d (%s)", request.id, this->opentherm_->message_id_to_str((MessageId) request.id));
  this->last_conversation_start_ = millis();
  this->opentherm_->send(request);
}

void OpenthermHub::read_response_() {
  OpenthermData response;
  if (!this->opentherm_->get_message(response)) { this->stop_opentherm_(); return; }
  this->stop_opentherm_();
  this->before_process_response_callback_.call(response);
  this->process_response(response);
  this->message_iterator_++;
}

void OpenthermHub::stop_opentherm_() {
  this->opentherm_->stop();
  this->last_conversation_end_ = millis();
}

void OpenthermHub::handle_protocol_error_() { this->stop_opentherm_(); }
void OpenthermHub::handle_timeout_error_() { this->stop_opentherm_(); }
void OpenthermHub::handle_timer_error_() { this->mark_failed(); }

void OpenthermHub::dump_config() {
  ESP_LOGCONFIG(TAG, "OpenTherm:");
  LOG_PIN("  In: ", this->in_pin_);
  LOG_PIN("  Out: ", this->out_pin_);
}

}  // namespace opentherm
}  // namespace esphome
