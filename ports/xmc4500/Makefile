# Select the board to build for: if not given on the command line,
# then default to PYBV10.
BOARD ?= XMC4500
SERIES ?= $(BOARD)_series
MEM ?= 1024
MCU ?= XMC4500_F100x1024

# If the build directory is not given, make it reflect the board name.
BUILD ?= build

# TODO
LIB_DIR ?= XMC_Peripheral_Library_v2.1.16

BOARD_DIR ?= $(LIB_DIR)/CMSIS/Infineon/$(SERIES)
ifeq ($(wildcard $(BOARD_DIR)/.),)
$(error Invalid BOARD specified: $(BOARD_DIR))
endif

include ../../py/mkenv.mk
-include mpconfigport.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h
#TODO: mpconfigboard_common.h, mpconfigboard.h, pins_qstr.h, modstm_qstr.h

# File containing description of content to be frozen into firmware.
FROZEN_MANIFEST ?= manifest.py

# include py core make definitions
include $(TOP)/py/py.mk

# TODO: Git submodules

CMSIS_DIR=$(LIB_DIR)/CMSIS/Infineon/$(SERIES)/Include
CMSIS_MCU_HDR=$(CMSIS_DIR)/$(BOARD).h
HAL_DIR=stmhal
XMC_DIR=$(LIB_DIR)/XMCLib
USB_DIR=$(LIB_DIR)/ThirdPartyLibraries/USBlib/USB
SERIAL_DIR=$(LIB_DIR)/ThirdPartyLibraries/USBlib/Examples/Device/VirtualSerial
STARTUP_FILE ?= $(BOARD_DIR)/Source/GCC/startup_$(BOARD).S
SYSTEM_FILE ?= $(BOARD_DIR)/Source/system_XMC4500.c
LINKER_FILE ?= $(BOARD_DIR)/Source/GCC/$(BOARD)x$(MEM).ld

# Select the cross compile prefix
CROSS_COMPILE ?= arm-none-eabi-

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)
INC += -I$(LIB_DIR)/CMSIS/Include/
INC += -I$(CMSIS_DIR)/
INC += -I$(HAL_DIR)/
INC += -I$(XMC_DIR)/inc/
INC += -I$(USB_DIR)/
INC += -I$(USB_DIR)/../
INC += -I$(SERIAL_DIR)

# Basic Cortex-M(4) flags
CFLAGS_CORTEX_M4 = -mthumb
CFLAGS_CORTEX_M4 += -mtune=cortex-m4 -mcpu=cortex-m4
CFLAGS_CORTEX_M4 += -mabi=aapcs-linux
#CFLAGS_CORTEX_M4 += -fsingle-precision-constant -Wdouble-promotion

CFLAGS_CORTEX_M4 += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
SUPPORTS_HARDWARE_FP_DOUBLE = 0
SUPPORTS_HARDWARE_FP_SINGLE = 1

CFLAGS = $(INC) -Wall -Wpointer-arith -Werror -std=gnu99 -nostdlib -D$(MCU) $(CFLAGS_EXTRA)
CFLAGS += $(CFLAGS_CORTEX_M4)
CFLAGS += $(COPT) 
#CFLAGS += -O0 -std=gnu99 -Wall -fms-extensions -DUC_ID=4503 -DXMC4500_F100x1024 -DARM_MATH_CM4 -g3 -fmessage-length=0
CFLAGS += -DXMC_HAL_H='<$(BOARD).h>'
CFLAGS += -D__SKIP_LIBC_INIT_ARRAY
#CFLAGS += -ansi
#CFLAGS += -DMICROPY_HW_VTOR=$(TEXT0_ADDR)
CFLAGS += -DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT
CFLAGS += -fsingle-precision-constant -Wdouble-promotion

#LDFLAGS = -nostdlib -T $(LINKER_FILE) -Map=$@.map --cref
LDFLAGS = -nostdlib -T $(LINKER_FILE) -Map=$(@:.elf=.map) --cref # TODO: test
LDFLAGS += --defsym=_estack_reserve=8  # TODO: test
LIBS = $(shell $(CC) $(CFLAGS) -print-libgcc-file-name) # TODO: test
#LIBS =

