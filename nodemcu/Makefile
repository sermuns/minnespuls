# Target board configuration
CHIP = esp8266
BOARD = esp8266:esp8266:nodemcu
SKETCH = nodemcu.ino
SKETCH_NAME = $(basename $(SKETCH))

# Output directory
OUTPUT_DIR = build

# Default target
all: $(OUTPUT_DIR)/$(SKETCH_NAME).ino.bin

# Ensure output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Compile the sketch
$(OUTPUT_DIR)/$(SKETCH_NAME).ino.bin: $(SKETCH) | $(OUTPUT_DIR)
	arduino-cli compile --quiet --fqbn $(BOARD) --output-dir $(OUTPUT_DIR) $(SKETCH)

# Program the chip
PROG_BAUDRATE = 1000000
PORT = /dev/ttyUSB0
prog: $(OUTPUT_DIR)/$(SKETCH_NAME).ino.bin
	esptool --chip $(CHIP) -p $(PORT) -b $(PROG_BAUDRATE) --after soft_reset write_flash 0 $<

monitor:
	arduino-cli monitor -q 

# Clean the output directory
clean:
	rm -rf $(OUTPUT_DIR)

# Phony targets
.PHONY: all clean prog
