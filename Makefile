# -- Variables --

# Project configuration
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
			   shaders/shader_sources				\
			   util/debug
SHADERS			:= shaders/default_fragment_shader			\
			   shaders/default_vertex_shader
PKGLIBS			:= glew glfw3
DEFINES			:= OGL_DEBUG

# Working directories
ROOTDIR			:= .
SRCDIR			:= $(ROOTDIR)/src
BUILDDIR		:= $(ROOTDIR)/build
OBJDIR			:= $(BUILDDIR)/obj
DEPDIR			:= $(BUILDDIR)/dep
INCDIR			:= $(BUILDDIR)/inc
BINDIR			:= $(BUILDDIR)/bin

# Input and output files
SRC			:= $(addprefix $(SRCDIR)/,$(addsuffix .cpp,$(MODULES)))
DEP			:= $(addprefix $(DEPDIR)/,$(addsuffix .d,$(MODULES)))
OBJ			:= $(addprefix $(OBJDIR)/,$(addsuffix .o,$(MODULES)))
GLSLC			:= $(addprefix $(INCDIR)/,$(addsuffix .glslc,$(SHADERS)))
EXE			:= $(BINDIR)/$(PROJECT)

# Toolchain
MKDIR			:= mkdir -p
CAT			:= cat
XXD			:= xxd -i
CPP			:= g++ -E
CXX			:= g++ -c
LD			:= g++

# Toolchain flags
CPPFLAGS		:= $(addprefix -D,$(DEFINES)) \
			   `pkg-config $(PKGLIBS) --cflags-only-I` \
		           -iquote $(SRCDIR) \
			   -iquote $(INCDIR)
CFLAGS			:= -std=gnu++11 -g -Wall -Wpedantic \
			   `pkg-config $(PKGLIBS) --cflags-only-other`
LDFLAGS			:= -g
LIBS			:= `pkg-config $(PKGLIBS) --libs`

# -- Rules --

.PHONY : all clean rebuild run

all : $(EXE)

clean :
	@$(RM) -r $(BUILDDIR)/*
	@echo "Build directory cleaned."

rebuild : clean all

# Run executable
run : $(EXE)
	$(EXE)

# Link executable
$(EXE) : $(OBJ)
	@$(MKDIR) $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

# Compile object code
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ $<

# Create dependency files
$(DEPDIR)/%.d : $(SRCDIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CPP) $(CPPFLAGS) -MM -MT $(OBJDIR)/$(notdir $(basename $<)).o -MT $@ -o $@ $<

# Create include files
$(INCDIR)/%.glslc : $(SRCDIR)/%.glsl
	@$(MKDIR) $(dir $@)
	$(CAT) $< | $(XXD) > $@

# Manual dependencies for specific files
$(OBJDIR)/shaders/shader_sources.o : $(GLSLC)
$(DEPDIR)/shaders/shader_sources.d : $(GLSLC)

-include $(DEP)
