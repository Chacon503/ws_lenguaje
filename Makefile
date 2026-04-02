# =========================================================
# Makefile  —  WS Language v3.0  (bison + flex)
# Pipeline: lexer.l -> flex -> lex.yy.c
#           parser.y -> bison -> parser.tab.c / parser.tab.h
#           gcc links everything into the final binary
# =========================================================

# -- Output binary ----------------------------------------
TARGET     = ws_compiler

# -- Source files -----------------------------------------
LEX_SRC    = lexer.l
YAC_SRC    = parser.y
SYM_SRC    = symbols.c
HELPER_SRC = parser_helper.c
AST_SRC    = ast.c
INTERP_SRC = interpreter.c

# -- Generated files --------------------------------------
LEX_OUT    = lex.yy.c
YAC_OUT    = parser.tab.c
YAC_HDR    = parser.tab.h

# -- Tools ------------------------------------------------
CC         = gcc
LEX        = flex
YAC        = bison -d
CFLAGS     = -Wall -Wextra -g -lm

# -- Main rule: link everything ---------------------------
$(TARGET): $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HELPER_SRC) $(AST_SRC) $(INTERP_SRC)
	$(CC) $(CFLAGS) $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HELPER_SRC) $(AST_SRC) $(INTERP_SRC) -lfl -o $(TARGET)

# -- Generate lexer C code (needs bison header first) -----
$(LEX_OUT): $(LEX_SRC) $(YAC_HDR)
	$(LEX) $(LEX_SRC)

# -- Generate parser C code and header --------------------
$(YAC_OUT) $(YAC_HDR): $(YAC_SRC)
	$(YAC) $(YAC_SRC)

# -- Run with default source file -------------------------
run: $(TARGET)
	./$(TARGET) source.ws

# -- Run with a custom file: make run-file FILE=hello.ws --
run-file: $(TARGET)
	./$(TARGET) $(FILE)

# -- Remove all generated files ---------------------------
clean:
	rm -f $(TARGET) $(LEX_OUT) $(YAC_OUT) $(YAC_HDR)

# -- Show available targets -------------------------------
help:
	@echo ""
	@echo "  WS Language Compiler -- available targets"
	@echo "  ------------------------------------------"
	@echo "  make               Build the compiler"
	@echo "  make run           Build and run source.ws"
	@echo "  make run-file FILE=x.ws   Run a custom file"
	@echo "  make clean         Remove generated files"
	@echo "  make help          Show this message"
	@echo ""
	@echo "  Direct usage: ./ws_compiler <file.ws>"
	@echo ""

.PHONY: run run-file clean help
