#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Game {
    public:
        Game() : board(3, vector<char>(3, ' ')), moves({'X', 'O'}) {} 
        ~Game() {}
        vector<vector<char> > board;
        vector<char> moves;
           //pot sa fac un string pt fiecare jucator care retine toate moves urile
        vector<char> playerA;
        vector<char> playerB;


  void createBoard() {
        int position = 1;

        cout << "\n\n" << endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << " (" << position << ") |";
                position++;
            }
            cout << endl;
        }
        cout << "\n\n" << endl;
    }

    void chooseFirstMove(vector<char>& moves) {
        cout << "Player A, choose your move (X/O): ";
        moves[0] = getchar();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        bool var = true;

       while(var){
            if (moves[0] == 'X' || moves[0] == 'O') {
                var = false;
            } else if (moves[0] == 'x' || moves[0] == 'o') {
                moves[0] = toupper(moves[0]);
            } else {
                cout << "Invalid move. Please choose again!" << endl;
                cout << "Player A, choose your move (X/O): ";
                moves[0] = getchar();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

       }
        if (moves[0] == 'X') {
            moves[1] = 'O';
        } else {
            moves[1] = 'X';
        } 

        cout << "Player B, your move is: " << moves[1] << endl;

    }
        

    void makeMove() {
        //chooseFirstMove(moves);
        int x, y;
        bool okA = true;
        bool okB = true;
        cout << "Player A, enter the position of your move (1-9): "; 



        while(okA) {
            cin >>  x;
            bool moveMade = false; // Flag to indicate if a valid move has been made

                for(int i = 0; i < 3; i++){
                    for (int j = 0; j < 3; j++){
                    
                        if (board[i][j] == ' '){
                            if (x == (i * 3 + j + 1)) {
                                board[i][j] = moves[0];
                                playerA.push_back(board[i][j]);
                                okA = false;
                                moveMade = true; // Set the flag since a valid move was made
                                break;
                            }
                        }    
                    }
                    if (moveMade) {
                        break; // Break the outer loop if a valid move was made
                    }
                }
                if (!moveMade) {
                    if(playerA.size()==5 || checkWin(board) == true){
                        break;
                    }
                    cout << "Invalid move. Position is already taken or out of bounds. Please choose again!" << endl;
                }
        }

        cout << "\n\n" << endl;
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << board[i][j] << "  |  ";
            }
            cout << endl;
        }

        cout << "\n\n" << endl;
        
        if(checkWin(board) == false){
            cout << "Player B, enter the position of your move (1-9): ";
            while (okB) {

            cin >> y;
            bool moveMade = false; // Flag to indicate if a valid move has been made

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                
                        if (board[i][j] == ' '){
                            if (y == (i * 3 + j + 1)) {
                                board[i][j] = moves[1];
                                playerB.push_back(board[i][j]);
                                okB = false;
                                moveMade = true; // Set the flag since a valid move was made
                                break; // Break the inner loop
                            }
                        }
                    }
                    if (moveMade) {
                        break; // Break the outer loop if a valid move was made
                    }
                }

                if (!moveMade) {
                    if(playerA.size()==5 || checkWin(board) == true){
                        break;
                    }
                    cout << "Invalid move. Position is already taken or out of bounds. Please choose again!" << endl;
                }
            }


            cout << "\n\n" << endl;
            for(int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    cout << board[i][j] << "  |  ";
                }
                cout << endl;
            }

            cout << "\n\n" << endl;
        }
        


    }

    vector <char> playerAwin(const vector<char>& playerA){
        vector<char> playerAsecond(3);
        if(playerA.size() >= 3){
            copy(playerA.begin(), playerA.begin() + 3, playerAsecond.begin());
        }
        return playerAsecond;
    }

     vector <char> playerBwin(const vector<char>& playerB){
        vector<char> playerBsecond(3);
        if(playerB.size() >= 3){
            copy(playerB.begin(), playerB.begin() + 3, playerBsecond.begin());
        }
        return playerBsecond;
    }
        


 
    vector<char> columnBoard(const vector<vector<char> >& board, int colIndex){
        int n = 3;
        vector<char> column;

        for (int i = 0; i < n; i++) {
            column.push_back(board[i][colIndex]);
        }

    return column;
}

    vector<char> rowBoard(const vector<vector<char> > &board, int rowIndex) {
        vector<char> row;
        int n = 3;
        for (int j = 0; j < n; j++){
            if (rowIndex >= 0 && rowIndex < n) {
                row.push_back(board[rowIndex][j]);
            }
        }
        return row;
    }

    vector<char> diagonalBoard(const vector<vector<char> > &board, int diagIndex) {
        vector<char> diag;
        int n = 3;
        if (diagIndex == 0) {
            for (int i = 0; i < n; i++) {
                diag.push_back(board[i][i]);
            }
        } else {
            for (int i = 0; i < n; i++) {
                diag.push_back(board[i][n - i - 1]);
            }
        }
        return diag;
    }

    bool checkWin(const vector<vector<char> > &board) {
        int n = 3;
        int winA  = 0;
        int winB = 0;

        for (int i = 0; i < 3; i++) {
            if (rowBoard(board, i) == playerAwin(playerA)) {
                winA++;
            } else if (rowBoard(board, i) == playerBwin(playerB)) {
                winB++;
            }
            if (columnBoard(board, i) == playerAwin(playerA)) {
                winA++;
            } else if (columnBoard(board, i) == playerBwin(playerB)) {
                winB++;
                
            }
        }

        if (diagonalBoard(board, 0) == playerAwin(playerA)) {
            winA++;
        } else if (diagonalBoard(board, 0) == playerBwin(playerB)) {
            winB++;
        }

        if (diagonalBoard(board, 1) == playerAwin(playerA)) {
            winA++;
        } else if (diagonalBoard(board, 1) == playerBwin(playerB)) {
            winB++;
        }

        if(winA >=1){
            cout << "----------    Player A wins!    ----------" << endl;
        } else if(winB >= 1){
            cout << "----------    Player B wins!    ----------" << endl;
        } else if(winA == 0 && winB == 0 && playerA.size() == 5 && playerB.size() == 4){
            cout << "----------    It's a draw!    ----------" << endl;
        }

        if(winA >= 1 || winB >= 1){
            return true;
        } else {
            return false;
        }
        
    }
    

};
int main() {

    int n = 3;

    Game newGame;

    newGame.createBoard();

    vector<char> moves = newGame.moves;
    vector<char> playerA = newGame.playerA;
    vector<char> playerB = newGame.playerB;
    vector<char> playerAwin = newGame.playerAwin(newGame.playerA);
    vector<char> playerBwin = newGame.playerBwin(newGame.playerB);
    newGame.chooseFirstMove(newGame.moves);


    for(int i = 0; i < 9; i ++){

        if(newGame.checkWin(newGame.board) == false) {
            if(newGame.playerA.size() <= 4){
                newGame.makeMove();
            } else {
                break;
            }
        }
    }

    vector<char> rowboard = newGame.rowBoard(newGame.board, n);
    vector<char> columnboard = newGame.columnBoard(newGame.board, n);
    vector<char> diagonalboard = newGame.diagonalBoard(newGame.board, n);


    newGame.checkWin(newGame.board);
    return 0;
}