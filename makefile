all: tempo

tempo: tempo.o smpl.o rand.o tree.o cisj.o utils.o
	$(LINK.c) -o $@ -Bstatic tempo.o smpl.o rand.o cisj.o utils.o tree.o -lm

smpl.o: smpl.c smpl.h
	$(COMPILE.c)  -g smpl.c

tempo.o: tempo.c tempo.h smpl.h
	$(COMPILE.c) -g  tempo.c

rand.o: rand.c
	$(COMPILE.c) -g rand.c

tree.o: tree.c
	$(COMPILE.c) -g tree.c

cisj.o: cisj.c
	$(COMPILE.c)  -g cisj.c

utils.o: utils.c
	$(COMPILE.c) -g utils.c

clean:
	$(RM) *.o tempo relat saida
