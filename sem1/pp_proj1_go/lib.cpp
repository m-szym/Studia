#define _CRT_SECURE_NO_WARNINGS
#include "conio2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"lib.h"



#include <windows.h>
void change_console_buffer_size(int Width, int Height)
{
	_COORD xy;
	xy.X = (SHORT) Width;
	xy.Y = (SHORT) Height;
	

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      
	SetConsoleScreenBufferSize(Handle, xy);             
}

//	MENU 

void menu_draw_main_menu(void)
{
	clrscr();
	gotoxy(38, Y_OFFSET);
	cputs("MENU");
	gotoxy(30, Y_OFFSET + 2);
	cputs("n - Start new game");
	gotoxy(30, Y_OFFSET + 3);
	cputs("l - Load saved game");
	gotoxy(30, Y_OFFSET + 4);
	cputs("e - Toggle edit mode");
	//gotoxy(30, Y_OFFSET + 5);
	//cputs("q - Quit");
}

void menu_main_menu_handling(FILE* ptr_file, Game_State* ptr_blank_game_state, int *edit_mode)
{

	int key_pressed = 0;

	menu_draw_main_menu();
	//key_pressed = getch();

	while (key_pressed != KEY_Q)
	{
		gotoxy(30, Y_OFFSET + 7);
		key_pressed = getch();

		if (key_pressed == KEY_N) {
			menu_new_game_menu_handling(ptr_blank_game_state);
			break;
		}
		else if (key_pressed == KEY_L)
		{
			gotoxy(30, Y_OFFSET + 7);
			clreol();
			//cputs("Load function currently unavailable");
			initialize_new_game_state(9, ptr_blank_game_state);
			n_load_game_state_from_file(ptr_file, ptr_blank_game_state);
			break;
		}
		else if (key_pressed == KEY_E)
		{
			gotoxy(30, Y_OFFSET + 7);
			clreol();
			if (*edit_mode == FALSE)
			{
				if (menu_confirm("Activate edit mode ?", Y_OFFSET + 7) == TRUE)
					*edit_mode = TRUE;
			}
			else
			{
				if (menu_confirm("Deactivate edit mode ?", Y_OFFSET + 7) == TRUE)
					*edit_mode = FALSE;
			}
		}
		else
		{
			gotoxy(30, Y_OFFSET + 7);
			clreol();
			cputs("Unknown input");
		}
	}

	//yadi yadi yada
}

void menu_draw_new_game_menu(void)
{
	clrscr();
	gotoxy(36, Y_OFFSET);
	cputs("NEW GAME");
	gotoxy(30, Y_OFFSET + 2);
	cputs("Select size of the board:");
	gotoxy(30, Y_OFFSET + 3);
	cputs("1 - 9 x 9");
	gotoxy(30, Y_OFFSET + 4);
	cputs("2 - 13 x 13");
	gotoxy(30, Y_OFFSET + 5);
	cputs("3 - 19 x 19");
	gotoxy(30, Y_OFFSET + 6);
	cputs("4 - Custom");
	//gotoxy(30, Y_OFFSET + 7);
	//cputs("r - return to main menu");
}

void menu_new_game_menu_handling(Game_State* ptr_blank_game_state)
{
	char text[32];
	int key_pressed = 0;
	int confirmed = -1;
	int board_size = 9;

	menu_draw_new_game_menu();
	gotoxy(30, Y_OFFSET + 11);
	key_pressed = getch();
	while (key_pressed != KEY_Q)
	{
		gotoxy(30, Y_OFFSET + 11);
		key_pressed = getch();

		if (key_pressed == KEY_1)
		{
			confirmed = menu_confirm(" Confirm 9 x 9 board ?", 9);
			if (confirmed == TRUE)
			{
				board_size = 9;
				break;
			}

		}
		else if (key_pressed == KEY_2)
		{
			confirmed = menu_confirm("Confirm 13 x 13 board ?", 9);
			if (confirmed == TRUE)
			{
				board_size = 13;
				break;
			}

		}
		else if (key_pressed == KEY_3)
		{
			confirmed = menu_confirm("Confirm 19 x 19 board ?", 9);
			if (confirmed == TRUE)
			{
				board_size = 19;
				break;
			}

		}
		else if (key_pressed == KEY_4)
		{
			board_size = 0;
			gotoxy(30, Y_OFFSET + 9);
			clreol();
			cputs("Enter your custom board size: ");
			//scanf_s("%d", &board_size);
			board_size = read_int(text, 32);
			gotoxy(30, Y_OFFSET + 10);
			clreol();
			//sprintf_s(text, "%d x %d", board_size, board_size);
			//cputs(text);
			print_int(text, 32, board_size);
			cputs(" x ");
			print_int(text, 32, board_size);
			confirmed = menu_confirm("Confirm ?", 11);
			if (confirmed == TRUE)
			{
				//board_size = board_size;
				break;
			}
			gotoxy(30, Y_OFFSET + 10);
			clreol();
		}
		else if (key_pressed == KEY_R);
		//return to main menu - how ?
		else
		{
			gotoxy(30, Y_OFFSET + 9);
			clreol();
			cputs("Unknown input");
		}
	}

	if (board_size < 1)
		board_size = 9;

	initialize_new_game_state(board_size, ptr_blank_game_state);
	if (board_size > 40) {
		change_console_buffer_size(BOARD_LEFT_GAP + board_size + X_OFFSET, 2 * Y_OFFSET + board_size);
	}

}

int menu_confirm(const char* message, int line)
{
	int key_pressed = 0;
	int confirmed = 0;
	gotoxy(30, Y_OFFSET + line);
	clreol();
	cputs(message);
	gotoxy(37, Y_OFFSET + line + 1);
	cputs("ENTER | ESC");
	while (key_pressed != KEY_Q)
	{
		key_pressed = getch();
		if (key_pressed == KEY_ENTER)
		{
			confirmed = TRUE;
			break;
		}
		else if (key_pressed == KEY_ESC)
		{
			confirmed = FALSE;
			break;
		}
		else
		{
			gotoxy(30, Y_OFFSET + line + 2);
			clreol();
			cputs("Unknown input");
		}
	}
	gotoxy(30, Y_OFFSET + line);
	clreol();
	gotoxy(30, Y_OFFSET + line + 1);
	clreol();
	gotoxy(30, Y_OFFSET + line + 2);
	clreol();
	return confirmed;
}


//	NEW GAME INITIALIZATION

void initialize_new_game_state(int board_size, Game_State* ptr_blank_game_state)
{
	Game_State* ptr_new_game_state = ptr_blank_game_state;

	ptr_new_game_state->round = 0;

	ptr_new_game_state->White_Player.symbol = SYMBOL_WHITE;
	ptr_new_game_state->White_Player.score = 0;
	//ptr_new_game_state->White_Player.stones_left_to_place = 0;
	ptr_new_game_state->White_Player.stones_captured = 0;

	ptr_new_game_state->Black_Player.symbol = SYMBOL_BLACK;
	ptr_new_game_state->Black_Player.score = 0;
	//ptr_new_game_state->Black_Player.stones_left_to_place = 0;
	ptr_new_game_state->Black_Player.stones_captured = 0;

	ptr_new_game_state->Current_Player = &ptr_new_game_state->Black_Player;
	ptr_new_game_state->Other_Player = &ptr_new_game_state->White_Player;

	ptr_new_game_state->last_Black_move.player = SYMBOL_BLACK;
	ptr_new_game_state->last_Black_move.board_x = -1;
	ptr_new_game_state->last_Black_move.board_y = -1;
	ptr_new_game_state->last_White_move.player = SYMBOL_WHITE;
	ptr_new_game_state->last_White_move.board_x = -1;
	ptr_new_game_state->last_White_move.board_y = -1;

	//initialize_new_board(board_size, ptr_new_game_state);

	ptr_new_game_state->board_info.board_size = board_size;

	ptr_new_game_state->board_info.board = (Square**)malloc(board_size * sizeof(Square*));
	for (int i = 0; i < board_size; i++) {
		ptr_new_game_state->board_info.board[i] = (Square*)malloc(board_size * sizeof(Square));
	}
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{

			//Square current_square = ptr_game_state->board_info.board[i][j];

			Square current_square;

			current_square.coords.x = i;
			current_square.coords.y = j;

			current_square.marker = SQUARE_MARKER_NONE;
			current_square.color = SYMBOL_EMPTY;
			current_square.liberties = 4;
			current_square.same_color_neigbours = 0;

			ptr_new_game_state->board_info.board[i][j] = current_square;
		}
	}
}