# Remove uncalled code from the final image.
CFLAGS += -fdata-sections -ffunction-sections
LDFLAGS += --gc-sections

OBJS  = $(SRC:.c=.o)
OBJS += src/system_$(BOARD).o

#Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -O0 -ggdb
COPT = -O0
else
COPT += -Os -DNDEBUG
endif

# Debugging/Optimization # TODO: test
#ifeq ($(DEBUG), 1)
#CFLAGS += -g -DPENDSV_DEBUG
#COPT = -O0
#else
#COPT += -Os -DNDEBUG
#endif

#CSUPEROPT = -Os # save some code space

# Tune for Debugging or Optimization
#ifeq ($(DEBUG), 1)
#CFLAGS += -O0 -ggdb
#else
#CFLAGS += -Os -DNDEBUG
#CFLAGS += -fdata-sections -ffunction-sections
#endif

# Options for mpy-cross
MPY_CROSS_FLAGS += -march=armv7m

SRC_LIB = $(addprefix lib/,\
  libc/string0.c \
  mp-readline/readline.c \
  timeutils/timeutils.c \
  utils/pyexec.c \
  )
  #oofatfs/ff.c \
  #oofatfs/ffunicode.c \
  #netutils/netutils.c \
  #netutils/trace.c \
  #netutils/dhcpserver.c \
  #utils/interrupt_char.c \
  #utils/sys_stdio_mphal.c \
  #utils/mpirq.c \

ifeq ($(MICROPY_FLOAT_IMPL),double)
SRC_LIBM = $(addprefix lib/libm_dbl/,\
	__cos.c \
	__expo2.c \
	__fpclassify.c \
	__rem_pio2.c \
	__rem_pio2_large.c \
	__signbit.c \
	__sin.c \
	__tan.c \
	acos.c \
	acosh.c \
	asin.c \
	asinh.c \
	atan.c \
	atan2.c \
	atanh.c \
	ceil.c \
	cos.c \
	cosh.c \
	copysign.c \
	erf.c \
	exp.c \
	expm1.c \
	floor.c \
	fmod.c \
	frexp.c \
	ldexp.c \
	lgamma.c \
	log.c \
	log10.c \
	log1p.c \
	modf.c \
	nearbyint.c \
	pow.c \
	rint.c \
	scalbn.c \
	sin.c \
	sinh.c \
	tan.c \
	tanh.c \
	tgamma.c \
	trunc.c \
	)
ifeq ($(SUPPORTS_HARDWARE_FP_DOUBLE),1)
SRC_LIBM += lib/libm_dbl/thumb_vfp_sqrt.c
else
SRC_LIBM += lib/libm_dbl/sqrt.c
endif
else
SRC_LIBM = $(addprefix lib/libm/,\
  math.c \
  acoshf.c \
  asinfacosf.c \
  asinhf.c \
  atan2f.c \
  atanf.c \
  atanhf.c \
  ef_rem_pio2.c \
  erf_lgamma.c \
  fmodf.c \
  kf_cos.c \
  kf_rem_pio2.c \
  kf_sin.c \
  kf_tan.c \
  log1pf.c \
  nearbyintf.c \
  sf_cos.c \
  sf_erf.c \
  sf_frexp.c \
  sf_ldexp.c \
  sf_modf.c \
  sf_sin.c \
  sf_tan.c \
  wf_lgamma.c \
  wf_tgamma.c \
  )
ifeq ($(SUPPORTS_HARDWARE_FP_SINGLE),1)
SRC_LIBM += lib/libm/thumb_vfp_sqrtf.c
else
SRC_LIBM += lib/libm/ef_sqrt.c
endif
endif

