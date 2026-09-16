NAME		=	RPN
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

OBJS_DIR	=	objs
SRCS		=	main.cpp RPN.cpp
OBJS		=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

RM			=	rm -rf
MKDIR		=	mkdir -p

$(OBJS_DIR)/%.o: %.cpp
	$(MKDIR) $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

