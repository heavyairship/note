all:
	g++ note.cpp -o note

build: all

install: all
	cp note /usr/local/bin

clean:
	rm -f note
