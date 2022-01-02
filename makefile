# cpp
CCFLAGS = -std=c++11 -Wall -g -Wno-unknown-pragmas
CC = g++
C_OUTPUT_DIR = _bin
# wasm
EXPORTED_FUNCTIONS = ["_malloc", "_free"]
EXPORTED_RUNTIME_METHODS = []
WCFLAGS = -s WASM=1 -s EXPORTED_FUNCTIONS='$(EXPORTED_FUNCTIONS)' -s EXPORTED_RUNTIME_METHODS='$(EXPORTED_RUNTIME_METHODS)'
WCC = em++
W_OUTPUT_DIR = web/public/wasm

chess:
	@mkdir -p $(C_OUTPUT_DIR)
	@$(CC) ConsoleChess.cpp engine/*.cpp engine/*/*.cpp $(CCFLAGS) -o $(C_OUTPUT_DIR)/chess
	@echo "Final file size:"
	@du -h $(C_OUTPUT_DIR)/chess

wasm_c:
	@mkdir -p $(C_OUTPUT_DIR)
	@$(CC) wasm/Main.cpp engine/*.cpp engine/*/*.cpp $(CCFLAGS) -o $(C_OUTPUT_DIR)/thing
	@echo "Final file size:"
	@du -h $(C_OUTPUT_DIR)/thing

wasm: wasm/Main.cpp
	@mkdir -p $(W_OUTPUT_DIR)
	@$(WCC) wasm/Main.cpp engine/*.cpp engine/*/*.cpp $(WCFLAGS) -o $(W_OUTPUT_DIR)/chess.js
	@cat wasm/*.js >> $(W_OUTPUT_DIR)/chess.js
	@echo "Final file sizes:"
	@du -h $(W_OUTPUT_DIR)/chess.js
	@du -h $(W_OUTPUT_DIR)/chess.wasm

clean:
	@rm -rf $(C_OUTPUT_DIR)
	@rm -rf $(W_OUTPUT_DIR)