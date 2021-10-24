#include <stdint.h>
#include XMC_HAL_H

// options to control how Micro Python is built

#define MICROPY_QSTR_EXTRA_POOL     mp_qstr_frozen_const_pool
#define MICROPY_ALLOC_PATH_MAX      (128)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT (16)
//#define MICROPY_EMIT_THUMB          (1)
//#define MICROPY_EMIT_INLINE_THUMB   (1)
#define MICROPY_COMP_MODULE_CONST   (1)
#define MICROPY_COMP_CONST          (1)
#define MICROPY_MEM_STATS           (0)
#define MICROPY_DEBUG_PRINTERS      (0)

#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (1)
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (1)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_PY_GC_COLLECT_RETVAL (0)
#define MICROPY_HELPER_REPL         (1)
#define MICROPY_REPL_EMACS_KEYS     (1)
#define MICROPY_REPL_AUTO_INDENT    (1)
#define MICROPY_HELPER_LEXER_UNIX   (1)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_NORMAL)
#define MICROPY_WARNINGS            (0)
#define MICROPY_OPT_COMPUTED_GOTO   (1)
#define MICROPY_OPT_MPZ_BITWISE     (1)
#define MICROPY_CAN_OVERRIDE_BUILTINS (1)
#define MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG (0)
#define MICROPY_CPYTHON_COMPAT      (0)
#define MICROPY_USE_INTERNAL_ERRNO  (0)
#define MICROPY_PY_BUILTINS_STR_UNICODE (1)
#define MICROPY_PY_BUILTINS_BYTEARRAY (1)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (1)
#define MICROPY_PY_BUILTINS_ENUMERATE (1)
#define MICROPY_PY_BUILTINS_FILTER  (1)
#define MICROPY_PY_BUILTINS_FROZENSET (1)
#define MICROPY_PY_BUILTINS_REVERSED (1)
#define MICROPY_PY_BUILTINS_SET     (1)
#define MICROPY_PY_BUILTINS_SLICE   (1)
#define MICROPY_PY_BUILTINS_PROPERTY (1)
#define MICROPY_PY_BUILTINS_MIN_MAX (1)
#define MICROPY_PY_BUILTINS_HELP    (1)
#define MICROPY_PY_BUILTINS_HELP_TEXT xmc_help_text
#define MICROPY_PY_BUILTINS_HELP_MODULES (1)
#define MICROPY_PY_GC               (1)
#define MICROPY_PY_ARRAY            (1)
#define MICROPY_PY_ATTRTUPLE        (1)
#define MICROPY_PY_COLLECTIONS      (1)
#define MICROPY_PY_MATH             (1)
#define MICROPY_PY_CMATH            (1)
#define MICROPY_PY_IO               (0)
#define MICROPY_PY_STRUCT           (1)
#define MICROPY_PY_SYS              (1)
#define MICROPY_PY_SYS_STDFILES     (0)
#ifndef MICROPY_MODULE_FROZEN_MPY // defined in Makefile?
#define MICROPY_MODULE_FROZEN_MPY   (1)
#endif /* MICROPY_MODULE_FROZEN_MPY */
#ifndef MICROPY_FLOAT_IMPL // defined in Makefile?
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_FLOAT)
#endif /* MICROPY_FLOAT_IMPL */

// Whether to include the stm module, with peripheral register constants
#ifndef MICROPY_PY_XMC
#define MICROPY_PY_XMC (1)
#endif

// Whether to enable the RTC, exposed as pyb.RTC
#ifndef MICROPY_HW_ENABLE_RTC
#define MICROPY_HW_ENABLE_RTC (0)
#endif

// Whether to enable the hardware RNG peripheral, exposed as pyb.rng()
#ifndef MICROPY_HW_ENABLE_RNG
#define MICROPY_HW_ENABLE_RNG (0)
#endif

// Whether to enable the ADC peripheral, exposed as pyb.ADC and pyb.ADCAll
#ifndef MICROPY_HW_ENABLE_ADC
#define MICROPY_HW_ENABLE_ADC (0)
#endif

// Whether to enable the DAC peripheral, exposed as pyb.DAC
#ifndef MICROPY_HW_ENABLE_DAC
#define MICROPY_HW_ENABLE_DAC (0)
#endif

// Heap start / end definitions
#ifndef MICROPY_HEAP_START
#define MICROPY_HEAP_START &_heap_start
#endif
#ifndef MICROPY_HEAP_END
#define MICROPY_HEAP_END &_heap_end
#endif

// Enable hardware I2C if there are any peripherals defined
/*#if defined(MICROPY_HW_I2C1_SCL) || defined(MICROPY_HW_I2C2_SCL) \
    || defined(MICROPY_HW_I2C3_SCL) || defined(MICROPY_HW_I2C4_SCL)
#define MICROPY_HW_ENABLE_HW_I2C (1)
#else
#define MICROPY_HW_ENABLE_HW_I2C (0)
#endif
*/

