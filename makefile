#########################
# customise these
CFILES := example.cpp plugin.cpp plugin_impl.cpp
PROG := example
CFLAGS := -Wall -Wextra -g -std=c++0x
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := g++

OBJFILES := $(CFILES:.cpp=.o)
DEPFILES := $(CFILES:.cpp=.d)

$(PROG) : $(OBJFILES)
	$(LINK.o) $(LDFLAGS) -o $@ $^

$(OBJFILES): $(CFILES)
	$(CC) $(CFLAGS) -c $(CFILES)

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES)

-include $(DEPFILES)
