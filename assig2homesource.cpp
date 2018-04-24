//Chris' Cylindrical Mule checkers program
//https://www.itsyourturn.com/t_helptopic2030.html#helpitem1534 has a summary of mule checkers. 
//Cylindrical Checkers allows a piece to move from the right edge of the board to the left edge.
//Note: Code is functional, but has not yet been optimized, placed on hold likely indefinitely.
//started 11/16/2017
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// all test cases passed

//global constants
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72; 
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

//funtions
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
void DisplayBoard( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yindex);
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[],  int yLocArray[]);
bool IsMove1Square( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int Makemoveimproved(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard, int fromSquareNum, int toSquareNum);

int main()
{
	int numRowsInBoard = 0;
	int counterforrows = 0;
	int turn = 0;
	int entertocontinue = 0;
	int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {0};
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {0}; //really unclear in the assignment description as to what this does. It is mentioned 3 times in the beginning, and then never again
	int xIndicesMove[MAX_PIECES] = {0};
	int yIndicesMove[MAX_PIECES] = {0};
	int xIndicesJump[MAX_PIECES] = {0};
	int yIndicesJump[MAX_PIECES] = {0};
	int player = 0;
	int selectedsquare = -1; //which they choose as their piece
	int destination = -1; //where they want to move
	int xLoc = 0;
	int yLoc = 0;
	int yLocArray[MAX_PIECES] = {0};
	int xLocArray[MAX_PIECES] = {0};
	int numjumps = 0;
	int tempy = -1;//used for seeing if the destination square isnt 0
	int tempx = -1;
	bool didjump = 0;

	for(int i = 0; i < 6; i++)
	{
		counterforrows++;
		if ( counterforrows == 4)
		{
			cout << "ERROR:  Too many errors entering the size of the board";
			return 1;
		}
		cout << "Enter the number of squares along each edge of the board\n";
		cin >> numRowsInBoard;
		if(cin.fail()) //needs fixing, it likes to keep rereading the character /fixed/
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "ERROR:  Board size is not an integer\n";
			cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << "\n";
			continue;
		}
		else if ( numRowsInBoard % 2 == 1)
		{
			cout << "ERROR:  board size odd\n";
			cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << "\n";
		}
		else if (numRowsInBoard > MAX_ARRAY_SIZE)
		{
			cout << "ERROR:  Board size too large\n";
			cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << "\n";
		}
		else if ( numRowsInBoard < MIN_ARRAY_SIZE)
		{
			cout << "ERROR:  Board size too small\n";
			cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << "\n";
		}
		else
		{
			break;
		}
	}
	InitializeBoard(CMCheckersBoard, numRowsInBoard);
	DisplayBoard(CMCheckersBoard, numRowsInBoard);
	
	for (turn = 1; turn < 10000; turn++)//This ensures the program eventually stops
	{
		if (turn % 2 == 1) //odd turns, or white turns
		{
			player = WHITEPLAYER;
			if(CountJumps == 0 && CountMove1Squares == 0)
			{
				cout << "White is unable to move\nGAME OVER, Red has won\nEnter any character to close the game";
				cin >> entertocontinue;
				return 0;
			}
			cout << "White takes a turn\n";
			while(1)
			{
				cout <<"Enter the square number of the checker you want to move\n";
				cin >> selectedsquare;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ERROR:  you did not enter an integer\nTry again\n";
					continue;
				} 
				if (selectedsquare > numRowsInBoard * numRowsInBoard - 1 || selectedsquare < 0)
				{
					cout << "ERROR: that square is not on the board.\nTry Again\n";
					continue;
				}
				yLoc = selectedsquare/numRowsInBoard; //this probably works
				xLoc = selectedsquare%numRowsInBoard;
				if (CMCheckersBoard[yLoc][xLoc] == 0 )
				{
					cout << "ERROR:  that square is empty\nTry again\n";
					continue;
				}
				if (CMCheckersBoard[yLoc][xLoc] == REDKING || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER)
				{
					cout << "ERROR:  that square contains an opponent's checker\nTry again\n";
					continue;
				}
				numjumps = CountJumps(CMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray); //this step screws with xLoc for some reason, but returns false as it should /fixed(this was a bounds error)/
				if (numjumps != 0 && IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0)
				{//this should call the checklist function, but this way means I don't need that function at all
					cout << "ERROR: You can jump with another checker, you may not move your chosen checker\nYou can jump using checkers on the following squares: ";
					for (int d = 0; d <= numjumps-1; d++)
					{
						cout << yLocArray[d]*numRowsInBoard + xLocArray[d] << " ";
					}
					cout << "\n";
					continue;
				}
				if(IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0 && IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0)
				{
					cout << "ERROR: There is no legal move for this checker\nTry again\n";
					continue;
				}
				break;
			}
			//end of errors for selecting a square
			//begin errors for moving it
			while(1)
			{
				if (didjump == 0)
				{
					cout << "Enter the square number of the square you would like to move your checker to\n";
				}
				else
				{
					cout << "You can jump again,  Please enter the next square you wish to move your checker to\n";
				}
				cin >> destination;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ERROR:  you did not enter an integer\nTry again\n";
				}
				if (destination > numRowsInBoard * numRowsInBoard - 1 || destination < 0)
				{
					cout << "ERROR:  It is not possible to move to a square that is not on the board.\nTry again\n";
					continue;
				}
				tempy = destination/numRowsInBoard;
				tempx = destination%numRowsInBoard;
				if (CMCheckersBoard[tempy][tempx] != 0)
				{
					cout << "ERROR:  It is not possible to move to a square that is already occupied\nTry again\n";
					continue;
				} 
				//test if piece didnt jump when it had to, done by creating a neutered version of makemove
				if(IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 1 && Makemoveimproved(CMCheckersBoard, numRowsInBoard, selectedsquare, destination) == 0)
				{
					cout << "ERROR:  You can jump with this checker, you must jump not move 1 space\nTry again\n";
					continue;
				}
				if(MakeMove(CMCheckersBoard, numRowsInBoard, player, selectedsquare, destination, didjump) == false)
				{
					cout << " ERROR: moving to that square is not legal, Try again\n";
					continue;
				}
				if(didjump == 1 && IsJump(CMCheckersBoard, numRowsInBoard, player, tempx, tempy) == 1)
				{
					selectedsquare = destination;
					continue;
				}
				didjump = 0;
				if (CheckWin(CMCheckersBoard, numRowsInBoard) == 1)
				{
					cout << "Enter any character to terminate the game then press the enter key ";
					cin >> entertocontinue;
					return 1;
				}
				else
				{
					DisplayBoard(CMCheckersBoard, numRowsInBoard);
				}
				player = NOPLAYER;
				break;
			}
		}
		else
		{
			player = REDPLAYER;
			if(CountJumps == 0 && CountMove1Squares == 0)
			{
				cout << "Red is unable to move\nGAME OVER, White has won\nEnter any character to close the game";
				cin >> entertocontinue;
				return 0;
			}
			cout << "Red takes a turn\n";
			while(1)
			{
				cout <<"Enter the square number of the checker you want to move\n";
				cin >> selectedsquare;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ERROR:  you did not enter an integer\nTry again\n";
					continue;
				} 
				if (selectedsquare > numRowsInBoard * numRowsInBoard - 1 || selectedsquare < 0)
				{
					cout << "ERROR: that square is not on the board.\nTry Again\n";
					continue;
				}
				yLoc = selectedsquare/numRowsInBoard;
				xLoc = selectedsquare%numRowsInBoard;
				if (CMCheckersBoard[yLoc][xLoc] == 0 )
				{
					cout << "ERROR:  that square is empty\nTry again\n";
					continue;
				}
				if (CMCheckersBoard[yLoc][xLoc] == WHITEKING || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER)
				{
					cout << "ERROR:  that square contains an opponent's checker\nTry again\n";
					continue;
				}
				numjumps = CountJumps(CMCheckersBoard, numRowsInBoard, player, xLocArray, yLocArray);
				if (numjumps != 0 && IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0)
				{//this should call the checklist function, but this way means I don't need that function at all
					cout << "ERROR: You can jump with another checker, you may not move your chosen checker\nYou can jump using checkers on the following squares: ";
					for (int d = 0; d <= numjumps-1; d++)
					{
						cout << yLocArray[d]*numRowsInBoard + xLocArray[d] << " ";
					}
					cout << "\n";
					continue;
				}
				if(IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0 && IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 0)
				{
					cout << "ERROR: There is no legal move for this checker\nTry again\n";
					continue;
				}
				break;
			}
			//end of errors for selecting a square
			//begin errors for moving it
			while(1)
			{
				if (didjump == 0)
				{
					cout << "Enter the square number of the square you would like to move your checker to\n";
				}
				else
				{
					cout << "You can jump again,  Please enter the next square you wish to move your checker to\n";
				}
				cin >> destination;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "ERROR:  you did not enter an integer\nTry again\n";
					continue;
				}
				if (destination > numRowsInBoard * numRowsInBoard - 1 || destination < 0)
				{
					cout << "ERROR:  It is not possible to move to a square that is not on the board.\nTry again\n";
					continue;
				}
				tempy = destination/numRowsInBoard;
				tempx = destination%numRowsInBoard;
				if (CMCheckersBoard[tempy][tempx] != 0)
				{
					cout << "ERROR:  It is not possible to move to a square that is already occupied\nTry again\n";
					continue;
				} 
				//test if piece didnt jump when it had to, done by creating a neutered version of makemove
				if(IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == 1 && Makemoveimproved(CMCheckersBoard, numRowsInBoard, selectedsquare, destination) == 0)
				{
					cout << "ERROR:  You can jump with this checker, you must jump not move 1 space\nTry again\n";
					continue;
				}
				if(MakeMove(CMCheckersBoard, numRowsInBoard, player, selectedsquare, destination, didjump) == false)
				{
					cout << " ERROR: moving to that square is not legal, Try again\n";
					continue;
				}
				if(didjump == 1 && IsJump(CMCheckersBoard, numRowsInBoard, player, tempx, tempy) == 1)
				{
					selectedsquare = destination;
					continue;
				}
				if (CheckWin(CMCheckersBoard, numRowsInBoard) == 1)
				{
					cout << "Enter any character to terminate the game then press the enter key ";
					cin >> entertocontinue;
					return 1;
				}
				else
				{
					DisplayBoard(CMCheckersBoard, numRowsInBoard);
				}
				player = NOPLAYER;
				didjump = 0;
				break;
			}
		}
		}
	return 0;
}
//looks good, working as intended
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int q = 0;
	int r = 0;
	bool trigger = 0; //tests for setting it up
	for (q = 0; q < numRowsInBoard; q++)
	{
		for (r = 0; r < numRowsInBoard; r++)
		{
			if (q == 0 && (r+1) % 2 == 0)
			{
				CMCheckersBoard[q][r] = WHITEMULE;
			}
			else if (q == (numRowsInBoard)/2 - 1)
			{
				trigger = 1;
			}
			else if (q == numRowsInBoard/2)
			{
				trigger = 1;
			}
			else if(trigger == 0 && (q+1) % 2 == 0 && (r+1) % 2 != 0)
			{
				CMCheckersBoard[q][r] = WHITESOLDIER;
			}
			else if(trigger == 0 && (q+1) % 2 != 0 && (r+1) % 2 == 0)
			{
				CMCheckersBoard[q][r] = WHITESOLDIER;
			}
			else if (q == (numRowsInBoard-1) && (r+1) % 2 != 0)
			{
				CMCheckersBoard[q][r] = REDMULE;
			}
			else if(trigger == 1 && (q+1) % 2 != 0 && (r+1) % 2 == 0)
			{
				CMCheckersBoard[q][r] = REDSOLDIER;
			}
			else if(trigger == 1 && (q+1) % 2 == 0 && (r+1) % 2 != 0)
			{
				CMCheckersBoard[q][r] = REDSOLDIER;
			}
			else
			{
			}
		}
	}
}
//looks good, working as intended
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int squarenumber = 0;
	int w = 0;
	int h = 0;
	for (h = 0; h < numRowsInBoard; h++)
	{
		for(w = 0; w < numRowsInBoard; w++)
		{
			if ( CMCheckersBoard[h][w] == 0)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << squarenumber << endl;
				}
				else
				{
					cout.width(4);
					cout << right << squarenumber;
				}
			}
			else if (CMCheckersBoard[h][w] == WHITEMULE)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "WM" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "WM";
				}
			}
			else if (CMCheckersBoard[h][w] == WHITESOLDIER)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "WS" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "WS";
				}
			}
			else if (CMCheckersBoard[h][w] == REDSOLDIER)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "RS" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "RS";
				}
			}
			else if (CMCheckersBoard[h][w] == REDMULE)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "RM" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "RM";
				}
			}
			else if (CMCheckersBoard[h][w] == WHITEKING)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "WK" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "WK";
				}
			}
			else if (CMCheckersBoard[h][w] == REDKING)
			{
				if(w == numRowsInBoard-1)
				{
					cout.width(4);
					cout << right << "RK" << endl;
				}
				else
				{
					cout.width(4);
					cout << right << "RK";
				}
			}
			else
			{
			}
			squarenumber++;
		}
	}
	cout << "\n\n\n";
}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[MAX_PIECES], int yLocArray[MAX_PIECES])
{
	int possiblejumps = 0;
	int y = 0;
	int x = 0;
	int loccounter = 0;
	for (int z = 0; z < MAX_PIECES; z++)
	{
		yLocArray[z] = -1;
		xLocArray[z] = -1;
	}
	for (y = 0; y < numRowsInBoard; y++)
	{
		for (x = 0; x < numRowsInBoard; x++)
		{
			if(IsJump(CMCheckersBoard, numRowsInBoard, player, x, y) == 1)
			{
				possiblejumps++;
				yLocArray[loccounter] = y;
				xLocArray[loccounter] = x;
				loccounter++;
			}
		}
	}
	return possiblejumps;
}

