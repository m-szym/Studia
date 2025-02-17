#define _CRT_SECURE_NO_WARNINGS

// Key codes for reading player input
#define KEY_Q 0x71				// "q" key code
#define KEY_N 0x6e				// "n" key code
#define KEY_L 0x6c				// "l" key code
#define KEY_S 0x73				// "s" key code
#define KEY_I 0x69				// "i" key code
#define KEY_ENTER 0x0d			// "enter" key code
#define KEY_ESC 0x1b			// "esc" key code
#define KEY_F 0x66				// "f" key code
#define KEY_R 0x72				// "r" key code
#define KEY_Y 0x79				// "y" key code
#define KEY_E 0x65				// "e" key code

#define KEY_0_UP 0x48			// "up arrow" key code
#define KEY_0_DOWN 0x50			// "down arrow" key code
#define KEY_0_LEFT 0x4b			// "left arrow" key code
#define KEY_0_RIGHT 0x4d		// "right arrow" key code

#define KEY_0 0x30				// "0" key code
#define KEY_1 0x31				// "1" key code
#define KEY_2 0x32				// "2" key code
#define KEY_3 0x33				// "3" key code
#define KEY_4 0x34				// "4" key code
#define KEY_5 0x35				// "5" key code
#define KEY_6 0x36				// "6" key code
#define KEY_7 0x37				// "7" key code
#define KEY_8 0x38				// "8" key code
#define KEY_9 0x39				// "9" key code


#define TRUE 1		// boolean value true
#define FALSE 0		// boolean value false



// UI (board + legend) position on screen


// UI (board + legend) offsets
// (1,1) is top-left screen corner
#define X_OFFSET 5				// x (horizontal) offset
#define Y_OFFSET 5				// y (vertical) offset


#define BORDER_WIDTH 1			// width of the board's border (in characters)


// codes used to check where (relative to the board) the legend should be placed later
#define LEFT 'L'				// left side code
#define RIGHT 'R'				// right side code

#define LEGEND_WIDTH 43			// width of the legend section

// if LEGEND_LEFT is defined the legend will be on the left side of the board
#define LEGEND_LEFT -10		// random value not actually used anywhere
#ifdef LEGEND_LEFT				
#define BOARD_LEFT_GAP 53		// LEGEND WIDTH + 2 * X_OFFSET
#define LEGEND_POSITION LEFT
#endif

// if LEGEND_RIGHT is defined the legend will be on the right side of the board
//#define LEGEND_RIGHT -10		// random value not actually used anywhere
#ifdef LEGEND_RIGHT				
#define BOARD_LEFT_GAP X_OFFSET
#define LEGEND_POSITION RIGHT	
#endif



#define SYMBOL_BORDER char(177)	

#define BOARD_BG_COLOR CYAN
#define ATARI_COLOR RED
#define BLACK_SYMBOL_COLOR BLACK
#define WHITE_SYMBOL_COLOR WHITE
#define EMPTY_SYMBOL_COLOR LIGHTGRAY

#define MAIN_TEXT_COLOR LIGHTGRAY
#define MAIN_BG_COLOR BLACK
#define CURSOR_BG_COLOR RED


// struct containing (x, y) coordinates 
struct XY_Coords
{
	int x;
	int y;
};




/* 
	a square represents intersection on board where stones may be placed 
	every square is represented by Square struct
*/

// struct representing single board square
struct Square
{
	XY_Coords coords;			// struct XY_Coords containing board coordinates of this square
	char color;					// current "external state" of this square - is this square empty or occupied by white / black stone
	char marker;				// current "internal state" of this square - is this square a member of a chain, atari square etc.
	int liberties;				// number of liberties that this square has - number of empty neighbouring squares
	int same_color_neigbours;	// number of same color neighbours that this square has - number of neighbouring squares that are occupied by stones of the same color as this one
};

// possible values of Square struct's "color" attribute
#define SYMBOL_WHITE 'O'		// White player symbol - if square has this symbol as it's "color" attribute it is occupied by white stone - occupied by White player
#define SYMBOL_BLACK 'X'		// Black player symbol - if square has this symbol as it's "color" attribute it is occupied by black stone - occupied by Black player
#define SYMBOL_EMPTY char(197)		// empty board square symbol - if square has this symbol as it's "color" attribute it is empty 

