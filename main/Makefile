include ../Common.mk

thisdir=main

objects= \
	lynx-snd.o \
	main.o \

all: objlist

objlist: $(objects)
	$(RM) objlist
	for obj in $(objects); do $(ECHO) ../$(thisdir)/$$obj >> objlist; done

clean:
	$(RM) objlist $(objects)
