Q		:= @
CC		:= gcc
LD		:= gcc
AR		:= ar rv
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=gnu99
CCFLAGS		+= -pedantic
CCFLAGS		+= -L.

LDFLAGS		+= -L.

LDLIBS		+= -lmsg
LDLIBS		+= -lrt
#=-----------------------------------------------------------------------------

all: libmsg.so msguse.x # serwer.x kilent.x

msguse.x: msguse.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

serwer.x: serwer.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

klient.x: klient.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

libmsg.so: msg.c
	@printf "  CC\t$?\n"
	$(Q)$(CC) -c -O -fPIC msg.c -pthread
	$(Q)$(CC) -shared -o libmsg.so msg.o -pthread

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@  

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
