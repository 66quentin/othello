CFLAGS=-Wall -g

testu: test_unitaire.o main.o conversion.o general.o jouer.o test_case_jouable.o
	gcc -o testu test_unitaire.o main.o conversion.o general.o jouer.o test_case_jouable.o

%.o: %.c
	gcc -o $@ $< $(CFLAGS) -c

.PHONY: clean
clean:
	rm -f *.o 
