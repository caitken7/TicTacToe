//Tic-Tac-Toe using pointers

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Set Constants:
const char EMPTY = ' ';
const char x = 'X';
const char o = 'O';
const char TIE = 'T';
const char NONE = 'N';

//Create Funtions:
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 1);
void displayBoard(const vector<char>* const board);
char winner(const vector<char>* const board);
bool isLegal(int move, const vector<char>* const board);
int humanMove(const vector<char>* const board, char human);
int computerMove(vector<char> board, char comp);
void announceWinner(char winner, char human, char comp);
char playAgain(string question);
void playGame();

int main()
{
	//Create empty game board:
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions(); //Display instructions

	char computer = x; //Computer gets x
	char human = o; //Human gets o

	char ans = askYesNo("Do you want to go first?"); //Ask player if they want to go first
	if (ans == 'y') //If yes
	{
		human = x; //human gets x
		computer = o; //computer gets o
	}
	char turn = x; //turn gets x
	displayBoard(&board); //Display board

	while (winner(&board) == NONE) //While nobody has won and it isn't a tie
	{
		if (turn == human) //If it's human's turn
		{
			move = humanMove(&board, human); //Get human move
			board[move] = human; //Set human piece to position on board
		}

		else //else
		{
			move = computerMove(board, computer); //Get computer move
			board[move] = computer; //Set computer piece to position on board
		}

		displayBoard(&board); //Display board

		if (turn == human) //If it's human's turn
		{
			turn = computer; //It's now computer's turn
		}
		else //Else
		{ 
			turn = human; //It's now human's turn
		}
	}

	announceWinner(winner(&board), human, computer); //Decide winner and display
	ans = playAgain("Do you want to play again? (y/n): "); //Ask player if they want to play again
	if (ans == 'y') //if yes
	{
		cout << endl;
		playGame(); //play again
	}
	else
	{
		cout << "Thanks for playing!";
		return 0; //Game over
	}
}

void playGame() //Play game
{
	main(); //Main function
}

char playAgain(string question) //Play again function
{
	char ans = 'n'; //answer is n
	cout << question; //ask question
	cin >> ans; //receive answer
	return ans; //return answer
}
void instructions() //Display instruction function
{
	//Text:
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "-where human brain is pit against silicon processor\n\n";

	cout << "Make your move known by entering a number, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";

	cout << "1 | 2 | 3\n";
	cout << "---------\n";
	cout << "4 | 5 | 6\n";
	cout << "---------\n";
	cout << "7 | 8 | 9\n\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question) //Ask y/n question
{
	char response; //declare response

	//ask question until valid answer is received
	do
	{
		cout << question << "(y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response; //return response
}

int askNumber(string question, int high, int low) //Ask number function
{
	int number; //declare number
	
	//Ask for a number until valid number is entered
	do
	{
		cout << question << "(" << low << "- " << high << "): ";
		cin >> number;
	} while (number > high || number < low);
	return number + 1; //return number and add 1
}

void displayBoard(const vector<char>* const board)
{
	//Display board using cout:
	cout << "\n\t" << (*board)[0] << " | " << (*board)[1] << " | " << (*board)[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*board)[3] << " | " << (*board)[4] << " | " << (*board)[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*board)[6] << " | " << (*board)[7] << " | " << (*board)[8];
	cout << "\n\n";
}

char winner(const vector<char>* const board) //Winner function
{
	// all possible winning rows
	const int WINNING_ROWS[8][3] = { { 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 },
	{ 0, 3, 6 },
	{ 1, 4, 7 },
	{ 2, 5, 8 },
	{ 0, 4, 8 },
	{ 2, 4, 6 }
	};

	const int TOTAL_ROWS = 8; //declare constant value of 'total rows' as 8

	// if any winning row has three values that are the same (and not EMPTY), then we have a winner:
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if (((*board)[WINNING_ROWS[row][0]] != EMPTY) &&
			((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
			((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]))
		{
			return (*board)[WINNING_ROWS[row][0]];
		}
	}

	// since nobody has won, check for a tie (no empty squares left)
	if (count(board->begin(), board->end(), EMPTY) == 0)
		return TIE;

	// since nobody has won and it isn't a tie, the game ain't over
	return NONE;
}

inline bool isLegal(int move, const vector<char>* const board)
{
	return ((*board)[move] == EMPTY);
}

int humanMove(const vector<char>* const board, char human)
{
	int move = askNumber("Where will you move?", (board->size()));
	while (!isLegal(move - 2, board))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", (board->size()));
	}
	cout << "Fine...\n";
	return move - 2;
}

int computerMove(vector<char> board, char computer) //Computer move function
{
	cout << "I shall take square number ";

	// if computer can win on next move, make that move
	for (unsigned int move = 0; move < board.size(); ++move)
	{
		if (isLegal(move, &board))
		{
			board[move] = computer;
			if (winner(&board) == computer)
			{
				cout << move + 1 << endl;
				return move;
			}
			// done checking this move, undo it
			board[move] = EMPTY;
		}
	}

	// if human can win on next move, block that move
	char human;
	if (computer == x)
	{
		human = o;
	}
	else { human = x; }

	for (unsigned int move = 0; move < board.size(); ++move)
	{
		if (isLegal(move, &board))
		{
			board[move] = human;
			if (winner(&board) == human)
			{
				cout << move + 1 << endl;
				return move;
			}
			// done checking this move, undo it
			board[move] = EMPTY;
		}
	}

	// the best moves to make, in order
	const int BEST_MOVES[] = { 5, 1, 3, 7, 9, 2, 4, 6, 8 };
	// since no one can win on next move, pick best open square
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		int move = BEST_MOVES[i];
		if (isLegal(move - 1, &board))
		{
			cout << move << endl;
			return move - 1;
		}
	}
	return 0;
}

void announceWinner(char winner, char human, char computer) //Announce winner function
{
	if (winner == computer) //If computer is the winner display this text:
	{
		cout << "computer" << " wins!\n";
		cout << "As I predicted, human, I am triumphant once more-proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human) //If human is the winner display this text:
	{
		cout << "human" << " wins!\n";
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else  //Else display this text:
	{
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate... for this is the best you will ever achieve.\n";
	}
}