void initialize_new_board(int new_board_size, Game_State* ptr_game_state) {
	if (new_board_size > 0)
	{
		Square** board = ptr_game_state->board_info.board;
		board = (Square**)malloc(new_board_size * sizeof(Square*));

		if (board != NULL)
		{
			for (int i = 0; i < new_board_size; i++) {
				if (board[i] != NULL)
				{
					board[i] = (Square*)malloc(new_board_size * sizeof(Square));
				}
			}

			for (int i = 0; i < new_board_size; i++) {
				for (int j = 0; j < new_board_size; j++) {

					//Square current_square = ptr_game_state->board_info.board[i][j];

					Square current_square;

					current_square.coords.x = i;
					current_square.coords.y = j;

					current_square.marker = SQUARE_MARKER_NONE;
					current_square.color = SYMBOL_EMPTY;
					current_square.liberties = 4;
					current_square.same_color_neigbours = 0;

					ptr_game_state->board_info.board[i][j] = current_square;
				}
			}
		}
	}


}


//	UI drawing

void draw_legend(Game_State* ptr_game_state, int legend_x_startpos, int legend_y_startpos, int cursor_x, int cursor_y) {
	char text[32];

	gotoxy(legend_x_startpos, legend_y_startpos);
	cputs("Student: Marek Szymanski");
	gotoxy(legend_x_startpos, legend_y_startpos + 1);
	cputs("Nr.: 193229");

	gotoxy(legend_x_startpos, legend_y_startpos + 2);
	cputs("Keys:");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 3);
	cputs("q - quit the program");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 4);
	cputs("n - start new game (current board size)");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 5);
	cputs("enter - confirm choice / end turn");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 6);
	cputs("esc - cancel current action");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 7);
	cputs("i - place a stone at the cursor's position");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 8);
	cputs("s - save game state to file");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 9);
	cputs("l - load game state from file");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 10);
	cputs("f - finish the game");

	gotoxy(legend_x_startpos, legend_y_startpos + 11);
	cputs("Implemented functionalities:");
	gotoxy(legend_x_startpos + 1, legend_y_startpos + 12);
	cputs("a b c d e f g h i j k l n");

	gotoxy(legend_x_startpos, legend_y_startpos + 13);
	cputs("-- Scoreboard ---");
	gotoxy(legend_x_startpos, legend_y_startpos + 14);
	//sprintf_s(text, "White player score: %d", ptr_game_state->White_Player.score);
	//cputs(text);
	cputs("White player score: ");
	//ptr_game_state->White_Player.score = ptr_game_state->White_Player.stones_captured;
	print_double(text, 32, ptr_game_state->White_Player.score);
	gotoxy(legend_x_startpos, legend_y_startpos + 15);
	//sprintf_s(text, "Black player score: %d", ptr_game_state->White_Player.score);
	//cputs(text);
	cputs("Black player score: ");
	//ptr_game_state->Black_Player.score = ptr_game_state->Black_Player.stones_captured;
	print_double(text, 32, ptr_game_state->Black_Player.score);

	gotoxy(legend_x_startpos, legend_y_startpos + 16);
	cputs("Cursor position: X:");
	print_int(text, 32, cursor_x);
	cputs(" Y:");
	print_int(text, 32, cursor_y);

	gotoxy(legend_x_startpos, legend_y_startpos + 17);
	cputs("Cursor position on board: X:");
	print_int(text, 32, x_absolute_to_board(cursor_x));
	cputs(" Y:");
	print_int(text, 32, y_absolute_to_board(cursor_y));
}

void draw_board(Game_State* ptr_game_state) {
	int board_x_startpos = 1 + BOARD_LEFT_GAP + BORDER_WIDTH;
	int board_y_startpos = 1 + Y_OFFSET + BORDER_WIDTH;
	int board_size = ptr_game_state->board_info.board_size;

	if (board_size > 40) {
		change_console_buffer_size(BOARD_LEFT_GAP + board_size + X_OFFSET, 2 * Y_OFFSET + board_size);
	}

	textbackground(BOARD_BG_COLOR);
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_WHITE)
				textcolor(WHITE_SYMBOL_COLOR);
			else if (ptr_game_state->board_info.board[i][j].color == SYMBOL_BLACK)
				textcolor(BLACK_SYMBOL_COLOR);
			else if (ptr_game_state->board_info.board[i][j].color == SYMBOL_EMPTY)
				textcolor(EMPTY_SYMBOL_COLOR);


			gotoxy(board_x_startpos + i, board_y_startpos + j);
			if (atari_square(ptr_game_state, i, j) == TRUE)
			{
				//textbackground(RED);
				putch(ptr_game_state->board_info.board[i][j].color);
				textbackground(BOARD_BG_COLOR);
			}
			else
				putch(ptr_game_state->board_info.board[i][j].color);
			
		}
	}
	textcolor(MAIN_TEXT_COLOR);
	textbackground(MAIN_BG_COLOR);

	int border_size = board_size + 2 * BORDER_WIDTH;
	for (int i = 0; i < border_size; i++)
	{
		for (int j = 0; j < border_size; j++)
		{
			gotoxy(board_x_startpos + i - 1, board_y_startpos + j - 1);
			if (i == 0 || i == border_size - 1 || j == 0 || j == border_size - 1)
				putch(SYMBOL_BORDER);
		}
	}
	
}

void draw_ui(Game_State* ptr_game_state, int cursor_x, int cursor_y)
{
	int board_middle_absolute = (ptr_game_state->board_info.board_size / 2) + 1;	//	probably slow, but more readable
	int board_x_middle_board = x_board_to_absolute(board_middle_absolute);
	int board_y_middle_board = y_board_to_absolute(board_middle_absolute);

	clrscr();
	if (LEGEND_POSITION == LEFT)
	{
		draw_legend(ptr_game_state, 1 + X_OFFSET, 1 + Y_OFFSET, cursor_x, cursor_y);
		//draw_testing_ui(0, 0, board_x_middle_board, board_y_middle_board, X_OFFSET, Y_OFFSET);
	}
	else if (LEGEND_POSITION == RIGHT)
	{
		int legend_x_startpos = 1 + X_OFFSET + BORDER_WIDTH + ptr_game_state->board_info.board_size + BORDER_WIDTH + X_OFFSET;
		draw_legend(ptr_game_state, legend_x_startpos, 1 + Y_OFFSET, cursor_x, cursor_y);
		//draw_testing_ui(0, 0, board_x_middle_board, board_y_middle_board, legend_x_startpos, Y_OFFSET);
	}
	draw_board(ptr_game_state);
}


//	UTILITY - coord base switching - needs changing - gotoxy counts from 1 - fixed

XY_Coords get_absolute_coords_of_cursor(void)
{
	XY_Coords absolute_coords;
	absolute_coords.x = wherex();
	absolute_coords.y = wherey();
	return absolute_coords;
}

XY_Coords get_board_coords_of_cursor(void)
{
	XY_Coords board_coords;

	board_coords.x = wherex() + BOARD_LEFT_GAP + BORDER_WIDTH;
	board_coords.y = wherey() + Y_OFFSET + BORDER_WIDTH;

	return board_coords;
}	  // makes sense only within board

int x_absolute_to_board(int absolute_x)
{
	return -1 + absolute_x - BOARD_LEFT_GAP - BORDER_WIDTH;
}

int y_absolute_to_board(int absolute_y)
{
	return -1 + absolute_y - Y_OFFSET - BORDER_WIDTH;
}

int x_board_to_absolute(int board_x)
{
	return board_x + BOARD_LEFT_GAP + BORDER_WIDTH;
}

