COMPILER = gcc -Wall -c -g

db: db.c utils.o tree.o list.o
		${COMPILER} utils.o tree.o list.o db.c -o db

utils.o: utils.c utils.h
		 ${COMPILER} utils.c

tree.o: tree.c tree.h
		${COMPILER} tree.c

list.o: list.c list.h
		${COMPILER} list.c

run: db
		./db

debug: db
		gdb db

clean:
	rm list.o tree.o utils.o -f


.PHONY: run debug clean 
