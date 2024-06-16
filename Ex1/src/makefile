#Definizione delle variabili per i file sorgente e oggetto
MAIN_SRCS := ex1.c
MERGE_TEST_SRCS := test_merge_sort.c
QUICK_TEST_SRCS := test_quick_sort.c
COMMON_OBJS := merge_sort.o ./shared/comparable.o ./shared/free.o ./shared/record.o
MAIN_OBJS := quick_sort.o $(COMMON_OBJS)

#Nome degli eseguibili
MAIN_TARGET := main_ex1
MERGE_TEST_TARGET := test_merge_sort
QUICK_TEST_TARGET := test_quick_sort

#Directory di destinazione
BIN_DIR := bin

#Directory contenente unity.o
UNITY_DIR := test/unity

#Compilatore
CC := clang

# Opzioni per il compilatore
CFLAGS := -Wall -Wextra -std=c11

all: $(BIN_DIR)/$(MAIN_TARGET) $(BIN_DIR)/$(MERGE_TEST_TARGET) $(BIN_DIR)/$(QUICK_TEST_TARGET)

# Assicurarsi che la directory di destinazione esista
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regole per la compilazione degli oggetti
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per il target main_ex1
$(BIN_DIR)/$(MAIN_TARGET): $(MAIN_OBJS) $(MAIN_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(MAIN_SRCS) -o $@

# Regola per il target test_merge_sort
$(BIN_DIR)/$(MERGE_TEST_TARGET): $(COMMON_OBJS) $(MERGE_TEST_SRCS) $(UNITY_DIR)/unity.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(MERGE_TEST_SRCS) $(UNITY_DIR)/unity.o -o $@

# Regola per il target test_quick_sort
$(BIN_DIR)/$(QUICK_TEST_TARGET): quick_sort.o $(COMMON_OBJS) $(QUICK_TEST_SRCS) $(UNITY_DIR)/unity.o | $(BIN_DIR)
	$(CC) $(CFLAGS) quick_sort.o $(COMMON_OBJS) $(QUICK_TEST_SRCS) $(UNITY_DIR)/unity.o -o $@

# Regola per compilare unity.o
$(UNITY_DIR)/unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file oggetto e gli eseguibili
clean:
	rm -f $(COMMON_OBJS) $(MAIN_OBJS) $(UNITY_DIR)/unity.o $(BIN_DIR)/$(MAIN_TARGET) $(BIN_DIR)/$(MERGE_TEST_TARGET) $(BIN_DIR)/$(QUICK_TEST_TARGET)

# Phony target per evitare conflitti con file o cartelle con lo stesso nome
.PHONY: clean all

