src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc src/partone.c -o d4p1

d4p1: all

.PHONY: clean
clean:
	@rm d4p1

.PHONY: edit
edit:
	@vim src/partone.c src/includes.h 

.PHONY: run1
run: d4p1
	@./d4p1 input


