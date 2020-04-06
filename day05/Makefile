src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc src/partone.c -o d5p1
	@gcc src/parttwo.c -o d5p2

d5p1: all
d5p2: all

.PHONY: clean
clean:
	@rm d5p1 d5p2

.PHONY: edit
edit:
	@vim src/partone.c src/includes.h 

.PHONY: run
run: d5p1
	@./d5p1 input

.PHONY: run2
run2: d5p2
	@./d5p2 input

