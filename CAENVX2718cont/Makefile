COMP_NAME = CAENVX2718cont

all: $(COMP_NAME)Comp

SRCS += $(COMP_NAME).cpp
SRCS += $(COMP_NAME)Comp.cpp
SRCS += ../src/VMEutils.cpp
SRCS += ../src/TDataContainer.cpp

LDLIBS += -lCAENVME
LDLIBS += -lCAENComm
LDLIBS += -ldl
CPPFLAGS += -I../../TDigiTES/include -I../include

# sample install target
#
# MODE = 0755
# BINDIR = /tmp/mybinary
#
# install: $(COMP_NAME)Comp
#	mkdir -p $(BINDIR)
#	install -m $(MODE) $(COMP_NAME)Comp $(BINDIR)

include /usr/share/daqmw/mk/comp.mk
