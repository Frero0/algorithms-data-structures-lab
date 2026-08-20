CC := clang
CFLAGS := -Wall -Wextra -Wpedantic -std=c11

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
UNITY_DIR := $(SRC_DIR)/test/unity

.PHONY: all clean demo test

all: $(BIN_DIR)/spell_checker $(BIN_DIR)/test_ex2

$(BIN_DIR) $(BUILD_DIR)/test/unity:
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test/unity/unity.o: $(UNITY_DIR)/unity.c | $(BUILD_DIR)/test/unity
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/spell_checker: $(BUILD_DIR)/edit_distance.o $(SRC_DIR)/ex2.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_ex2: \
	$(BUILD_DIR)/edit_distance.o \
	$(BUILD_DIR)/test/unity/unity.o \
	$(SRC_DIR)/edit_distance_test.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

test: all
	$(BIN_DIR)/test_ex2

demo: $(BIN_DIR)/spell_checker
	$(BIN_DIR)/spell_checker examples/sample-dictionary.txt examples/sample-text.txt

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
