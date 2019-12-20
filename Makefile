
# toolchain
CC           = sdcc
CP           = sdobjcopy
AS           = sdasstm8
LD			= sdld
HEX          = packihx
BIN          = $(CP) -O binary -S

# define mcu, specify the target processor
F_CPU   ?= 16000000
MCU          = stm8s103f3
ARCH = stm8

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJECT_NAME=MUSIC-BOX-STM8

# specify define
DDEFS       =

# define root dir
ROOT_DIR     = .

# define include dir
INCLUDE_DIRS = 

# define stm32f4 lib dir
LIBDIR   = $(ROOT_DIR)/stm8

# user specific

SRC 	+= main.c
SRC 	+= AlgorithmTest.c
SRC 	+= SynthCore.c
SRC 	+= Player.c
SRC 	+= UartRedirect.c
SRC 	+= WaveTable.c
SRC 	+= EnvelopTable.c
SRC 	+= score.c
SRC 	+= $(LIBDIR)/delay.c
SRC 	+= $(LIBDIR)/uart.c

ASM_SRC   += PeriodTimer.s
ASM_SRC   += PlayerUtil.s
ASM_SRC   += SynthCoreAsm.s


INC_DIR  = $(patsubst %, -I%, $(INCLUDE_DIRS))

# run from Flash
DEFS	 = $(DDEFS)
DEPS  = $(SRC:.c=.d)
OBJECTS  = $(SRC:.c=.rel) $(ASM_SRC:.s=.rel)
OTHER_OUTPUTS += $(ASM_SRC:.s=.asm) $(SRC:.c=.asm)
OTHER_OUTPUTS += $(ASM_SRC:.s=.lst) $(SRC:.c=.lst)
OTHER_OUTPUTS += $(ASM_SRC:.s=.rst) $(SRC:.c=.rst)
OTHER_OUTPUTS += $(ASM_SRC:.s=.sym) $(SRC:.c=.sym)


CFLAGS  = -m$(ARCH) -p$(MCU) --std-sdcc11
CFLAGS += -DF_CPU=$(F_CPU)UL -I. -I$(LIBDIR)
CFLAGS += --stack-auto --use-non-free
ASFLAGS  = -plosgff
LD_FLAGS = -m$(ARCH) -l$(ARCH) --out-fmt-ihx

#
# makefile rules
#
all: $(OBJECTS) $(PROJECT_NAME).ihx $(PROJECT_NAME).hex $(PROJECT_NAME).bin

# Don't delete dependency files
.PRECIOUS: %.d

# Don't rebuild deps if cleaning
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
# Beacuse SDCC's assembler has no way to auto output dependency info,
# the dependency is manually written here.	
PeriodTimer.rel: SynthCore.inc STM8.inc Synth.inc UpdateTick.inc
SynthCoreAsm.rel: SynthCore.inc
PlayerUtil.rel: SynthCore.inc Player.inc
endif




%.rel: %.c Makefile
	@echo [CC] $(notdir $<)
# Output dependency
	@$(CC) $(CFLAGS) $(INC_DIR) -MM -c $< > $(patsubst %.c,%.d,$<)
# Do compiling
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@
	


%.rel: %.s
	@echo [AS] $(notdir $<)
	@$(AS) $(ASFLAGS) $<

%.ihx: $(OBJECTS)
	@echo [LD] $(PROJECT_NAME).ihx
	@$(CC) $(LD_FLAGS) $(OBJECTS) -o $@
	
%.hex: %.ihx
	@echo [HEX] $(PROJECT_NAME).hex
	@$(HEX) $< > $@	
	
%.bin: %.ihx
	@echo [BIN] $(PROJECT_NAME).bin
	@$(CP) -I ihex -O binary $< $@

flash: $(PROJECT_NAME).hex
	stm8flash -c stlinkv2 -p $(MCU) -w $(PROJECT_NAME).hex
	
clean:
	@echo [RM] OBJ
	@-rm -rf $(OBJECTS)
	@echo [RM] HEX
	@-rm -rf $(PROJECT_NAME).ihx
	@echo [RM] Intermediate outputs
	@-rm -rf $(OTHER_OUTPUTS)
	@-rm -rf $(PROJECT_NAME).lk
	@-rm -rf $(PROJECT_NAME).map	
	@-rm -rf $(PROJECT_NAME).cdb	
	@-rm -rf $(PROJECT_NAME).hex
	@-rm -rf $(PROJECT_NAME).bin
	@-rm -rf $(DEPS)