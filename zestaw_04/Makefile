Q		:= @
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=gnu99
CCFLAGS		+= -pedantic
# LDFLAGS		+= -v

#=-----------------------------------------------------------------------------

all: prodkons.x

prodkons.x: prodkons.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x

.PHONY: all clean
