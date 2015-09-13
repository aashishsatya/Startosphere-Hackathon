#include <iostream>
#include <cstdlib>

using namespace std;

int squares_remaining;
int board[4][4];

struct coordinates
{
    // top left is zero
    int x;
    int y;
};

struct return_struct	
{
    int v;  // the v or value of a node in alpha beta search
    coordinates action; // square to mark
};

return_struct max_value(int alpha, int beta);
return_struct min_value(int alpha, int beta);
void print_board();

int score()
{
    int zero_count = 0;
    int one_count = 0;

    // checking horizontally

    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1)
                one_count++;
            else if(board[i][j] == 0 && board[i][j + 1] == 0 && board[i][j + 2] == 0)
                zero_count++;
        }
    }

    // checking vertically
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1)
                one_count++;
            else if(board[i][j] == 0 && board[i + 1][j] == 0 && board[i + 2][j] == 0)
                zero_count++;
        }
    }

    // check main diagonal
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (board[i][j] == 1 && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1)
                one_count++;
            else if(board[i][j] == 0 && board[i + 1][j + 1] == 0 && board[i + 2][j + 2] == 0)
                zero_count++;
        }
    }

    // check off diagonal
    for (int i = 0; i < 2; i++)
    {
        for(int j = 2; j < 4; j++)
        {
            if (board[i][j] == 1 && board[i + 1][j - 1] == 1 && board[i + 2][j - 2] == 1)
                one_count++;
            else if(board[i][j] == 0 && board[i + 1][j - 1] == 0 && board[i + 2][j - 2] == 0)
                zero_count++;
        }
    }

    return zero_count - one_count;
}

int INF = 1000;

return_struct max_value(int alpha, int beta)
{
    if (squares_remaining == 0)
    {
        // terminal state
        return_struct ans;
        ans.v = score();
        return ans;
    }

    // not a terminal state
    // so check all remaining moves

    return_struct ans;
    ans.v = - 1 * INF;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != -1)
                continue;

            // consider this new square
            board[i][j] = 0;
            squares_remaining--;

            return_struct result = min_value(alpha, beta);

            if (result.v > ans.v)
            {
                ans.v = result.v;
                ans.action.x = i;
                ans.action.y = j;
            }

            // alpha beta pruning step
            if (ans.v >= beta)
            {
                // restore the board
                board[i][j]  = -1;
                squares_remaining++;
                return ans;
            }

            if (ans.v > alpha)
            {
                alpha = ans.v;
            }

            // restore the board
            board[i][j]  = -1;
            squares_remaining++;
        }
    }
    
    return ans;
}

return_struct min_value(int alpha, int beta)
{

    if (squares_remaining == 0)
    {
        // terminal state
        return_struct ans;
        ans.v = score();
        return ans;
    }

    // not a terminal state
    // so check all remaining moves

    return_struct ans;
    ans.v = INF;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != -1)
                continue;

            // consider this new square
            board[i][j] = 1;
            squares_remaining--;

            return_struct result = max_value(alpha, beta);

            if (result.v < ans.v)
            {
                ans.v = result.v;
                ans.action.x = i;
                ans.action.y = j;
            }

            // alpha beta pruning step
            if (ans.v <= alpha)
            {
                // restore the board
                board[i][j]  = -1;
                squares_remaining++;
                return ans;
            }

            if (ans.v < beta)
            {
                beta = ans.v;
            }

            // restore the board
            board[i][j]  = -1;
            squares_remaining++;
        }
    }
    return ans;
}

coordinates alpha_beta_search()
{
    return_struct v = min_value(-1 * INF, INF);
    return v.action;
}

void print_board()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                cout << "X" << '\t';
            else if (board[i][j] == 1)
                cout << "O" << '\t';
            else
                cout << "-" << '\t';
        }
        cout << endl << endl;
    }
}

int main()
{
    // initialize board

    squares_remaining = 16;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = -1;
        }
    }

    cout << "Program that plays 4 x 4 Tic Tac Toe." << endl;

    int x_coord, y_coord;

    // play the game!!
    for (int i = 0; i < 8; i++)
    {
		cout << "\nCurrent board state:" << endl << endl;
        print_board();
        
        cout << "Enter X and Y coordinates:" << endl << endl;
        cin >> x_coord;
        cin >> y_coord;

		// check move validity
        if (board[x_coord][y_coord] != -1)
        {
			cout << "Invalid move." << endl;
			exit(EXIT_FAILURE);
		}
		
		// check values of xcoord and ycoord
		if (x_coord < 0 || x_coord > 3)
		{
			cout << "Invalid move." << endl;
			exit(EXIT_FAILURE);
		}
		
		// check values of xcoord and ycoord
		if (y_coord < 0 || y_coord > 3)
		{
			cout << "Invalid move." << endl;
			exit(EXIT_FAILURE);
		}

        board[x_coord][y_coord] = 0;
        squares_remaining--;

        coordinates adv_move = alpha_beta_search();	// adversary's move
        x_coord = adv_move.x;
        y_coord = adv_move.y;
        board[x_coord][y_coord] = 1;
        squares_remaining--;
    }

    print_board();
    cout << "Result: ";
    if (score() == 0)
        cout << "Draw.";
    else if (score() > 0)
        cout << "Player 1 wins!!";
    else
        cout << "Player 2 wins!!";

    cout << endl;
}
