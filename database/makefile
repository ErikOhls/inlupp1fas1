COMPILER = gcc -Wall -g -c
db: db.c utils.o tree.o list.o
		$(COMPILER) utils.o tree.o list.o db.c -o db

utils.o: utils.c utils.h
		gcc -Wall -g utils.c -c

tree.o: tree.c tree.h
		gcc -Wall -g tree.c -c

list.o: list.c list.h
		gcc -Wall -g list.c -c



run: db
		./db

debug: db
		gdb db
clean:
		rm utils.o tree.o list.o -f
.PHONY run debug clean
