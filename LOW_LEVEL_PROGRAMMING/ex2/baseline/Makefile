# Example Makefile
#
# Exercise 2, TDT4258

DIR = ../music/
INC_DIR = $(DIR:%=-I%)

OUTPUT = OUTPUT
MAIN = ex2.c

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

OBJECTS = $(shell find *.c | grep -v $(MAIN) )

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall $(INC_DIR)
LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg -Llib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g
LINKERSCRIPT=lib/efm32gg.ld

$(OUTPUT)/ex2.bin : $(OUTPUT)/ex2.elf
	${OBJCOPY} -g -O binary $< $@

$(OUTPUT)/ex2.elf : $(OUTPUT)/$(MAIN:%.c=%.o) $(OBJECTS:%.c=$(OUTPUT)/%.o)
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

$(OUTPUT)/%.o : %.c
	@mkdir -p $(OUTPUT)
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : pretty
pretty :
	-indent *.c *.h

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f $(OUTPUT)/ex2.bin -r

.PHONY : clean
clean :
	-rm -rf *.o *.elf *.bin *.hex $(OUTPUT)
