/* 
* Obstruction Main function
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-01-15 03:47:12
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-02-17 01:20:27
*/
#include <stdio.h>
#include <string.h>
#include "obstruction.h"

int main (void)
{
    int i;
    int j;
    int turn= 1;
    int cursorX = 0;
    int cursorY = 0;
    int cpuPlayer;
    int maxX;
    int maxY;
    char input = 'a';
    char playerOneName[21];
    char playerTwoName[21];
    Board board;
    Score scoreboard[10];


    /*ncurses initialization */
    initscr();
    cbreak ();
    noecho ();
    start_color();
    curs_set(0);

    getmaxyx( stdscr, maxX, maxY);

    if (maxX < 38 || maxY < 80)
    {
        mvwprintw(stdscr, 0, 0, "Invalid window size. Please, resize your window to a bigger size.\n");
        mvwprintw(stdscr, 1, 0, "Press any key to close the program.\n");
        getch();
        endwin();
        return 0;
    }

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = blank;
        }
    }

    loadScoreboard(scoreboard);

    drawBoard(board);
    drawHelper();

    do
    {
        showHelpMessage("Player one name?");
        drawUsernameOnePrompt(playerOneName);
    } while (!strcmp(playerOneName, ""));
    
    do
    {
        showHelpMessage("Player two name? (\"CPU\" for AI)");
        drawUsernameTwoPrompt(playerTwoName);

        if (!strcmp(playerOneName, playerTwoName))
        {
            showHelpWarning("Players names can't be equals.");
        }
    } while (!strcmp(playerTwoName, "") || !strcmp(playerOneName, playerTwoName));
    clearHelpWarning();

    drawScoreboard(scoreboard);
    drawCursor(board, cursorX, cursorY);
    cpuPlayer = !strcmp(playerTwoName, "CPU");

    do
    {
        if (turn == 1)
        {
            showHelpMessage("Player One's turn");
        }
        else
        {
            showHelpMessage("Player Two's turn");
        }

        if (cpuPlayer && (turn == 2))
        {
            cpuMovement(board);
            turn = 1;
            input = 'z';
        }
        else
        {
            input = getch();
        }

        switch (input)
        {
        case 'q':
        case 'Q':
            turn = 3;
            break;

        case 'i':
        case 'I':
            cursorX--;
            break;

        case 'k':
        case 'K':
            cursorX++;
            break;

        case 'j':
        case 'J':
            cursorY--;
            break;

        case 'l':
        case 'L':
            cursorY++;
            break;
        case ' ':
            if (turn == 1)
            {
                if (markPlayerOne(board, cursorX, cursorY))
                {
                    clearHelpWarning();
                    turn = 2;
                }
                else
                {
                    showHelpWarning("Invalid move, try again.");
                }
            }
            else if (turn==2)
            {
                if (markPlayerTwo(board, cursorX, cursorY))
                {
                    clearHelpWarning();
                    turn = 1;
                }
                else
                {
                    showHelpWarning("Invalid move, try again.");
                }
            }
            break;
        }

        validateCursorCoordinate(&cursorX, &cursorY);
        drawBoard(board);
        drawCursor(board, cursorX, cursorY);

    } while (input != 'q' && input != 'Q' && hasPossibleMove(board));

    if (turn == 1)
    {
        showHelpMessage("Player Two won the game!");
        insertScore(scoreboard, playerTwoName);
    }
    else if (turn == 2)
    {
        showHelpMessage("Player One won the game!");
        insertScore(scoreboard, playerOneName);
    }
    else
    {
        showHelpMessage("Game ended!");
    }

    drawScoreboard(scoreboard);
    saveScoreboard(scoreboard);
    showHelpWarning("Press any key to close");

    getch();

    endwin();

    return 0;
}
