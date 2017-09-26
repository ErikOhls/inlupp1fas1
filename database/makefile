db: db.c utils.o tree.o list.o
	gcc utils.o tree.o list.o db.c -o db -g

utils.o: utils.c utils.h
	gcc utils.c -Wall -c -g

tree.o: tree.c tree.h
	gcc tree.c -Wall -c -g

list.o: list.c list.h
	gcc list.c -Wall -c -g

run: db
	./db

debug: db
	gdb db

clean:
	rm list.o tree.o utils.o -f

.PHONY: run debug clean 
