COMP_NAME = VMEcrate

all: $(COMP_NAME)Comp

SRCS += $(COMP_NAME).cpp
SRCS += $(COMP_NAME)Comp.cpp
SRCS += ../src/VMEbase.cpp
SRCS += ../src/VMEethSIS.cpp
SRCS += ../src/TDataContainer.cpp
SRCS += ../include/includesiseth/sis3153ETH_vme_class.cpp

LDLIBS += -ldl
CPPFLAGS += -I../../TDigiTES/include -I../include -I../include/includesiseth

# sample install target
#
# MODE = 0755
# BINDIR = /tmp/mybinary
#
# install: $(COMP_NAME)Comp
#	mkdir -p $(BINDIR)
#	install -m $(MODE) $(COMP_NAME)Comp $(BINDIR)

include /usr/share/daqmw/mk/comp.mk
