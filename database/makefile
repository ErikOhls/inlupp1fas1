
COMPILER = gcc 

db: db.c utils.o tree.o list.o
	$(COMPILER) utils.o tree.o list.o db.c -o db -g

utils.o: utils.c utils.h
	 $(COMPILER) utils.c -Wall -c -g

tree.o: tree.c tree.h
	$(COMPILER) tree.c -Wall -c -g

list.o: list.c list.h
	$(COMPILER) list.c -Wall -c -g


run: db
	./db

debug: db
	gdb db


clean:
	rm list.o tree.o utils.o -f

.PHONY: run debug clean 

clean:
	rm utils.o tree.o list.o -f