# TODO
#EXTMOD_SRC_C = $(addprefix extmod/,\
#  modonewire.c \
#        )
#
#DRIVERS_SRC_C = $(addprefix drivers/,\
#  bus/softspi.c \
#  bus/softqspi.c \
#  memory/spiflash.c \
#  dht/dht.c \
#  )

SRC_C = \
	main.c \
  $(SYSTEM_FILE) \
	uart_core.c \
	uart_extra.c \
  help.c \
  mphalport.c \
  modmachine.c \
  moduos.c \
  modxmc.c \
  $(XMC_DIR)/src/xmc_gpio.c \
  $(XMC_DIR)/src/xmc4_gpio.c \
  pin_defs_xmc4500.c \
  pin.c \
  led.c \
  #$(XMC_DIR)/src/xmc_common.c \
  #$(XMC_DIR)/src/xmc_gpio.c \
  #$(XMC_DIR)/src/xmc_uart.c \
  #$(XMC_DIR)/src/xmc_usic.c \
  #$(XMC_DIR)/src/xmc4_scu.c \
  #$(XMC_DIR)/src/xmc_usbd.c \
  #$(USB_DIR)/Class/Device/CDCClassDevice.c \
  #$(USB_DIR)/Common/memcpy.c \
  #$(USB_DIR)/Core/ConfigDescriptors.c \
  #$(USB_DIR)/Core/Events.c \
  #$(USB_DIR)/Core/XMC4000/Endpoint_XMC4000.c \
  #$(USB_DIR)/Core/XMC4000/USBController_XMC4000.c \
  #$(USB_DIR)/Core/XMC4000/EndpointStream_XMC4000.c \
  #$(USB_DIR)/Core/HostStandardReq.c \
  #$(USB_DIR)/Core/USBTask.c \
  #$(SERIAL_DIR)/VirtualSerial.c \
  #$(SERIAL_DIR)/Descriptors.c \
	#$(BUILD)/_frozen_mpy.c \ # TODO: test
  #lib/libm/math.c \
  #lib/libm/asinfacosf.c \
  #lib/libm/atanf.c \
  #lib/libm/atan2f.c \
  #lib/libm/fmodf.c \
  #lib/libm/roundf.c \
  #lib/libm/log1pf.c \
  #lib/libm/acoshf.c \
  #lib/libm/asinhf.c \
  #lib/libm/atanhf.c \
  #lib/libm/kf_rem_pio2.c \
  #lib/libm/kf_sin.c \
  #lib/libm/kf_cos.c \
  #lib/libm/kf_tan.c \
  #lib/libm/ef_rem_pio2.c \
  #lib/libm/sf_sin.c \
  #lib/libm/sf_cos.c \
  #lib/libm/sf_tan.c \
  #lib/libm/sf_frexp.c \
  #lib/libm/sf_modf.c \
  #lib/libm/sf_ldexp.c \
  #lib/libm/sf_erf.c \
	#lib/libc/string0.c \
  #lib/timeutils/timeutils.c \
	#lib/mp-readline/readline.c \
	#lib/utils/pyexec.c \
  #lib/utils/printf.c \
  #lib/utils/pyhelp.c \
	#lib/utils/stdout_helpers.c \

SRC_S = \
  $(STARTUP_FILE) \
  $(HAL_DIR)/gchelper.S \

# TODO
#SRC_O = \
#  $(STARTUP_FILE) \
#  $(SYSTEM_FILE)
#SRC_O += \
#  system_stm32.o \
#  resethandler.o \
#  lib/utils/gchelper_m3.o

# TODO: test und extend
SRC_HAL = $(addprefix $(HAL_DIR)/,\
	)
	#systick.c \

SRC_XMC = $(addprefix $(XMC_DIR)/src/,\
  xmc_common.c \
  xmc_gpio.c \
  xmc_uart.c \
  xmc_usic.c \
  xmc4_scu.c \
  xmc4_gpio.c \
  xmc_usbd.c \
  )

