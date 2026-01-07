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
# Importujemy namespace i komponent główny z folderu wyżej
from .. import opentherm_ns, OpenthermComponent, CONF_OPENTHERM_ID

# Deklaracja klasy C++
OpenthermNumber = opentherm_ns.class_(
    "OpenthermNumber", number.Number, cg.Component
)

CONF_MSG_ID = "msg_id"

CONFIG_SCHEMA = number.NUMBER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(OpenthermNumber),
        cv.GenerateID(CONF_OPENTHERM_ID): cv.use_id(OpenthermComponent),
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_MSG_ID): cv.uint8_t, # To odblokowuje msg_id w YAML
        cv.Optional(CONF_INITIAL_VALUE): cv.float_,
        cv.Optional(CONF_RESTORE_VALUE, default=False): cv.bool_,
        cv.Optional(CONF_MIN_VALUE, default=0): cv.float_,
        cv.Optional(CONF_MAX_VALUE, default=100): cv.float_,
        cv.Optional(CONF_STEP, default=1): cv.float_,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_pointer(config[CONF_ID])
    await cg.register_component(var, config)
    await number.register_number(
        var,
        config,
        min_value=config[CONF_MIN_VALUE],
        max_value=config[CONF_MAX_VALUE],
        step=config[CONF_STEP],
    )

    parent = await cg.get_variable(config[CONF_OPENTHERM_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_message_id(config[CONF_MSG_ID]))

    if CONF_INITIAL_VALUE in config:
        cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
    cg.add(var.set_restore_value(config[CONF_RESTORE_VALUE]))
