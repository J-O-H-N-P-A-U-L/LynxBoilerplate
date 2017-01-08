include ../Common.mk

objects= \
	exehdr.o \
	directory.o

objlists = \
	../intro/objlist \
	../music/objlist \
	../play/objlist \
	../main/objlist

others = \
	@../intro/objlist \
	@../music/objlist \
	@../play/objlist \
	@../main/objlist

all:
	$(MAKE) -C ../intro
	$(MAKE) -C ../music
	$(MAKE) -C ../play
	$(MAKE) -C ../main
	$(MAKE) game.lnx

game.lnx: $(objects) $(objlists)
	$(CL) -t lynx -C lynx-coll.cfg -o $@ -m game.map $(objects) $(others) lynx.lib

clean:
	$(MAKE) -C ../intro clean
	$(MAKE) -C ../music clean
	$(MAKE) -C ../play clean
	$(MAKE) -C ../main clean
	$(RM) game.map game.lnx $(objects)

