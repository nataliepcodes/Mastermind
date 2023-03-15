my_mastermind:
	gcc -Wall -Wextra -Werror -o my_mastermind my_mastermind.c

my_mastermind.o: my_mastermind.c
	gcc -Wall -Wextra -Werror -c my_mastermind.c

clean:
	rm my_mastermind

fclean: clean
	rm my_mastermind

re: fclean my_mastermind