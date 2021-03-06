TARGET = mono_project
ARCH="/usr/local/gcc-arm-none-eabi-5_2-2015q4/bin/arm-none-eabi-"
FLASH_SIZE=262144
FLASH_ROW_SIZE=256
FLASH_ARRAY_SIZE=65536
EE_ARRAY=64
EE_ROW_SIZE=16
OPTIMIZATION = -Os
LINKER_SCRIPT=${INCLUDE_DIR}/cm3gcc.ld
BUILD_DIR=build
PSOC5_PATH=../mono_psoc5_library
MONO_FRAMEWORK_PATH =../mono_framework
MBED_PATH=.
MBED_FS=../mbed/libraries/fs
INCLUDE_DIR=$(PSOC5_PATH)/include
COMP_LIB=$(PSOC5_PATH)/lib/CyComponentLibrary.a
MONO_LIB=$(PSOC5_PATH)/lib/monoCyLib.a

MBED_OBJECTS =	$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/common/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/common/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/target_cypress/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/sd/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/fat/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_FS)/fat/ChaN/*.cpp))

MBED_INCLUDES =	$(MBED_PATH)/api \
				$(MBED_PATH)/hal \
				$(MBED_PATH)/target_cypress \
				$(MBED_FS)/sd \
				$(MBED_FS)/fat \
				$(MBED_FS)/fat/ChaN

MBED_INCLUDE_FILES = $(foreach FILE,$(MBED_INCLUDES),$(wildcard $(FILE)/*.h))

MBED_TARGET_OBJECTS = $(addprefix ./$(BUILD_DIR)/, $(MBED_OBJECTS))

CC=$(ARCH)gcc
CXX=$(ARCH)g++
LD=$(ARCH)gcc
AS=$(ARCH)gcc
AR=$(ARCH)ar
RANLIB=$(ARCH)ranlib
STRIP=$(ARCH)strip
OBJCOPY=$(ARCH)objcopy
OBJDUMP=$(ARCH)objdump
COPY=cp
MKDIR=mkdir
MONOPROG=monoprog
ELFTOOL='C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\bin\cyelftool.exe'
INCS = -I . $(addprefix -I, $(MONO_INCLUDES) $(MBED_INCLUDES) $(INCLUDE_DIR))
CDEFS=
ASDEFS=
AS_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb -mthumb-interwork -march=armv7-m
CC_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb $(OPTIMIZATION) -mthumb-interwork -fno-common -fmessage-length=0 -ffunction-sections -fdata-sections -march=armv7-m
ONLY_C_FLAGS = -std=gnu99
ONLY_CPP_FLAGS = -std=gnu++98 -fno-rtti -fno-exceptions
LDSCRIPT = -T $(LINKER_SCRIPT)
LD_FLAGS = -g -mcpu=cortex-m3 -mthumb -march=armv7-m -fno-rtti -Wl,--gc-sections -specs=nano.specs
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

#"libs/CyCompLib.a"
#   -mfix-cortex-m3-ldrd -u _printf_float -u _scanf_float
COPY_FLAGS = -j .text -j .eh_frame -j .rodata -j .ramvectors -j .noinit -j .data -j .bss -j .stack -j .heap -j .cyloadablemeta

all: $(BUILD_DIR) mbed

library: monoCyLib.a

mbed: mbedlib.a

$(BUILD_DIR):
	@echo "creating build directory"
	@mkdir -p ./$(BUILD_DIR)

.s.o: $(BUILD_DIR)
	@echo "Assembling: $(notdir $<)"
	@$(AS) $(AS_FLAGS) $(INCS) -o $(BUILD_DIR)/$(notdir $@) $<

$(BUILD_DIR)/%.o: %.c
	@echo "Compiling mbed C: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(ONLY_C_FLAGS) $(CDEFS) $(INCS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp
	@echo "Compiling mbed C++: $<"
	@$(MKDIR) -p $(dir $@)
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $@ $<

mbedlib.a: $(MBED_TARGET_OBJECTS)
	@echo "Linking mbed framework ..."
	@$(AR) rcs $@ $^
	@echo "Copying header files to include dir..."
	@$(MKDIR) -p include
	@$(COPY) $(MBED_INCLUDE_FILES) include/.

mbedFiles:
	@echo $(MBED_TARGET_OBJECTS)

mbedIncludes:
	@echo $(MBED_INCLUDE_FILES)

includeFiles:
	@echo $(INCS)


clean:
	$(RM) $(MBED_TARGET_OBJECTS) include/*.h mbedlib.a



## $(LD) -Wl,--start-group $(LD_FLAGS) libs/CyCompLib.a $(LDSCRIPT) -o $@ $^ -Wl,--end-group $(LD_SYS_LIBS)
## $(ELFTOOL) -C $@ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)