// possible values of Square struct's "marker" attribute
#define SQUARE_MARKER_NONE '.'				// "none" marker - if square has this marker as it's "marker" attribute it does not have any special state
#define SQUARE_MARKER_CHAIN_MEMBER ':'		// "chain member" marker - if square has this marker as it's "marker" attribute it is a member of currently proccesed chain of squares
#define SQUARE_MARKER_EVALUATED ','			// "evaluated" marker - if square has this marker as it's "marker" attribute it has been already evaluated and won't be evaluated again in this round 
											/* most often square will get the "evaluated" marker after it has been identified as a member of a chain of squares and the chain has
											 been evaluated - "evaluated" square will cannot be again inclueded as part of another chain this round */
#define SQUARE_MARKER_TERRITORY ';'			// "territory" marker - if square has this marker as it's "marker" attribute it has been identified as potential territory of one of the players
#define SQUARE_MARKER_ATARI_CHAIN '!'		// "atari chain" marker - if square has this marker as it's "marker" attribute it is a member of chain of squares that has only one shared liberty
#define SQUARE_MARKER_EYE '*'				// "none" marker - if square has this marker as it's "marker" attribute it has been identified as eye of a chain of squares



// Board_Info struct containing information related to game board
struct Board_Info
{
	int board_size;		// size of game board
	Square** board;		// game board
};


// Player struct containing information about player - their symbol, score etc.
struct Player
{
	char symbol;				// symbol representing color of this player stones
	double score;					// player's score - equals: number of enemy stones captured by player + size territory controlled by player
	//int stones_left_to_place;
	int stones_captured;		// number of enemy stones captured by player
};


// Move struct representing a move made by a player - move is placing a legal stone on board
struct Move
{
	char player;		// symbol representing color of this player stones
	int board_x;		// x coordinate of board square where the player placed their stone
	int board_y;		// y coordinate of board square where the player placed their stone
};


/*
	global state of the game is represented by Game_State struct
	game state is defined as the sum of: 
		- Board_Info struct containing current board state and it's size
		- game round
		- two Player structs containing information about both players
		- two pointers to Player stucts indicating which player is currently taking their turn
		- two Move structs storing last moves made by each player ensuring thath the Ko rule is kept
*/

// struct representing global state of the game
struct Game_State
{
	Board_Info board_info;		// Board_Info struct containing current board state and it's size

	int round;					// game round as int number

	Player White_Player;		// Player struct containing information about White player
	Player Black_Player;		// Player struct containing information about Black player

	Player* Current_Player;		// pointer to one of the Player structs in this Game_State struct pointing to the Player struct of the player that is currently taking their turn
	Player* Other_Player;		// pointer to one of the Player structs in this Game_State struct pointing to the Player struct of the player that is currently not taking their turn

	Move last_Black_move;		// Move struct storing last move made by Black player
	Move last_White_move;		// Move struct storing last move made by White player
};

// simplified struct representing global state of the game
// used for loading and saving game files
struct stripped_Game_State {
	int board_size;				// size of game board as int number

	int round;					// game round as int number

	Player White_Player;		// Player struct containing information about White player
	Player Black_Player;		// Player struct containing information about Black player

	char current;				// char player symbol - represents current player

	Move last_Black_move;		// Move struct storing last move made by Black player
	Move last_White_move;		// Move struct storing last move made by White player
};





// --- Functions ---

void change_console_buffer_size(int Width, int Height);
// changes the size of console buffer, allowing it to be resized


	// Menu functions

void menu_draw_main_menu(void);
// draws main menu on startup

void menu_main_menu_handling(FILE* ptr_file, Game_State* ptr_blank_game_state, int* edit_mode);
// handles control in main menu

void menu_draw_new_game_menu(void);
// draws new game menu

void menu_new_game_menu_handling(Game_State* ptr_blank_game_state);
// handles control in new game menu

int menu_confirm(const char* message, int line);
// submenu for confirming actions
// "line" is the number of vertical line wherethe submenu should appear


	// New game state initialization

void initialize_new_game_state(int board_size, Game_State* ptr_blank_game_state);
// fills up provided pointer to Game_State struct 
// board is created dynamically (malloc) according to the board size given

void initialize_new_board(int new_board_size, Game_State* ptr_game_state);
// defunct

void reset_game_state(Game_State* ptr_game_state_to_reset);
// resets the game state - score, board etc.
// DOES NOT change the board size


	//	UI (board + legend) drawing

void draw_legend(Game_State* ptr_game_state, int legend_x_startpos, int legend_y_startpos, int cursor_x, int cursor_y);
// draws legend starting at (legend_x_startpos, legend_y_startpos)

