
CC      = arm-none-eabi-gcc

MACH    = cortex-m3

ARCH    = mthumb #mthumb or marm  

CFLAGS  = -c -mcpu=$(MACH) -$(ARCH)

LDFLAGS = -nostdlib -T stm32f103_LinkerScript.ld -Wl,-Map=final.map

main.o:main.c
	
	$(CC) $(CFLAGS) $^ -o $@
	@echo main.o GENRATED
	@echo.
GPIO_Prog.o:GPIO_Prog.c
	
	$(CC) $(CFLAGS) $^ -o $@
	@echo GPIO_Prog.o GENRATED
	@echo.
	
RCC_Prog.o:RCC_Prog.c
	
	$(CC) $(CFLAGS) $^ -o $@
	@echo RCC_Prog.o GENRATED
	@echo.
	
stm32f103_startUp.o:stm32f103_startUp.c
	$(CC) $(CFLAGS) $^ -o $@
	@echo stm32f103_startUp.o GENRATED
	@echo.
clean:
	del *.i *.s *.o *.elf *.hex *.map
	if exist "Debug\" rmdir /S /Q "Debug"
	@echo all generated files deleted
	@echo.

final.elf:main.o GPIO_Prog.o stm32f103_startUp.o RCC_Prog.o
	$(CC) $(LDFLAGS) $^ -o $@
	@echo final.elf GENRATED
	@echo.
	 
all:main.o GPIO_Prog.o stm32f103_startUp.o RCC_Prog.o final.elf
	@echo all GENRATED
	


rebuild: clean all



load:
	openocd -f interface/stlink-v2.cfg -f board/stm32f103c8_blue_pill.cfg