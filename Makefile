all: clean build run

build:
	g++ spinningsquare.cpp -o spinningsquare

run:
	./spinningsquare

clean:
	rm -rf spinningsquare build/
