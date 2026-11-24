CXX      := g++
WARNINGS := -Wall -Wextra -Wconversion -Wsign-conversion
STD      := -std=c++20
LDFLAGS  :=
LDLIBS   :=

TARGET := utils_cpp_capstone
SRCS   := main.cpp \
          simple_file_info.cpp \
          prime_checker.cpp \
          other_utils.cpp \
          statistical_calc.cpp \
          word_and_char_counter.cpp

# Default is a release build; "make debug" switches to the debug settings.
ifeq ($(MAKECMDGOALS),debug)
  BUILD    := debug
  OPTFLAGS := -Og -g -fsanitize=address,undefined
  LDFLAGS  += -fsanitize=address,undefined
else
  BUILD    := release
  OPTFLAGS := -O2 -DNDEBUG
endif

BUILDDIR := build/$(BUILD)
OBJS     := $(SRCS:%.cpp=$(BUILDDIR)/%.o)
CXXFLAGS := $(STD) $(WARNINGS) $(OPTFLAGS)

.PHONY: all debug clean

all: $(BUILDDIR)/$(TARGET)

debug: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -rf build