int y_board_to_absolute(int board_y)
{
	return board_y + Y_OFFSET + BORDER_WIDTH;
}

XY_Coords xy_absolute_to_board(XY_Coords absolute_coords)
{
	XY_Coords board_coords;
	board_coords.x = absolute_coords.x + BOARD_LEFT_GAP + BORDER_WIDTH;
	board_coords.y = absolute_coords.y + Y_OFFSET + BORDER_WIDTH;
	return board_coords;
}

XY_Coords xy_board_to_absolute(XY_Coords board_coords)
{
	XY_Coords absolute_coords;
	absolute_coords.x = board_coords.x - BOARD_LEFT_GAP - BORDER_WIDTH;
	absolute_coords.y = board_coords.y - Y_OFFSET - BORDER_WIDTH;
	return absolute_coords;
}


//	maintaing cursor on board

int out_of_board(Game_State* ptr_game_state, int board_x, int board_y, int direction) {
	int board_size = ptr_game_state->board_info.board_size;

	if (direction == KEY_0_UP)
	{
		board_y--;
	}
	else if (direction == KEY_0_DOWN)
	{
		board_y++;
	}
	else if (direction == KEY_0_LEFT)
	{
		board_x--;
	}
	else if (direction == KEY_0_RIGHT)
	{
		board_x++;
	}

	if ((board_x < 0 || board_x >= board_size) || (board_y < 0 || board_y >= board_size))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//	stone placing

void simple_stone_placement(Game_State* ptr_game_state, int cursor_x, int cursor_y)
{
	int board_size = ptr_game_state->board_info.board_size;
	int cursor_x_board = x_absolute_to_board(cursor_x);
	int cursor_y_board = y_absolute_to_board(cursor_y);

	if (ptr_game_state->board_info.board[cursor_x_board][cursor_y_board].color == SYMBOL_EMPTY)
	{
		//update_square_ptr(ptr_game_state, cursor_x_board, cursor_y_board);
		if (can_stone_be_placed(ptr_game_state, cursor_x_board, cursor_y_board) == TRUE)
		{
			ptr_game_state->board_info.board[cursor_x_board][cursor_y_board].color = ptr_game_state->Current_Player->symbol;

			//update_neighbouring_squares(ptr_game_state, cursor_x_board, cursor_y_board);
			//update_square(ptr_game_state, cursor_x_board, cursor_y_board);
			update_neighbouring_squares(ptr_game_state, cursor_x_board, cursor_y_board);
		}
	}
}

int can_stone_be_placed(Game_State* ptr_game_state, int square_board_x, int square_board_y)
{
	if (
		square_has_liberties(ptr_game_state, square_board_x, square_board_y) || 
		square_would_have_same_color_neighbours(ptr_game_state, square_board_x, square_board_y) ||
		square_is_serial_killer(ptr_game_state, square_board_x, square_board_y) ||
		square_is_killer(ptr_game_state, square_board_x, square_board_y))
	{
		if (allowed_by_ko(ptr_game_state, square_board_x, square_board_y))
			return TRUE;
		else
			return FALSE;
			

	}
	else
		return FALSE;
}


//	managing single square

void update_square(Game_State* ptr_game_state, int square_to_update_board_x, int square_to_update_board_y)
{
	int board_size = ptr_game_state->board_info.board_size;

	ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties = 0;
	ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours = 0;


	int direction = 0;

	direction = KEY_0_UP;
	if (out_of_board(ptr_game_state, square_to_update_board_x, square_to_update_board_y, direction) == TRUE)
	{
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties += 0;
	}
	else
	{
		if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y - 1].color == SYMBOL_EMPTY)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties++;
		else if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y - 1].color == ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours++;
	}

	direction = KEY_0_DOWN;
	if (out_of_board(ptr_game_state, square_to_update_board_x, square_to_update_board_y, direction) == TRUE)
	{
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties += 0;
	}
	else
	{
		if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y + 1].color == SYMBOL_EMPTY)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties++;
		else if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y + 1].color == ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours++;
	}

	direction = KEY_0_LEFT;
	if (out_of_board(ptr_game_state, square_to_update_board_x, square_to_update_board_y, direction) == TRUE)
	{
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties += 0;
	}
	else
	{
		if (ptr_game_state->board_info.board[square_to_update_board_x - 1][square_to_update_board_y].color == SYMBOL_EMPTY)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties++;
		else if (ptr_game_state->board_info.board[square_to_update_board_x - 1][square_to_update_board_y].color == ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours++;
	}

	direction = KEY_0_RIGHT;
	if (out_of_board(ptr_game_state, square_to_update_board_x, square_to_update_board_y, direction) == TRUE)
	{
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties += 0;
	}
	else
	{
		if (ptr_game_state->board_info.board[square_to_update_board_x + 1][square_to_update_board_y].color == SYMBOL_EMPTY)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties++;
		else if (ptr_game_state->board_info.board[square_to_update_board_x + 1][square_to_update_board_y].color == ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color)
			ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours++;
	}

	if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color != SYMBOL_EMPTY &&
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].liberties == 0 &&
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours == 0)
	{
		if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color == SYMBOL_BLACK)
			ptr_game_state->White_Player.score++;
		else if (ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color == SYMBOL_WHITE)
			ptr_game_state->Black_Player.score++;

		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].color = SYMBOL_EMPTY;
		ptr_game_state->board_info.board[square_to_update_board_x][square_to_update_board_y].same_color_neigbours = 0;
		update_square(ptr_game_state, square_to_update_board_x, square_to_update_board_y);
	}
}

void reset_square(Game_State* ptr_game_state, int square_to_reset_board_x, int square_to_reset_board_y)
{
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].marker = SQUARE_MARKER_EVALUATED;
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].color = SYMBOL_EMPTY;
}

void mark_square_as_evaluated(Game_State* ptr_game_state, int square_to_reset_board_x, int square_to_reset_board_y)
{
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].marker = SQUARE_MARKER_EVALUATED;
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].color = SYMBOL_EMPTY;
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].liberties = 4;
	ptr_game_state->board_info.board[square_to_reset_board_x][square_to_reset_board_y].same_color_neigbours = 0;
}

void update_neighbouring_squares(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y)
{
	int direction = 0;

	direction = KEY_0_UP;
	if (out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE)
	{
		update_square(ptr_game_state, starting_square_board_x, starting_square_board_y - 1);
	}

	direction = KEY_0_DOWN;
	if (out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE)
	{
		update_square(ptr_game_state, starting_square_board_x, starting_square_board_y + 1);
	}

	direction = KEY_0_LEFT;
	if (out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE)
	{
		update_square(ptr_game_state, starting_square_board_x - 1, starting_square_board_y);
	}

	direction = KEY_0_RIGHT;
	if (out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE)
	{
		update_square(ptr_game_state, starting_square_board_x + 1, starting_square_board_y);
	}
}

int square_has_liberties(Game_State* ptr_game_state, int board_x, int board_y)
{
	if (ptr_game_state->board_info.board[board_x][board_y].liberties > 0)
		return TRUE;
	else
		return FALSE;
}

int square_has_same_color_neighbours(Game_State* ptr_game_state, int board_x, int board_y)
{
	if (ptr_game_state->board_info.board[board_x][board_y].same_color_neigbours > 0)
		return TRUE;
	else
		return FALSE;
}

int square_would_have_same_color_neighbours(Game_State* ptr_game_state, int square_board_x, int square_board_y)
{
	int same_color_neighbours = 0;
	int direction = 0;

	direction = KEY_0_UP;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y - 1].color == ptr_game_state->Current_Player->symbol)
			same_color_neighbours++;
	}

	direction = KEY_0_DOWN;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y + 1].color == ptr_game_state->Current_Player->symbol)
			same_color_neighbours++;
	}

	direction = KEY_0_LEFT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x - 1][square_board_y].color == ptr_game_state->Current_Player->symbol)
			same_color_neighbours++;
	}

	direction = KEY_0_RIGHT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x + 1][square_board_y].color == ptr_game_state->Current_Player->symbol)
			same_color_neighbours++;
	}

	if (same_color_neighbours > 0)
		return TRUE;
	else
		return FALSE;
}

