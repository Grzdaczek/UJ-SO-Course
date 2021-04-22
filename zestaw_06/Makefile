Q		:= @
CC		:= gcc
LD		:= gcc
AR		:= ar rv
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=c99
CCFLAGS		+= -pedantic
CCFLAGS		+= -pthread
LDFLAGS		+= -pthread
#=-----------------------------------------------------------------------------

all: semuse.x

semuse.x: semuse.o libsem.a
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