int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[MAX_PIECES],  int yLocArray[MAX_PIECES] )
{//this function is essentially a copy of countjumps
	int possiblemoves = 0;
	int y = 0;
	int x = 0;
	int loccounter = 0;
	for (int z = 0; z < MAX_PIECES; z++)
	{
		yLocArray[z] = -1;
		xLocArray[z] = -1;
	}
	for (y = 0; y < numRowsInBoard; y++)
	{
		for (x = 0; x < numRowsInBoard; x++)
		{
			if(IsJump(CMCheckersBoard, numRowsInBoard, player, x, y) == 1)
			{
				possiblemoves++;
				yLocArray[loccounter] = y;
				xLocArray[loccounter] = x;
				loccounter++;
			}
		}
	}
	return possiblemoves;
}
//may be working
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{//inefficient, but may work
	if (player == REDPLAYER) //reds, bottom
	{
	if(CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING)
	{//left part/right part integrated, not separate
		//kings go first
		if (CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (xLoc-1 == 0)//1 away from the edge, can go down or up
			{//this one is up
				if(CMCheckersBoard[yLoc-1][xLoc-1] == WHITEKING || CMCheckersBoard[yLoc-1][xLoc-1] == WHITEMULE || CMCheckersBoard[yLoc-1][xLoc-1] == WHITESOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				} //this one is down
				if(CMCheckersBoard[yLoc+1][xLoc-1] == WHITEKING || CMCheckersBoard[yLoc+1][xLoc-1] == WHITEMULE || CMCheckersBoard[yLoc+1][xLoc-1] == WHITESOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == 0) // edge of board on the left
			{//going up
				if (CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITEKING || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITESOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc+1][numRowsInBoard-1] == WHITEKING || CMCheckersBoard[yLoc+1][numRowsInBoard-1] == WHITEMULE || CMCheckersBoard[yLoc+1][numRowsInBoard-1] == WHITESOLDIER)
				{//going down
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
			}//regular case
			if (CMCheckersBoard[yLoc-1][xLoc-1]== WHITEKING || CMCheckersBoard[yLoc-1][xLoc-1]== WHITEMULE || CMCheckersBoard[yLoc-1][xLoc-1]== WHITESOLDIER)
			{//going up left
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc-2] == 0 && xLoc-2 >= 0)
				{
					return true;
				}
			}
			if (CMCheckersBoard[yLoc+1][xLoc-1] == WHITEKING || CMCheckersBoard[yLoc+1][xLoc-1] == WHITEMULE || CMCheckersBoard[yLoc+1][xLoc-1] == WHITESOLDIER)
			{//going down left
				if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc-2] == 0 && xLoc-2 >= 0)
				{
					return true;
				}
			}
			/*RIGHT MOVES*/
			if (xLoc == numRowsInBoard-2) //1 away from right side
			{//going up
				if(CMCheckersBoard[yLoc-1][xLoc+1] == WHITEKING || CMCheckersBoard[yLoc-1][xLoc+1] == WHITEMULE || CMCheckersBoard[yLoc-1][xLoc+1] == WHITESOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][0] == 0)
					{
						return true;
					}
				} //this one is down
				if(CMCheckersBoard[yLoc+1][xLoc+1] == WHITEKING || CMCheckersBoard[yLoc+1][xLoc+1] == WHITEMULE || CMCheckersBoard[yLoc+1][xLoc+1] == WHITESOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][0] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == numRowsInBoard-1) //on the right edge
			{//going up
				if (CMCheckersBoard[yLoc-1][0] == WHITEKING || CMCheckersBoard[yLoc-1][0] == WHITEMULE || CMCheckersBoard[yLoc-1][0] == WHITESOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][1] == 0)
					{
						return true;
					}
				}//going down
				if (CMCheckersBoard[yLoc+1][0] == WHITEKING || CMCheckersBoard[yLoc+1][0] == WHITEMULE || CMCheckersBoard[yLoc+1][0] == WHITESOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][1] == 0)
					{
						return true;
					}
				}
			}//regular case right
			if (CMCheckersBoard[yLoc-1][xLoc+1]== WHITEKING || CMCheckersBoard[yLoc-1][xLoc+1]== WHITEMULE || CMCheckersBoard[yLoc-1][xLoc+1]== WHITESOLDIER)
			{//going up right
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
			if (CMCheckersBoard[yLoc+1][xLoc+1] == WHITEKING || CMCheckersBoard[yLoc+1][xLoc+1] == WHITEMULE || CMCheckersBoard[yLoc+1][xLoc-1] == WHITESOLDIER)
			{//going down right
				if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER)
		{
			if(xLoc-1 == 0) //1 away from left edge
			{
				if(CMCheckersBoard[yLoc-1][xLoc-1] == WHITEKING || CMCheckersBoard[yLoc-1][xLoc-1] == WHITEMULE || CMCheckersBoard[yLoc-1][xLoc-1] == WHITESOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == 0) //edge left
			{ 
				if (CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITEKING || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == WHITESOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
			}//regular left
			if (CMCheckersBoard[yLoc-1][xLoc-1] == WHITEKING || CMCheckersBoard[yLoc-1][xLoc-1] == WHITEMULE || CMCheckersBoard[yLoc-1][xLoc-1] == WHITESOLDIER)
			{
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc-2] == 0 && xLoc-2 >= 0) //prevents overjumping the board, assumes that yloc starts at 0
				{
					return true;
				}
			}
			if (xLoc == numRowsInBoard-2) //1 away from right side
			{//going up
				if(CMCheckersBoard[yLoc-1][xLoc+1] == WHITEKING || CMCheckersBoard[yLoc-1][xLoc+1] == WHITEMULE || CMCheckersBoard[yLoc-1][xLoc+1] == WHITESOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][0] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == numRowsInBoard-1) //on the right edge
			{//going up
				if (CMCheckersBoard[yLoc-1][0] == WHITEKING || CMCheckersBoard[yLoc-1][0] == WHITEMULE || CMCheckersBoard[yLoc-1][0] == WHITESOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][1] == 0)
					{
						return true;
					}
				}
			}
			if (CMCheckersBoard[yLoc-1][xLoc+1]== WHITEKING || CMCheckersBoard[yLoc-1][xLoc+1]== WHITEMULE || CMCheckersBoard[yLoc-1][xLoc+1]== WHITESOLDIER)//regular case right
			{//going up right
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
		}
		else
		{
		}
	}
	}
	if (player == WHITEPLAYER) //whites, top
	{
	if(CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
	{//left part/ right part integrated, not separate
		//kings go first
		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (xLoc-1 == 0)//1 away from the edge, can go down or up
			{//this one is up
				if(CMCheckersBoard[yLoc-1][xLoc-1] == REDKING || CMCheckersBoard[yLoc-1][xLoc-1] == REDMULE || CMCheckersBoard[yLoc-1][xLoc-1] == REDSOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				} //this one is down
				if(CMCheckersBoard[yLoc+1][xLoc-1] == REDKING || CMCheckersBoard[yLoc+1][xLoc-1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc-1] == REDSOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == 0) // edge of board on the left
			{//going up
				if (CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == REDKING || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc-1][numRowsInBoard - 1] == REDSOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
				if (CMCheckersBoard[yLoc+1][numRowsInBoard-1] == REDKING || CMCheckersBoard[yLoc+1][numRowsInBoard-1] == REDMULE || CMCheckersBoard[yLoc+1][numRowsInBoard-1] == REDSOLDIER)
				{//going down
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
			}
			if (CMCheckersBoard[yLoc-1][xLoc-1]== REDKING || CMCheckersBoard[yLoc-1][xLoc-1]== REDMULE || CMCheckersBoard[yLoc-1][xLoc-1]== REDSOLDIER)//regular case
			{//going up
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc-2] == 0 && xLoc-2 >= 0)
				{
					return true;
				}
			}
			if (CMCheckersBoard[yLoc+1][xLoc-1] == REDKING || CMCheckersBoard[yLoc+1][xLoc-1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc-1] == REDSOLDIER)
			{//going down left
				if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc-2] == 0 && xLoc-2 >= 0)
				{
					return true;
				}
			}
			/*RIGHT MOVES*/
			if (xLoc == numRowsInBoard-2) //1 away from right side
			{//going up
				if(CMCheckersBoard[yLoc-1][xLoc+1] == REDKING || CMCheckersBoard[yLoc-1][xLoc+1] == REDMULE || CMCheckersBoard[yLoc-1][xLoc+1] == REDSOLDIER)
				{
					if ( yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][0] == 0)
					{
						return true;
					}
				} //this one is down
				if(CMCheckersBoard[yLoc+1][xLoc+1] == REDKING || CMCheckersBoard[yLoc+1][xLoc+1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc+1] == REDSOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][0] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == numRowsInBoard-1) //on the right edge
			{//going up
				if (CMCheckersBoard[yLoc-1][0] == REDKING || CMCheckersBoard[yLoc-1][0] == REDMULE || CMCheckersBoard[yLoc-1][0] == REDSOLDIER) 
				{
					if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][1] == 0)
					{
						return true;
					}
				}//going down
				if (CMCheckersBoard[yLoc+1][0] == REDKING || CMCheckersBoard[yLoc+1][0] == REDMULE || CMCheckersBoard[yLoc+1][0] == REDSOLDIER)
				{
					if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][1] == 0)
					{
						return true;
					}
				}
			}
			if (CMCheckersBoard[yLoc-1][xLoc+1]== REDKING || CMCheckersBoard[yLoc-1][xLoc+1]== REDMULE || CMCheckersBoard[yLoc-1][xLoc+1]== REDSOLDIER)//regular case right
			{//going up right
				if (yLoc - 2 >= 0 && CMCheckersBoard[yLoc-2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
			if (CMCheckersBoard[yLoc+1][xLoc+1] == REDKING || CMCheckersBoard[yLoc+1][xLoc+1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc-1] == REDSOLDIER)
			{//going down right
				if (yLoc+2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER)
		{
			if(xLoc-1 == 0) //1 away from left edge, down left
			{
				if(CMCheckersBoard[yLoc+1][xLoc-1] == REDKING || CMCheckersBoard[yLoc+1][xLoc-1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc-1] == REDSOLDIER)
				{
					if ( yLoc + 2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == 0) //edge left, down left
			{ 
				if (CMCheckersBoard[yLoc+1][numRowsInBoard - 1] == REDKING || CMCheckersBoard[yLoc+1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc+1][numRowsInBoard - 1] == REDSOLDIER) 
				{
					if (yLoc + 2 <= numRowsInBoard -1 && CMCheckersBoard[yLoc+2][numRowsInBoard-2] == 0)
					{
						return true;
					}
				}
			}//regular left down
			if (CMCheckersBoard[yLoc+1][xLoc-1] == REDKING || CMCheckersBoard[yLoc+1][xLoc-1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc-1] == REDSOLDIER)
			{
				if (yLoc + 2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc-2] == 0 && xLoc-2 >= 0) //prevents overjumping the board, assumes that yloc starts at 0, which it does because thats how i programmed it
				{
					return true;
				}
			}
			if (xLoc == numRowsInBoard-2) //1 away from right side
			{//going down right
				if(CMCheckersBoard[yLoc+1][xLoc+1] == REDKING || CMCheckersBoard[yLoc+1][xLoc+1] == REDMULE || CMCheckersBoard[yLoc+1][xLoc+1] == REDSOLDIER)
				{
					if ( yLoc + 2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][0] == 0)
					{
						return true;
					}
				}
			}
			if (xLoc == numRowsInBoard-1) //on the right edge
			{//going down
				if (CMCheckersBoard[yLoc+1][0] == REDKING || CMCheckersBoard[yLoc+1][0] == REDMULE || CMCheckersBoard[yLoc+1][0] == REDSOLDIER) 
				{
					if (yLoc + 2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][1] == 0)
					{
						return true;
					}
				}
			}
			if (CMCheckersBoard[yLoc+1][xLoc+1]== REDKING || CMCheckersBoard[yLoc+1][xLoc+1]== REDMULE || CMCheckersBoard[yLoc+1][xLoc+1]== REDSOLDIER)//regular case right
			{//going down right
				if (yLoc + 2 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+2][xLoc+2] == 0 && xLoc+2 <= numRowsInBoard-1)
				{
					return true;
				}
			}
		}
		else
		{
		}
	}
	}
	return false;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if(player == REDPLAYER)
	{
		if (CMCheckersBoard[yLoc][xLoc] == REDKING || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER)
		{
			if (CMCheckersBoard[yLoc][xLoc] == REDKING )
			{//left edge
				if (xLoc == 0)
				{ //up left
					if (yLoc != 0 && CMCheckersBoard[yLoc-1][numRowsInBoard-1] == 0)
					{
						return true;
					}//down left
					if (yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}//right edge
				if (xLoc == numRowsInBoard-1)
				{//right up
					if (yLoc!= 0 && CMCheckersBoard[yLoc-1][0] == 0)
					{
						return true;
					}//right down
					if(yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][0] == 0)
					{
						return true;
					}
				}//regular left up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc-1] == 0 && xLoc != 0)
				{
					return true;
				}//regular left down
				if (yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][numRowsInBoard-1] == 0  && xLoc != 0)
				{
					return true;
				}//regular right up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}//regular right down
				if(yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}
			}
			if (CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER)
			{//left edge
				if (xLoc == 0)
				{ //up left
					if (yLoc != 0 && CMCheckersBoard[yLoc-1][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
				//right edge
				if (xLoc == numRowsInBoard-1)
				{//right up
					if (yLoc!= 0 && CMCheckersBoard[yLoc-1][0] == 0)
					{
						return true;
					}
				}//regular left up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc-1] == 0 && xLoc != 0)
				{
					return true;
				}//regular right up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}
			}
		}
	}
	if (player == WHITEPLAYER)
	{
		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER)
		{
			if (CMCheckersBoard[yLoc][xLoc] == WHITEKING )
			{//left edge
				if (xLoc == 0)
				{ //up left
					if (yLoc != 0 && CMCheckersBoard[yLoc-1][numRowsInBoard-1] == 0)
					{
						return true;
					}//down left
					if (yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}//right edge
				if (xLoc == numRowsInBoard-1)
				{//right up
					if (yLoc!= 0 && CMCheckersBoard[yLoc-1][0] == 0)
					{
						return true;
					}//right down
					if(yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][0] == 0)
					{
						return true;
					}
				}//regular left up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc-1] == 0 && xLoc != 0)
				{
					return true;
				}//regular left down
				if (yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][numRowsInBoard-1] == 0  && xLoc != 0)
				{
					return true;
				}//regular right up
				if (yLoc != 0 && CMCheckersBoard[yLoc-1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}//regular right down
				if(yLoc+1 <= numRowsInBoard-1 && CMCheckersBoard[yLoc+1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}
			}
			if(CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER)
			{//left edge
				if (xLoc == 0)
				{ //down left
					if (yLoc != numRowsInBoard-1 && CMCheckersBoard[yLoc+1][numRowsInBoard-1] == 0)
					{
						return true;
					}
				}
				//right edge
				if (xLoc == numRowsInBoard-1)
				{//right down
					if (yLoc != numRowsInBoard-1 && CMCheckersBoard[yLoc+1][0] == 0)
					{
						return true;
					}
				}//regular left down
				if (yLoc != numRowsInBoard-1 && CMCheckersBoard[yLoc+1][xLoc-1] == 0 && xLoc != 0)
				{
					return true;
				}//regular right down
				if (yLoc != numRowsInBoard-1 && CMCheckersBoard[yLoc+1][xLoc+1] == 0 && xLoc != numRowsInBoard-1)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//One will note the following function is incredibly repetitive and could certainly be optomized. However, for our purposes of a quick checkers game, the most efficient solution is not entirely neccessary
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	int initialx = -1;
	int initialy = -1;
	int destx = -1;
	int desty = -1;
	int xdist = 0;
	int ydist = 0;
	int entertocontinue = -1;
	bool *myp = NULL;
	bool moved = 0;

	myp = &jumped;
	initialy = fromSquareNum/numRowsInBoard;
	initialx = fromSquareNum%numRowsInBoard;
	desty = toSquareNum/numRowsInBoard;
	destx = toSquareNum%numRowsInBoard;
	jumped = 0;

	ydist = abs(initialy-desty);
	xdist = abs(initialx-destx);
	//1 away from edge
	if((initialx == 1 && destx == numRowsInBoard-1) ||  (initialx == numRowsInBoard-2 && destx == 0))
	{
		xdist = 2;
	}//on edge
	if ((initialx == 0 && destx == numRowsInBoard -2) || (initialx == numRowsInBoard-1 && destx == 1))
	{
		xdist = 2;
	}
	if((initialx == 0 && destx == numRowsInBoard-1) || (initialx == numRowsInBoard-1 && destx == 0))
	{
		xdist = 1;
	}
	if (player == REDPLAYER)
	{
		if (xdist > 2 || ydist > 2)
		{
			cout<< "Error; illegal move\n";
			return false;
		}
		if (CMCheckersBoard[initialy][initialx] == REDMULE || CMCheckersBoard[initialy][initialx] == REDSOLDIER)
		{ //going down
			if (initialy < desty)
			{
				cout << "Error; illegal move\n";
				return false;
			}
		}
		if (xdist == 2 && ydist == 2)
		{//1 away from left edge, jumping up
			if (initialx == 1 && destx == numRowsInBoard-1 && initialy >= 2 && desty == initialy - 2)
			{
				if (CMCheckersBoard[initialy-1][initialx-1] == WHITEKING || CMCheckersBoard[initialy-1][initialx-1] == WHITEMULE || CMCheckersBoard[initialy-1][initialx-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//1 away from left edge, jumping down
			if (initialx == 1 && destx == numRowsInBoard-1 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialx-1] == WHITEKING || CMCheckersBoard[initialy+1][initialx-1] == WHITEMULE || CMCheckersBoard[initialy+1][initialx-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}//left edge, going up
			if (initialx == 0 && destx == numRowsInBoard -2 && initialy >= 2 && desty == initialy -2)
			{
				if (CMCheckersBoard[initialy-1][numRowsInBoard-1] == WHITEKING || CMCheckersBoard[initialy-1][numRowsInBoard-1] == WHITEMULE || CMCheckersBoard[initialy-1][numRowsInBoard-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//left edge, going down
			if (initialx == 0 && destx == numRowsInBoard-2 && initialy +2 <= numRowsInBoard-1 && desty == initialy+2)
			{
				if (CMCheckersBoard[initialy+1][numRowsInBoard-1] == WHITEKING || CMCheckersBoard[initialy+1][numRowsInBoard-1] == WHITEMULE || CMCheckersBoard[initialy+1][numRowsInBoard-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}//right edge, going up
			if ( initialx == numRowsInBoard-1 && destx == 1 && initialy >= 2 && desty == initialy-2)
			{
				if (CMCheckersBoard[initialy-1][0] == WHITEKING || CMCheckersBoard[initialy-1][0] == WHITEMULE || CMCheckersBoard[initialy-1][0] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//right edge going down
			if (initialx == numRowsInBoard-1 && destx == 1 && initialy +2 <= numRowsInBoard-1 && desty == initialy + 2)
			{
				if (CMCheckersBoard[initialy+1][0] == WHITEKING || CMCheckersBoard[initialy+1][0] == WHITEMULE || CMCheckersBoard[initialy+1][0] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}//1 away from right edge, going up
			if(initialx == numRowsInBoard-2 && destx == 0 && initialy >= 2 && desty == initialy - 2)
			{
				if (CMCheckersBoard[initialy-1][initialx+1] == WHITEKING || CMCheckersBoard[initialy-1][initialx+1] == WHITEMULE || CMCheckersBoard[initialy-1][initialx+1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//1 away from right edge, going down
			if (initialx == numRowsInBoard-2 && destx == 0 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialy+1] == WHITEKING ||  CMCheckersBoard[initialy+1][initialy+1] == WHITEMULE || CMCheckersBoard[initialy+1][initialy+1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}//regular jump left up
			if (initialx >= 2 && destx == initialx -2 && initialy >= 2 && desty == initialy - 2)
			{
				if(CMCheckersBoard[initialy-1][initialx-1] == WHITEKING || CMCheckersBoard[initialy-1][initialx-1] == WHITEMULE || CMCheckersBoard[initialy-1][initialx-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//regular jump left down
			if(initialx >=2 && destx == initialx - 2 && initialy +2 <= numRowsInBoard-1 && desty == initialy+2)
			{
				if (CMCheckersBoard[initialy+1][initialx-1] == WHITEKING || CMCheckersBoard[initialy+1][initialx-1] == WHITEMULE || CMCheckersBoard[initialy+1][initialx-1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}//regular jump up right
			if(initialx <= numRowsInBoard-3 && destx == initialx+2 && initialy >= 2 && desty == initialy -2)
			{
				if (CMCheckersBoard[initialy -1][initialx+1] == WHITEKING || CMCheckersBoard[initialy -1][initialx+1] == WHITEMULE || CMCheckersBoard[initialy -1][initialx+1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDMULE)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDSOLDIER;
						*myp = 1;
					}
				}
			}//regular jump down right
			if(initialx <= numRowsInBoard-3 && destx == initialx+2 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialx+1] == WHITEKING || CMCheckersBoard[initialy+1][initialx+1] == WHITEMULE || CMCheckersBoard[initialy+1][initialx+1] == WHITESOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == REDKING)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = REDKING;
						*myp = 1;
					}
				}
			}
		}
		if (xdist == 1 && ydist == 1)
		{//leftedge up
			if (initialx == 0 && destx == numRowsInBoard -1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDMULE;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDSOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//leftedge down
			if (initialx == 0 && destx == numRowsInBoard -1 && initialy+1 <= numRowsInBoard -1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
			}//right edge up
			if (initialx == numRowsInBoard-1 && destx == 0 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDSOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//right edge down
			if (initialx == numRowsInBoard-1 && destx == 0 && initialy+1 <= numRowsInBoard -1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
			}//regular left up
			if (initialx != 0 && destx == initialx-1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDSOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//regular left down
			if (initialx != 0 && destx == initialx-1 && initialy +1 <= numRowsInBoard-1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
			}//regular right up
			if(initialx != numRowsInBoard-1 && destx == initialx+1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == REDSOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDSOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//regular right down
			if (initialx != numRowsInBoard-1 && destx == initialx+1 && initialy +1 <= numRowsInBoard-1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == REDKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = REDKING;
					*myp = 0;
					moved = 1;
				}
			}	
		}
		//this is for king me and win, above this shall be regular moving
		for(int m = 0; m < numRowsInBoard; m++)
		{
			if(CMCheckersBoard[0][m] == REDSOLDIER)
			{
				CMCheckersBoard[0][m] = REDKING;
			}
			//checks for red mule kings
			if(CMCheckersBoard[0][m] == REDMULE)
			{
				cout << "Red has created a Mule King,  White wins the game\nEnter any character to terminate the game then press the enter key ";
				cin >> entertocontinue;
				exit(1);
			}
		}
	}
	//here comes whites moves
	if (player == WHITEPLAYER)
	{
		if (xdist > 2 || ydist > 2)
		{
			cout<< "Error; illegal move\n";
			return false;
		}
		if (CMCheckersBoard[initialy][initialx] == WHITEMULE || CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
		{ //going down
			if (initialy > desty)
			{
				cout << "Error; illegal move\n";
				return false;
			}
		}
		if (xdist == 2 && ydist == 2)
		{//1 away from left edge, jumping up
			if (initialx == 1 && destx == numRowsInBoard-1 && initialy >= 2 && desty == initialy - 2)
			{
				if (CMCheckersBoard[initialy-1][initialx-1] == REDKING || CMCheckersBoard[initialy-1][initialx-1] == REDMULE || CMCheckersBoard[initialy-1][initialx-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//1 away from left edge, jumping down
			if (initialx == 1 && destx == numRowsInBoard-1 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialx-1] == REDKING || CMCheckersBoard[initialy+1][initialx-1] == REDMULE || CMCheckersBoard[initialy+1][initialx-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}//left edge, going up
			if (initialx == 0 && destx == numRowsInBoard -2 && initialy >= 2 && desty == initialy -2)
			{
				if (CMCheckersBoard[initialy-1][numRowsInBoard-1] == REDKING || CMCheckersBoard[initialy-1][numRowsInBoard-1] == REDMULE || CMCheckersBoard[initialy-1][numRowsInBoard-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//left edge, going down
			if (initialx == 0 && destx == numRowsInBoard-2 && initialy +2 <= numRowsInBoard-1 && desty == initialy+2)
			{
				if (CMCheckersBoard[initialy+1][numRowsInBoard-1] == REDKING || CMCheckersBoard[initialy+1][numRowsInBoard-1] == REDMULE || CMCheckersBoard[initialy+1][numRowsInBoard-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][numRowsInBoard-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}//right edge, going up
			if ( initialx == numRowsInBoard-1 && destx == 1 && initialy >= 2 && desty == initialy-2)
			{
				if (CMCheckersBoard[initialy-1][0] == REDKING || CMCheckersBoard[initialy-1][0] == REDMULE || CMCheckersBoard[initialy-1][0] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//right edge going down
			if (initialx == numRowsInBoard-1 && destx == 1 && initialy +2 <= numRowsInBoard-1 && desty == initialy + 2)
			{
				if (CMCheckersBoard[initialy+1][0] == REDKING || CMCheckersBoard[initialy+1][0] == REDMULE || CMCheckersBoard[initialy+1][0] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][0] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}//1 away from right edge, going up
			if(initialx == numRowsInBoard-2 && destx == 0 && initialy >= 2 && desty == initialy - 2)
			{
				if (CMCheckersBoard[initialy-1][initialx+1] == REDKING || CMCheckersBoard[initialy-1][initialx+1] == REDMULE || CMCheckersBoard[initialy-1][initialx+1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//1 away from right edge, going down
			if (initialx == numRowsInBoard-2 && destx == 0 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialx+1] == REDKING || CMCheckersBoard[initialy+1][initialx+1] == REDMULE || CMCheckersBoard[initialy+1][initialx+1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}//regular jump left up
			if (initialx >= 2 && destx == initialx -2 && initialy >= 2 && desty == initialy - 2)
			{
				if(CMCheckersBoard[initialy-1][initialx-1] == REDKING || CMCheckersBoard[initialy-1][initialx-1] == REDMULE || CMCheckersBoard[initialy-1][initialx-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//regular jump left down
			if(initialx >=2 && destx == initialx - 2 && initialy +2 <= numRowsInBoard-1 && desty == initialy+2)
			{
				if (CMCheckersBoard[initialy+1][initialx-1] == REDKING || CMCheckersBoard[initialy+1][initialx-1] == REDMULE || CMCheckersBoard[initialy+1][initialx-1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][initialx-1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}//regular jump up right
			if(initialx <= numRowsInBoard-3 && destx == initialx+2 && initialy >= 2 && desty == initialy -2)
			{
				if (CMCheckersBoard[initialy -1][initialx+1] == REDKING || CMCheckersBoard[initialy -1][initialx+1] == REDMULE || CMCheckersBoard[initialy -1][initialx+1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy-1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
				}
			}//regular jump down right
			if(initialx <= numRowsInBoard-3 && destx == initialx+2 && initialy +2 <= numRowsInBoard-1 && desty == initialy +2)
			{
				if(CMCheckersBoard[initialy+1][initialx+1] == REDKING || CMCheckersBoard[initialy+1][initialx+1] == REDMULE || CMCheckersBoard[initialy+1][initialx+1] == REDSOLDIER)
				{
					if (CMCheckersBoard[initialy][initialx] == WHITEKING)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEKING;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITEMULE;
						*myp = 1;
					}
					if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
					{
						CMCheckersBoard[initialy+1][initialx+1] = 0;
						CMCheckersBoard[initialy][initialx] = 0;
						CMCheckersBoard[desty][destx] = WHITESOLDIER;
						*myp = 1;
					}
				}
			}
		}
		if (xdist == 1 && ydist == 1)
		{//leftedge up
			if (initialx == 0 && destx == numRowsInBoard -1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
			}//leftedge down
			if (initialx == 0 && destx == numRowsInBoard -1 && initialy+1 <= numRowsInBoard -1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITESOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//right edge up
			if (initialx == numRowsInBoard-1 && destx == 0 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
			}//right edge down
			if (initialx == numRowsInBoard-1 && destx == 0 && initialy+1 <= numRowsInBoard -1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITESOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//regular left up
			if (initialx != 0 && destx == initialx-1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
			}//regular left down
			if (initialx != 0 && destx == initialx-1 && initialy +1 <= numRowsInBoard-1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITESOLDIER;
					*myp = 0;
					moved = 1;
				}
			}//regular right up
			if(initialx != numRowsInBoard-1 && destx == initialx+1 && initialy >= 1 && desty == initialy -1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
			}//regular right down
			if (initialx != numRowsInBoard-1 && destx == initialx+1 && initialy +1 <= numRowsInBoard-1 && desty == initialy +1)
			{
				if (CMCheckersBoard[initialy][initialx] == WHITEKING)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEKING;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITEMULE)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITEMULE;
					*myp = 0;
					moved = 1;
				}
				if (CMCheckersBoard[initialy][initialx] == WHITESOLDIER)
				{
					CMCheckersBoard[initialy][initialx] = 0;
					CMCheckersBoard[desty][destx] = WHITESOLDIER;
					*myp = 0;
					moved = 1;
				}
			}	
		}
		//this is for king me and win, above this shall be regular moving
		for(int m = 0; m < numRowsInBoard; m++)
		{
			if(CMCheckersBoard[numRowsInBoard-1][m] == WHITESOLDIER)
			{
				CMCheckersBoard[numRowsInBoard-1][m] = WHITEKING;
			}
			//checks for red mule kings
			if(CMCheckersBoard[numRowsInBoard-1][m] == WHITEMULE)
			{
				cout << "White has created a Mule King,  Red wins the game\nEnter any character to terminate the game then press the enter key ";
				cin >> entertocontinue;
				exit(1);
			}
		}
	}
	if (*myp == 1 || moved == 1)
	{
		return true;
	}
	cout << "Error; illegal move\n";
	*myp = 0;
	return false;
}
//untested, but it seems like it should work ((Tested, works for all win conditions))
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int q = 0;
	int r = 0;
	int rsoldcounter = 0;
	int wsoldcounter = 0;
	int wmulecounter = 0;
	int rmulecounter = 0;
	int wkingcounter = 0;
	int rkingcounter = 0;

	for (q = 0; q < numRowsInBoard; q++)
	{
		for (r = 0; r < numRowsInBoard; r++)
		{
			if(CMCheckersBoard[q][r] == REDMULE)
			{
				rmulecounter++;
			}
			if(CMCheckersBoard[q][r] == WHITEMULE)
			{
				wmulecounter++;
			}
			if(CMCheckersBoard[q][r] == REDSOLDIER)
			{
				rsoldcounter++;
			}
			if(CMCheckersBoard[q][r] == WHITESOLDIER)
			{
				wsoldcounter++;
			}
			if(CMCheckersBoard[q][r] == REDKING)
			{
				rkingcounter++;
			}
			if(CMCheckersBoard[q][r] == WHITEKING)
			{
				wkingcounter++;
			}
		}
	}
	if (rmulecounter == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules\n";
		return true;
	}
	if (wmulecounter == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules\n";
		return true;
	}
	if (rsoldcounter == 0 && rkingcounter == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings\n";
		return true;
	}
	if (wsoldcounter == 0 && wkingcounter == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings\n";
		return true;
	}
	return false;
}
//I dont ever call this, but I probably lose marks for omitting it
bool CheckList(int inArray1[], int inArray2[], int xindex, int yindex)
{
	for (int k = 0; k < MAX_PIECES; k++)
	{
		if (inArray1[k] == xindex)
		{
			return true;
		}
		if (inArray2[k] == yindex)
		{
			return true;
		}
	}
	return false;
}

int Makemoveimproved(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard, int fromSquareNum, int toSquareNum)
{
	int initialx = -1;
	int initialy = -1;
	int destx = -1;
	int desty = -1;
	int xdist = 0;
	int ydist = 0;

	initialy = fromSquareNum/numRowsInBoard;
	initialx = fromSquareNum%numRowsInBoard;
	desty = toSquareNum/numRowsInBoard;
	destx = toSquareNum%numRowsInBoard;

	ydist = abs(initialy-desty);
	xdist = abs(initialx-destx);
	//1 away from edge
	if((initialx == 1 && destx == numRowsInBoard-1) ||  (initialx == numRowsInBoard-2 && destx == 0))
	{
		xdist = 2;
	}//on edge
	if ((initialx == 0 && destx == numRowsInBoard -2) || (initialx == numRowsInBoard-1 && destx == 1))
	{
		xdist = 2;
	}
	if (xdist == 2 && ydist == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