int square_is_killer(Game_State* ptr_game_state, int square_board_x, int square_board_y)
{

	int direction = 0;

	direction = KEY_0_UP;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y - 1].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x][square_board_y - 1].liberties == 1 &&
			ptr_game_state->board_info.board[square_board_x][square_board_y - 1].same_color_neigbours == 0)
			return TRUE;
	}

	direction = KEY_0_DOWN;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y + 1].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x][square_board_y + 1].liberties == 1 &&
			ptr_game_state->board_info.board[square_board_x][square_board_y + 1].same_color_neigbours == 0)
			return TRUE;
	}

	direction = KEY_0_LEFT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x - 1][square_board_y].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x - 1][square_board_y].liberties == 1 &&
			ptr_game_state->board_info.board[square_board_x - 1][square_board_y].same_color_neigbours == 0)
			return TRUE;
	}

	direction = KEY_0_RIGHT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x + 1][square_board_y].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x + 1][square_board_y].liberties == 1 &&
			ptr_game_state->board_info.board[square_board_x + 1][square_board_y].same_color_neigbours == 0)
			return TRUE;
	}


	return FALSE;
}

int square_is_serial_killer(Game_State* ptr_game_state, int square_board_x, int square_board_y)
{
	int direction = 0;

	direction = KEY_0_UP;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y - 1].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x][square_board_y - 1].liberties == 0 &&
			ptr_game_state->board_info.board[square_board_x][square_board_y - 1].marker == SQUARE_MARKER_NONE &&
			ptr_game_state->board_info.board[square_board_x][square_board_y - 1].same_color_neigbours > 0)
		{
			stack_t chain_members_stack;
			init(&chain_members_stack);

			chain_evaluate_square(&chain_members_stack, ptr_game_state, square_board_x, square_board_y, ptr_game_state->Other_Player->symbol);

			if (chain_get_liberties(&chain_members_stack) > 1)
				return FALSE;
			else
				return TRUE;

		}
	}

	direction = KEY_0_DOWN;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x][square_board_y + 1].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x][square_board_y + 1].liberties == 0 &&
			ptr_game_state->board_info.board[square_board_x][square_board_y + 1].marker == SQUARE_MARKER_NONE &&
			ptr_game_state->board_info.board[square_board_x][square_board_y + 1].same_color_neigbours > 0)
		{
			stack_t chain_members_stack;
			init(&chain_members_stack);

			chain_evaluate_square(&chain_members_stack, ptr_game_state, square_board_x, square_board_y, ptr_game_state->Other_Player->symbol);

			if (chain_get_liberties(&chain_members_stack) > 1)
				return FALSE;
			else
				return TRUE;
		}
	}

	direction = KEY_0_LEFT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x - 1][square_board_y].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x - 1][square_board_y].liberties == 0 &&
			ptr_game_state->board_info.board[square_board_x - 1][square_board_y].marker == SQUARE_MARKER_NONE &&
			ptr_game_state->board_info.board[square_board_x - 1][square_board_y].same_color_neigbours > 0)
		{
			stack_t chain_members_stack;
			init(&chain_members_stack);

			chain_evaluate_square(&chain_members_stack, ptr_game_state, square_board_x, square_board_y, ptr_game_state->Other_Player->symbol);

			if (chain_get_liberties(&chain_members_stack) > 1)
				return FALSE;
			else
				return TRUE;
		}
	}

	direction = KEY_0_RIGHT;
	if (out_of_board(ptr_game_state, square_board_x, square_board_y, direction) == FALSE)
	{
		if (ptr_game_state->board_info.board[square_board_x + 1][square_board_y].color == ptr_game_state->Other_Player->symbol &&
			ptr_game_state->board_info.board[square_board_x + 1][square_board_y].liberties == 0 &&
			ptr_game_state->board_info.board[square_board_x + 1][square_board_y].marker == SQUARE_MARKER_NONE &&
			ptr_game_state->board_info.board[square_board_x + 1][square_board_y].same_color_neigbours > 0)
		{
			stack_t chain_members_stack;
			init(&chain_members_stack);

			chain_evaluate_square(&chain_members_stack, ptr_game_state, square_board_x, square_board_y, ptr_game_state->Other_Player->symbol);

			if (chain_get_liberties(&chain_members_stack) > 1)
				return FALSE;
			else
				return TRUE;
		}
	}

	return FALSE;
}

void reset_markers(Game_State* ptr_game_state)
{
	for (int i = 0; i < ptr_game_state->board_info.board_size; i++)
	{
		for (int j = 0; j < ptr_game_state->board_info.board_size; j++)
		{
			ptr_game_state->board_info.board[i][j].marker = SQUARE_MARKER_NONE;
		}
	}
}


//	managing board

void reset_game_state(Game_State* ptr_game_state_to_reset)
{
	Game_State* ptr_game_state_after_reset = ptr_game_state_to_reset;

	ptr_game_state_after_reset->round = 0;


	ptr_game_state_after_reset->White_Player.score = 0;
	//ptr_game_state_after_reset->White_Player.stones_left_to_place = 0;
	ptr_game_state_after_reset->White_Player.score = 0;


	ptr_game_state_after_reset->Black_Player.score = 0;
	//ptr_game_state_after_reset->Black_Player.stones_left_to_place = 0;
	ptr_game_state_after_reset->Black_Player.score = 0;

	ptr_game_state_after_reset->Current_Player = &ptr_game_state_after_reset->Black_Player;
	ptr_game_state_after_reset->Other_Player = &ptr_game_state_after_reset->White_Player;

	for (int i = 0; i < ptr_game_state_after_reset->board_info.board_size; i++)
	{
		for (int j = 0; j < ptr_game_state_after_reset->board_info.board_size; j++)
		{
			ptr_game_state_after_reset->board_info.board[i][j].marker = SQUARE_MARKER_NONE;
			ptr_game_state_after_reset->board_info.board[i][j].color = SYMBOL_EMPTY;
			ptr_game_state_after_reset->board_info.board[i][j].liberties = 4;
			ptr_game_state_after_reset->board_info.board[i][j].same_color_neigbours = 0;
		}
	}

	ptr_game_state_after_reset->last_Black_move.player = SYMBOL_BLACK;
	ptr_game_state_after_reset->last_Black_move.board_x = -1;
	ptr_game_state_after_reset->last_Black_move.board_y = -1;

	ptr_game_state_after_reset->last_White_move.player = SYMBOL_WHITE;
	ptr_game_state_after_reset->last_White_move.board_x = -1;
	ptr_game_state_after_reset->last_White_move.board_y = -1;
}


