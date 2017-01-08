include ../Common.mk

thisdir=play

objects= \
	game.o

SEGMENTS= \
	--code-name game_CODE \
	--rodata-name game_RODATA \
	--data-name game_DATA \
	--bss-name game_BSS

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

clean:
	$(RM) objlist $(objects)
