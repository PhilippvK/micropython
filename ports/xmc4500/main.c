#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "py/nlr.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "lib/utils/pyexec.h"

#include "gccollect.h"
#include "modnetwork.h"
#include "lib/mp-readline/readline.h"
#include "storage.h"

#include "VirtualSerial.h"

#include "py/stackctrl.h"

#include "led.h"
#include "led_pwm.h"

#include "systick.h"

// TODO
#include <xmc_scu.h>
#include <xmc4_scu.h>
#include <xmc_ccu4.h>
#define MP_STACK_SIZE (16 * 1024)

static char *stack_top;
static char heap[16 * 1024];

/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .syspll_config.p_div = 2,
  .syspll_config.n_div = 80,
  .syspll_config.k_div = 4,
  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,
  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 1,
  .fcpu_clkdiv = 1,
  .fccu_clkdiv = 1,
  .fperipheral_clkdiv = 1
};


void SystemCoreClockSetup(void)
{
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);

  XMC_SCU_CLOCK_EnableUsbPll();
  XMC_SCU_CLOCK_StartUsbPll(2, 64);
  XMC_SCU_CLOCK_SetUsbClockDivider(4);
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  SystemCoreClockUpdate();
}

void led_blink(xmc_led_t led, mp_uint_t count, mp_uint_t target) {
    for (int i = 0 ; i < count ; i++ ){
        mp_uint_t tick0 = mp_hal_ticks_ms();
        while(( mp_hal_ticks_ms()-tick0) < target);
        led_state(led, 1);
        tick0 = mp_hal_ticks_ms();
        while(( mp_hal_ticks_ms()-tick0) < target);
        led_state(led, 0);
    }
}

void xmc_init(void) {
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
  uint32_t start_tick = HAL_GetTick();

  USB_Init();

  led_init();
  
  systick_wait_at_least(start_tick, 200);
}

void fade_leds(void) {
    int8_t dir = 1;
    uint16_t val = 0;
    uint8_t i = 0;
    while(i<10) {
      for(int32_t waiter=(1<<5); waiter >= 0; waiter--);
      val += dir;
      if (dir < 0 && val == 0) {
        dir = +1;
        i++;
        led_toggle(XMC_LED1);
      } else if (dir > 0 && val == 0xFFFF) {
        dir = -1;
        i++;
        led_toggle(XMC_LED1);
      }
      led_set_intensity(XMC_LED2,val);
    }
}

int main(int argc, char **argv) {

    volatile int stack_dummy;
    stack_top = (char*)&stack_dummy;

    xmc_init();

soft_reset:
    fade_leds();

    led_state(XMC_LED1, 0);
    led_state(XMC_LED2, 0);
    // Stack limit should be less than real stack size, so we have a chance
    // to recover from limit hit.  (Limit is measured in bytes.)
    // Note: stack control relies on main thread being initialised above
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(MP_STACK_SIZE - 1024);
    //mp_stack_set_limit((mp_uint_t)((char*)&stack_dummy - 1024));

    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init();

    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir
    mp_obj_list_init(mp_sys_argv, 0);

  //  led_blink(XMC_LED2,50,100);

    readline_init0();

    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            if (pyexec_raw_repl() != 0) {
                break;
            }
        } else {
            if (pyexec_friendly_repl() != 0) {
                break;
            }
        }
    }

    printf("PYB: soft reboot\n");

    mp_deinit();

    goto soft_reset;
}

void gc_collect(void) {
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    void *dummy;
    gc_collect_start();
    gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end();
}

mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    return NULL;
}

mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_obj_t mp_builtin_open(uint n_args, const mp_obj_t *args, mp_map_t *kwargs) {
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

void NORETURN __fatal_error(const char *msg) {
//    led_state(1, 1);
//    led_state(2, 1);
//    led_state(3, 1);
//    led_state(4, 1);
//    mp_hal_stdout_tx_strn("\nFATAL ERROR:\n", 14);
//    mp_hal_stdout_tx_strn(msg, strlen(msg));
    for (uint i = 0;;) {
//      led_toggle(((i++) & 3) + 1);
         i++;
        for (volatile uint delay = 0; delay < 10000000; delay++) {
        }
        if (i >= 16) {
            // to conserve power
            __WFI();
        }
    }
}

void nlr_jump_fail(void *val) {
    printf("FATAL: uncaught exception %p\n", val);
    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
    __fatal_error("");
}

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif
