/* 
* Obstruction Functions headers
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-01-12 22:39:39
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-02-17 01:20:41
* This file contains the prototypes and documentation of the functions used on the Obstruction game
*/

#ifndef INCLUDE_OBSTRUCTION_H_
#define INCLUDE_OBSTRUCTION_H_ 1

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definition of some constants for faster redesign

#define SQUARE_SIZE 6
#define BOARD_SIZE 6
#define SCOREBOARD_SIZE 10
#define SCOREBOARD_FILE "resources/.scoreboard"

#define PROMPT_HEIGHT 4
#define PROMPT_WIDTH 36

#define SCOREBOARD_HEIGHT 16
#define SCOREBOARD_WIDTH 36

#define BOARD_X_OFFSET 1
#define BOARD_Y_OFFSET 1

#define HELP_BOX_HEIGHT 6
#define HELP_BOX_WIDTH 36

#define HELP_MESSAGE_X 2
#define HELP_MESSAGE_Y 40

#define HELP_WARNING_X 4
#define HELP_WARNING_Y 40

#define HELP_BOX_X 0
#define HELP_BOX_Y 38

#define PLAYER_ONE_X 8
#define PLAYER_ONE_Y 38

#define PLAYER_TWO_X 14
#define PLAYER_TWO_Y 38

#define SCOREBOARD_X 20
#define SCOREBOARD_Y 38


typedef enum square {
	blank,
	playerOne,
	playerTwo,
	blocked
} Square;

typedef struct Score {
	char name[21];
	int score;
}Score;

typedef Score Scoreboard[SCOREBOARD_SIZE];

typedef Square Board[BOARD_SIZE][BOARD_SIZE];

/**
 MarkBoard: Assign the value of $square to the $board based on the $x and $y coordinates
 Pre: Pass the board, coordinates and value you want to be assigned
 Post: The board will be marked with the value on the coordinate provided if the move is possible
 */
void markBoard (Board board, int x, int y, Square square);

/**
 MarkPlayerOne: Assign the player one mark to the $board on the $x and $y coordinates
 Pre: Pass the board and coordinates
 Post: The board will be marked with the player one mark, if the move is possible
 */
int markPlayerOne (Board board, int x, int y);

/**
 MarkPlayerTwo: Assign the player two mark to the $board on the $x and $y coordinates
 Pre: Pass the board and coordinates.
 Post: The board will be marked with the player two mark, if the move is possible
 */
int markPlayerTwo (Board board, int x, int y);

/**
 CpuMovement: Makes a random (but valid) movement on the $board
 Pre: Pass the board to be marked.
 Post: The board is marked with a player two's movement
 */
void cpuMovement(Board board);

/**
 HasPossibleMove: Checks if there is any empty (blank) square on the $board
 Pre: Pass the board to be checked
 Post: Returns TRUE if there is an empty space on the board, FALSE otherwise
 */
int hasPossibleMove (Board board);

/**
 IsBlankSquare: Checks if the $board is empty (blank) on the given $x and $y coordinates
 Pre: Pass the board and coordinates to be checked
 Post: Returns TRUE if the square is empty, FALSE otherwise
 */
int isBlankSquare (Board board, int x, int y);

/**
 ValidateCursorCoordinate: Checks if the coordinates referenced by the  $x and $y pointers are valid
 Pre: Pass the coordinates
 Post: Modify the coordinates in case of any of them are invalid (off the board)
 */
void validateCursorCoordinate (int* x, int* y);

/**
 InitScoreboard: Create the start values for a given $scoreboard
 Pre: Pass the scoreboard
 Post: The scoreboard will contain a serie of dashes for the names and value 0 (zero) for the scores
 */
void initScoreboard (Scoreboard scoreboard);

/**
 InsertScore: Insert the win of the player by its $name on the $scoreboard
 Pre: Pass the scoreboard and the winner player's name
 Post: If the player is already on the scoreboard, the number of victories will be incremented. Otherwise, the player will receive an entry, and the oldest entry will be discarded
 */
void insertScore (Scoreboard scoreboard, char* name);

/**
 LoadScoreboard: Load the scoreboard from the file on disk (if it exists) on the $scoreboard
 Pre: Pass the scoreboard
 Post: If the scoreboard file exists, its values will be put on the scoreboard variable, otherwise, scoreboard will have the start values
 */
void loadScoreboard (Scoreboard scoreboard);

/**
 SaveScoreboard: Writes the $scoreboard on the disk
 Pre: Pass the scoreboard to be saved
 Post: The scoreboard is saved on the disk.
 */
void saveScoreboard (Scoreboard scoreboard);

/**
 DrawBoard: Draws the $board on the screen.
 Pre: Pass the board to be drawn
 Post: The board is drawn on the screen
 */
void drawBoard (Board board);

/**
 DrawCursor: Draws the cursor based on the $board content on the given $x and $y coordinates
 Pre: Pass the board and the coordinates
 Post: The cursor is drawn with a green color if it is located on a empty square. Otherwise, it is drawn with a yellow color
 */
void drawCursor (Board board, int x, int y);

/**
 DrawPlayerOneMark: Draws the player one's mark at the given $x and $y coordinates
 Pre: Pass the coordinates
 Post: The mark is drawn on the given coordinates
 */
void drawPlayerOneMark (int x, int y);

/**
 DrawPlayerTwoMark: Draws the player two's mark at the given $x and $y coordinates
 Pre: Pass the coordinates
 Post: The mark is drawn on the given coordinates 
 */
void drawPlayerTwoMark (int x, int y);

/**
 DrawBlockedMark: Draws the blocked's mark at the given $x and $y coordinates
 Pre: Pass the coordinates
 Post: The mark is drawn ont he given coordinates
 */
void drawBlockedMark (int x, int y);

/**
 DrawUsernameOnePrompt: Draws a input box for the $playerOneName and waits for user input
 Pre: Pass the string variable to receive the user input
 Post: The variable will contain the user input
 */
void drawUsernameOnePrompt (char* playerOneName);

/**
 DrawUsernameTwoPrompt: Draws a input box for the $playerTwoName and waits for user input
 Pre: Pass the string variable to receive the user input
 Post: The variable will contain the user input 
 */
void drawUsernameTwoPrompt (char* playerTwoName);

/**
 DrawHelper: Draws a helper box on the screen
 Pre: Not applicable
 Post: The helper box is drawn on the screen
 */
void drawHelper ();

/**
 ShowHelpMessage: Writes the given $message on the helper box (First line)
 Pre: Pass the message to be written
 Post: The message is written on the screen
 */
void showHelpMessage (char* message);

/**
 ShowHelpWarning: Writes the given $message on the helper box (Second line)
 Pre: Pass the message to be written
 Post: The message is written on the screen
 */
void showHelpWarning (char* message);

/**
 ClearHelpWarning: Clean the message written at the second line of the helper box (if any)
 Pre: Not applicable
 Post: The second line of the helper box its clean
 */
void clearHelpWarning ();

/**
 DrawScoreboard: Draws the $scoreboard values on the screen 
 Pre: Pass the scoreboard to be drawn
 Post: The scoreboard is drawn on the screen
 */
void drawScoreboard (Scoreboard scoreboard);

#endif  // INCLUDE_OBSTRUCTION_H_
