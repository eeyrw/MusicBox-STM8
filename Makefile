
# toolchain
CC           = sdcc
CP           = sdobjcopy
AS           = sdasstm8
LD			= sdld
HEX          = $(CP) -O ihex
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
SRC 	+= WaveTable_Celesta_C5.c
SRC 	+= EnvelopTable.c
SRC 	+= score.c
SRC 	+= $(LIBDIR)/delay.c
SRC 	+= $(LIBDIR)/uart.c

ASM_SRC   += PlayerUtil.s
ASM_SRC   += Synth.s



INC_DIR  = $(patsubst %, -I%, $(INCLUDE_DIRS))

# run from Flash
DEFS	 = $(DDEFS)

OBJECTS  = $(ASM_SRC:.s=.rel) $(SRC:.c=.rel)
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
all: $(OBJECTS) $(PROJECT_NAME).ihx

%.rel: %.c Makefile
	@echo [CC] $(notdir $<)
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

%.rel: %.s
	@echo [AS] $(notdir $<)
	@$(AS) $(ASFLAGS) $<

%.ihx: $(OBJECTS)
	@echo [LD] $(PROJECT_NAME).ihx
	@$(CC) $(LD_FLAGS) $(OBJECTS) -o $@

flash: $(PROJECT_NAME).ihx
	./stm8flash -c stlinkv2 -p $(MCU) -w $(PROJECT_NAME).ihx
	
clean:
	@echo [RM] OBJ
	@-rm -rf $(OBJECTS)
	@echo [RM] HEX
	@-rm -rf $(PROJECT_NAME).ihx
	@echo [RM] intermediate outputs
	@-rm -rf $(OTHER_OUTPUTS)
	@-rm -rf $(PROJECT_NAME).lk
	@-rm -rf $(PROJECT_NAME).map	
	@-rm -rf $(PROJECT_NAME).cdb	