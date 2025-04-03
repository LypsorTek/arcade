NAME = arcade
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fno-gnu-unique
LDFLAGS = -ldl

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
GAMES_DIR = games
GRAPHICS_DIR = graphics
BUILD_DIR = build

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

GAMES_LIBS = arcade_snake.so arcade_nibbler.so arcade_minesweeper.so
GRAPHICS_LIBS = arcade_ncurses.so arcade_sdl2.so arcade_sfml.so

GAMES_LIB_PATHS = $(addprefix $(LIB_DIR)/, $(GAMES_LIBS))
GRAPHICS_LIB_PATHS = $(addprefix $(LIB_DIR)/, $(GRAPHICS_LIBS))

all: core games graphicals

core: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

games: $(GAMES_LIB_PATHS)

$(LIB_DIR)/arcade_snake.so: $(wildcard $(GAMES_DIR)/snake/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@

$(LIB_DIR)/arcade_nibbler.so: $(wildcard $(GAMES_DIR)/nibbler/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@

$(LIB_DIR)/arcade_minesweeper.so: $(wildcard $(GAMES_DIR)/minesweeper/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@

graphicals: $(GRAPHICS_LIB_PATHS)

$(LIB_DIR)/arcade_ncurses.so: $(wildcard $(GRAPHICS_DIR)/ncurses/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@ -lncurses

$(LIB_DIR)/arcade_sdl2.so: $(wildcard $(GRAPHICS_DIR)/sdl2/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@ -lSDL2 -lSDL2_ttf

$(LIB_DIR)/arcade_sfml.so: $(wildcard $(GRAPHICS_DIR)/sfml/*.cpp)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -shared -fPIC $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/*.so

re: fclean all

.PHONY: all core games graphicals clean fclean re