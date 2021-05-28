Q		:= @
CC		:= gcc
LD		:= gcc
AR		:= ar rv
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -std=gnu99
CCFLAGS		+= -pedantic

LDLIBS		+= -lpthread
LDLIBS		+= -lrt
#=-----------------------------------------------------------------------------

all: piekarnia.x

piekarnia.x: piekarnia.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
