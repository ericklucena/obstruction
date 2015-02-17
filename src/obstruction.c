/* 
* Obstruction Functions implementation
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-01-12 22:55:29
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-02-17 01:20:14
* This file contains the implementation of the functions used in the Obstruction game
*/

#include "obstruction.h"

void markBoard (Board board, int x, int y, Square square)
{
    int i;
    int j;

    if (board[x][y] == blank)
    {
        board[x][y] = square;

        for (i=-1;i<=1;i++)
        {
            for (j=-1; j<=1; j++)
            {
                if ( (((x+i) >= 0) && ((x+i)<BOARD_SIZE)) && (((y+j) >= 0) && ((y+j)<BOARD_SIZE)) && (i != 0 || j != 0) )
                {
                    board[x+i][y+j] = blocked;
                }
            }
        }
    }
}

int markPlayerOne (Board board, int x, int y)
{
    if (board[x][y] == blank)
    {
        markBoard(board, x, y, playerOne);
        return TRUE;
    }

    return FALSE;
}

int markPlayerTwo (Board board, int x, int y)
{
    if (board[x][y] == blank)
    {
        markBoard(board, x, y, playerTwo);
        return TRUE;
    }

    return FALSE;
}

void cpuMovement (Board board)
{

    int x;
    int y;

    srand(time(NULL));

    do
    {
        x = rand()%BOARD_SIZE;
        y = rand()%BOARD_SIZE;
    } while (!isBlankSquare(board, x, y));

    markPlayerTwo(board, x, y);
}

int hasPossibleMove (Board board)
{
    int i;
    int j;

    for (i=0; i<BOARD_SIZE; i++)
    {
        for (j=0; j<BOARD_SIZE; j++)
        {
            if (board[i][j] == blank)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int isBlankSquare (Board board, int x, int y)
{
    if (board[x][y] == blank)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void validateCursorCoordinate (int* x, int* y)
{
    if (*x<0)
    {
        *x = 0;
    }
    else if (*x >=BOARD_SIZE)
    {
        *x  = BOARD_SIZE-1;
    }

    if (*y<0)
    {
        *y = 0;
    }
    else if (*y >=BOARD_SIZE)
    {
        *y  = BOARD_SIZE-1;
    }
}

void initScoreboard (Scoreboard scoreboard)
{
    int i;

    for (i=0; i<SCOREBOARD_SIZE; i++)
    {
        strcpy(scoreboard[i].name, "----------");
        scoreboard[i].score = 0;
    }
}

void insertScore(Scoreboard scoreboard, char* name)
{
    int i;
    Score swap;

    for (i=0; i<SCOREBOARD_SIZE; i++)
    {
        if (!strcmp(scoreboard[i].name, name))
        {
            strcpy(swap.name, name);
            swap.score = scoreboard[i].score;
            swap.score++;
            break;
        }
    }

    if (i>=SCOREBOARD_SIZE)
    {
        strcpy(swap.name, name);
        swap.score = 1;
        i--;
    }

    for (;i>0;i--)
    {
        strcpy(scoreboard[i].name, scoreboard[i-1].name);
        scoreboard[i].score = scoreboard[i-1].score;
    }

    strcpy(scoreboard[0].name, swap.name);
    scoreboard[0].score = swap.score;
}

void loadScoreboard (Scoreboard scoreboard)
{
    int i;
    FILE* scoreFile;

    scoreFile = fopen(SCOREBOARD_FILE, "r");
    initScoreboard(scoreboard);

    if (scoreFile != NULL)
    {
        for (i=0; i<SCOREBOARD_SIZE; i++)
        {
            fscanf(scoreFile, "%20[^\n]", scoreboard[i].name);
            fscanf(scoreFile, "%d\n", &scoreboard[i].score);
        }
        
        fclose(scoreFile);
    }

}

void saveScoreboard (Scoreboard scoreboard)
{
    int i;
    FILE* scoreFile;

    scoreFile = fopen(SCOREBOARD_FILE, "w");    

    if (scoreFile != NULL)
    {
        for (i=0; i<SCOREBOARD_SIZE; i++)
        {
            fprintf(scoreFile, "%s\n", scoreboard[i].name);
            fprintf(scoreFile, "%d\n", scoreboard[i].score);
        }

        fclose(scoreFile);
    }
    
}

void drawBoard (Board board)
{

    int i;
    int j;
    int size;

    size = BOARD_SIZE*SQUARE_SIZE+1;

    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(5));

    // Draws the inner grid
    for (i=1;i<(size-1);i++)
    {
        for (j=0;j<size;j++)
        {
            if ((i%SQUARE_SIZE) == 0)
            {
                if ((j%SQUARE_SIZE) == 0)
                {
                    if (j == 0)
                    {
                        mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ACS_LTEE);
                    }
                    else if (j == (size-1))
                    {
                        mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ACS_RTEE);
                    }
                    else
                    {
                        mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ACS_PLUS);
                    }
                }
                else
                {
                    mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ACS_HLINE);    
                }
            }
            else
            {
                if ((j%SQUARE_SIZE) == 0)
                {
                    mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ACS_VLINE);
                }
                else
                {
                    attroff(COLOR_PAIR(5));
                    mvaddch(i+BOARD_X_OFFSET,j+BOARD_Y_OFFSET, ' ');
                    attron(COLOR_PAIR(5));

                }
            }
        }
    }

    //Draws the top line
    for (j=0; j<size; j++)
    {
        if ((j%SQUARE_SIZE) == 0)
        {
            mvaddch(BOARD_X_OFFSET, j+BOARD_Y_OFFSET, ACS_TTEE);
        }
        else
        {
            mvaddch(BOARD_X_OFFSET, j+BOARD_Y_OFFSET, ACS_HLINE);
        }
    }

    //Draws the bottom line
    for (j=0; j<size; j++)
    {
        if ((j%SQUARE_SIZE) == 0)
        {
            mvaddch(BOARD_X_OFFSET+size-1, j+BOARD_Y_OFFSET, ACS_BTEE);
        }
        else
        {
            mvaddch(BOARD_X_OFFSET+size-1, j+BOARD_Y_OFFSET, ACS_HLINE);
        }
    }

    //Draws board corners
    mvaddch(BOARD_X_OFFSET, BOARD_Y_OFFSET, ACS_ULCORNER);
    mvaddch(BOARD_X_OFFSET, BOARD_Y_OFFSET+size-1, ACS_URCORNER);
    mvaddch(BOARD_X_OFFSET+size-1, BOARD_Y_OFFSET, ACS_LLCORNER);
    mvaddch(BOARD_X_OFFSET+size-1, BOARD_Y_OFFSET+size-1, ACS_LRCORNER);

    attroff(COLOR_PAIR(5));

    //Draws board elements
    for (i=0; i<BOARD_SIZE; i++)
    {
        for (j=0; j<BOARD_SIZE; j++)
        {
            switch (board[i][j])
            {
            case playerOne:
                drawPlayerOneMark(i, j);
                break;

            case playerTwo:
                drawPlayerTwoMark(i, j);
                break;

            case blocked:
                drawBlockedMark(i, j);
                break;
            default:
                break;
            }
        }
    }

    refresh();
}

void drawCursor (Board board, int x, int y)
{
    int i;

    if (isBlankSquare(board, x, y))
    {
        init_pair(3, COLOR_GREEN, COLOR_GREEN); 
        attron(COLOR_PAIR(3)); 
    }
    else
    {
        init_pair(3, COLOR_YELLOW, COLOR_YELLOW); 
        attron(COLOR_PAIR(3)); 
    }

    for (i=0; i < SQUARE_SIZE-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+1, BOARD_Y_OFFSET+y*SQUARE_SIZE+i+1, ACS_CKBOARD);
    }

    for (i=1; i < SQUARE_SIZE-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+1+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+1, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+1+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+SQUARE_SIZE-1, ACS_CKBOARD);
    }

    for (i=0; i < SQUARE_SIZE-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+SQUARE_SIZE-1, BOARD_Y_OFFSET+y*SQUARE_SIZE+i+1, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(3));

    refresh();
}

