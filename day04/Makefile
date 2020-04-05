src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc src/partone.c -o d4p1
	@gcc src/parttwo.c -o d4p2

d4p1: all
d4p2: all

.PHONY: clean
clean:
	@rm d4p1 d4p2

.PHONY: edit
edit:
	@vim src/parttwo.c src/includes.h 

.PHONY: run1
run1: d4p1
	@./d4p1 input

.PHONY: run
run: d4p2
	@./d4p2 input

