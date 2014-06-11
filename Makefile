###############################################################################
#	Makefile by Alex Chadwick
#	with significant additions by:
#	Omar, Chris, Chad, Joseph, Matthew in CMPT 432 
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))

OBJECTS += $(BUILD)main.o
OBJECTS += $(BUILD)leds.o
OBJECTS += $(BUILD)memcpy.o
OBJECTS += $(BUILD)tostring.o
OBJECTS += $(BUILD)print.o
OBJECTS += $(BUILD)memory.o
OBJECTS += $(BUILD)process.o
OBJECTS += $(BUILD)scheduler.o
OBJECTS += $(BUILD)master_process.o
OBJECTS += $(BUILD)interrupts.o
OBJECTS += $(BUILD)console_proc.o
OBJECTS += $(BUILD)io_init.o
OBJECTS += $(BUILD)ipc_syscalls.o
OBJECTS += $(BUILD)memory_syscalls.o
OBJECTS += $(BUILD)misc_syscalls.o
OBJECTS += $(BUILD)process_syscalls.o
OBJECTS += $(BUILD)user_syscalls.o
OBJECTS += $(BUILD)syscalls_init.o
OBJECTS += $(BUILD)string.o
OBJECTS += $(BUILD)user_programs.o

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) -L. -lcsud -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the object files.
$(BUILD)%.o: $(SOURCE)%.s $(BUILD)
	$(ARMGNU)-as -I $(SOURCE) $< -o $@

$(BUILD)main.o: $(SOURCE)main.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)main.c -o $(BUILD)main.o

$(BUILD)leds.o: $(SOURCE)leds.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)leds.c -o $(BUILD)leds.o

$(BUILD)memcpy.o: $(SOURCE)memcpy.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)memcpy.c -o $(BUILD)memcpy.o

$(BUILD)tostring.o: $(SOURCE)tostring.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)tostring.c -o $(BUILD)tostring.o

$(BUILD)print.o: $(SOURCE)print.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)print.c -o $(BUILD)print.o

$(BUILD)memory.o: $(SOURCE)memory.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)memory.c -o $(BUILD)memory.o

$(BUILD)process.o: $(SOURCE)process.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)process.c -o $(BUILD)process.o

$(BUILD)scheduler.o: $(SOURCE)scheduler.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)scheduler.c -o $(BUILD)scheduler.o

$(BUILD)master_process.o: $(SOURCE)master_process.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)master_process.c -o $(BUILD)master_process.o

$(BUILD)interrupts.o: $(SOURCE)interrupts.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)interrupts.c -o $(BUILD)interrupts.o

$(BUILD)console_proc.o: $(SOURCE)console_proc.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)console_proc.c -o $(BUILD)console_proc.o

$(BUILD)io_init.o: $(SOURCE)io_init.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)io_init.c -o $(BUILD)io_init.o

$(BUILD)ipc_syscalls.o: $(SOURCE)ipc_syscalls.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)ipc_syscalls.c -o $(BUILD)ipc_syscalls.o

$(BUILD)memory_syscalls.o: $(SOURCE)memory_syscalls.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)memory_syscalls.c -o $(BUILD)memory_syscalls.o

$(BUILD)misc_syscalls.o: $(SOURCE)misc_syscalls.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)misc_syscalls.c -o $(BUILD)misc_syscalls.o

$(BUILD)process_syscalls.o: $(SOURCE)process_syscalls.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)process_syscalls.c -o $(BUILD)process_syscalls.o

$(BUILD)user_syscalls.o: $(SOURCE)user_syscalls.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)user_syscalls.c -o $(BUILD)user_syscalls.o

$(BUILD)syscalls_init.o: $(SOURCE)syscalls_init.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)syscalls_init.c -o $(BUILD)syscalls_init.o

$(BUILD)string.o: $(SOURCE)string.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)string.c -o $(BUILD)string.o

$(BUILD)user_programs.o: $(SOURCE)user_programs.c
	$(ARMGNU)-gcc -c -I $(SOURCE) $(SOURCE)user_programs.c -o $(BUILD)user_programs.o
$(BUILD):
	mkdir $@

# Rule to clean files.
clean : 
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
