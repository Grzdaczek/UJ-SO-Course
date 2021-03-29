Q		:= @
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=c99
# LDFLAGS		+= -v

#=-----------------------------------------------------------------------------

all: drzewko1.x drzewko2.x macierzysty.x potomny.x zombie.x orphan.x execute.x

drzewko1.x: drzewko1.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

drzewko2.x: drzewko2.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

macierzysty.x: macierzysty.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

potomny.x: potomny.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

zombie.x: zombie.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

orphan.x: orphan.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

execute.x: execute.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^


%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x

.PHONY: all clean
