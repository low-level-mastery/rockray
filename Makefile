# SPDX-License-Identifier: MIT
# Raycaster Kernel - Core Build System

CC          := gcc
CFLAGS      := -Wall -Wextra -O2 -std=c11 -Iinclude
LIBS        := `pkg-config --libs sdl3` -lm
TARGET      := raycaster
BUILD_DIR   := build

# Recursive wildcard utility
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$(d),$(2)) $(filter $(subst *,%,$(2)),$(d)))

# Source files auto-discovery
SRCS        := $(call rwildcard,src,*.c) $(call rwildcard,arch,*.c)
OBJS        := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean info

all: $(TARGET)

# Link target binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Object build rule with directory shadow tree creation
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Debugging targets
info:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"

# Clean rules
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

