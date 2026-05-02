SRC = $(shell find src -name '*.c')
exec: $(SRC)
	gcc $(SRC) -o main -Wall -Wextra -Wpedantic -fsanitize=address -g -lm


