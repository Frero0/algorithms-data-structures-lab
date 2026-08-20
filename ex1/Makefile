CC := clang
CFLAGS := -Wall -Wextra -Wpedantic -std=c11

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
UNITY_DIR := $(SRC_DIR)/test/unity

SHARED_OBJS := \
	$(BUILD_DIR)/shared/comparable.o \
	$(BUILD_DIR)/shared/free.o \
	$(BUILD_DIR)/shared/record.o
SORT_OBJS := $(BUILD_DIR)/merge_sort.o $(BUILD_DIR)/quick_sort.o

.PHONY: all clean demo test

all: \
	$(BIN_DIR)/sort_records \
	$(BIN_DIR)/test_merge_sort \
	$(BIN_DIR)/test_quick_sort \
	$(BIN_DIR)/test_ex1

$(BIN_DIR) $(BUILD_DIR)/test/unity:
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test/unity/unity.o: $(UNITY_DIR)/unity.c | $(BUILD_DIR)/test/unity
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/sort_records: $(SORT_OBJS) $(SHARED_OBJS) $(SRC_DIR)/ex1.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_merge_sort: \
	$(BUILD_DIR)/merge_sort.o \
	$(SHARED_OBJS) \
	$(BUILD_DIR)/test/unity/unity.o \
	$(SRC_DIR)/test_merge_sort.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_quick_sort: \
	$(BUILD_DIR)/quick_sort.o \
	$(SHARED_OBJS) \
	$(BUILD_DIR)/test/unity/unity.o \
	$(SRC_DIR)/test_quick_sort.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test_ex1: $(BIN_DIR)/test_merge_sort $(BIN_DIR)/test_quick_sort
	printf '%s\n' '#!/bin/sh' 'set -e' 'bin_dir=$$(CDPATH= cd -- "$$(dirname -- "$$0")" && pwd)' '"$$bin_dir/test_merge_sort"' '"$$bin_dir/test_quick_sort"' > $@
	chmod +x $@

test: all
	$(BIN_DIR)/test_ex1

demo: $(BIN_DIR)/sort_records
	mkdir -p ../output
	$(BIN_DIR)/sort_records examples/sample-records.csv ../output/sorted-records.csv 2 1
	@printf '\nSorted records:\n'
	@cat ../output/sorted-records.csv

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
