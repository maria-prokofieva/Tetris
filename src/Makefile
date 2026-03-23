CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L
LDFLAGS = -lncurses
CHECK_LIBS = -lcheck -lm -lsubunit 

BUILD_DIR = build
INSTALL_DIR = install_dir

INCLUDES = -I. -Ibrick_game/tetris 

BACKEND_SRC = brick_game/tetris/tetris_backend.c
FRONTEND_SRC = gui/cli/tetris_frontend.c
MAIN = gui/cli/main.c
TEST_SRC = test.c

BACKEND_OBJ = $(BUILD_DIR)/tetris_backend.o
FRONTEND_OBJ = $(BUILD_DIR)/tetris_frontend.o
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o

LIB = $(BUILD_DIR)/lib_tetris.a

all: install

clean:
	rm -rf $(BUILD_DIR) $(INSTALL_DIR) *.o *.a *.gcda *.gcno *.gcov coverage.info report

$(BACKEND_OBJ): $(BACKEND_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FRONTEND_OBJ): $(FRONTEND_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MAIN_OBJ): $(MAIN)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIB): $(BACKEND_OBJ)
	ar rcs $@ $^

install: clean $(LIB) $(FRONTEND_OBJ) $(MAIN_OBJ)
	mkdir -p $(INSTALL_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(FRONTEND_OBJ) $(LIB) -o $(BUILD_DIR)/program $(LDFLAGS)
	cp $(BUILD_DIR)/program $(INSTALL_DIR)/

uninstall:
	rm -rf $(INSTALL_DIR)

start: install
	./$(BUILD_DIR)/program

$(TEST_OBJ): $(TEST_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: clean $(BACKEND_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(BACKEND_OBJ) -o $(BUILD_DIR)/test $(CHECK_LIBS)
	./$(BUILD_DIR)/test

valgrind_test: test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./build/test

gcov_report: clean $(BACKEND_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) --coverage $(TEST_SRC) $(BACKEND_SRC) -o $(BUILD_DIR)/test $(CHECK_LIBS)
	./$(BUILD_DIR)/test
	lcov -t "tetris_test" -o coverage.info -c -d .
	lcov --remove coverage.info '*/test.c' -o coverage.info
	genhtml -o report coverage.info

dvi:
	xdg-open dvi/README.md

dist: clean install
	tar -czf tetris.tar.gz $(INSTALL_DIR)

