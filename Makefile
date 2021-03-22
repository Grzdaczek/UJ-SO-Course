Q		:= @
CC		:= gcc
LD		:= gcc
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=c99
# LDFLAGS		+= -v

#=-----------------------------------------------------------------------------

all: z1_procinfo.x z2_kopiowanie.x z3_procesy.x #z4_lider.x

z1_procinfo.x: main.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ main.o procinfo.o

z2_kopiowanie.x: kopiuj.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ kopiuj.o

z3_procesy.x: procesy.o procinfo.o
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ procesy.o procinfo.o

# z4_lider.x: lider.o

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x

.PHONY: all clean
