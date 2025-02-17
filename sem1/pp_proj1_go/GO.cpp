#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include"lib.h"
#include<stdlib.h>


int main() {

#ifndef __cplusplus
	Conio2_Init();
#endif
	Game_State game_state;
	Game_State* ptr_game_state = &game_state;

	FILE* ptr_file = NULL;

	int key_pressed = 0;
	int is_arrow_key = 0;
	int edit_mode = FALSE;

	char textbuffer[50] = "";
	int textbuffer_size = 50;

	settitle("Marek, Szymanski, 193229");
	_setcursortype(_NOCURSOR);

	menu_main_menu_handling(ptr_file,ptr_game_state, &edit_mode);
	//initialize_new_game_state(5, ptr_game_state);

	int cursor_x =  x_board_to_absolute((ptr_game_state->board_info.board_size / 2) + 1);
	int cursor_y =  y_board_to_absolute((ptr_game_state->board_info.board_size / 2) + 1);

	if (edit_mode == TRUE) { game_state.White_Player.score += 0.5; }

	draw_ui(ptr_game_state, cursor_x, cursor_y);

	do {
		if (edit_mode == FALSE)
		{
			if (game_state.round % 2 == 0)
			{
				game_state.Current_Player = &game_state.Black_Player;
				game_state.Other_Player = &game_state.White_Player;
			}
			else
			{
				game_state.Current_Player = &game_state.White_Player;
				game_state.Other_Player = &game_state.Black_Player;
			}
		}

		
		draw_ui(ptr_game_state, cursor_x, cursor_y);
		//update_ui(ptr_game_state, is_arrow_key, key_pressed, cursor_x, cursor_y);
		draw_board(ptr_game_state);	


		draw_cursor(cursor_x, cursor_y, game_state.Current_Player);


		is_arrow_key = 0;
		key_pressed = getch();

		if (key_pressed == 0)
		{
			is_arrow_key = 1;					
			key_pressed = getch();				
			if (key_pressed == KEY_0_UP)		
			{
				if (out_of_board(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y), key_pressed) == FALSE)
				{
					cursor_y--;
				}
			}
			else if (key_pressed == KEY_0_DOWN)
			{
				if (out_of_board(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y), key_pressed) == FALSE)
				{
					cursor_y++;
				}
			}
			else if (key_pressed == KEY_0_LEFT)
			{
				if (out_of_board(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y), key_pressed) == FALSE)
				{
					cursor_x--;
				}
			}
			else if (key_pressed == KEY_0_RIGHT)
			{
				if (out_of_board(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y), key_pressed) == FALSE)
				{
					cursor_x++;
				}
			}
		}
		else if (key_pressed == KEY_N)
			reset_game_state(ptr_game_state);
		else if (key_pressed == KEY_R)
			change_console_buffer_size(BOARD_LEFT_GAP + ptr_game_state->board_info.board_size + X_OFFSET, 2 * Y_OFFSET + ptr_game_state->board_info.board_size);
		else if (key_pressed == KEY_S)
			n_save_game_state_to_file(ptr_file, ptr_game_state);
		else if (key_pressed == KEY_L)
		{
			n_load_game_state_from_file(ptr_file, ptr_game_state);
			cursor_x = x_board_to_absolute((ptr_game_state->board_info.board_size / 2) + 1);
			cursor_y = y_board_to_absolute((ptr_game_state->board_info.board_size / 2) + 1);
			clrscr();
		}
		else if (key_pressed == KEY_F)
		{
			finish_game(ptr_game_state);
			draw_ui(ptr_game_state, cursor_x, cursor_y);
			draw_board(ptr_game_state);
			key_pressed = KEY_Q;
			gotoxy(1, 1);
		}
		else if (key_pressed == KEY_E)
		{
			if (edit_mode == TRUE)
				edit_mode = FALSE;
			else if (edit_mode == FALSE)
				edit_mode = TRUE;
		}
		else if (key_pressed == KEY_I)
		{
			if (menu_confirm("Place stone here ?", 1) == TRUE)
			{
				simple_stone_placement(ptr_game_state, cursor_x, cursor_y);

				if (edit_mode == FALSE)
				{
					game_state.round++;

					reset_markers(ptr_game_state);

					for (int i = 0; i < ptr_game_state->board_info.board_size; i++)
					{
						for (int j = 0; j < ptr_game_state->board_info.board_size; j++)
						{
							update_square(ptr_game_state, i, j);
							update_neighbouring_squares(ptr_game_state, i, j);
						}
					}

					chain_execute_chain_killing_protocl_B(ptr_game_state);
					chain_execute_chain_killing_protocl_W(ptr_game_state);
					update_square(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y));
					update_neighbouring_squares(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y));
					reset_markers(ptr_game_state);
					chain_execute_chain_killing_protocl_B(ptr_game_state);
					chain_execute_chain_killing_protocl_W(ptr_game_state);
					update_square(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y));
					update_neighbouring_squares(ptr_game_state, x_absolute_to_board(cursor_x), y_absolute_to_board(cursor_y));

				}
			}
		

		}

	} while (key_pressed != KEY_Q);


	for (int i = 0; i < ptr_game_state->board_info.board_size; i++) {
		free(ptr_game_state->board_info.board[i]);
	}
	free(ptr_game_state->board_info.board);


	_setcursortype(_SOLIDCURSOR);	
	return 0;
}