void draw_board(Game_State* ptr_game_state);
// draws game board

int atari_square(Game_State* ptr_game_state, int square_board_x, int square_board_y);
// changes the background color of the next drawn square if it is an atari square - alive square with only 1 liberty

void draw_ui(Game_State* ptr_game_state, int cursor_x, int cursor_y);

void draw_cursor(int cursor_x, int cursor_y, Player* current_player);
// 


	// Other functions
	//	Coordinate switching

XY_Coords get_absolute_coords_of_cursor(void);
// returns XY_Coords struct of current pointer position in window

XY_Coords get_board_coords_of_cursor(void);
// returns XY_Coords struct of current pointer postion in relation to board's coordinate system

int x_absolute_to_board(int absolute_x);
// returns x coordinate converted to board's coordinate system

int y_absolute_to_board(int absolute_y);
// returns y coordinate converted to board's coordinate system

int x_board_to_absolute(int board_x);
// returns x coordinate converted to window's coordinate system

int y_board_to_absolute(int board_y);
// returns y coordinate converted to window's coordinate system

XY_Coords xy_absolute_to_board(XY_Coords absolute_coords);
// returns XY_Coords struct converted to board's coordinate system

XY_Coords xy_board_to_absolute(XY_Coords board_coords);
// returns XY_Coords struct converted to window's coordinate system

	//	Reading and writing - using only functions from template

void read_string_to_buff(char* textbuffer, int textbuffer_size);
// reads up to "textbuffer_size"-1 chars from standard input to "textbuffer" array of chars and appends a '\0' at the end
// stops reading at ENTER, SPACE or TAB

int read_int(char* textbuffer, int textbuffer_size);
// reads and returns int number
// reads '\0\ ended string to "textbuffer", converts it to int with atoi() and returns

void print_int(char* textbuffer, int textbuffer_size, int int_to_print);
// prints given int number
// puts the int number converted to string with _itoa() into "textbuffer", prints the string and clears "textbuffer"

void print_double(char* textbuffer, int textbuffer_size, double double_to_print);

void reset_textbuffer(char* textbuffer, int textbuffer_size);
// clears "textbuffer", filling it with '\0' 


	// Simple stone placement

void simple_stone_placement(Game_State* ptr_game_state, int cursor_x, int cursor_y);
// on empty squares
// if allowed (can_stone_be_placed returned TRUE) places the stone on the board square board[cursor_x, cursor_y

int can_stone_be_placed(Game_State* ptr_game_state, int board_x, int board_y);
// checks a number of conditions to determine if stone can be placed at board[cursor_x, cursor_y
// returns TRUE if stone can be placed or FALSE if not
/* Condtitions checked:
	- would square placed here any liberties
	- would square placed here any same color neighbours - i.e. would be part of chain of stones
	- would square placed kill any nearby enemy stones
	- would square placed kill any nearby chain of enemy stones
	- is the move allowed by Ko rule - i.e. different than last move made by current player
*/

	// Managing single square

void update_square(Game_State* ptr_game_state, int square_to_update_board_x, int square_to_update_board_y);
// updates this (board[square_to_update_board_x, square_to_update_board_y]) square 
// based on current neighbours updates liberites and same_color_neighbours

void update_neighbouring_squares(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y);
// updates neighbours of this (board[square_to_update_board_x, square_to_update_board_y]) square 
// runs update_square() on each neighbour

void reset_square(Game_State* ptr_game_state, int square_to_reset_board_x, int square_to_reset_board_y);
// resets this (board[square_to_update_board_x, square_to_update_board_y]) square 
// the square becomes empty

int square_has_liberties(Game_State* ptr_game_state, int board_x, int board_y);
// checks if this square has any liberties
// returns TRUE if it has or FALSE if it does not

int square_has_same_color_neighbours(Game_State* ptr_game_state, int board_x, int board_y);
// checks if this square has any same color neighbours
// returns TRUE if it has or FALSE if it does not

int square_would_have_same_color_neighbours(Game_State* ptr_game_state, int square_board_x, int square_board_y);
// checks if as stone placed by the current player on this square would have any same color neighbours
// returns TRUE if it would or FALSE if it would not

int square_is_killer(Game_State* ptr_game_state, int square_board_x, int square_board_y);
// checks if as stone placed by the current player on this square would kill any neibourghing enemy stones
// returns TRUE if it would or FALSE if it would not

