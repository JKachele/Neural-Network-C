CC = gcc
CFLAGS = -std=c99 -g
CFLAGS += -Wall -Wextra -Wpedantic 
CFLAGS += -Wno-unused-parameter
CFLAGS += -Ilib/cglm/include -DCGLM_OMIT_NS_FROM_STRUCT_API
LDFLAGS += lib/cglm/libcglm.a -lm -g

BIN := bin
BUILD_DIR := build

SRC := $(shell find src/ -type f -name '*.c')
OBJ := $(SRC:%=$(BUILD_DIR)/%.o)

OUT := $(BIN)/out

.PHONY: clean run

run: $(OUT)
	$(OUT) | tee $(BIN)/output.log

libs:
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make

$(OUT): $(OBJ) libs
	@mkdir -p $(dir $@)
	$(CC) -o $(OUT) $(OBJ) $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN)/
	rm -rf $(BUILD_DIR)/

