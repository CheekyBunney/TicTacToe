TicTacToe: TicTacToe.c ttt.c
	gcc TicTacToe.c ttt.c -o TicTacToe -Wall -ansi -pedantic -Werror
Secret:
	gcc TicTacToe.c ttt.c -o TicTacToe -Wall -ansi -pedantic -Werror -DSECRET
Editor:
	gcc TicTacToe.c ttt.c -o TicTacToe -Wall -ansi -pedantic -Werror -DEDITOR
clean:
	rm -f TicTacToe