SRC_USB = $(addprefix $(USB_DIR)/,\
  Class/Device/CDCClassDevice.c \
  Common/memcpy.c \
  Core/ConfigDescriptors.c \
  Core/Events.c \
  Core/XMC4000/Endpoint_XMC4000.c \
  Core/XMC4000/USBController_XMC4000.c \
  Core/XMC4000/EndpointStream_XMC4000.c \
  Core/HostStandardReq.c \
  Core/USBTask.c \
  )

SRC_SERIAL = $(addprefix $(SERIAL_DIR)/,\
  VirtualSerial.c \
  Descriptors.c \
  )

OBJ =
OBJ += $(PY_O)
#OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o) $(SRC_S:.S=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_LIB:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_LIBM:.c=.o))
#OBJ += $(addprefix $(BUILD)/, $(EXTMOD_SRC_C:.c=.o))
#OBJ += $(addprefix $(BUILD)/, $(DRIVERS_SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_S:.S=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_O))
OBJ += $(addprefix $(BUILD)/, $(SRC_HAL:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_XMC:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_USB:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_SERIAL:.c=.o))
#OBJ += $(BUILD)/pins_$(BOARD).o

# This file contains performance critical functions so turn up the optimisation
# level.  It doesn't add much to the code size and improves performance a bit.
# Don't use -O3 with this file because gcc tries to optimise memset in terms of itself.
$(BUILD)/lib/libc/string0.o: COPT += -O2

# We put several files into the first 16K section with the ISRs.
# If we compile these using -O0 then it won't fit. So if you really want these
# to be compiled with -O0, then edit boards/common.ld (in the .isr_vector section)
# and comment out the following lines.
#$(BUILD)/$(FATFS_DIR)/ff.o: COPT += -Os
#$(filter $(PY_BUILD)/../extmod/vfs_fat_%.o, $(PY_O)): COPT += -Os
$(PY_BUILD)/formatfloat.o: COPT += -Os
$(PY_BUILD)/parsenum.o: COPT += -Os
$(PY_BUILD)/mpprint.o: COPT += -Os

all: $(BUILD)/firmware.elf
#TODO: try another?

#TODOL fetch submodules

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(ECHO) $(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h $< > $@
	#$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h $< > $@

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

firmware.elf: $(OBJS)
	mkdir -p
	$(CROSS_COMPILE)gcc -T $(LINKER_FILE) $(LFLAGS) $(CFLAGS) -o firmware.elf $(OBJS) $(LIBS)

firmware: firmware.elf
	$(CROSS_COMPILE)objcopy $(CPFLAGS) firmware.elf bin/firmware.bin
	$(CROSS_COMPILE)objdump -S firmware.elf > bin/firmware.lst
	$(CROSS_COMPILE)size firmware.elf

ifneq ($(FROZEN_MANIFEST)$(FROZEN_DIR),)
# To use frozen source modules, put your .py files in a subdirectory (eg scripts/)
# and then invoke make with FROZEN_DIR=scripts (be sure to build from scratch).
CFLAGS += -DMICROPY_MODULE_FROZEN_STR
endif

ifneq ($(FROZEN_MANIFEST)$(FROZEN_MPY_DIR),)
# To use frozen bytecode, put your .py files in a subdirectory (eg frozen/) and
# then invoke make with FROZEN_MPY_DIR=frozen (be sure to build from scratch).
CFLAGS += -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool
CFLAGS += -DMICROPY_MODULE_FROZEN_MPY
endif

.PHONY: deploy

deploy: $(BUILD)/firmware.hex
	echo "h;loadfile ${BUILD}/firmware.hex;r;g;q;" | $(SED) 's/;/\n/g' > $(BUILD)/JLinkCommands
	JLinkExe -Device $(BOARD) -If SWD -Speed 1000 -CommanderScript $(BUILD)/JLinkCommands
	rm $(BUILD)/JLinkCommands

# MacOS Compatibility
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin) # OSX
  SED = gsed
else # Linux
  SED = sed
endif

# Custom deploy script via JLink
OC = $(CROSS_COMPILE)objcopy
$(BUILD)/%.bin: $(BUILD)/%.elf
	$(OC) -O binary $< $@

