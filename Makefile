SRC = $(shell find src -name '*.c')
exec: $(SRC)
	gcc $(SRC) -o exec -Wall -Wextra -Wpedantic -fsanitize=address -g -lm


