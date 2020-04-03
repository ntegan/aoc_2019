src_files=src/*.c
header_files=src/*.h

.PHONY: all
all: $(src_files) $(header_files)
	@gcc $(src_files) -o d3p1

.PHONY: clean
clean:
	@rm d3p1

.PHONY: edit
edit:
	@vim src/includes.h src/partone.c src/path.h src/path.c


