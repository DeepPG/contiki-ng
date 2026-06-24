CC = arm-none-eabi-gcc
CFLAGS = -DPICO_RP2040 -mcpu=cortex-m0plus -mthumb 
LDFLAGS = -mcpu=cortex-m0plus -mthumb -nostdlib -T linker.ld # please check on -nostdlib, does pico-sdk use it? what should I do? remove it?
CFILES = main.c startup.c

FUNCTION_WRAPPER = -Wl,--wrap=__aeabi_idiv \
        -Wl,--wrap=__aeabi_idivmod \
        -Wl,--wrap=__aeabi_ldivmod \
        -Wl,--wrap=__aeabi_uidiv \
        -Wl,--wrap=__aeabi_uidivmod \
        -Wl,--wrap=__aeabi_uldivmod \
		-Wl,--wrap=sprintf \
        -Wl,--wrap=snprintf \
        -Wl,--wrap=vsnprintf \
        -Wl,--wrap=__clzsi2 \
        -Wl,--wrap=__clzdi2 \
        -Wl,--wrap=__ctzsi2 \
        -Wl,--wrap=__popcountsi2 \
        -Wl,--wrap=__popcountdi2 \
        -Wl,--wrap=__clz \
        -Wl,--wrap=__clzl \
        -Wl,--wrap=__clzll \

LDFLAGS += $(FUNCTION_WRAPPER) 


PICO_SDK = ./pico-sdk/src
 

DIRS += $(shell find $(PICO_SDK)/rp2_common/ -type d -iname "include")
# DIRS += $(shell ls -d $(PICO_SDK)/rp2350/*/include/) # only for rp2350 include ut
DIRS += $(shell ls -d $(PICO_SDK)/rp2040/*/include/)
DIRS += $(shell ls -d $(PICO_SDK)/common/*/include/)



CFILES += $(shell find $(PICO_SDK)/rp2_common/hardware_gpio/ -name "*.c")
CFILES += $(shell find $(PICO_SDK)/common/hardware_claim/ -name "*.c")



CFILES += $(shell find $(PICO_SDK)/rp2_common/hardware_irq/ -name "*.c")
# CFILES += $(shell find $(PICO_SDK)/rp2_common/pico_divider/ -name "*.c") # only work for rp2350 and most compiled with, add ifeq
CFILES += $(shell find $(PICO_SDK)/rp2_common/pico_bootrom/ -name "*.c")
# CFILES += $(shell find $(PICO_SDK)/rp2_common/pico_cyw43_driver/ -name "*.c")



CFILES += ${PICO_SDK}/rp2_common/pico_clib_interface/newlib_interface.c # declare it if you want
CFILES += ${PICO_SDK}/rp2_common/pico_runtime/runtime.c
CFILES += ${PICO_SDK}/rp2_common/hardware_timer/timer.c
CFILES += ${PICO_SDK}/rp2_common/pico_runtime_init/runtime_init.c # always link
CFILES += ${PICO_SDK}/rp2_common/hardware_sync_spin_lock/sync_spin_lock.c
CFILES += ${PICO_SDK}/rp2_common/pico_runtime_init/runtime_init_clocks.c
CFILES += ${PICO_SDK}/rp2_common/hardware_clocks/clocks.c
CFILES += ${PICO_SDK}/rp2_common/hardware_pll/pll.c
CFILES += ${PICO_SDK}/rp2_common/hardware_ticks/ticks.c
CFILES += ${PICO_SDK}/rp2_common/hardware_xosc/xosc.c # crystal ocsilator
CFILES += $(PICO_SDK)/rp2_common/hardware_uart/uart.c # uart
CFILES += $(PICO_SDK)/rp2_common/hardware_rtc/rtc.c # rtc
CFILES += $(PICO_SDK)/common/pico_time/time.c
CFILES += $(PICO_SDK)/common/pico_sync/lock_core.c # some of prevent locking function? related on spin lock and cpus, learn about it
CFILES += $(PICO_SDK)/rp2_common/hardware_sync/sync.c






# CFILES += ${PICO_SDK}/host/pico_time_adapter/time_adapter.c # it's listed on always link but did not know how to link it with makefile



ASMFILES += $(shell find ./pico-sdk/src/rp2_common/hardware_irq/ -name "*.S")
ASMFILES += $(shell find ./pico-sdk/src/rp2_common/pico_divider/ -name "*.S") # only work for rp2040 and most compiled with
ASMFILES += ${PICO_SDK}/rp2_common/pico_printf/printf_none.S # always link, this file contain dummy weak functions I think
ASMFILES += ${PICO_SDK}/rp2_common/pico_bit_ops/bit_ops_aeabi.S # always link



OBJS = $(notdir $(CFILES:.c=.o)) $(notdir $(ASMFILES:.S=.o))



INCLUDE_PICO = $(addprefix -I, $(DIRS))
INCLUDE_PICO += -I./pico-sdk/src/boards/include/




VPATH = $(sort $(dir $(CFILES))) $(sort $(dir $(ASMFILES)))
 



CFLAGS += $(INCLUDE_PICO)
CFLAGS += -I$(PICO_SDK)/bazel/include/
CFLAGS += -I$(PICO_SDK)/tools/pioasm/

# ${info $(INCLUDE_PICO)}




all: firm.uf2





firm.uf2: firm.elf 
	./elf2uf2/elf2uf2 firm.elf firm.uf2

# firm.elf: $(OBJS) astartup.o boot.o
# 	$(CC) $(LDFLAGS) $^ -o firm.elf


firm.elf: $(OBJS) boot.o  
	$(CC) $(LDFLAGS) $^ -o firm.elf -lgcc -lc





%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 



# main.o: main.c
# 	$(CC) $(CFLAGS)  -c main.c -o main.o

# gpio.o: $(CFILES)
# 	$(CC) $(CFLAGS) -c $(CFILES) -o gpio.o




clear: 
	rm -rf *.o firm.elf firm.uf2

