CFLAGS = -Wall -g
CC = g++
OUTPUT_DIR = _bin

chess:
	@mkdir -p $(OUTPUT_DIR)
	@$(CC) Main.cpp $(CFLAGS) -o $(OUTPUT_DIR)/chess

clean:
	rm -rf $(OUTPUT_DIR)