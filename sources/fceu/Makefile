TARGET = fceu-psp

DRIVERS_OBJS = src/drivers/psp/main.o src/drivers/psp/pspvideo.o src/drivers/psp/pspinput.o \
src/drivers/psp/vram.o src/drivers/psp/filebrowser.o src/drivers/psp/pspaudio.o \
src/drivers/psp/sml.o src/drivers/psp/menugame.o

BASE_OBJS = src/cart.o src/cheat.o src/crc32.o src/debug.o src/endian.o \
src/fceu.o src/fceustr.o src/fds.o src/file.o src/filter.o \
src/general.o src/ines.o src/input.o src/md5.o src/memory.o \
src/movie.o src/netplay.o src/nsf.o src/palette.o src/ppu.o \
src/sound.o src/state.o src/unif.o src/unzip.o \
src/video.o src/vsuni.o src/wave.o src/x6502.o 
#src/soundexp.o

MAPPERS_OBJS = src/mappers/15.o src/mappers/151.o src/mappers/16.o src/mappers/17.o src/mappers/18.o \
src/mappers/193.o src/mappers/200.o src/mappers/201.o src/mappers/202.o src/mappers/203.o \
src/mappers/204.o src/mappers/21.o src/mappers/212.o src/mappers/213.o src/mappers/214.o \
src/mappers/215.o src/mappers/217.o src/mappers/22.o src/mappers/225.o \
src/mappers/227.o src/mappers/228.o src/mappers/229.o src/mappers/23.o src/mappers/230.o src/mappers/231.o \
src/mappers/232.o src/mappers/234.o src/mappers/240.o src/mappers/241.o src/mappers/242.o \
src/mappers/244.o src/mappers/246.o src/mappers/24and26.o src/mappers/25.o src/mappers/255.o src/mappers/27.o \
src/mappers/32.o src/mappers/33.o src/mappers/40.o src/mappers/41.o src/mappers/42.o \
src/mappers/43.o src/mappers/46.o src/mappers/50.o src/mappers/51.o src/mappers/59.o \
src/mappers/6.o src/mappers/60.o src/mappers/61.o src/mappers/62.o src/mappers/65.o src/mappers/67.o \
src/mappers/68.o src/mappers/69.o src/mappers/71.o src/mappers/72.o src/mappers/73.o \
src/mappers/75.o src/mappers/76.o src/mappers/77.o src/mappers/79.o src/mappers/8.o src/mappers/80.o \
src/mappers/82.o src/mappers/83.o src/mappers/85.o src/mappers/86.o src/mappers/89.o \
src/mappers/91.o src/mappers/92.o src/mappers/97.o src/mappers/99.o src/mappers/emu2413.o \
src/mappers/mmc2and4.o src/mappers/simple.o src/mappers/__226.o

BOARDS_OBJS = src/boards/01-222.o src/boards/112.o src/boards/117.o src/boards/164.o \
src/boards/183.o src/boards/185.o src/boards/186.o src/boards/187.o \
src/boards/189.o src/boards/199.o src/boards/208.o src/boards/222.o src/boards/235.o \
src/boards/43.o src/boards/57.o src/boards/603-5052.o src/boards/68.o \
src/boards/8157.o src/boards/8237.o src/boards/88.o src/boards/90.o src/boards/95.o \
src/boards/a9711.o src/boards/addrlatch.o src/boards/bmc13in1jy110.o \
src/boards/bmc42in1r.o src/boards/bmc64in1nr.o src/boards/bmc70in1.o src/boards/bonza.o \
src/boards/datalatch.o src/boards/deirom.o src/boards/dream.o \
src/boards/edu2000.o src/boards/fk23c.o src/boards/h2288.o src/boards/karaoke.o \
src/boards/kof97.o src/boards/konami-qtai.o src/boards/malee.o src/boards/mmc1.o \
src/boards/mmc3.o src/boards/mmc5.o src/boards/n-c22m.o src/boards/n106.o src/boards/novel.o \
src/boards/sachen.o src/boards/sheroes.o src/boards/sl1632.o src/boards/subor.o \
src/boards/super24.o src/boards/supervision.o src/boards/t-262.o src/boards/tengen.o \
src/boards/__dummy_mapper.o

#MBSHARE_OBJS = src/mbshare/164.o src/mbshare/90.o src/mbshare/deirom.o \
#src/mbshare/mmc1.o src/mbshare/mmc3.o \
#src/mbshare/mmc5.o src/mbshare/n106.o src/mbshare/tengen.o
#src/mbshare/maxicart.o 

INPUT_OBJS = src/input/arkanoid.o src/input/bworld.o src/input/cursor.o \
src/input/fkb.o src/input/ftrainer.o src/input/hypershot.o \
src/input/mahjong.o src/input/mouse.o src/input/oekakids.o src/input/pads.o \
src/input/powerpad.o src/input/quiz.o src/input/shadow.o \
src/input/suborkb.o src/input/toprider.o src/input/zapper.o

OBJS = $(BASE_OBJS) $(DRIVERS_OBJS) $(MAPPERS_OBJS) $(BOARDS_OBJS) $(INPUT_OBJS) 
#$(MBSHARE_OBJS)

INCDIR =
CFLAGS = -O3 -G0 -Wall -DHAVE_ASPRINTF -D_GNU_SOURCE -DPSS_STYLE=1 -DZLIB -DFCEU_VERSION_NUMERIC=9812 -DFCEU_VERSION=\"0.98.13\" -DLSB_FIRST=1 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DHAVE_ASPRINTF -D_GNU_SOURCE -DPSS_STYLE=1 -DZLIB -DFCEU_VERSION_NUMERIC=9812 -DFCEU_VERSION=\"0.98.12\" -DLSB_FIRST=1 
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION=371
BUILD_PRX=1

LIBDIR =
LDFLAGS =
LIBS = -lz -lm -lpspgu -lpsppower -lpspaudiolib -lpspaudio

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = FCEUltra for PSP
PSP_EBOOT_ICON = icon.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
