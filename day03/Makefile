src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc $(src_files) -o d3p1

d3p1: all

.PHONY: clean
clean:
	@rm d3p1

.PHONY: edit
edit:
	@vim src/includes.h src/partone.c src/path.h src/path.c  

.PHONY: run1
run1: d3p1
	@./d3p1 input1


