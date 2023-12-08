##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Compile
##

DIRS	=	*

SRC =	main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	r-type_client

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) -I include $(SRC) $(CFLAGS)
	rm -f $(OBJ)

clean:
	rm -f *~

fclean:	clean
	rm -f ../../$(NAME)

re:	fclean all

debug:	CFLAGS += -g
debug:	re