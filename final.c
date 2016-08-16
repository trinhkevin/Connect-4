// final.c
// Final Project - Connect 4
//
// Kevin Trinh

// Libaries
#include "gfx4.h"
#include <unistd.h>
#include <math.h>

// Prototypes
void drawboard();
void drawdisc(int board[11][10]);
int insertdisc(int board[11][10], int sliderPos, int turn);
void drawpossible(int board[11][10], int sliderPos);
void sidepanel(int turn);
void newgame(int board[11][10], int* turn);
int checkwin(int board[11][10]);
void displaywin(int win);

// Definitions
#define EMPTY 0
#define RED 1
#define YELLOW 2
#define TIMECONST pow(10, 6) // Converts Microseconds to Seconds

int main() {
	// Initialize Variables
	int board[11][10] = {[0 ... 10][0 ... 9] = EMPTY}; // Board Array
	char input; // Input
	int sliderPos = 5; // Initial Slider Pos
	int turn = RED; // Initial Turn
	int success; // Placement Success
	int win; // Checks Board for Win

	// Create Window
	gfx_open(1100, 800, "Connect Four");

	while(1) {
		// Draw Board
		drawboard();

		// Draw Disc
		drawdisc(board);

		// Draw Possible
		drawpossible(board, sliderPos);

		// Draw Side Panel
		sidepanel(turn);

		// Check Win
		win = checkwin(board);

		// Display Win (if there is one)
		displaywin(win);

		// Wait for User Input
		if(gfx_event_waiting()) {
			input = gfx_waiet();
			if(input == 'S') { // Right
				sliderPos++;
				if(sliderPos > 8) {
					sliderPos = 8;
				}
			}
			else if(input == 'Q') { // Left
				sliderPos--;
				if(sliderPos < 2) {
					sliderPos = 2;
				}
			}
			else if(input == ' ') { // Enter
				success = insertdisc(board, sliderPos, turn);
				if(success == 1) {
					if(turn == RED) {
						turn = YELLOW;
					}
					else if(turn == YELLOW) {
						turn = RED;
					}
				}
			}
			else if(input == 'n') { // New Game
				newgame(board, &turn);
			}
			else if(input == 'q') { // Quit
				return 0;
			}

		}

		// Sleep
		usleep(0.02 * TIMECONST);

		// Clear
		gfx_clear();
	}

}

void drawboard() {
	// Draw Board
	gfx_color(37, 31, 192);
	gfx_fill_rectangle(50, 100, 700, 600);
}

void drawdisc(int board[11][10]) {
	// Initialize Variables
	int i, j; // Counters

	for(i = 50; i < 700; i = i + 100) {
		for(j = 50; j < 600; j = j + 100) {
			if(board[((i-50)/100) + 2][((j-50)/100) + 2] == 0) { // Empty
				gfx_color(0, 0, 0);
				gfx_fill_circle(50 + i, 100 + j, 40);
			}
			if(board[((i-50)/100) + 2][((j-50)/100) + 2] == RED) { // Red
				gfx_color(255, 0, 0);
				gfx_fill_circle(50 + i, 100 + j, 40);
			}
			if(board[((i-50)/100) + 2][((j-50)/100) + 2] == YELLOW) { // Yellow
				gfx_color(255, 255, 0);
				gfx_fill_circle(50 + i, 100 + j, 40);
			}
		}
	}

	return;
}

int insertdisc(int board[11][10], int sliderPos, int turn) {
	// Initialize Variables
	int i;

	// Place Disc
	for(i = 7; i > 1; i--) {
		if(board[sliderPos][i] == EMPTY) {
			// Draw Disc
			board[sliderPos][i] = turn;

			// Success
			return 1;
		}
	}

	// Failure
	return 0;
}

void drawpossible(int board[11][10], int sliderPos) {
	// Initialize Variables
	int i;

	// Place Disc
	for(i = 7; i > 1; i--) {
		if(board[sliderPos][i] == EMPTY) {
			// Draw Ring
			gfx_color(255, 255, 255);
			gfx_circle(100 + (sliderPos - 2) * 100, 150 + (i - 2) * 100, 40);

			return;
		}
	}
}

void sidepanel(int turn) {
	// Side Panel
	gfx_color(76, 0, 153);
	gfx_fill_rectangle(800, 0, 300, 800);

	// Instructions
	gfx_changefont("9x15bold");
	gfx_color(255, 255, 255);
	gfx_text(880, 420, "Controls:");
	gfx_text(880, 440, "<- = LEFT");
	gfx_text(880, 460, "-> = RIGHT");
	gfx_text(880, 480, "SPACE = ENTER");
	gfx_text(880, 500, "'n' = NEW GAME");
	gfx_text(880, 520, "'q' = QUIT");

	// Current Turn
	gfx_color(255, 255, 255);
	gfx_text(890, 50, "Current Turn:");
	if(turn == RED) {
		gfx_color(255, 0, 0);
	}
	if(turn == YELLOW) {
		gfx_color(255, 255, 0);
	}
	gfx_fill_circle(950, 200, 100);

	// Title
	gfx_color(255, 255, 255);
	gfx_changefont("lucidasans-24");
	gfx_text(870, 700, "CONNECT 4");
}