//	saving and loading
void n_save_game_state_to_file(FILE* ptr_file, Game_State* ptr_game_state_to_save)
{
	char savefile_name[50];

	if (LEGEND_POSITION == LEFT)
	{
		gotoxy(1 + X_OFFSET + 2, 1 + Y_OFFSET + 23);
		cputs("Enter savefile name: ");
	}
	else if (LEGEND_POSITION == RIGHT)
	{
		int legend_x_startpos = 1 + X_OFFSET + BORDER_WIDTH + ptr_game_state_to_save->board_info.board_size + BORDER_WIDTH + X_OFFSET;
		cputs("Enter savefile name: ");
	}
	//scanf_s("%49s", &savefile_name, 50);
	read_string_to_buff(savefile_name, 50);
	//strcpy(savefile_name, textbuffer);

	//char *real_savefile_name = (char*) malloc(sizeof(char) * (strlen(savefile_name) + 10 + 1));
	char real_savefile_name[70] = "";
	char real_savefile_name2[70] = "";

	strcpy(real_savefile_name, "saves/");
	strcat(real_savefile_name, savefile_name);
	strcat(real_savefile_name, ".bin\0");

	strcpy(real_savefile_name2, "saves/");
	strcat(real_savefile_name2, savefile_name);
	strcat(real_savefile_name2, "-board");
	strcat(real_savefile_name2, ".bin\0");


	int board_size = ptr_game_state_to_save->board_info.board_size;

	stripped_Game_State stripped;
	stripped.board_size = ptr_game_state_to_save->board_info.board_size;
	stripped.round = ptr_game_state_to_save->round;
	stripped.Black_Player = ptr_game_state_to_save->Black_Player;
	stripped.White_Player = ptr_game_state_to_save->White_Player;
	if (ptr_game_state_to_save->Current_Player == &ptr_game_state_to_save->Black_Player)
		stripped.current = 'B';
	else
		stripped.current = 'W';
	stripped.last_Black_move = ptr_game_state_to_save->last_Black_move;
	stripped.last_White_move = ptr_game_state_to_save->last_White_move;

	//	doesnt check if file already exists - overwrites anything
	ptr_file = fopen(real_savefile_name, "wb");
	fwrite(&stripped, sizeof(stripped_Game_State), 1, ptr_file);
	fclose(ptr_file);

	Square *flat_board = (Square*) malloc(board_size * board_size * sizeof(Square));
	/*
	for (int i = 0; i < board_size; i++) {
		ptr_new_game_state->board_info.board[i] = (Square*)malloc(board_size * sizeof(Square));
	}*/
	int k = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			flat_board[k].coords.x = i;
			flat_board[k].coords.y = j;

			flat_board[k].marker = ptr_game_state_to_save->board_info.board[i][j].marker;
			flat_board[k].color = ptr_game_state_to_save->board_info.board[i][j].color;
			flat_board[k].liberties = ptr_game_state_to_save->board_info.board[i][j].liberties;
			flat_board[k].same_color_neigbours = ptr_game_state_to_save->board_info.board[i][j].same_color_neigbours;

			k++;
		}
	}

	

	ptr_file = fopen(real_savefile_name2, "wb");
	fwrite(flat_board, sizeof(Square), board_size * board_size, ptr_file);
	fclose(ptr_file);

	free(flat_board);

}

void n_load_game_state_from_file(FILE* ptr_file, Game_State* ptr_game_state_to_change)
{
	char savefile_name[50];

	if (LEGEND_POSITION == LEFT)
	{
		gotoxy(1 + X_OFFSET + 2, 1 + Y_OFFSET + 23);
		cputs("Enter savefile name: ");
	}
	else if (LEGEND_POSITION == RIGHT)
	{
		int legend_x_startpos = 1 + X_OFFSET + BORDER_WIDTH + ptr_game_state_to_change->board_info.board_size + BORDER_WIDTH + X_OFFSET;
		cputs("Enter savefile name: ");
	}
	//scanf_s("%49s", &savefile_name, 50);
	read_string_to_buff(savefile_name, 50);
	//strcpy(savefile_name, textbuffer);
	//reset_textbuffer(textbuffer, textbuffer_size);

	//char *real_savefile_name = (char*) malloc(sizeof(char) * (strlen(savefile_name) + 10 + 1));
	char real_savefile_name[70] = "";
	char real_savefile_name2[70] = "";

	strcpy(real_savefile_name, "saves/");
	strcat(real_savefile_name, savefile_name);
	strcat(real_savefile_name, ".bin\0");

	strcpy(real_savefile_name2, "saves/");
	strcat(real_savefile_name2, savefile_name);
	strcat(real_savefile_name2, "-board");
	strcat(real_savefile_name2, ".bin\0");




	stripped_Game_State stripped;
	stripped.board_size = 0;
	stripped.round = 0;
	stripped.Black_Player = { 'B', 0, 0 };
	stripped.Black_Player = { 'W', 0, 0 };	
	stripped.current = 'O';
	//stripped.last_Black_move = 
	//stripped.last_White_move = 



	//	doesnt check if file already exists - overwrites anything
	ptr_file = fopen(real_savefile_name, "rb");
	if (ptr_file != NULL)
		fread(&stripped, sizeof(stripped_Game_State), 1, ptr_file);
	else
		return;
	fclose(ptr_file);

	int board_size = stripped.board_size;
	
	Square* flat_board = (Square*)malloc(board_size * board_size * sizeof(Square));
	
	for (int k = 0; k < board_size * board_size; k++)
	{	
		flat_board[k].coords.x = 0;
		flat_board[k].coords.y = k;

		flat_board[k].marker = SQUARE_MARKER_NONE;
		flat_board[k].color = SYMBOL_EMPTY;
		flat_board[k].liberties = 4;
		flat_board[k].same_color_neigbours = 0;
		
	}

	ptr_file = fopen(real_savefile_name2, "rb");
	fread(flat_board, sizeof(Square), board_size * board_size, ptr_file);
	fclose(ptr_file);

	//	druga czêœæ
	ptr_game_state_to_change->round = stripped.round;

	int old_board_size = ptr_game_state_to_change->board_info.board_size;
	ptr_game_state_to_change->board_info.board_size = stripped.board_size;


	for (int i = 0; i < old_board_size; i++) {
		free(ptr_game_state_to_change->board_info.board[i]);
	}
	free(ptr_game_state_to_change->board_info.board);

	ptr_game_state_to_change->board_info.board = (Square**)malloc(board_size * sizeof(Square*));
	for (int i = 0; i < board_size; i++) {
		ptr_game_state_to_change->board_info.board[i] = (Square*)malloc(board_size * sizeof(Square));
	}
	int k = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{

			//Square current_square = ptr_game_state->board_info.board[i][j];

			Square current_square;

			current_square.coords.x = i;
			current_square.coords.y = j;

			current_square.marker = flat_board[k].marker;
			current_square.color = flat_board[k].color;
			current_square.liberties = flat_board[k].liberties;
			current_square.same_color_neigbours = flat_board[k].same_color_neigbours;

			ptr_game_state_to_change->board_info.board[i][j] = current_square;
			k++;
		}
	}

	ptr_game_state_to_change->Black_Player = stripped.Black_Player;
	ptr_game_state_to_change->White_Player = stripped.White_Player;

	if (stripped.current = 'B')
	{
		ptr_game_state_to_change->Current_Player = &ptr_game_state_to_change->Black_Player;
		ptr_game_state_to_change->Other_Player = &ptr_game_state_to_change->White_Player;
	}
	else
	{
		ptr_game_state_to_change->Current_Player = &ptr_game_state_to_change->White_Player;
		ptr_game_state_to_change->Other_Player = &ptr_game_state_to_change->Black_Player;
	}

	ptr_game_state_to_change->last_Black_move = stripped.last_Black_move;
	ptr_game_state_to_change->last_White_move = stripped.last_White_move;


	free(flat_board);
	fclose(ptr_file);
	
}


//	move history - 2 back
Move make_move(Player* moving_player, int board_x, int board_y)
{
	Move new_move;
	new_move.player = moving_player->symbol;
	new_move.board_x = board_x;
	new_move.board_y = board_y;
	return new_move;
}

int are_moves_identical(Move move1, Move move2)
{
	if ((move1.board_x == move2.board_x) && (move1.board_y == move2.board_y))
		return TRUE;
	else
		return FALSE;
}

int allowed_by_ko(Game_State* ptr_game_state, int board_x, int board_y)
{
	Move move_to_check = make_move(ptr_game_state->Current_Player, board_x, board_y);

	if (ptr_game_state->Current_Player == &ptr_game_state->Black_Player)
	{
		if (are_moves_identical(move_to_check, ptr_game_state->last_Black_move) == TRUE)
			return FALSE;
		else
		{
			ptr_game_state->last_Black_move = move_to_check;
			return TRUE;
		}
	}
	else if (ptr_game_state->Current_Player == &ptr_game_state->White_Player)
	{
		if (are_moves_identical(move_to_check, ptr_game_state->last_White_move) == TRUE)
			return FALSE;
		else
		{
			ptr_game_state->last_White_move = move_to_check;
			return TRUE;
		}
	}
	else
		return FALSE;
}


//	chain killing