$(BUILD)/%.hex: $(BUILD)/%.elf
	$(OC) -O ihex $< $@

$(BUILD)/%.lst: $(BUILD)/%.elf
	$(OD) -h -S $< > $@

# Write a script file for JLinkExe
$(BUILD)/JLinkCommands: | $(BUILD)
	echo "h;loadfile ${BUILD}/firmware.hex;r;g;q;" | $(SED) 's/;/\n/g' > $(BUILD)/JLinkCommands

deploy2: $(BUILD)/firmware.hex $(BUILD)/JLinkCommands
	JLinkExe -Device $(BOARD) -If SWD -Speed 1000 -CommanderScript $(BUILD)/JLinkCommands

# A board should specify TEXT0_ADDR if to use a different location than the
# default for the firmware memory location.  A board can also optionally define
# TEXT1_ADDR to split the firmware into two sections; see below for details.
#TEXT0_ADDR ?= 0x08000000

#ifeq ($(TEXT1_ADDR),)
# No TEXT1_ADDR given so put all firmware at TEXT0_ADDR location

#TEXT0_SECTIONS ?= .isr_vector .text .data

debug: $(BUILD)/firmware.elf
	JLinkGDBServer -device $(BOARD) -endian little -if SWD -speed 1000 -halt -logtofile -log JLinkLog -silent -vd &
	sleep 1
	$(CROSS_COMPILE)gdb $(BUILD)/firmware.elf -ex "target remote :2331" -ex "monitor reset" -ex "load" -ex "break main" -tui
	killall JLinkGDBServer

# Custom debugging via JLink


# Write a script file for GDB
$(BUILD)/GDBCommands: | $(BUILD)
	echo "file ${BUILD}/firmware.elf;target remote localhost:2331;monitor reset;load;break main;" | $(SED) 's/;/\n/g' > $(BUILD)/GDBCommands

DB = $(CROSS_COMPILE)gdb
debug2: $(BUILD)/firmware.elf $(BUILD)/GDBCommands
	echo "##### Debug session started at $(date) #####" > JLinkLog
	JLinkGDBServer -device $(BOARD) -endian little -if SWD -speed 1000 -halt -logtofile -log JLinkLog -silent -vd &
	sleep 1
	sh -ci "$(DB) -command=$(BUILD)/GDBCommands -tui"
	killall JLinkGDBServer

# List of sources for qstr extraction
SRC_QSTR += $(SRC_C) $(SRC_MOD) $(SRC_LIB) $(EXTMOD_SRC_C)
# Append any auto-generated sources that are needed by sources listed in
# SRC_QSTR
SRC_QSTR_AUTO_DEPS += $(GEN_CDCINF_HEADER)

# Making OBJ use an order-only depenedency on the generated pins.h file
# has the side effect of making the pins.h file before we actually compile
# any of the objects. The normal dependency generation will deal with the
# case when pins.h is modified. But when it doesn't exist, we don't know
# which source files might need it.
$(OBJ): | $(GEN_PINS_HDR)

# With conditional pins, we may need to regenerate qstrdefs.h when config
# options change.
#$(HEADER_BUILD)/qstrdefs.generated.h: mpconfigboard.h

main.c: $(GEN_CDCINF_HEADER)

$(GEN_CDCINF_HEADER): $(GEN_CDCINF_FILE) $(FILE2H) | $(HEADER_BUILD)
	$(ECHO) "GEN $@"
	$(Q)$(PYTHON) $(FILE2H) $< > $@

$(GEN_CDCINF_FILE): $(CDCINF_TEMPLATE) $(INSERT_USB_IDS) $(USB_IDS_FILE) | $(HEADER_BUILD)
	$(ECHO) "GEN $@"
	$(Q)$(PYTHON) $(INSERT_USB_IDS) $(USB_IDS_FILE) $< > $@

include $(TOP)/py/mkrules.mk

# TODO: stm32 makefile cotents with prefix and so on
