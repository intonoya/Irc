NAME		= ircserv

SRCS		= $(wildcard *.cpp)

OBJS		= $(SRCS:.cpp=.o)

CC			= c++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -I.

RM			= rm -f

all:		$(NAME)

.cpp.o:
			@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			@echo "\x1b[32m$(NAME) is compiled!\x1b[32m"

clean:
			@$(RM) $(OBJS)

fclean: clean
			@$(RM) $(NAME)

re: fclean all

server: all
			./$(NAME) 6667 asd
client: 
		nc localhost 6667

.PHONY:		all clean fclean re run server client