/*
typedef Square* stack_el_t;  // Stos przechowuje elementy typu in w polu value
// Wartoœæ, która zwróci funkcja pop() w przypadku próby usuwania elementu
// z pustego stosu:
#define STACK_ERROR NULL

// Typ struktury, opisuj¹cy listê jednokierunkow¹ liczb ca³kowitych.
// G³owa listy ma nieokreœlon¹ wartoœæ pola "value".
// Lista jest wykorzystana do implementacji stosu.
// W naszej implementacji element na szczycie stosu, to ten
// wskazywany przez pole next nale¿¹ce do "g³owy" listy.
typedef struct list {
	stack_el_t value;
	struct list* next;
} stack_t;
*/
// Inicjalizacja stosu o "g³owie" head.
void init(stack_t* head) {
	head->next = NULL;
	head->value = STACK_ERROR;
	
}

// Operacja wstawia element z wartoœci¹ value na szczyt stosu.
void push(stack_t* l, stack_el_t value) {
	stack_t* x = (stack_t*) malloc(sizeof(stack_t));

	x->value = value;
	x->next = l->next;
	l->next = x;

}

// Usuwanie elementu ze szczytu stosu.
// Funkcja zwraca wartoœæ pola value usuniêtego elementu, lub
// wartoœæ STACK_ERROR w przypadku gdy stos jest pusty i nie by³o mo¿liwe
// usuniêcie elementu. Uwaga: jest to implementacja b³êdna jeœli
// -1 jest dopuszczaln¹ wartoœci¹ dla pola value.
stack_el_t pop(stack_t* l) {
	if (l->next == NULL)
		return STACK_ERROR;   // Stos jest pusty.
	stack_el_t el = l->next->value;
	void* x = l->next;
	l->next = l->next->next;
	free(x);
	return el;
}

// Wypisuje zawartoœæ stosu "h", zaczynaj¹c od elementów na jego szczycie.
/*
void print(stack_t* h) {
	h = h->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	while (h != NULL) {
		printf("%d ", h->value);
		h = h->next;
	}
	printf("\n");
}
*/

/*
	stack_t s;

	init(&s);

	for (stack_el_t i = 1; i <= 5; i++) {
		push(&s, i);
		print(&s);
	}

	for (stack_el_t i = 1; i <= 6; i++)
		printf("Usuniêto: %d\n", pop(&s));
*/

int count_stack(stack_t* ptr_chain_members_stack)
{
	ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	int stack_real_members = 0;
	while (ptr_chain_members_stack != NULL && ptr_chain_members_stack->value != STACK_ERROR)
	{
		stack_real_members++;
		ptr_chain_members_stack = ptr_chain_members_stack->next;
	}

	return stack_real_members;
}

void chain_evaluate_square(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol) {
	//	dla dowolnego gracza, wystarczy podaæ - lista w górnej funkcji musi sprawdzaæ i odpowiednio odpalaæ t¹
	//	najproœciej - osobno liczy oddechy

	push(ptr_chain_members_stack, &ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y]);
	//dodaje ten square do stosu
	ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y].marker = SQUARE_MARKER_CHAIN_MEMBER;
	//oznacza ten square jako elemnent aktualnie przetwarzanego ³añcucha

	int direction = 0;

	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == player_symbol) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker == SQUARE_MARKER_NONE))
	{
		chain_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y - 1, player_symbol);
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == player_symbol) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker == SQUARE_MARKER_NONE))
	{
		chain_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y + 1, player_symbol);
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y ].color == player_symbol) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker == SQUARE_MARKER_NONE))
	{
		chain_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x - 1, starting_square_board_y, player_symbol);
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].color == player_symbol) &&
		(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker == SQUARE_MARKER_NONE))
	{
		chain_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x + 1, starting_square_board_y, player_symbol);
	}
}

int chain_get_liberties(stack_t* ptr_chain_members_stack)
{
	int liberties = 0;
	ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.

	while (ptr_chain_members_stack != NULL) 
	{
		liberties += ptr_chain_members_stack->value->liberties;
		ptr_chain_members_stack = ptr_chain_members_stack->next;
	}

	return liberties;
}

int is_chain_alive(stack_t* ptr_chain_members_stack)
{
	if (chain_get_liberties(ptr_chain_members_stack) > 0)
		return TRUE;
	else
		return FALSE;
}

void chain_classify_evaluated_chain(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int chain_liberties)
{
	ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	while (ptr_chain_members_stack != NULL) {
		if (chain_liberties > 0)
		{
			if (chain_liberties < 2)
				ptr_chain_members_stack->value->marker = SQUARE_MARKER_ATARI_CHAIN;
			else
				ptr_chain_members_stack->value->marker = SQUARE_MARKER_EVALUATED;
		}
		else if (chain_liberties < 1)
		{
			//reset square
			//update its neighbours
			//repeat for every member of stack / chain
			if (ptr_chain_members_stack->value->color == SYMBOL_WHITE)
				ptr_game_state->Black_Player.score += 1;
			else if (ptr_chain_members_stack->value->color == SYMBOL_BLACK)
				ptr_game_state->White_Player.score += 1;

			reset_square(ptr_game_state, ptr_chain_members_stack->value->coords.x, ptr_chain_members_stack->value->coords.y);
			update_square(ptr_game_state, ptr_chain_members_stack->value->coords.x, ptr_chain_members_stack->value->coords.y);
			update_neighbouring_squares(ptr_game_state, ptr_chain_members_stack->value->coords.x, ptr_chain_members_stack->value->coords.y);
		}	
		ptr_chain_members_stack = ptr_chain_members_stack->next;
	}
}

void destroy_stack(stack_t* ptr_chain_members_stack)
{
	//zostawia g³owê (chyba)

	//ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	while (ptr_chain_members_stack->next != NULL) {
		//random thing as actuall content of the loop is being done in while()
		pop(ptr_chain_members_stack);
	}
	//free(ptr_chain_members_stack);
	//pop(ptr_chain_members_stack);
	//pop(ptr_chain_members_stack);
}

void chain_execute_chain_killing_protocl_W(Game_State* ptr_game_state)
{
	stack_t chain_members_stack;

	init(&chain_members_stack);	// jakby ptr_chain_members_stack

	int chain_liberties = 0;

	int board_size = ptr_game_state->board_info.board_size;

		//wybieramy nie pusty i nie ruszony jeszcze square, który ma s¹siadów tego samego koloru
		// zaczynamy budowê stosu - chain_evaluate_square(...)
		//	dodajemy element
		//	sprawdzamy czy s¹siedzi spe³niaj¹ warunki
		//	 jeœli tak to powtarzamy proces na s¹siadach
		//po zakoñczeniu siê tej rekurencji
		//czyli powrocie tutaj zbudowany zosta³ stos zawieraj¹cy adresy pól nale¿¹cych do ³añcucha
		// sprawdzamy czy ³añcuch ¿yje
		//  zliczamy oddechy jego elemntów - za pomoc¹ chain_get_liberties()
		//   przechodz¹c przez wszystkie elementy sumujemy oddechy
		//  (wrapper is_chain_alive() zwraca stan koñcow
	

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_WHITE &&
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE &&
				ptr_game_state->board_info.board[i][j].same_color_neigbours > 0)
			{

				chain_evaluate_square(&chain_members_stack, ptr_game_state, i, j, SYMBOL_WHITE);
				chain_liberties = chain_get_liberties(&chain_members_stack);
				chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, chain_liberties);
				destroy_stack(&chain_members_stack);
			}

		}
	}

	
}

void chain_execute_chain_killing_protocl_B(Game_State* ptr_game_state)
{
	stack_t chain_members_stack;

	init(&chain_members_stack);	// jakby ptr_chain_members_stack

	int chain_liberties = 0;

	int board_size = ptr_game_state->board_info.board_size;

	//wybieramy nie pusty i nie ruszony jeszcze square, który ma s¹siadów tego samego koloru
	// zaczynamy budowê stosu - chain_evaluate_square(...)
	//	dodajemy element
	//	sprawdzamy czy s¹siedzi spe³niaj¹ warunki
	//	 jeœli tak to powtarzamy proces na s¹siadach
	//po zakoñczeniu siê tej rekurencji
	//czyli powrocie tutaj zbudowany zosta³ stos zawieraj¹cy adresy pól nale¿¹cych do ³añcucha
	// sprawdzamy czy ³añcuch ¿yje
	//  zliczamy oddechy jego elemntów - za pomoc¹ chain_get_liberties()
	//   przechodz¹c przez wszystkie elementy sumujemy oddechy
	//  (wrapper is_chain_alive() zwraca stan koñcow


	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_BLACK &&
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE &&
				ptr_game_state->board_info.board[i][j].same_color_neigbours > 0)
			{

				chain_evaluate_square(&chain_members_stack, ptr_game_state, i, j, SYMBOL_BLACK);
				chain_liberties = chain_get_liberties(&chain_members_stack);
				chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, chain_liberties);
				destroy_stack(&chain_members_stack);
			}

		}
	}


}


