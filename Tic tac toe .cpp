#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;

typedef struct{
    int *row;
}WinList;


class Player {
private:
    string name; 
    int score;  
public:
    Player() :Player {""}{}
    Player(string n) :score{0}, name{n}{}

    void won(){
        score++;
    }


    int getScore(){
        return this->score;
    }

    string getName(){
         return this->name;
    }
};

class Game {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    WinList winlist[8];

    
    void displayBoard(){
        system("cls");
        cout<<"\t\t\t<=======================================>"<<endl;
        cout<<"\t\t\t                 Tic Tac Toe             "<<endl;
        cout<<"\t\t\t<=======================================>"<<endl<<endl<<endl<<endl<<endl;
        cout <<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout << "\t\t\t\t\t "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout << "\t\t\t\t\t-----------"<<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout << "\t\t\t\t\t "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout << "\t\t\t\t\t-----------"<<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout << "\t\t\t\t\t "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<<endl;
        cout << "\t\t\t\t\t   |   |   "<<endl;
        cout <<endl;
    }

  
    void computerInput(){
        int pos;
        pos = rand()%10; //generate any value between 1-9 randomly
        if(emptyIndex[pos] == 1){
            if(emptyCount < 0)
                return;
            computerInput();
        } else {
            cout<< "Computer choose: " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;
            board[pos] = 'O';
        }

    }

    void playerInput(Player &player){
        int pos;
        cout << endl;
        cout << "\t " << player.getName() <<" Turn"<<endl;
        cout <<"\t Enter the position(1-9):" << endl;
        cin >> pos;
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "-----Position not empty-------"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Your") == 0 ? board[pos] ='X': board[pos] ='O';
        }

    }

    void checkWin(Player &p1,Player &p2){
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[winlist[i].row[0]];

            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[winlist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                gameOn = 0;
                if(first_symbol == 'X'){
                    cout << "-----------------------"<< endl;
                    cout << "\t You WIN"<< endl;
                    cout << "-----------------------"<< endl;
                    p1.won();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------"<< endl;
                        cout << "\t Computer WON"<< endl;
                        cout << "-----------------------"<< endl;
                    } else {
                        cout << "-----------------------"<< endl;
                        cout << "\t Your friend WON"<< endl;
                        cout << "-----------------------"<< endl;

                    }
                }
                displayScore(p1,p2); //display the score of both the player
                break;
            }
        }
    }

    void play(Player &p1,Player &p2){
        char rematch ='\0';
        int hand = 0;
        gameOn =1;
        displayBoard();
        while((emptyCount > 0) && (gameOn != 0)){

            if(againstComputer)
                hand == 1 ? computerInput(): playerInput(p2);
            else
                hand == 1 ? playerInput(p1): playerInput(p2);
            hand= !hand;
            displayBoard();
            checkWin(p1,p2);
        }
        if (emptyCount <=0){
            cout << "      -----------------------"<< endl;
            cout << "\t No WINNER"<< endl;
            cout << "      -----------------------"<< endl;
        }
        cout<< endl;
        cout << "Rematch Y/N: ";
        cin >> rematch;
        if((rematch == 'Y')||(rematch == 'y')){
            init();
            play(p1,p2);
        }

    }

    void displayScore(Player &p1, Player &p2){
        cout << endl;
        cout << "\t SCORE: \t";
        if(againstComputer)
            cout<<" You: " <<p1.getScore()<<" \t Computer: "<<p2.getScore()<< endl;
        else
            cout<<" You: " <<p1.getScore()<<" \t Your friend: "<<p2.getScore()<< endl;
    }

public:
    Game(): emptyCount{0}, gameOn{1}, againstComputer{0}{
        init();
        winlist[0].row = new int[3]{0,1,2};
        winlist[1].row = new int[3]{3,4,5};
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        winlist[7].row = new int[3]{2,4,6};
    }

    void init(){
        gameOn = 1;

        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = ' ';
            emptyCount++;
        }
        emptyCount--;
    }

    void onePlayerGame(){
        Player p("Your");
        Player c("Computer");
        cout << "       -----------------------"<< endl;
        cout << "\t You: X \t Computer: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 1;
        play(c,p);

    }

    void twoPlayerGame(){
        Player p("Your");
        Player c("Your friend");
        cout << "       -----------------------"<< endl;
        cout << "\t You: X \t Your friend: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 0;
        play(c,p);
    }
};

int main()
{
    system("color 0E");
    system("title Tic Tac Toe @copyassignment");
    int ch;

    while(1){
        cout<<"\t\t\t<=======================================>"<<endl;
        cout<<"\t\t\t             Welcome to the Game         "<<endl;
        cout<<"\t\t\t                 Tic Tac Toe             "<<endl;
        cout<<"\t\t\t<=======================================>"<<endl<<endl<<endl<<endl<<endl;
        cout<< "      <----------Please choose the Mode---------->" << endl << endl;
        cout << "\t 1. Play with computer" <<endl;
        cout << "\t 2. Play with friend" <<endl;
        cout << "\t 3. To exit " <<endl;
        cout <<"      <------------------------------------------>" << endl;
        cout << endl;
        cout <<"\t Select an option from above" << endl;
        cin >> ch;
        switch(ch){
        case 1:{
            Game *game = new Game;
            game->init();
            game->onePlayerGame();
            }
            break;
        case 2:{
            Game *game = new Game;
            game->init();
            game->twoPlayerGame();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid Option! TRY AGAIN";
        }

    }
    return 0;
}
