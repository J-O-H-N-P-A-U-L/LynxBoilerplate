RM=rm -f
CC=cc65
AS=ca65
CL=cl65
ECHO=echo
TOUCH=touch
RUN=mednafen

ifeq ($(CC65_HOME),)
	CC65_HOME=/usr/local/lib/cc65
endif
ifeq ($(CC65_INC),)
	CC65_INC=$(CC65_HOME)/include
endif
ifeq ($(CC65_ASMINC),)
	CC65_ASMINC=$(CC65_HOME)/asminc
endif

# Rule for making a *.o file out of a *.c file
%.o: %.c
	$(CC) -t lynx $(CFLAGS) $(SEGMENTS) -o $(patsubst %c, %s, $(notdir $<)) $<
	$(AS) -t lynx -o $@ $(AFLAGS) $(*).s
	$(RM) $*.s

# Rule for making a *.o file out of a *.s file
%.o: %.s
	$(AS) -t lynx -I $(CC65_ASMINC) -o $@ $(AFLAGS) $<


