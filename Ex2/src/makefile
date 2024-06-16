# Definizione delle variabili per i file sorgente e oggetto
MAIN_SRCS := ex2.c
TEST_SRCS := edit_distance_test.c
COMMON_OBJS := edit_distance.o 
MAIN_OBJS := edit_distance.o 

# Nome degli eseguibili
MAIN_TARGET := main_ex2
TEST_TARGET := test_ex2

# Directory di destinazione
BIN_DIR := bin

# Directory contenente unity.o
UNITY_DIR := test/unity

# Compilatore
CC := clang

# Opzioni per il compilatore
CFLAGS := -Wall -Wextra -std=c11

all: $(BIN_DIR)/$(MAIN_TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Assicurarsi che la directory di destinazione esista
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regole per la compilazione degli oggetti
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per il target main_ex1
$(BIN_DIR)/$(MAIN_TARGET): $(MAIN_OBJS) $(MAIN_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(MAIN_SRCS) -o $@

# Regola per il target test_ex1
$(BIN_DIR)/$(TEST_TARGET): $(COMMON_OBJS) $(TEST_SRCS) $(UNITY_DIR)/unity.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(TEST_SRCS) $(UNITY_DIR)/unity.o -o $@

# Regola per compilare unity.o
$(UNITY_DIR)/unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file oggetto e gli eseguibili
clean:
	rm -f $(COMMON_OBJS) $(MAIN_OBJS) $(UNITY_DIR)/unity.o $(BIN_DIR)/$(MAIN_TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Phony target per evitare conflitti con file o cartelle con lo stesso nome
.PHONY: clean all