// Enable CAN if there are any peripherals defined
#if defined(MICROPY_HW_CAN1_TX) || defined(MICROPY_HW_CAN2_TX) || defined(MICROPY_HW_CAN3_TX)
#define MICROPY_HW_ENABLE_CAN (1)
#if defined(STM32H7)
#define MICROPY_HW_ENABLE_FDCAN (1) // define for MCUs with FDCAN
#endif
#else
#define MICROPY_HW_ENABLE_CAN (0)
#define MICROPY_HW_MAX_CAN (0)
#endif
#if defined(MICROPY_HW_CAN3_TX)
#define MICROPY_HW_MAX_CAN (3)
#elif defined(MICROPY_HW_CAN2_TX)
#define MICROPY_HW_MAX_CAN (2)
#elif defined(MICROPY_HW_CAN1_TX)
#define MICROPY_HW_MAX_CAN (1)
#endif

// Pin definition header file
#define MICROPY_PIN_DEFS_PORT_H "pin_defs_xmc4500.h"

// type definitions for the specific machine

#define BYTES_PER_WORD (4)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

// This port is intended to be 32-bit, but unfortunately, int32_t for
// different targets may be defined in different ways - either as int
// or as long. This requires different printf formatting specifiers
// to print such value. So, we avoid int32_t and use int directly.
#define UINT_FMT "%u"
#define INT_FMT "%d"
typedef int mp_int_t; // must be pointer size
typedef unsigned mp_uint_t; // must be pointer size

typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size
typedef long mp_off_t;

#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

// memory allocation policies
#ifndef MICROPY_GC_STACK_ENTRY_TYPE
#if MICROPY_HW_SDRAM_SIZE
#define MICROPY_GC_STACK_ENTRY_TYPE uint32_t
#else
#define MICROPY_GC_STACK_ENTRY_TYPE uint16_t
#endif
#endif
//#define MICROPY_ALLOC_PATH_MAX      (128)

// emitters
#define MICROPY_PERSISTENT_CODE_LOAD (1)
#ifndef MICROPY_EMIT_THUMB
#define MICROPY_EMIT_THUMB          (1)
#endif
#ifndef MICROPY_EMIT_INLINE_THUMB
#define MICROPY_EMIT_INLINE_THUMB   (1)
#endif

// compiler configuration
//#define MICROPY_COMP_MODULE_CONST   (1)
//#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (1)
#define MICROPY_COMP_RETURN_IF_EXPR (1)

// optimisations
//#define MICROPY_OPT_COMPUTED_GOTO   (1)
//#define MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE (0)
//#define MICROPY_OPT_MPZ_BITWISE     (1)
//#define MICROPY_OPT_MATH_FACTORIAL  (1)

// Python internal features
//#define MICROPY_READER_VFS          (1)
//#define MICROPY_ENABLE_GC           (1)
#define MICROPY_ENABLE_FINALISER    (1)
#define MICROPY_STACK_CHECK         (1)
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (1)
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE (0)
#define MICROPY_READER_POSIX        (0)
//#define MICROPY_KBD_EXCEPTION       (1)
//#define MICROPY_HELPER_REPL         (1)
//#define MICROPY_REPL_EMACS_KEYS     (1)
//#define MICROPY_REPL_AUTO_INDENT    (1)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_MPZ)
//#define MICROPY_ENABLE_SOURCE_LINE  (1)
//#define MICROPY_STREAMS_NON_BLOCK   (1)
#define MICROPY_MODULE_WEAK_LINKS   (1)
//#define MICROPY_CAN_OVERRIDE_BUILTINS (1)
//#define MICROPY_USE_INTERNAL_ERRNO  (1)
//#define MICROPY_ENABLE_SCHEDULER    (1)
//#define MICROPY_SCHEDULER_DEPTH     (8)
//#define MICROPY_VFS                 (1)
//#ifndef MICROPY_VFS_FAT
//#define MICROPY_VFS_FAT             (1)
//#endif