//	misc.

void read_string_to_buff(char *textbuffer, int textbuffer_size)
{
	char c = 'a';
	int i = 0;

	while (i < (textbuffer_size - 1))
	{
		c = getche();
		if ((c == KEY_ENTER) || (c == ' ') || (c == 0x09))
		{
			textbuffer[i] = '\0';
			break;
		}
		
		textbuffer[i] = c;
		i++;
	}

	textbuffer[i + 1] = '\0';
}

int read_int(char* textbuffer, int textbuffer_size)
{
	read_string_to_buff(textbuffer, textbuffer_size);
	return atoi(textbuffer);
}

void print_int(char* textbuffer, int textbuffer_size, int int_to_print)
{
	_itoa(int_to_print, textbuffer, 10);
	cputs(textbuffer);
	reset_textbuffer(textbuffer, textbuffer_size);
}

void reset_textbuffer(char* textbuffer, int textbuffer_size)
{
	for (int i = 0; i < textbuffer_size; i++)
	{
		textbuffer[i] = '\0';
	}
}


//	scoring maybe
int get_square_White_neigbours(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y)
{
	int White_neighbours = 0;

	int direction = 0;
	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == SYMBOL_WHITE))
	{
		White_neighbours++;
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == SYMBOL_WHITE))
	{
		White_neighbours++;
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y ].color == SYMBOL_WHITE))
	{
		White_neighbours++;
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y + 1].color == SYMBOL_WHITE))
	{
		White_neighbours++;
	}
	return White_neighbours;
}

int get_square_Black_neigbours(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y)
{
	int Black_neighbours = 0;

	int direction = 0;
	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == SYMBOL_BLACK))
	{
		Black_neighbours++;
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == SYMBOL_BLACK))
	{
		Black_neighbours++;
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].color == SYMBOL_BLACK))
	{
		Black_neighbours++;
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y + 1].color == SYMBOL_BLACK))
	{
		Black_neighbours++;
	}
	return Black_neighbours;
}

int territory_borders_White(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state)
{
	ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.

	while (ptr_chain_members_stack != NULL)
	{
		if (get_square_White_neigbours(ptr_game_state, ptr_chain_members_stack->value->coords.x, ptr_chain_members_stack->value->coords.y) > 0)
			return TRUE;
		ptr_chain_members_stack = ptr_chain_members_stack->next;
	}

	return FALSE;
}

int territory_borders_Black(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state)
{
	ptr_chain_members_stack = ptr_chain_members_stack->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.

	while (ptr_chain_members_stack != NULL)
	{
		if (get_square_Black_neigbours(ptr_game_state, ptr_chain_members_stack->value->coords.x, ptr_chain_members_stack->value->coords.y) > 0)
			return TRUE;
		ptr_chain_members_stack = ptr_chain_members_stack->next;
	}

	return FALSE;
}

int count_territory_B(Game_State* ptr_game_state)
{
	stack_t territory_stack;

	init(&territory_stack);	

	int territory_Black_size = 0;

	int board_size = ptr_game_state->board_info.board_size;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_EMPTY &&
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE)
			{

				territory_evaluate_square(&territory_stack, ptr_game_state, i, j);
				if (territory_borders_Black(&territory_stack, ptr_game_state) == TRUE &&
					territory_borders_White(&territory_stack, ptr_game_state) == FALSE)
				{
					territory_Black_size += count_stack(&territory_stack);
				}
				destroy_stack(&territory_stack);
			}

		}
	}

	return territory_Black_size;
}

int count_territory_W(Game_State* ptr_game_state)
{
	stack_t territory_stack;

	init(&territory_stack);

	int territory_White_size = 0;

	int board_size = ptr_game_state->board_info.board_size;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_EMPTY && 
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE)
			{

				territory_evaluate_square(&territory_stack, ptr_game_state, i, j);
				if (territory_borders_White(&territory_stack, ptr_game_state) == TRUE &&
					territory_borders_Black(&territory_stack, ptr_game_state) == FALSE)
				{
					territory_White_size += count_stack(&territory_stack);
				}
				destroy_stack(&territory_stack);
			}

		}
	}

	return territory_White_size;
}

void territory_evaluate_square(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y) {


	push(ptr_chain_members_stack, &ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y]);
	//dodaje ten square do stosu
	ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y].marker = SQUARE_MARKER_TERRITORY;
	//oznacza ten square jako elemnent aktualnie przetwarzanego ³añcucha

	int direction = 0;
	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == SYMBOL_EMPTY) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker == SQUARE_MARKER_NONE))
	{
		territory_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y - 1);
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == SYMBOL_EMPTY) &&
		(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker == SQUARE_MARKER_NONE))
	{
		territory_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y + 1);
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].color == SYMBOL_EMPTY) &&
		(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker == SQUARE_MARKER_NONE))
	{
		territory_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x - 1, starting_square_board_y);
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE) &&
		ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].color == SYMBOL_EMPTY &&
		ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker == SQUARE_MARKER_NONE)
	{
		territory_evaluate_square(ptr_chain_members_stack, ptr_game_state, starting_square_board_x + 1, starting_square_board_y);
	}
}


int is_eye(Game_State* ptr_game_state, int square_board_x, int square_board_y, char player_symbol)
{
	if (player_symbol == SYMBOL_BLACK)
	{
		if (get_square_White_neigbours(ptr_game_state, square_board_x, square_board_y) == 0)
			return TRUE;
		else
			return FALSE;
	}
	else if (player_symbol == SYMBOL_WHITE)
	{
		if (get_square_Black_neigbours(ptr_game_state, square_board_x, square_board_y) == 0)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

void chain_evaluate_square_for_eyes(stack_t* ptr_chain_members_stack, Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol, int* chain_eyes) {
	//	dla dowolnego gracza, wystarczy podaæ - lista w górnej funkcji musi sprawdzaæ i odpowiednio odpalaæ t¹
	//	najproœciej - osobno liczy oddechy

	push(ptr_chain_members_stack, &ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y]);
	//dodaje ten square do stosu
	ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y].marker = SQUARE_MARKER_CHAIN_MEMBER;
	//oznacza ten square jako elemnent aktualnie przetwarzanego ³añcucha

	int direction = 0;
	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == player_symbol) &&
			(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker == SQUARE_MARKER_NONE))
		{
			chain_evaluate_square_for_eyes(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y - 1, player_symbol, chain_eyes);
		}
		else if (ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == SYMBOL_EMPTY &&
				ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker != SQUARE_MARKER_EYE)
		{
			if (is_eye(ptr_game_state, starting_square_board_x, starting_square_board_y - 1, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker = SQUARE_MARKER_EYE;
				mark_neighbours_also_eyes(ptr_game_state, starting_square_board_x, starting_square_board_y - 1, player_symbol);
				*chain_eyes += 1;
			}
		}
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == player_symbol) &&
			(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker == SQUARE_MARKER_NONE))
		{
			chain_evaluate_square_for_eyes(ptr_chain_members_stack, ptr_game_state, starting_square_board_x, starting_square_board_y + 1, player_symbol, chain_eyes);
		}
		else if (ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == SYMBOL_EMPTY &&
			ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker != SQUARE_MARKER_EYE)
		{
			if (is_eye(ptr_game_state, starting_square_board_x, starting_square_board_y + 1, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker = SQUARE_MARKER_EYE;
				mark_neighbours_also_eyes(ptr_game_state, starting_square_board_x, starting_square_board_y + 1, player_symbol);
				*chain_eyes += 1;
			}
		}
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].color == player_symbol) &&
			(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker == SQUARE_MARKER_NONE))
		{
			chain_evaluate_square_for_eyes(ptr_chain_members_stack, ptr_game_state, starting_square_board_x - 1, starting_square_board_y, player_symbol, chain_eyes);
		}
		else if (ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].color == SYMBOL_EMPTY &&
			ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker != SQUARE_MARKER_EYE)
		{
			if (is_eye(ptr_game_state, starting_square_board_x - 1, starting_square_board_y, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker = SQUARE_MARKER_EYE;
				mark_neighbours_also_eyes(ptr_game_state, starting_square_board_x - 1, starting_square_board_y, player_symbol);
				*chain_eyes += 1;
			}
		}
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].color == player_symbol) &&
			(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker == SQUARE_MARKER_NONE))
		{
			chain_evaluate_square_for_eyes(ptr_chain_members_stack, ptr_game_state, starting_square_board_x + 1, starting_square_board_y, player_symbol, chain_eyes);
		}
		else if (ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].color == SYMBOL_EMPTY &&
			ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker != SQUARE_MARKER_EYE)
		{
			if (is_eye(ptr_game_state, starting_square_board_x + 1, starting_square_board_y, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker = SQUARE_MARKER_EYE;
				mark_neighbours_also_eyes(ptr_game_state, starting_square_board_x + 1, starting_square_board_y, player_symbol);
				*chain_eyes += 1;
			}
		}
	}
}

