import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_INITIAL_VALUE,
    CONF_RESTORE_VALUE,
    CONF_MIN_VALUE,
    CONF_MAX_VALUE,
    CONF_STEP,
)
from .. import opentherm_ns, OpenthermComponent, CONF_OPENTHERM_ID

# Deklaracja klasy C++
OpenthermNumber = opentherm_ns.class_(
    "OpenthermNumber", number.Number, cg.Component
)

CONF_MSG_ID = "msg_id"

CONFIG_SCHEMA = number.number_schema(
    OpenthermNumber,
).extend(
    {
        cv.GenerateID(CONF_OPENTHERM_ID): cv.use_id(OpenthermComponent),
        cv.Required(CONF_MSG_ID): cv.uint8_t,
        cv.Optional(CONF_INITIAL_VALUE): cv.float_,
        # POPRAWKA: cv.boolean zamiast cv.bool_
        cv.Optional(CONF_RESTORE_VALUE, default=False): cv.boolean,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_pointer(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Rejestracja bazy komponentu number
    await number.register_number(
        var,
        config,
        min_value=config[CONF_MIN_VALUE] if CONF_MIN_VALUE in config else 0,
        max_value=config[CONF_MAX_VALUE] if CONF_MAX_VALUE in config else 100,
        step=config[CONF_STEP] if CONF_STEP in config else 1,
    )

    parent = await cg.get_variable(config[CONF_OPENTHERM_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_message_id(config[CONF_MSG_ID]))

    if CONF_INITIAL_VALUE in config:
        cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
    cg.add(var.set_restore_value(config[CONF_RESTORE_VALUE]))
