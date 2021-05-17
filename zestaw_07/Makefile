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

LDLIBS		+= -lshmem -lsem
#=-----------------------------------------------------------------------------

all: libshmem.so libsem.so shmuse.x glowny.x producent.x konsument.x

shmuse.x: shmuse.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

glowny.x: glowny.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

producent.x: producent.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

konsument.x: konsument.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

libshmem.so: shmem.c
	@printf "  CC\t$?\n"
	$(Q)$(CC) -c -O -fPIC shmem.c -lrt
	$(Q)$(CC) -shared -o libshmem.so shmem.o -lrt

libsem.so: sem.c
	@printf "  CC\t$?\n"
	$(Q)$(CC) -c -O -fPIC sem.c -pthread
	$(Q)$(CC) -shared -o libsem.so sem.o -pthread

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@  

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
