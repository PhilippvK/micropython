#include "py/obj.h"
//#include <xmc_common.h>
#include "pin.h"

// Returns the pin mode. This value returned by this macro should be one of:
// GPIO_MODE_INPUT, GPIO_MODE_OUTPUT_PP, GPIO_MODE_OUTPUT_OD,
// GPIO_MODE_AF_PP, GPIO_MODE_AF_OD, or GPIO_MODE_ANALOG.

uint32_t pin_get_mode(const pin_obj_t *pin) {
    XMC_GPIO_MODE_t gpio_mode = pin->pin_mode->mode;
    uint32_t mode = 0;

    switch (gpio_mode) {
        case XMC_GPIO_MODE_OUTPUT_PUSH_PULL:
            mode = GPIO_MODE_OUTPUT_PP;
            break;
        case XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN:
            mode = GPIO_MODE_OUTPUT_OD;
            break;
        case XMC_GPIO_MODE_INPUT_TRISTATE:
        case XMC_GPIO_MODE_INPUT_PULL_DOWN:
        case XMC_GPIO_MODE_INPUT_PULL_UP:
        case XMC_GPIO_MODE_INPUT_INVERTED_TRISTATE:
        case XMC_GPIO_MODE_INPUT_INVERTED_PULL_DOWN:
        case XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP:
            mode = GPIO_MODE_INPUT;
            break;
//        case XMC_GPIO_MODE_OUTPUT_ALT1:
//        case XMC_GPIO_MODE_OUTPUT_ALT2:
//        case XMC_GPIO_MODE_OUTPUT_ALT3:
//        case XMC_GPIO_MODE_OUTPUT_ALT4:
        case XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1:
        case XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2:
        case XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3:
        case XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4:
            mode = GPIO_MODE_AF_PP;
            break;
        case XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT1:
        case XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2:
        case XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT3:
        case XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT4:
            mode = GPIO_MODE_AF_OD;
            break;
        case XMC_GPIO_MODE_INPUT_SAMPLING:
        case XMC_GPIO_MODE_INPUT_INVERTED_SAMPLING:
            mode = GPIO_MODE_ANALOG;
            break;
        default:
            mode = XMC_GPIO_MODE_INPUT_TRISTATE;
    }

    return mode;
}

// Returns the pin pullup/pulldown. The value returned by this macro should
// be one of GPIO_NOPULL, GPIO_PULLUP, or GPIO_PULLDOWN.

uint32_t pin_get_pull(const pin_obj_t *pin) {
    uint32_t ret = 0;
    XMC_GPIO_MODE_t gpio_mode = pin->pin_mode->mode;

    switch (gpio_mode) {
        case XMC_GPIO_MODE_INPUT_PULL_UP:
        case XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP:
            ret = GPIO_PULLUP;
            break;
        case XMC_GPIO_MODE_INPUT_PULL_DOWN:
        case XMC_GPIO_MODE_INPUT_INVERTED_PULL_DOWN:
            ret = GPIO_PULLDOWN;
            break;
        default:
            ret = GPIO_NOPULL;
    }

    return ret;
}

// Returns the af (alternate function) index currently set for a pin.

uint32_t pin_get_af(const pin_obj_t *pin) {
    XMC_GPIO_MODE_t gpio_mode = pin->pin_mode->mode;

    return (gpio_mode >> PORT0_IOCR0_PC0_Pos) & 0b111;
}

