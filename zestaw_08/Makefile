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

XTSERVER	= export LD_LIBRARY_PATH=. && ./serwer.x
XTKLIENT1	= export LD_LIBRARY_PATH=. && sleep 0.1 && ./klient.x
XTKLIENT2	= export LD_LIBRARY_PATH=. && sleep 0.2 && ./klient.x
#=-----------------------------------------------------------------------------

all: libmsg.so msguse.x serwer.x klient.x

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

test:
	xterm -title SERWER -bg red -e "$(XTSERVER)" &\
	xterm -title KLIENT_1 -bg blue -e "$(XTKLIENT1)" &\
	xterm -title KLIENT_2 -bg blue -e "$(XTKLIENT2)" &\

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
