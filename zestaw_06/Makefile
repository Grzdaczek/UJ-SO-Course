Q		:= @
CC		:= gcc
LD		:= gcc
AR		:= ar rv
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=gnu99
CCFLAGS		+= -pedantic
CCFLAGS		+= -pthread
LDFLAGS		+= -pthread
#=-----------------------------------------------------------------------------

all: semuse.x prog.x powielacz.x

semuse.x: semuse.o libsem.a
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

prog.x: prog.o libsem.a
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

powielacz.x: powielacz.o libsem.a
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

libsem.a: sem.o
	@printf "  AR\t$?\n"
	$(Q)$(AR) $@ $?

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a

.PHONY: all clean
