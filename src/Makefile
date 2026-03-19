clean:
	rm -rf ./build
	rm -f *.gcda *.gcno *.gcov
	rm -rf report


install: clean
	mkdir ./build
	cd build && gcc -I.. ../gui/cli/main.c ../backend.c -o program -lncurses
	
start: install
	./build/program


test: clean
	gcc -I. backend.c test.c -o test \
	-lcheck -lsubunit -lm -lpthread -lrt
	./test


gcov_report: clean
	gcc -I. backend.c test.c -o test \
	--coverage -lcheck -lsubunit -lm -lpthread -lrt
	./test
	lcov -t "tetris_test" -o coverage.info -c -d .
	lcov --remove coverage.info '*/test.c' -o coverage.info
	genhtml -o report coverage.info
	explorer.exe report || true