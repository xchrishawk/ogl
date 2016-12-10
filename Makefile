# -- Variables --

PROJECT			:= ogl
MODULES			:= main							\
			   app/application					\
			   app/input						\
			   opengl/error						\
			   opengl/glew						\
			   opengl/glfw						\
			   opengl/program					\
			   opengl/shader					\
			   opengl/vertex_array					\
			   opengl/window					\
			   util/debug
PKGLIBS			:= glew glfw3
DEFINES			:= OGL_DEBUG

ROOTDIR			:= .
SRCDIR			:= $(ROOTDIR)/src
BUILDDIR		:= $(ROOTDIR)/build
BINDIR			:= $(ROOTDIR)/bin

SRCS			:= $(addprefix $(SRCDIR)/,$(addsuffix .cpp,$(MODULES)))
DEPS			:= $(addprefix $(BUILDDIR)/,$(addsuffix .d,$(MODULES)))
OBJS			:= $(addprefix $(BUILDDIR)/,$(addsuffix .o,$(MODULES)))
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
	$(RM) -r $(BUILDDIR)/*

rebuild : clean all

# Run executable
run : $(BIN)
	@$ (cd $(BINDIR) && ./$(PROJECT))

# Link executable
$(BIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile object code
$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $<

# Create dependency files
$(BUILDDIR)/%.d : $(SRCDIR)/%.cpp
	@$(MKDIR) $(dir $@)
	@$(CPP) $(CPPFLAGS) -MM -MT $(OBJDIR)/$(notdir $(basename $<)).o -MT $@ -o $@ $<

-include $(DEPS)
