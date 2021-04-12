Q		:= @
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=gnu99
# LDFLAGS		+= -v

#=-----------------------------------------------------------------------------

all: obsluga.x wysylaj.x grupa.x

obsluga.x: obsluga.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

wysylaj.x: wysylaj.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

grupa.x: grupa.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x

.PHONY: all clean
