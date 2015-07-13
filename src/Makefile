OUT = trafficlights
MCU = attiny13
F_CPU = 1200000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude -c usbasp -p t13
CFLAGS += -Wall -g -Os -std=c99 -mmcu=$(MCU) -ffunction-sections -fdata-sections -DF_CPU=$(F_CPU)
LDFLAGS += -Wl,--gc-sections
OBJS = $(OUT).o

all: $(OUT).hex

$(OUT).hex: $(OUT).elf
	$(OBJCOPY) -O ihex $< $@

$(OUT).elf: $(OUT).o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash: $(OUT).hex
	$(AVRDUDE) -U flash:w:$(OUT).hex

clean:
	rm $(OBJS)
	rm $(OUT).elf
	rm $(OUT).hex
