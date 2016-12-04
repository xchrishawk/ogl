# -- Variables --

PROJECT			:= ogl
MODULES			:= application glew glfw key_input main opengl renderer shader state util window
PKGLIBS			:= glew glfw3
DEFINES			:= OGL_DEBUG

ROOTDIR			:= .
SRCDIR			:= $(ROOTDIR)/src
DEPDIR			:= $(ROOTDIR)/dep
OBJDIR			:= $(ROOTDIR)/obj
BINDIR			:= $(ROOTDIR)/bin

SRCS			:= $(addprefix $(SRCDIR)/,$(addsuffix .cpp,$(MODULES)))
DEPS			:= $(addprefix $(DEPDIR)/,$(addsuffix .d,$(MODULES)))
OBJS			:= $(addprefix $(OBJDIR)/,$(addsuffix .o,$(MODULES)))
BIN			:= $(BINDIR)/$(PROJECT)

CPP			:= g++ -E
CXX			:= g++ -c
LD			:= g++

CPPFLAGS		:= $(addprefix -D,$(DEFINES)) `pkg-config $(PKGLIBS) --cflags-only-I`
CFLAGS			:= -std=gnu++11 -g -Wall -Wpedantic `pkg-config $(PKGLIBS) --cflags-only-other`
LDFLAGS			:= -g
LIBS			:= `pkg-config $(PKGLIBS) --libs`

# -- Rules --

.PHONY : all clean rebuild run

all : $(BIN)

clean :
	$(RM) $(BIN) $(OBJS) $(DEPS)

rebuild : clean all

# Run executable
run : $(BIN)
	$ (cd $(BINDIR) && ./$(PROJECT))

# Link executable
$(BIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile object code
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $<

# Create dependency files
$(DEPDIR)/%.d : $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -MM -MT $(OBJDIR)/$(notdir $(basename $<)).o -MT $@ -o $@ $<

-include $(DEPS)