void mark_neighbours_also_eyes(Game_State* ptr_game_state, int starting_square_board_x, int starting_square_board_y, char player_symbol)
{
	int direction = 0;
	direction = KEY_0_UP;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].color == SYMBOL_EMPTY) &&
			(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker != SQUARE_MARKER_EYE))
		{
			if (is_eye(ptr_game_state, starting_square_board_x, starting_square_board_y - 1, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y - 1].marker = SQUARE_MARKER_EYE;
			}
		}
	}

	direction = KEY_0_DOWN;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].color == SYMBOL_EMPTY) &&
			(ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker != SQUARE_MARKER_EYE))
		{
			if (is_eye(ptr_game_state, starting_square_board_x, starting_square_board_y + 1, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x][starting_square_board_y + 1].marker = SQUARE_MARKER_EYE;
			}
		}
	}

	direction = KEY_0_LEFT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].color == SYMBOL_EMPTY) &&
			(ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker != SQUARE_MARKER_EYE))
		{
			if (is_eye(ptr_game_state, starting_square_board_x - 1, starting_square_board_y, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x - 1][starting_square_board_y].marker = SQUARE_MARKER_EYE;
			}
		}
	}

	direction = KEY_0_RIGHT;
	if ((out_of_board(ptr_game_state, starting_square_board_x, starting_square_board_y, direction) == FALSE))
	{
		if ((ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].color == SYMBOL_EMPTY) &&
			(ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker != SQUARE_MARKER_EYE))
		{
			if (is_eye(ptr_game_state, starting_square_board_x + 1, starting_square_board_y, player_symbol) == TRUE)
			{
				ptr_game_state->board_info.board[starting_square_board_x + 1][starting_square_board_y].marker = SQUARE_MARKER_EYE;
			}
		}
	}
}

void chain_execute_chain_killing_protocl_W_with_eyes(Game_State* ptr_game_state)
{
	stack_t chain_members_stack;

	init(&chain_members_stack);	

	int chain_eyes = 0;

	int board_size = ptr_game_state->board_info.board_size;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_WHITE &&
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE &&
				ptr_game_state->board_info.board[i][j].same_color_neigbours > 0)
			{

				chain_evaluate_square_for_eyes(&chain_members_stack, ptr_game_state, i, j, SYMBOL_WHITE, &chain_eyes);
				if (chain_eyes >= 2)
					chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, 2);	//zostawia ³añcuch
				else if (chain_eyes < 2)
					chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, 0);	//zabija ³añcuch
				chain_eyes = 0;
				destroy_stack(&chain_members_stack);
			}

		}
	}


}

void chain_execute_chain_killing_protocl_B_with_eyes(Game_State* ptr_game_state)
{
	stack_t chain_members_stack;

	init(&chain_members_stack);	// jakby ptr_chain_members_stack

	int chain_eyes = 0;

	int board_size = ptr_game_state->board_info.board_size;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color == SYMBOL_BLACK &&
				ptr_game_state->board_info.board[i][j].marker == SQUARE_MARKER_NONE &&
				ptr_game_state->board_info.board[i][j].same_color_neigbours > 0)
			{

				chain_evaluate_square_for_eyes(&chain_members_stack, ptr_game_state, i, j, SYMBOL_BLACK, &chain_eyes);
				if (chain_eyes >= 2)
					chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, 3);	//zostawia ³añcuch
				else if (chain_eyes < 2)
					chain_classify_evaluated_chain(&chain_members_stack, ptr_game_state, 0);	//zabija ³añcuch
				chain_eyes = 0;
				destroy_stack(&chain_members_stack);
			}

		}
	}


}

void kill_loners(Game_State* ptr_game_state)
{
	int board_size = ptr_game_state->board_info.board_size;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (ptr_game_state->board_info.board[i][j].color != SYMBOL_EMPTY &&
				ptr_game_state->board_info.board[i][j].same_color_neigbours == 0)
			{
				if (ptr_game_state->board_info.board[i][j].color == SYMBOL_WHITE)
					ptr_game_state->White_Player.score++;
				else if (ptr_game_state->board_info.board[i][j].color == SYMBOL_BLACK)
					ptr_game_state->Black_Player.score++;

				reset_square(ptr_game_state, i, j);
				update_square(ptr_game_state, i, j);
				update_neighbouring_squares(ptr_game_state, i, j);
			}

		}
	}
}

void finish_game(Game_State* ptr_game_state)
{
	kill_loners(ptr_game_state);

	reset_markers(ptr_game_state);
	chain_execute_chain_killing_protocl_B_with_eyes(ptr_game_state);
	reset_markers(ptr_game_state);
	chain_execute_chain_killing_protocl_W_with_eyes(ptr_game_state);

	reset_markers(ptr_game_state);
	ptr_game_state->White_Player.score += count_territory_W(ptr_game_state);
	//ptr_game_state->White_Player.score += ptr_game_state->White_Player.stones_captured;
	reset_markers(ptr_game_state);
	ptr_game_state->Black_Player.score += count_territory_B(ptr_game_state);
	//ptr_game_state->Black_Player.score += ptr_game_state->Black_Player.stones_captured;
}


// atari
int atari_square(Game_State* ptr_game_state, int square_board_x, int square_board_y)
{
	if (ptr_game_state->board_info.board[square_board_x][square_board_y].color != SYMBOL_EMPTY 
		&&
		(
			(ptr_game_state->board_info.board[square_board_x][square_board_y].liberties == 1 && 
			ptr_game_state->board_info.board[square_board_x][square_board_y].marker == SQUARE_MARKER_NONE)
			||
			(
			ptr_game_state->board_info.board[square_board_x][square_board_y].marker == SQUARE_MARKER_ATARI_CHAIN)
		))
	{
		textbackground(ATARI_COLOR);
		return TRUE;
	}
	else
		return FALSE;
}


void draw_cursor(int cursor_x, int cursor_y, Player* current_player)
{
	gotoxy(cursor_x, cursor_y);
	textbackground(CURSOR_BG_COLOR);
	if (current_player->symbol == SYMBOL_WHITE)
		textcolor(WHITE_SYMBOL_COLOR);
	else if (current_player->symbol == SYMBOL_BLACK)
		textcolor(BLACK_SYMBOL_COLOR);
	putch(current_player->symbol);
	textbackground(MAIN_BG_COLOR);
	textcolor(MAIN_TEXT_COLOR);
}

void print_double(char* textbuffer, int textbuffer_size, double double_to_print)
{
	_gcvt(double_to_print, 4, textbuffer);
	cputs(textbuffer);
	reset_textbuffer(textbuffer, textbuffer_size);
}