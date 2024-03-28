build: compile
	gcc -o test_shell ssd.c test_shell.c

compile: 
	gcc -c ssd.c
	gcc -c test_shell.c

clean:
	rm *.o test_shell