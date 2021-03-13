PNAME	:= cppclass

Q		:= @
CXX		:= g++
LD		:= g++
RM		:= rm -rf
MKDIR	:= mkdir -p

CXXFLAGS	+= -Wall
CXXFLAGS	+= -O2
DEPFLAGS	+= -MT $@ -MD -MP -MF $(BLDDIR)$*.d
# LDFLAGS	=

BLDDIR	:= build/
SRCDIR	:= src/

SRCNMS	:= $(notdir $(wildcard $(SRCDIR)*.cpp))
OBJS	:= $(addprefix $(BLDDIR), $(SRCNMS:.cpp=.o))
EXEC	:= $(BLDDIR)$(PNAME).x

all: build

build: $(EXEC)

run: build
	$(Q)./$(EXEC)

$(EXEC): $(OBJS)
	@printf "  LD\t$?\n"
	$(Q)$(LD) $(LDFLAGS) $? -o $@

$(BLDDIR)%.o: $(SRCDIR)%.cpp
	@printf "  CXX\t$<\n"
	$(Q)$(MKDIR) $(BLDDIR)
	$(Q)$(CXX) $(DEPFLAGS) $(CXXFLAGS) -o $@ -c $<

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) $(BLDDIR)

.PHONY: all build run clean

include $(wildcard $(BLDDIR)*.d)
