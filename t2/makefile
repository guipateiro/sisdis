all: tree

tree: tree.o cisj.o utils.o
	$(LINK.c) -o $@ -Bstatic tree.o cisj.o utils.o -lm

cisj.o: cisj.c cisj.h
	$(COMPILE.c)  -g cisj.c

tree.o: tree.c
	$(COMPILE.c) -g  tree.c

utils.o: utils.c
	$(COMPILE.c) -g utils.c

clean:
	$(RM) *.o tree relat saida
