link: compile
	gcc -o test_shell ssd.o test_shell.o

compile: 
	gcc -c ssd.c
	gcc -c test_shell.c

clean:
	rm *.o test_shell