void drawPlayerOneMark (int x, int y)
{
    int i;
    int symbolSize = SQUARE_SIZE-2;

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    attron(COLOR_PAIR(1));

    for (i=0; i < symbolSize-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+2+i, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+SQUARE_SIZE-2-i, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(1)); 

    refresh(); 
}

void drawPlayerTwoMark (int x, int y)
{
    int i;
    int symbolSize = SQUARE_SIZE-2;

    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    attron(COLOR_PAIR(2));

    for (i=0; i < symbolSize-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2, BOARD_Y_OFFSET+y*SQUARE_SIZE+i+2, ACS_CKBOARD);
    }

    for (i=1; i < symbolSize-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+2, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+SQUARE_SIZE-2, ACS_CKBOARD);
    }

    for (i=0; i < symbolSize-1; i++)
    {
        mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+SQUARE_SIZE-2, BOARD_Y_OFFSET+y*SQUARE_SIZE+i+2, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(2));

    refresh(); 
}

void drawBlockedMark (int x, int y)
{
    int i;
    int j;
    int symbolSize = SQUARE_SIZE-2;

    for (i=0; i < symbolSize-1; i++)
    {
        for (j=0; j < symbolSize-1; j++)
        {
            mvaddch(BOARD_X_OFFSET+x*SQUARE_SIZE+2+i, BOARD_Y_OFFSET+y*SQUARE_SIZE+2+j, ACS_DIAMOND);
        }
        
    }

    refresh(); 
}

void drawUsernameOnePrompt (char* playerOneName)
{
    int i;

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    attron(COLOR_PAIR(1));

    //Draws the prompt box
    for (i=0; i < PROMPT_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+PLAYER_ONE_X, BOARD_Y_OFFSET+PLAYER_ONE_Y+i, ACS_CKBOARD);
    }

    for (i=1; i < PROMPT_HEIGHT; i++)
    {
        mvaddch(BOARD_X_OFFSET+PLAYER_ONE_X+i, BOARD_Y_OFFSET+PLAYER_ONE_Y, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+PLAYER_ONE_X+i, BOARD_Y_OFFSET+PLAYER_ONE_Y+PROMPT_WIDTH-1, ACS_CKBOARD);
    }    

    for (i=0; i < PROMPT_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+PROMPT_HEIGHT+PLAYER_ONE_X, BOARD_Y_OFFSET+PLAYER_ONE_Y+i, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(1));

    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_ONE_X, BOARD_Y_OFFSET+PLAYER_ONE_Y+1, " PLAYER ONE ");
    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_ONE_X+2, BOARD_Y_OFFSET+PLAYER_ONE_Y+2, "                    ");
    move(BOARD_X_OFFSET+PLAYER_ONE_X+2, BOARD_Y_OFFSET+PLAYER_ONE_Y+2);
    
    curs_set(1);
    echo ();
    getnstr(playerOneName, 20);
    noecho ();

    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_ONE_X+2, BOARD_Y_OFFSET+PLAYER_ONE_Y+2, playerOneName);
    curs_set(0);

    refresh(); 
}

void drawUsernameTwoPrompt (char* playerTwoName)
{
    int i;

    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    attron(COLOR_PAIR(2));

    //Draws the prompt box
    for (i=0; i < PROMPT_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+PLAYER_TWO_X, BOARD_Y_OFFSET+PLAYER_TWO_Y+i, ACS_CKBOARD);
    }

    for (i=1; i < PROMPT_HEIGHT; i++)
    {
        mvaddch(BOARD_X_OFFSET+PLAYER_TWO_X+i, BOARD_Y_OFFSET+PLAYER_TWO_Y, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+PLAYER_TWO_X+i, BOARD_Y_OFFSET+PLAYER_TWO_Y+PROMPT_WIDTH-1, ACS_CKBOARD);
    }    

    for (i=0; i < PROMPT_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+PROMPT_HEIGHT+PLAYER_TWO_X, BOARD_Y_OFFSET+PLAYER_TWO_Y+i, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(2));

    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_TWO_X, BOARD_Y_OFFSET+PLAYER_TWO_Y+1, " PLAYER TWO ");
    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_TWO_X+2, BOARD_Y_OFFSET+PLAYER_TWO_Y+2, "                    ");
    move(BOARD_X_OFFSET+PLAYER_TWO_X+2, BOARD_Y_OFFSET+PLAYER_TWO_Y+2);
    curs_set(1);

    echo ();
    getnstr(playerTwoName, 20);
    noecho ();

    mvwprintw(stdscr, BOARD_X_OFFSET+PLAYER_TWO_X+2, BOARD_Y_OFFSET+PLAYER_TWO_Y+2, playerTwoName);
    curs_set(0);

    refresh(); 
}