void newgame(int board[11][10], int *turn) {
	// Initialize Variables
	int i, j; // Counters

	// Make Board Empty
	for(i = 2; i < 9; i ++) {
		for(j = 2; j < 9; j++) {
			board[i][j] = EMPTY;
		}
	}

	// Set Initial Turn to Red
	*turn = RED;
}

int checkwin(int board[11][10]) {
	// Initialize Variables
	int i, j; // Counters

	for(i = 2; i < 9; i++) {
		for(j = 2; j < 8; j++) {
			// Check Red
			if(board[i][j] == RED) {
				// Vertical
				if(board[i][j-1] == RED &&
					board[i][j-2] == RED &&
					board[i][j+1] == RED) {
					return RED;
				}
				if(board[i][j-1] == RED &&
					board[i][j+1] == RED &&
					board[i][j+2] == RED) {
					return RED;
				}
				// Horizontal
				if(board[i+1][j] == RED &&
					board[i+2][j] == RED &&
					board[i-1][j] == RED) {
					return RED;
				}
				if(board[i-1][j] == RED &&
					board[i-2][j] == RED &&
					board[i+1][j] == RED) {
					return RED;
				}
				// Diagonal (/)
				if(board[i+1][j-1] == RED &&
					board[i-1][j+1] == RED &&
					board[i-2][j+2] == RED) {
					return RED;
				}
				if(board[i+1][j-1] == RED &&
					board[i+2][j-2] == RED &&
					board[i-1][j+1] == RED) {
					return RED;
				}
				// Diagonal (\)
				if(board[i+1][j+1] == RED &&
					board[i-1][j-1] == RED &&
					board[i-2][j-2] == RED) {
					return RED;
				}
				if(board[i+1][j+1] == RED &&
					board[i+2][j+2] == RED &&
					board[i-1][j-1] == RED) {
					return RED;
				}
  			}

  			// Check Yellow
  			if(board[i][j] == YELLOW) {
				// Vertical
				if(board[i][j-1] == YELLOW &&
					board[i][j-2] == YELLOW &&
					board[i][j+1] == YELLOW) {
					return YELLOW;
				}
				if(board[i][j-1] == YELLOW &&
					board[i][j+1] == YELLOW &&
					board[i][j+2] == YELLOW) {
					return YELLOW;
				}
				// Horizontal
				if(board[i+1][j] == YELLOW &&
					board[i+2][j] == YELLOW &&
					board[i-1][j] == YELLOW) {
					return YELLOW;
				}
				if(board[i-1][j] == YELLOW &&
					board[i-2][j] == YELLOW &&
					board[i+1][j] == YELLOW) {
					return YELLOW;
				}
				// Diagonal (/)
				if(board[i+1][j-1] == YELLOW &&
					board[i-1][j+1] == YELLOW &&
					board[i-2][j+2] == YELLOW) {
					return YELLOW;
				}
				if(board[i+1][j-1] == YELLOW &&
					board[i+2][j-2] == YELLOW &&
					board[i-1][j+1] == YELLOW) {
					return YELLOW;
				}
				// Diagonal (\)
				if(board[i+1][j+1] == YELLOW &&
					board[i-1][j-1] == YELLOW &&
					board[i-2][j-2] == YELLOW) {
					return YELLOW;
				}
				if(board[i+1][j+1] == YELLOW &&
					board[i+2][j+2] == YELLOW &&
					board[i-1][j-1] == YELLOW) {
					return YELLOW;
				}
			}
		}
	}

	// Failure (No Win)
	return 0;
}

void displaywin(int win) {
	// Red
	if(win == RED) {
		gfx_color(255, 0, 0);
		gfx_fill_rectangle(300, 350, 200, 100);
		gfx_color(255, 255, 255);
		gfx_changefont("lucidasans-24");
		gfx_text(345, 400, "Red Wins");
		gfx_changefont("lucidasans-12");
		gfx_text(330, 420, "Press 'n' for new game");
	}
	// Yellow
	else if(win == YELLOW) {
		gfx_color(255, 255, 0);
		gfx_fill_rectangle(300, 350, 200, 100);
		gfx_color(0, 0, 0);
		gfx_changefont("lucidasans-24");
		gfx_text(330, 400, "Yellow Wins");
		gfx_changefont("lucidasans-12");
		gfx_text(330, 420, "Press 'n' for new game");
	}
}
