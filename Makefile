##
## EPITECH PROJECT, 2023
## Rtype
## File description:
## Root Makefile
##

# Variables

SERVER_NAME = r-type_server

CLIENT_NAME = r-type_client


# Rules

$(SERVER_NAME):
	@make -C src/Server

$(CLIENT_NAME):
	@make -C src/Client


all: $(CLIENT_NAME) $(SERVER_NAME)
	mv src/Server/$(SERVER_NAME) .
	mv src/Client/$(CLIENT_NAME) .

clean:
	@make clean -C src/Server
	@make clean -C src/Client

fclean: clean
	@make fclean -C src/Server
	@make fclean -C src/Client

re: fclean all

debug:
	@make debug -C src/Server
	@make debug -C src/Client

.PHONY: all clean fclean re