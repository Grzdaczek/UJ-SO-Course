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
CCFLAGS		+= -pthread

LDFLAGS		+= -L.
LDFLAGS		+= -pthread

LDLIBS		+= -lshmem
#=-----------------------------------------------------------------------------

all: libshmem.so shmuse.x

shmuse.x: shmuse.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

libshmem.so: shmem.c
	@printf "  CC\t$?\n"
	$(Q)$(CC) -c -O -fPIC shmem.c -lrt
	$(Q)$(CC) -shared -o libshmem.so shmem.o -lrt

%.o: %.c
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@  

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
