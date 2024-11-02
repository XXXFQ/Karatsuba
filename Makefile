BUILDDIR	:=	Build
INCLUDEDIR	:=	Includes
SOURCES		:=	src

# Detect OS type
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    TARGET := Karatsuba.elf
else ifeq ($(UNAME), Darwin)
    TARGET := Karatsuba  # No extension for macOS
else
    TARGET := Karatsuba.exe
endif

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CC			:=	g++
CFLAGS		:=	-fdiagnostics-color=always -g
CPPFLAGS	:=	-I $(INCLUDEDIR)

#---------------------------------------------------------------------------------
# Get source files
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export LD	:=	$(CC)
OFILES		:=	$(addprefix $(BUILDDIR)/,$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o))

.PHONY: $(BUILDDIR) clean all

#---------------------------------------------------------------------------------
all: $(TARGET)

$(TARGET): $(OFILES)
	$(LD) $(CFLAGS) $(OFILES) -o $@

$(BUILDDIR)/%.o: src/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

#---------------------------------------------------------------------------------
clean:
	rm -rf $(BUILDDIR) $(TARGET)