#include<iostream>
#include<cstdlib>

using namespace std;

const int rozmiarPola = 8;
int score = 0;
void printPole(string (&pole)[rozmiarPola][rozmiarPola]);
bool strzel(int x, int y, int (&bombs)[rozmiarPola][rozmiarPola]);

int main() {
    srand((unsigned) time(NULL));

    int numberOfBombs = 10;
    string pole[rozmiarPola][rozmiarPola];
    int bombsNearby[rozmiarPola][rozmiarPola];
    int bombs[rozmiarPola][rozmiarPola];

    for (int i = 0; i < rozmiarPola; i++) {
        for (int j= 0; j < rozmiarPola; j++) {
            pole[i][j] = "@";
            bombs[i][j] = 0;
            bombsNearby[i][j] = 0;
        }
    }
    
    // PLANT BOMBS
    int planted = 0;
    while (planted < numberOfBombs) {
                int x = rand() % rozmiarPola;
                int y = rand() % rozmiarPola;
          
                if (bombs[x][y] == 0) {
                    planted++;

                    if (planted > numberOfBombs) {
                        break;
                    }

                    bombs[x][y] = 1;
                    // cout<<x+1<<" "<<y+1<<": "<<bombs[x][y]<<endl;
                    for(int k = -1; k <=1; k++) {
                        for(int l = -1; l <=1; l++) {
                            int xAfter = x-l;
                            int yAfter = y-k;
                            if  (!((k==0) && (l==0)) && !((xAfter < 0) || (yAfter < 0)) && !((xAfter >= rozmiarPola) || (yAfter >= rozmiarPola))) {
                                bombsNearby[xAfter][yAfter]++;
                            }
                        }
                    }
                }
    }

    // for (int i = 0; i < rozmiarPola; i++) {
    //     for (int j= 0; j < rozmiarPola; j++) {
    //         cout<<bombs[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl<<endl<<endl;
    // for (int i = 0; i < rozmiarPola; i++) {
    //     for (int j= 0; j < rozmiarPola; j++) {
    //         cout<<bombsNearby[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    bool game = true;
    while(game) {
        printPole(pole);
        bool notShot = true;
        int x,y;
        cout<<"\033[0m"<<"Podaj rzad: ";
        cin>>x;
        cout<<"Podaj kolumne: ";
        cin>>y;
        
        
        if ((x>rozmiarPola) || (x<1) || (y<1) || (y>rozmiarPola)) {
            cout<<"Nie istnieje pole z takimi kordynatami."<<endl;
        } else {
            x = x-1;
            y = y-1;
            if (pole[x][y].compare("@")!=0) {
                cout<<endl<<"\033[31m"<<"Juz tu strzelales."<<endl<<endl;
            } else {
                if (strzel(x, y, bombs)) {
                        if (bombsNearby[x][y]==0) {
                            pole[x][y] = " ";
                        } else {
                            pole[x][y] = to_string(bombsNearby[x][y]);
                        }
                        score++;
                        if (bombsNearby[x][y] == 0) {
                            for(int k = -1; k <=1; k++) {
                                for(int l = -1; l <=1; l++) {
                                    int xAfter = x-k;
                                    int yAfter = y-l;
                                    if (!((k == 0) && (l == 0)) && !((xAfter < 0) || (yAfter < 0)) && !((xAfter >= rozmiarPola) || (yAfter >= rozmiarPola)) && (pole[xAfter][yAfter].compare("@") == 0)) {
                                        if (bombsNearby[xAfter][yAfter]==0) {
                                            pole[xAfter][yAfter] = " ";

                                        } else {
                                            pole[xAfter][yAfter] = to_string(bombsNearby[xAfter][yAfter]);
                                        }
                                        score++;
                                    }
                                }
                            }
                        }
                        if (score == rozmiarPola*rozmiarPola-numberOfBombs) {
                            cout<<"\033[32m"<<"You won!!!!!!"<<"\033[0m"<<endl;
                            game = false;
                        }
                    

                } else {
                    cout<<"\033[31m"<<"BOOOOOOOOOOOOOOM!!!"<<endl<<"You finished with a score of: "<<score<<"!"<<"\033[0m"<<endl;
                    game = false;
                }
            }
        }
    }

    return 1;
}

void printPole(string (&pole)[rozmiarPola][rozmiarPola]) {
    cout<<"\033[34m";
    for(int i=0; i <rozmiarPola*rozmiarPola; i++) {
        cout<<(char)196;
    }
    cout<<"     "<<"Your score: "<<score<<endl;
    cout<<"\033[0m"<<"    ";
    for(int i = 1; i <= rozmiarPola; i++) {
        cout<<i<<" ";
    }
    cout<<endl;
 
    cout<<"\033[0m"<<"  "<<(char)218;
    for(int i = 1; i < rozmiarPola*2+2; i++) {
        cout<<(char)196;
    }
    cout<<(char)191<<endl;

    int column = 1;
    for (int i = 0; i < rozmiarPola; i++) {
        cout<<column<<" "<<(char)179<<" ";
        for (int j= 0; j < rozmiarPola; j++) {
            if (pole[i][j].compare("1")==0) {
                cout<<"\033[34m" <<pole[i][j]<<" ";
            } else if (pole[i][j].compare("2")==0) {
                 cout<<"\033[32m" <<pole[i][j]<<" ";
            } else if (pole[i][j].compare("3")==0) {
                 cout<<"\033[31m" <<pole[i][j]<<" ";
            } else if (pole[i][j].compare("4")==0) {
                 cout<<"\033[35m" <<pole[i][j]<<" ";
            }
            else {
                cout<<"\033[0m"<<pole[i][j]<<" ";
            }
        }
        cout<<"\033[0m"<<(char)179<<endl;
        column++;
    }

    cout<<"\033[0m"<<"  "<<(char)192;
    for(int i = 1; i < rozmiarPola*2+2; i++) {
        cout<<(char)196;
    }
    cout<<(char)217<<endl;
}

bool strzel(int x, int y, int (&bombs)[rozmiarPola][rozmiarPola]) {

    // Trafiona
    if (bombs[x][y] == 1) {
        return false;
    // Nie trafiona
    } else {
        return true;
    }
}
