#pragma once
namespace esphome {
namespace opentherm {

// ... (zachowaj początek pliku bez zmian aż do OPENTHERM_SET_SETTING) ...

// ===== hub.cpp macros =====

// Nowe makro do budowania zapytań TSP (HVAC_IDX_TSP)
// Wykorzystuje przełącznik (flip-flop) do naprzemiennego odpytywania bajtów 52 i 53
#define OPENTHERM_MESSAGE_TSP_READ_MESSAGE(msg, index_low, index_high) \
  case MessageId::msg: { \
    static bool flip = false; \
    data.type = MessageType::READ_DATA; \
    data.id = request_id; \
    data.valueHB = flip ? index_high : index_low; \
    flip = !flip; \
    return data; \
  }

// Nowe makro do odbierania i składania danych TSP
// Składa dane tylko gdy otrzyma bajt wysoki (index_high)
#define OPENTHERM_MESSAGE_TSP_RESPONSE(msg, key, index_low, index_high) \
  case MessageId::msg: { \
    static uint8_t temp_lb = 0; \
    if (data.valueHB == index_low) { \
      temp_lb = data.valueLB; \
    } else if (data.valueHB == index_high) { \
      if (this->key != nullptr) { \
        this->key->publish_state(((uint16_t)data.valueLB << 8) | temp_lb); \
      } \
    } \
    break; \
  }

// ... (reszta standardowych makr pozostaje bez zmian) ...

// Write data request builders
#define OPENTHERM_MESSAGE_WRITE_MESSAGE(msg) \
  case MessageId::msg: { \
    data.type = MessageType::WRITE_DATA; \
    data.id = request_id;
#define OPENTHERM_MESSAGE_WRITE_ENTITY(key, msg_data) message_data::write_##msg_data(this->key->state, data);
#define OPENTHERM_MESSAGE_WRITE_SETTING(key, msg_data) message_data::write_##msg_data(this->key, data);
#define OPENTHERM_MESSAGE_WRITE_POSTSCRIPT \
  return data; \
  }

#define OPENTHERM_MESSAGE_READ_MESSAGE(msg) \
  case MessageId::msg: \
    data.type = MessageType::READ_DATA; \
    data.id = request_id; \
    return data;

#define OPENTHERM_MESSAGE_RESPONSE_MESSAGE(msg) case MessageId::msg:
#define OPENTHERM_MESSAGE_RESPONSE_ENTITY(key, msg_data) if(this->key != nullptr) this->key->publish_state(message_data::parse_##msg_data(data));
#define OPENTHERM_MESSAGE_RESPONSE_POSTSCRIPT break;

// ... (reszta pliku) ...
