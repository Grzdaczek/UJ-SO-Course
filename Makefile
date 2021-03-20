PNAME	:= exec

Q		:= @
CC		:= gcc
LD		:= gcc
RM		:= rm -rf
MKDIR	:= mkdir -p

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
DEPFLAGS	+= -MT $@ -MD -MP -MF $(BLDDIR)$*.d
# LDFLAGS	=

BLDDIR	:= build/
SRCDIR	:= src/

SRCNMS	:= $(notdir $(wildcard $(SRCDIR)*.c))
OBJS	:= $(addprefix $(BLDDIR), $(SRCNMS:.c=.o))
EXEC	:= $(BLDDIR)$(PNAME).x

all: build

build: $(EXEC)

run: build
	$(Q)./$(EXEC)

$(EXEC): $(OBJS)
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) $? -o $@

$(BLDDIR)%.o: $(SRCDIR)%.c
	@printf "  CC\t$<\n"
	$(Q)$(MKDIR) $(BLDDIR)
	$(Q)$(CC) $(DEPFLAGS) $(CCFLAGS) -o $@ -c $<

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) $(BLDDIR)

.PHONY: all build run clean

include $(wildcard $(BLDDIR)*.d)
