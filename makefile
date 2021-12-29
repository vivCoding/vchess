CFLAGS = -std=c++11 -Wall -g -Wno-unknown-pragmas
CC = g++
OUTPUT_DIR = _bin

chess:
	@mkdir -p $(OUTPUT_DIR)
	@$(CC) ConsoleChess.cpp engine/*/*.cpp $(CFLAGS) -o $(OUTPUT_DIR)/chess

clean:
	rm -rf $(OUTPUT_DIR)