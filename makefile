CFLAGS = -std=c++11 -Wall -g
CC = g++
OUTPUT_DIR = _bin

chess:
	@mkdir -p $(OUTPUT_DIR)
	@$(CC) src/Main.cpp src/*/*.cpp $(CFLAGS) -o $(OUTPUT_DIR)/chess

stuff:
	@mkdir -p $(OUTPUT_DIR)
	@$(CC) test/test.cpp test/A.cpp test/B.cpp $(CFLAGS) -o $(OUTPUT_DIR)/test

clean:
	rm -rf $(OUTPUT_DIR)