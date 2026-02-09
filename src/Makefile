clean:
	rm -rf ./build


install: clean
	mkdir ./build
	cd build && gcc ../main.c ../test_front.c ../backend.c -o program -lncurses

start: install
	./build/program