// control over Python builtins
#define MICROPY_PY_FUNCTION_ATTRS   (1)
#define MICROPY_PY_DESCRIPTORS      (1)
#define MICROPY_PY_DELATTR_SETATTR  (1)
//#define MICROPY_PY_BUILTINS_STR_UNICODE (1)
#define MICROPY_PY_BUILTINS_STR_CENTER (1)
#define MICROPY_PY_BUILTINS_STR_PARTITION (1)
#define MICROPY_PY_BUILTINS_STR_SPLITLINES (1)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (1)
//#define MICROPY_PY_BUILTINS_FROZENSET (1)
#define MICROPY_PY_BUILTINS_SLICE_ATTRS (1)
#define MICROPY_PY_BUILTINS_ROUND_INT (1)
#define MICROPY_PY_ALL_SPECIAL_METHODS (1)
#define MICROPY_PY_BUILTINS_COMPILE (MICROPY_ENABLE_COMPILER)
#define MICROPY_PY_BUILTINS_EXECFILE (MICROPY_ENABLE_COMPILER)
#define MICROPY_PY_BUILTINS_NOTIMPLEMENTED (1)
#define MICROPY_PY_BUILTINS_INPUT   (1)
#define MICROPY_PY_BUILTINS_POW3    (1)
//#define MICROPY_PY_BUILTINS_HELP    (1)
//#define MICROPY_PY_BUILTINS_HELP_TEXT stm32_help_text
//#define MICROPY_PY_BUILTINS_HELP_MODULES (1)
#define MICROPY_PY___FILE__         (0)
#define MICROPY_PY_MICROPYTHON_MEM_INFO (1)
#define MICROPY_PY_ARRAY_SLICE_ASSIGN (1)
#define MICROPY_PY_COLLECTIONS_DEQUE (1)
#define MICROPY_PY_COLLECTIONS_ORDEREDDICT (1)
#define MICROPY_PY_MATH_SPECIAL_FUNCTIONS (1)
#define MICROPY_PY_MATH_ISCLOSE     (1)
#define MICROPY_PY_MATH_FACTORIAL   (1)
//#define MICROPY_PY_CMATH            (1)
//#define MICROPY_PY_IO               (1)
//#define MICROPY_PY_IO_IOBASE        (1)
//#define MICROPY_PY_IO_FILEIO        (MICROPY_VFS_FAT) // because mp_type_fileio/textio point to fatfs impl
#define MICROPY_PY_SYS_MAXSIZE      (1)
#define MICROPY_PY_SYS_EXIT         (1)
//#define MICROPY_PY_SYS_STDFILES     (1)
#define MICROPY_PY_SYS_STDIO_BUFFER (1)
//#ifndef MICROPY_PY_SYS_PLATFORM     // let boards override it if they want
//#define MICROPY_PY_SYS_PLATFORM     "pyboard"
//#endif
#define MICROPY_PY_UERRNO           (1)
#ifndef MICROPY_PY_THREAD
#define MICROPY_PY_THREAD           (0)
#endif

// extended modules
//#define MICROPY_PY_UCTYPES          (1)
//#define MICROPY_PY_UZLIB            (1)
//#define MICROPY_PY_UJSON            (1)
//#define MICROPY_PY_URE              (1)
//#define MICROPY_PY_URE_SUB          (1)
//#define MICROPY_PY_UHEAPQ           (1)
//#define MICROPY_PY_UHASHLIB         (1)
//#define MICROPY_PY_UHASHLIB_MD5     (MICROPY_PY_USSL)
//#define MICROPY_PY_UHASHLIB_SHA1    (MICROPY_PY_USSL)
//#define MICROPY_PY_UCRYPTOLIB       (MICROPY_PY_USSL)
//#define MICROPY_PY_UBINASCII        (1)
//#define MICROPY_PY_URANDOM          (1)
//#define MICROPY_PY_URANDOM_EXTRA_FUNCS (1)
#define MICROPY_PY_USELECT          (0)
#define MICROPY_PY_UTIMEQ           (1)
#define MICROPY_PY_UTIME_MP_HAL     (1)
#define MICROPY_PY_OS_DUPTERM       (3)
#define MICROPY_PY_UOS_DUPTERM_BUILTIN_STREAM (1)
//#define MICROPY_PY_LWIP_SOCK_RAW    (MICROPY_PY_LWIP)
//#define MICROPY_PY_MACHINE          (1)
//#define MICROPY_PY_MACHINE_PULSE    (1)
//#define MICROPY_PY_MACHINE_PIN_MAKE_NEW mp_pin_make_new
//#define MICROPY_PY_MACHINE_I2C      (1)
//#if MICROPY_HW_ENABLE_HW_I2C
//#define MICROPY_PY_MACHINE_I2C_MAKE_NEW machine_hard_i2c_make_new
//#endif
//#define MICROPY_PY_MACHINE_SPI      (1)
//#define MICROPY_PY_MACHINE_SPI_MSB  (SPI_FIRSTBIT_MSB)
//#define MICROPY_PY_MACHINE_SPI_LSB  (SPI_FIRSTBIT_LSB)
//#define MICROPY_PY_MACHINE_SPI_MAKE_NEW machine_hard_spi_make_new
//#define MICROPY_HW_SOFTSPI_MIN_DELAY (0)
//#define MICROPY_HW_SOFTSPI_MAX_BAUDRATE (HAL_RCC_GetSysClockFreq() / 48)

// extra built in names to add to the global namespace
//extern const struct _mp_obj_fun_builtin_t mp_builtin_open_obj;
#define MICROPY_PORT_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), (mp_obj_t)&mp_builtin_open_obj },

