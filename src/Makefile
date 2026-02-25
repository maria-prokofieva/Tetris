clean:
	rm -rf ./build


install: clean
	mkdir ./build
	cd build && gcc -I.. ../gui/cli/main.c ../backend.c -o program -lncurses

start: install
	./build/program
