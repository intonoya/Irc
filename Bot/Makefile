NAME		= ircbot

SRCS		= $(wildcard *.cpp) $(wildcard Commands/*.cpp)

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

CC			= c++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -I.

RM			= rm -f

all:		$(NAME)

$(OBJ_DIR)/%.o: %.cpp
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/Commands
			@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			@echo "\x1b[32m$(NAME) is compiled! 🤠🐱\x1b[32m"

clean:
			@rm -rf $(OBJ_DIR)
			@$(RM) $(OBJS)

fclean: clean
			@$(RM) $(NAME)

re: fclean all

.PHONY:		all clean fclean re