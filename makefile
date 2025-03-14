default:
	gcc -Wall -o prog main.c input.c etf.c
debug:
	gcc -Wall -o prog -g main.c input.c etf.c
clean:
	rm -f prog
