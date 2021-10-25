default: all

SRC_DIRS := . src src/libmld src/libp src/libu src/libxmalloc src/uopt

AVOID_UB ?= 1

ARCH ?= x86

ifeq ($(ARCH),x86)
CC := gcc
ENDIANNESS := -DLITTLE_ENDIAN
ARCH_FLAGS := -m32 -mfpmath=sse -msse2 -ffp-contract=off $(ENDIANNESS)
OPTIMIZATION = -ggdb3
#OPTIMIZATION = -O2 -march=native -mtune=native -flto
else ifeq ($(ARCH),mips)
CC := mips-linux-gnu-gcc
ARCH_FLAGS := -fPIC -mips2 -mfp32
OPTIMIZATION := -ggdb3
else
$(error unsupported arch "$(ARCH)")
endif

CFLAGS := -I src -Wall $(ARCH_FLAGS) $(OPTIMIZATION)
LDFLAGS := $(ARCH_FLAGS) $(OPTIMIZATION)

ifeq ($(AVOID_UB),1)
    CFLAGS := $(CFLAGS) -DAVOID_UB
endif

BUILD_DIR := build

ALL_DIRS := $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
O_FILES := $(addprefix $(BUILD_DIR)/,$(C_FILES:.c=.o))
DEP_FILES := $(O_FILES:.o=.d)

# Ensure build directories exist before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

TARGET := $(BUILD_DIR)/uopt

all: $(TARGET)

$(TARGET): $(O_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -MMD -c $(CFLAGS) -o $@ $<

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: all clean default

-include $(DEP_FILES)
