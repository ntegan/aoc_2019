src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc src/partone.c src/path.c -o d3p1
	@gcc src/parttwo.c src/path.c -o d3p2

d3p1: all
d3p2: all

.PHONY: clean
clean:
	@rm d3p1 d3p2

.PHONY: edit
edit:
	@vim src/includes.h src/parttwo.c src/path.h src/path.c  

.PHONY: run1
run1: d3p1
	@./d3p1 input1
.PHONY: run2
run2: d3p2
	@./d3p2 input1


