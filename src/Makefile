# === Компилятор и флаги ===
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L
LDFLAGS = -lncurses
CHECK_LIBS = -lcheck -lsubunit -lm -lpthread -lrt

# === Директории ===
BUILD_DIR = build
INSTALL_DIR = install_dir

# === Include пути ===
INCLUDES = -I. -Ibrick_game/tetris -Igui/cli

# === Исходники ===
BACKEND_SRC = brick_game/tetris/tetris_backend.c
FRONTEND_SRC = gui/cli/tetris_frontend.c
MAIN_SRC = main.c
TEST_SRC = test.c

# === Объектные файлы ===
BACKEND_OBJ = $(BUILD_DIR)/tetris_backend.o
FRONTEND_OBJ = $(BUILD_DIR)/tetris_frontend.o
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o

# === Библиотека ===
LIB = $(BUILD_DIR)/libtetris.a



valgrind_test:
	./build/test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
         --track-origins=yes --show-reachable=yes ./build/test

# === Основные цели ===
all: install

# === Очистка ===
clean:
	rm -rf $(BUILD_DIR) $(INSTALL_DIR) *.o *.a *.gcda *.gcno *.gcov coverage.info report

# === Сборка бэкенда ===
$(BACKEND_OBJ): $(BACKEND_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Сборка фронтенда ===
$(FRONTEND_OBJ): $(FRONTEND_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Сборка main ===
$(MAIN_OBJ): $(MAIN_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Сборка библиотеки ===
$(LIB): $(BACKEND_OBJ)
	ar rcs $@ $^

# === Сборка программы ===
install: clean $(LIB) $(FRONTEND_OBJ) $(MAIN_OBJ)
	mkdir -p $(INSTALL_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(FRONTEND_OBJ) $(LIB) -o $(BUILD_DIR)/program $(LDFLAGS)
	cp $(BUILD_DIR)/program $(INSTALL_DIR)/
	touch $(INSTALL_DIR)/high_score.txt

# === Удаление установленного ===
uninstall:
	rm -rf $(INSTALL_DIR)

# === Запуск игры ===
start: install
	./$(BUILD_DIR)/program

# === Сборка тестов ===
$(TEST_OBJ): $(TEST_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: clean $(BACKEND_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(BACKEND_OBJ) -o $(BUILD_DIR)/test $(CHECK_LIBS)
	./$(BUILD_DIR)/test

# === Отчёт покрытия gcov ===
gcov_report: clean $(BACKEND_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) --coverage $(TEST_SRC) $(BACKEND_SRC) -o $(BUILD_DIR)/test $(CHECK_LIBS)
	./$(BUILD_DIR)/test
	lcov -t "tetris_test" -o coverage.info -c -d .
	lcov --remove coverage.info '*/test.c' -o coverage.info
	genhtml -o report coverage.info

# === Заглушки по требованиям ===
dvi:
	@echo "No documentation"

dist: clean install
	tar -czf tetris.tar.gz $(INSTALL_DIR)

leaks: test
	$(LEAK_CHECK) ./$(BUILD_DIR)/test