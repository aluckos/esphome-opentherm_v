from typing import Any

from esphome.components import sensor
import esphome.config_validation as cv

# Upewnij się, że importujesz const, który zawiera CONF_FLOW_RATE
from .. import const, generate, schema, validate

DEPENDENCIES = [const.OPENTHERM]
COMPONENT_TYPE = const.SENSOR

# Jeśli Twój sensor flow_rate używa "u16" (zgodnie z Twoim schema.py), 
# upewnij się że u16 jest w MSG_DATA_TYPES
MSG_DATA_TYPES = {
    "u8_lb",
    "u8_hb",
    "s8_lb",
    "s8_hb",
    "u8_lb_60",
    "u8_hb_60",
    "u16",
    "s16",
    "f88",
    "u16_tsp",
}

def get_entity_validation_schema(entity: schema.SensorSchema) -> cv.Schema:
    return sensor.sensor_schema(
        unit_of_measurement=entity.unit_of_measurement or cv.UNDEFINED,
        accuracy_decimals=entity.accuracy_decimals,
        device_class=entity.device_class or cv.UNDEFINED,
        icon=entity.icon or cv.UNDEFINED,
        state_class=entity.state_class,
    ).extend(
        {
            cv.Optional(const.CONF_DATA_TYPE): cv.one_of(*MSG_DATA_TYPES, lower=True),
        }
    )

CONFIG_SCHEMA = validate.create_component_schema(
    schema.SENSORS, get_entity_validation_schema
)

async def to_code(config: dict[str, Any]) -> None:
    # Ten generator szuka kluczy w config, które odpowiadają kluczom w schema.SENSORS
    await generate.component_to_code(
        COMPONENT_TYPE,
        schema.SENSORS,
        sensor.Sensor,
        generate.create_only_conf(sensor.new_sensor),
        config,
    )
