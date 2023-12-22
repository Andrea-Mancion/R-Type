##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Compile
##

DIRS	=	*

SRC =	event.cpp	\
		collision.cpp	\
		createBulletFoe.cpp	\
		redirectFile.cpp	\
		showSprite.cpp	\
		nextRound.cpp	\
		shipExplode.cpp	\
		createSong.cpp	\
		ECS/registerComponent.cpp	\
		ECS/addSystem.cpp	\
		ECS/addComponent.cpp	\
		main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	r-type_client

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I include $(SRC) $(CFLAGS)
	rm -f $(OBJ)

clean:
	rm -f *~

fclean:	clean
	rm -f ../../$(NAME)

re:	fclean all

debug:	CFLAGS += -g
debug:	re