// extra built in modules to add to the list of known ones
extern const struct _mp_obj_module_t machine_module;
//extern const struct _mp_obj_module_t pyb_module;
extern const struct _mp_obj_module_t xmc_module;
//extern const struct _mp_obj_module_t mp_module_ubinascii;
//extern const struct _mp_obj_module_t mp_module_ure;
//extern const struct _mp_obj_module_t mp_module_uzlib;
//extern const struct _mp_obj_module_t mp_module_ujson;
//extern const struct _mp_obj_module_t mp_module_uheapq;
//extern const struct _mp_obj_module_t mp_module_uhashlib;
extern const struct _mp_obj_module_t mp_module_uos;
extern const struct _mp_obj_module_t mp_module_utime;
//extern const struct _mp_obj_module_t mp_module_usocket;
//extern const struct _mp_obj_module_t mp_module_network;
//extern const struct _mp_obj_module_t mp_module_onewire;


#if MICROPY_PY_XMC
#define XMC_BUILTIN_MODULE               { MP_ROM_QSTR(MP_QSTR_xmc), MP_ROM_PTR(&xmc_module) },
#else
#define XMC_BUILTIN_MODULE
#endif

#define MICROPY_PORT_BUILTIN_MODULES \
    { MP_ROM_QSTR(MP_QSTR_xmc), MP_ROM_PTR(&xmc_module) }, \
    { MP_ROM_QSTR(MP_QSTR_utime), MP_ROM_PTR(&mp_module_utime) }, \
    XMC_BUILTIN_MODULE \

/*    { MP_ROM_QSTR(MP_QSTR_uos), MP_ROM_PTR(&mp_module_uos) }, \
    { MP_ROM_QSTR(MP_QSTR_umachine), MP_ROM_PTR(&machine_module) }, \
    SOCKET_BUILTIN_MODULE \
    NETWORK_BUILTIN_MODULE \
    { MP_ROM_QSTR(MP_QSTR__onewire), MP_ROM_PTR(&mp_module_onewire) }, \
*/

// extra constants
/*
#define MICROPY_PORT_CONSTANTS \
    { MP_ROM_QSTR(MP_QSTR_umachine), MP_ROM_PTR(&machine_module) }, \
    { MP_ROM_QSTR(MP_QSTR_machine), MP_ROM_PTR(&machine_module) }, \
    XMC_BUILTIN_MODULE \
*/

// type definitions for the specific machine
#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))
#define MP_SSIZE_MAX (0x7fffffff)
#define UINT_FMT "%u"
#define INT_FMT "%d"

// TODO
typedef int mp_int_t; // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
typedef long mp_off_t;

// TODO: Test
#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

// We have inlined IRQ functions for efficiency (they are generally
// 1 machine instruction).
//
// Note on IRQ state: you should not need to know the specific
// value of the state variable, but rather just pass the return
// value from disable_irq back to enable_irq.  If you really need
// to know the machine-specific values, see irq.h.

static inline void enable_irq(mp_uint_t state) {
    __set_PRIMASK(state);
}

static inline mp_uint_t disable_irq(void) {
    mp_uint_t state = __get_PRIMASK();
    __disable_irq();
    return state;
}

#define MICROPY_BEGIN_ATOMIC_SECTION()     disable_irq()
#define MICROPY_END_ATOMIC_SECTION(state)  enable_irq(state)

// We need an implementation of the log2 function which is not a macro
#define MP_NEED_LOG2 (1)

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

/* BOARD CONFIG */
#define MICROPY_HW_BOARD_NAME "RelaxLiteKit"
#define MICROPY_HW_MCU_NAME "XMC4500"

#define MICROPY_HW_HAS_SWITCH       (0)
//#define MICROPY_HW_HAS_FLASH        (0)
//#define MICROPY_HW_HAS_MMA7660      (0)
//#define MICROPY_HW_HAS_LCD          (0)
#define MICROPY_HW_ENABLE_RNG       (0)
#define MICROPY_HW_ENABLE_RTC       (0)
#define MICROPY_HW_ENABLE_SERVO     (0)
#define MICROPY_HW_ENABLE_DAC       (0)
#define MICROPY_HW_ENABLE_USB       (0)
#define MICROPY_HW_ENABLE_SDCARD    (0)

// TODO: Other config: RTC, Clock, UART, I2C, SPI, CAN, LED, SD, USB,...

#define MP_STATE_PORT MP_STATE_VM

// TODO: add more like in stm32/mpconfigport.h
#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8]; \
    \
    mp_obj_t pin_class_mapper; \
    mp_obj_t pin_class_map_dict;


#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(void); \
        mp_handle_pending(); \
        __WFI(); \
    } while (0);

#define MICROPY_THREAD_YIELD()
