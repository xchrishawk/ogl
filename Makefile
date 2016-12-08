# -- Variables --

PROJECT			:= ogl
MODULES			:= main							\
			   opengl/error						\
			   opengl/glew						\
			   opengl/glfw						\
			   util/debug
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

MKDIR			:= mkdir -p
CPP			:= g++ -E
CXX			:= g++ -c
LD			:= g++

CPPFLAGS		:= $(addprefix -D,$(DEFINES)) `pkg-config $(PKGLIBS) --cflags-only-I` -iquote $(SRCDIR)
CFLAGS			:= -std=gnu++11 -g -Wall -Wpedantic `pkg-config $(PKGLIBS) --cflags-only-other`
LDFLAGS			:= -g
LIBS			:= `pkg-config $(PKGLIBS) --libs`

# -- Rules --

.PHONY : all clean rebuild run

all : $(BIN)

clean :
	$(RM) -r $(BINDIR)/*
	$(RM) -r $(OBJDIR)/*
	$(RM) -r $(DEPDIR)/*

rebuild : clean all

# Run executable
run : $(BIN)
	$ (cd $(BINDIR) && ./$(PROJECT))

# Link executable
$(BIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile object code
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(MKDIR) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $<

# Create dependency files
$(DEPDIR)/%.d : $(SRCDIR)/%.cpp
	$(MKDIR) $(dir $@)
	$(CPP) $(CPPFLAGS) -MM -MT $(OBJDIR)/$(notdir $(basename $<)).o -MT $@ -o $@ $<

-include $(DEPS)
