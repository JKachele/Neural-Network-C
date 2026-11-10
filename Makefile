CC = gcc
CFLAGS  := -std=c99 -g -MMD
CFLAGS  += -Wall -Wextra -Wpedantic 
CFLAGS  += -Wno-unused-parameter -Wno-unused-variable
# CFLAGS  += -Ilib/cglm/include -DCGLM_OMIT_NS_FROM_STRUCT_API
LDFLAGS := -lm -g
# LDFLAGS += lib/cglm/libcglm.a

BIN := bin
BUILD_DIR := build

SRC  := $(shell find src/ -type f -name '*.c')
OBJ  := $(SRC:%=$(BUILD_DIR)/%.o)
DEPS := $(SRC:%=$(BUILD_DIR)/%.d)

OUT := $(BIN)/out

.PHONY: build run clean

run: $(OUT)
	$(OUT) | tee $(BIN)/output.log

build: $(OUT)

libs:
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make

$(OUT): $(OBJ) # libs
	@mkdir -p $(dir $@)
	$(CC) -o $(OUT) $(OBJ) $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

-include $(DEPS)

clean:
	rm -rf $(BIN)/
	rm -rf $(BUILD_DIR)/

