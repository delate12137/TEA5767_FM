#project name
TARGET = TEA5767

export CC         = arm-none-eabi-gcc           
export AS         = arm-none-eabi-as
export LD         = arm-none-eabi-ld
export OBJCOPY    = arm-none-eabi-objcopy


#the top dir
#linux & mac os
#top = $(shell pwd)
#windows
top = $(shell echo %cd%)


#lib_path= ./STM32F10x_StdPeriph_Lib_V3.5.0
#windows
lib_path= $(top)\STM32F10x_StdPeriph_Lib_V3.5.0

inc = -I $(top)/cmsis/inc \
      -I $(top)/libraries/inc \
      -I $(top)/user/inc \
      -I $(top)/driver/inc 

obj_flag    = -W -Wall -g -mcpu=cortex-m3 -mthumb -D STM32F10X_HD -D USE_STDPERIPH_DRIVER $(inc) -O0 -std=gnu11 
target_flag = -mthumb -mcpu=cortex-m3 -Wl,--start-group -lc -lm -Wl,--end-group \
	      -specs=nano.specs -specs=nosys.specs -static -Wl,-cref,-u,Reset_Handler \
	      -Wl,-Map=./project/project.map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 
as_flag     = -c -mthumb -mcpu=cortex-m3 -g -Wa,--warn -o


#sources file path
#linux & mac os
#src = $(shell find ./ -name '*.c')
#windows
src = $(shell for /r ./ %%i in (*.c) do @echo %%i)

obj = $(src:%.c=%.o)


all:$(obj)
	$(CC)  $(as_flag) ./startup/startup_stm32f10x_hd.o ./startup/startup_stm32f10x_hd.s 
	$(CC) $(obj) ./startup/startup_stm32f10x_hd.o -T ./project/stm32_flash.ld -o ./project/output/$(TARGET).elf  $(target_flag)
	$(OBJCOPY) ./project/output/$(TARGET).elf  ./project/output/$(TARGET).bin -Obinary 
	$(OBJCOPY) ./project/output/$(TARGET).elf  ./project/output/$(TARGET).hex -Oihex

$(obj):%.o:%.c
	$(CC) -c $(obj_flag) -o $@ $<

project:
# mkdir cmsis cmsis/inc cmsis/src driver driver/inc driver/src project project/output user user/inc user/src doc startup
# cp $(lib_path)/stm32f10x_stdperiph_lib_um.chm ./doc
# cp -r $(lib_path)/Libraries/STM32F10x_StdPeriph_Driver ./
# mv STM32F10x_StdPeriph_Driver libraries
# cp $(lib_path)/Libraries/CMSIS/CM3/CoreSupport/core_cm3.h ./cmsis/inc
# cp $(lib_path)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h ./cmsis/inc
# cp $(lib_path)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h ./cmsis/inc
# cp $(lib_path)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c ./cmsis/src 
# cp $(lib_path)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_hd.s ./startup
# cp $(lib_path)/Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c ./user/src 
# cp $(lib_path)/Project/STM32F10x_StdPeriph_Template/stm32f10x_it.h ./user/inc
# cp $(lib_path)/Project/STM32F10x_StdPeriph_Template/stm32f10x_conf.h ./user/inc
# cp $(lib_path)/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210E-EVAL/stm32_flash.ld ./project 
# touch ./user/src/main.c
# rm -rf STM32F10x_StdPeriph_Lib_V3.5.0
#windows
	md cmsis cmsis\inc cmsis\src driver driver\inc driver\src project project\output user user\inc user\src doc startup libraries
	copy $(lib_path)\stm32f10x_stdperiph_lib_um.chm $(top)\doc
	xcopy /e  $(lib_path)\Libraries\STM32F10x_StdPeriph_Driver $(top)\libraries
	xcopy $(lib_path)\Libraries\CMSIS\CM3\CoreSupport\core_cm3.h $(top)\cmsis\inc
	xcopy $(lib_path)\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\stm32f10x.h $(top)\cmsis\inc
	xcopy $(lib_path)\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.h $(top)\cmsis\inc
	xcopy $(lib_path)\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.c $(top)\cmsis\src
	xcopy $(lib_path)\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\TrueSTUDIO\startup_stm32f10x_hd.s $(top)\startup
	xcopy $(lib_path)\Project\STM32F10x_StdPeriph_Template\stm32f10x_it.c $(top)\user\src
	xcopy $(lib_path)\Project\STM32F10x_StdPeriph_Template\stm32f10x_it.h $(top)\user\inc
	xcopy $(lib_path)\Project\STM32F10x_StdPeriph_Template\stm32f10x_conf.h $(top)\user\inc
	xcopy $(lib_path)\Project\STM32F10x_StdPeriph_Template\TrueSTUDIO\STM3210E-EVAL\stm32_flash.ld $(top)\project
	echo #include "stm32f10x.h" int main() {}> $(top)\user\src\main.c
	rd /s /q STM32F10x_StdPeriph_Lib_V3.5.0
update:
# openocd -f /usr/local/share/openocd/scripts/interface/jlink.cfg \
# -f /usr/local/share/openocd/scripts/target/stm32f1x.cfg \
# -c init -c halt -c "flash write_image erase ./project/output/$(TARGET).hex" -c reset -c shutdown
	openocd -f $(top)/project/jlink.cfg \
	 -f $(top)/project/stm32f1x.cfg \
	-c init -c halt -c "flash write_image erase ./project/output/$(TARGET).hex" -c reset -c shutdown
clean:
# rm -f $(shell find ./ -name '*.o')
# rm -f $(shell find ./ -name '*.map')
# rm -f $(shell find ./ -name '*.elf')
# rm -f $(shell find ./ -name '*.bin')
# rm -f $(shell find ./ -name '*.hex')
#windows
	del /q  $(shell for /r ./ %%i in (*.o,*.map,*.hex,*.elf,*.bin) do @echo %%i)