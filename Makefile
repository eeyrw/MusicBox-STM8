export PATH := $(PATH):$(HOME)/local/sdcc/bin

MCU  = stm8s103f3
ARCH = stm8

F_CPU   ?= 16000000
TARGET  ?= main.ihx

LIBDIR   = ./stm8

SRCS 	+= main.c
SRCS 	+= AlgorithmTest.c
SRCS 	+= SynthCore.c
SRCS 	+= Player.c
SRCS 	+= UartRedirect.c
SRCS 	+= WaveTable_Celesta_C5.c
SRCS 	+= EnvelopTable.c
SRCS 	+= score.c
SRCS 	+= $(LIBDIR)/delay.c
SRCS 	+= $(LIBDIR)/uart.c

ASRCS   += PlayerUtil.s
ASRCS   += Synth.s

OBJS     = $(SRCS:.c=.rel)
OBJS    += $(ASRCS:.s=.rel)

CC       = sdcc
LD       = sdld
AS       = sdasstm8
OBJCOPY  = sdobjcopy
ASFLAGS  = -plosgff
CFLAGS   = -m$(ARCH) -p$(MCU) --std-sdcc11
CFLAGS  += -DF_CPU=$(F_CPU)UL -I. -I$(LIBDIR)
CFLAGS  += --stack-auto --use-non-free
## Disable lospre (workaround for bug 2673)
#CFLAGS  += --nolospre
## Extra optimization rules - use with care
#CFLAGS  += --peep-file $(LIBDIR)/util/extra.def
LDFLAGS  = -m$(ARCH) -l$(ARCH) --out-fmt-ihx

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $<

flash: $(TARGET)
	./stm8flash -c stlinkv2 -p $(MCU) -w $(TARGET)

clean:
	rm -f *.map *.asm *.rel *.ihx *.o *.sym *.lk *.lst *.rst *.cdb *.bin

.PHONY: clean all flash
