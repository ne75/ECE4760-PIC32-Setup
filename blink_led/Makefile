# 
# Nikita Ermoshkin (ne75)
# Eric Dai (emd88)
# 
# September 2017
#

# put a config.mk file in same directory as makefile
include config.mk

CC = $(XC32)/xc32-gcc
BIN2HEX = $(XC32)/xc32-bin2hex

OBJDIR = ./build
TARGET = blink_led

PROCESSOR = 32MX250F128B
LOADTOOL = PKOB

CFLAGS = -g -x c -c -mprocessor=$(PROCESSOR) -no-legacy-libc -D_SUPPRESS_PLIB_WARNING=1 -D_DISABLE_OPENADC10_CONFIGPORT_WARNING
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