int square_is_serial_killer(Game_State* ptr_game_state, int square_board_x, int square_board_y);
// checks if as stone placed by the current player on this square would kill any neibourghing chains of enemy stones
// returns TRUE if it would or FALSE if it would not

int get_square_White_neigbours(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y);
// returns the number of white squares (squares occupied by white stones) this (board[starting_square_board_x, starting_square_board_y]) square neighbours

int get_square_Black_neigbours(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y);
// returns the number of black squares (squares occupied by white stones) this (board[starting_square_board_x, starting_square_board_y]) square neighbours

	// Managing entire board

void reset_markers(Game_State* ptr_game_state);
// resets markers of every square on board
// markers are set to SQUARE_MARKER_NONE

	//	Movement

int out_of_board(Game_State* ptr_game_state, int cursor_x, int cursor_y, int direction);
// direction is one of the key codes of arrow keys, indicating the direction relative to this (board[square_to_update_board_x, square_to_update_board_y]) square
// checks if moving cursor in the direction provided would make it leave board space
// returns TRUE if it would or FALSE if it would not


	//	Saving and loading game state

void n_save_game_state_to_file(FILE* ptr_file, Game_State* ptr_game_state_to_save);
// takes a filename and save the game state to such file 
// 2 files are created in /saves directory, one with most of Game_State data and the second with board data
/*
	first prompts the user for filename
	constructs 2 savefile names: /saves/"filename".bin and /saves/"filename"-board.bin to be used to save the actual files
	than creates a Stripped_Game_State struct and array of Square* - both will be used to temorarily store data before saving
	copies data from current Game_State to the Stripped_Game_State and saves in binary write mode to /saves/"filename".bin
	copies data from current Game_State.board to the array of Square* and saves in binary write mode to /saves/"filename"-board.bin
*/

void n_load_game_state_from_file(FILE* ptr_file, Game_State* ptr_game_state_to_change);
// takes a filename and loads the game state from given file 
// 2 files are loaded from /saves directory, one with most of Game_State data and the second with board data
/*
	first prompts the user for filename
	constructs 2 savefile names: /saves/"filename".bin and /saves/"filename"-board.bin to be used to save the actual files
	than creates a Stripped_Game_State struct and array of Square* - both will be used to temorarily store data before saving
	binary reads data from /saves/"filename".bin to the Stripped_Game_State 
	binary reads data from /saves/"filename"-board.bin to the array of Square*
	copies data from Stripped_Game_State to current Game_State 
	copies data from the array of Square* to current Game_State.board 

	the files are split in order to make it possible to read amount of data (board state) that is unknown until some of the data (board size) has already been read
	the data is split and thus amount of data (board state) to read is known from 1st file before 2nd (with the data) is read
*/

	//	Ko rule - preserving move history

Move make_move(Player* moving_player, int board_x, int board_y);
// creates and returns a Move struct from the given data 

int are_moves_identical(Move move1, Move move2);
// compares by value 2 given Move structs
// returns TRUE if they (all their values) are identical or FALSE if they are not

int allowed_by_ko(Game_State* ptr_game_state, int board_x, int board_y);
// checks if the move atttempted would be allowed by Ko rule - it is a different move than the last move by this player
// returns TRUE if ko rule would allow this move or FALSE if it would not


	// Basic stack strutures, functions and constants

#define STACK_ERROR nullptr

typedef Square* stack_el_t;

// struct representing one member of chain of stones stack
typedef struct list {
	stack_el_t value;
	struct list* next;
} stack_t;

void init(stack_t* head);
// initializes an empty "head" of of chain stack with the type of stack_t with the value of NULL

stack_el_t pop(stack_t* l);
// removes the stack_t element from the top of the chain stack

void push(stack_t* l, stack_el_t value);
// adds new stack_t element with value of "value" on top of the chain stack

int count_stack(stack_t* ptr_chain_members_stack);
// returns number of real elements in stack (skips the empty "head" of the stack)

void destroy_stack(stack_t* ptr_chain_members_stack);
// one by one removes elements from stack and frees memory alloacated to them
// does not remove the "head" of the stack - as the head is a standard local variable it is cleared when the parent function returns


	// Chains of stones

/*
	chains of stones are dynamically created stacks of pointers to board squares that share color and neighbour each other
	as per rules chains share their liberties
*/

void chain_execute_chain_killing_protocl_W(Game_State* ptr_game_state);
// main function for finding and managing chains of white stones
/*
	looks through entire board for white squares that are part of a chain (are alive and have neighbours of the same color)
	recursively constructs chain of squares as stack
	checks if chain is alive or not
	removes dead chains and marks alive ones, so that they will not be evaluated again this round
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated alive chains of white stones on board
*/