void drawScoreboard (Scoreboard scoreboard)
{
    int i;
    char text[25];

    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    attron(COLOR_PAIR(4));

    //Draws the scoreboard box
    for (i=0; i < SCOREBOARD_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+SCOREBOARD_X, BOARD_Y_OFFSET+SCOREBOARD_Y+i, ACS_CKBOARD);
    }

    for (i=1; i < SCOREBOARD_HEIGHT; i++)
    {
        mvaddch(BOARD_X_OFFSET+SCOREBOARD_X+i, BOARD_Y_OFFSET+SCOREBOARD_Y, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+SCOREBOARD_X+i, BOARD_Y_OFFSET+SCOREBOARD_Y+SCOREBOARD_WIDTH-1, ACS_CKBOARD);
    }    

    for (i=0; i < SCOREBOARD_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+SCOREBOARD_HEIGHT+SCOREBOARD_X, BOARD_Y_OFFSET+SCOREBOARD_Y+i, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(4));

    for (i=0; i < SCOREBOARD_SIZE; i++)
    {
        sprintf(text, "%20s %4d", scoreboard[i].name, scoreboard[i].score);
        mvwprintw(stdscr, BOARD_X_OFFSET+SCOREBOARD_X+3+i, BOARD_Y_OFFSET+SCOREBOARD_Y+2, text);    
    }

    mvwprintw(stdscr, BOARD_X_OFFSET+SCOREBOARD_X, BOARD_Y_OFFSET+SCOREBOARD_Y+1, " SCOREBOARD ");

    refresh(); 
}

void drawHelper ()
{
    int i;

    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    attron(COLOR_PAIR(4));

    //Draws the helper box
    for (i=0; i < HELP_BOX_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+HELP_BOX_X, BOARD_Y_OFFSET+HELP_BOX_Y+i, ACS_CKBOARD);
    }

    for (i=1; i < HELP_BOX_HEIGHT; i++)
    {
        mvaddch(BOARD_X_OFFSET+HELP_BOX_X+i, BOARD_Y_OFFSET+HELP_BOX_Y, ACS_CKBOARD);
        mvaddch(BOARD_X_OFFSET+HELP_BOX_X+i, BOARD_Y_OFFSET+HELP_BOX_Y+HELP_BOX_WIDTH-1, ACS_CKBOARD);
    }    

    for (i=0; i < HELP_BOX_WIDTH; i++)
    {
        mvaddch(BOARD_X_OFFSET+HELP_BOX_HEIGHT+HELP_BOX_X, BOARD_Y_OFFSET+HELP_BOX_Y+i, ACS_CKBOARD);
    }

    attroff(COLOR_PAIR(4));

    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_BOX_X, BOARD_Y_OFFSET+HELP_BOX_Y+1, " HELPER ");
    
    refresh(); 
}

void showHelpMessage (char* message)
{
    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_MESSAGE_X, BOARD_Y_OFFSET+HELP_MESSAGE_Y, "                                 ");
    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_MESSAGE_X, BOARD_Y_OFFSET+HELP_MESSAGE_Y, message);
    refresh();
}

void showHelpWarning (char* message)
{
    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_WARNING_X, BOARD_Y_OFFSET+HELP_WARNING_Y, "                                 ");
    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_WARNING_X, BOARD_Y_OFFSET+HELP_WARNING_Y, message);
    refresh();
}

void clearHelpWarning (char* message)
{
    mvwprintw(stdscr, BOARD_X_OFFSET+HELP_WARNING_X, BOARD_Y_OFFSET+HELP_WARNING_Y, "                                 ");
    refresh();
}
