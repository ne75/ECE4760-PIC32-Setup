XC32 = /Applications/microchip/xc32/v1.44/bin

CC = $(XC32)/xc32-gcc
BIN2HEX = $(XC32)/xc32-bin2hex

LOADER = /Users/Nikita/Github/ECE4760/ipecmd.sh

OBJDIR = ./build
TARGET = blink_led

PROCESSOR = 32MX250F128B
LOADTOOL = PKOB

CFLAGS = -g -x c -c -mprocessor=$(PROCESSOR) -no-legacy-libc
LFLAGS = -no-legacy-libc -mprocessor=$(PROCESSOR)
LOADFLAGS = -TP$(LOADTOOL) -P$(PROCESSOR) -OL -M 

.PHONY: all setup load clean

all: setup $(OBJDIR)/$(TARGET).hex load

setup:
	mkdir -p $(OBJDIR)

$(OBJDIR)/$(TARGET).hex: $(OBJDIR)/$(TARGET).elf 
	$(BIN2HEX) $<

$(OBJDIR)/$(TARGET).elf: $(OBJDIR)/main.o
	$(CC) $(LFLAGS) -o $@ $< 

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -o $@ $<

load: $(OBJDIR)/$(TARGET).hex
	$(LOADER) $(LOADFLAGS) -F$<

clean:
	rm -rf $(OBJDIR)/*