void chain_execute_chain_killing_protocl_B(Game_State* ptr_game_state);
// main function for finding and managing chains of black stones
/*
	looks through entire board for white squares that are part of a chain (are alive and have neighbours of the same color)
	recursively constructs chain of squares as stack
	checks if chain is alive or not
	removes dead chains and marks alive ones, so that they will not be evaluated again this round
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated alive chains of black stones on board
*/

void chain_evaluate_square(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol);
// recursive function that adds this square to currently evaluated chain and then, if conditions are met, calls itself on some of neighoruing squares

int chain_get_liberties(stack_t* ptr_chain_members_stack);
// returns the sum of liberties of chain stack from given pointer

int is_chain_alive(stack_t* ptr_chain_members_stack);
// returns TRUE if chain stack has at least 1 liberty or FALSE if it has 0 liberties 

void chain_classify_evaluated_chain(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int is_chain_alive);
// checks the number of shared liberties the chain stack has and kills the chain or marks it as evaluated (also marks atari chains - these with only 1 liberty)


	// Territory 
/*
	territory is represented by dynamically created stacks of pointers to empty board squares
	territory belongs to player if it borders only their stones - i.e. no stone in black territory borders a white stone
*/

int territory_borders_White(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state);
// returns TRUE if any square in "ptr_chain_members_stack" stack borders a white square or FALSE if none does

int territory_borders_Black(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state);
// returns TRUE if any square in "ptr_chain_members_stack" stack borders a black square or FALSE if none does

int count_territory_B(Game_State* ptr_game_state);
// main function for finding and managing chains of black stones
/*
	looks through entire board for empty squares and recursively constructs territory stack from them
	if none of the squares in the stack borders a white square the territory is counted and added to black player's score
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated empty squares on board
*/

int count_territory_W(Game_State* ptr_game_state);
// main function for finding and managing chains of white stones
/*
	looks through entire board for empty squares and recursively constructs territory stack from them
	if none of the squares in the stack borders a black square the territory is counted and added to white player's score
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated empty squares on board
*/

void territory_evaluate_square(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y);
// recursive function that adds this square to currently evaluated territory stack and then, if conditions are met, calls itself on some of neighoruing squares

		// Chains of stones when the game is finished
int is_eye(Game_State* ptr_game_state, int square_board_x, int square_board_y, char player_symbol);
// returns TRUE if the square is an eye for the player indicated by "player_symbol" or FALSE if it is not
// an eye is defined here as follows: a square that only borders empty squares or squares occupied by the given player

void mark_neighbours_also_eyes(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol);
// checks if any of the neighbours of this (board[starting_square_board_x, starting_square_board_y]) square is an eye square
// marks eyes that were found with SQUARE_MARKER_EYE

void chain_evaluate_square_for_eyes(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol, int* chain_eyes);
// extended recursive function that adds this square to currently evaluated chain and then, if conditions are met, calls itself on some of neighoruing squares
// also searches for eyes while building the chain and updates the numbers of eyes found to "chain_eyes"

void chain_execute_chain_killing_protocl_W_with_eyes(Game_State* ptr_game_state);
// main extended function for finding and managing chains of white stones
/*
	looks through entire board for white squares that are part of a chain (are alive and have neighbours of the same color)
	recursively constructs chain of squares as stack and counts found eyes
	checks if chain can be killed (has only 1 eye) or not (has =< 2 eyes)
	removes dead chains and marks alive ones, so that they will not be evaluated again this round
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated alive chains of white stones on board
*/

void chain_execute_chain_killing_protocl_B_with_eyes(Game_State* ptr_game_state);
// main extended function for finding and managing chains of black stones
/*
	looks through entire board for white squares that are part of a chain (are alive and have neighbours of the same color)
	recursively constructs chain of squares as stack and counts found eyes
	checks if chain can be killed (has only 1 eye) or not (has =< 2 eyes)
	removes dead chains and marks alive ones, so that they will not be evaluated again this round
	deconstructs the stack and frees allocated memory
	repeats until there are no more unevaluated alive chains of black stones on board
*/

void kill_loners(Game_State* ptr_game_state);
// kills any squares occupied by a stone that do not have any neighbours of the same color

void finish_game(Game_State* ptr_game_state);
// finishes the game, killing any squares / chains that could be killed and counts territory captured by players