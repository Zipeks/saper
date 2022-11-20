#include<iostream>
#include<cstdlib>

using namespace std;

const int rozmiarPola = 8;
int score = 0;
void printPole(string (&pole)[rozmiarPola][rozmiarPola]);
bool strzel(int x, int y, int (&bombs)[rozmiarPola][rozmiarPola]);

int main() {
    srand((unsigned) time(NULL));

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
    int numberOfBombs = 10;
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
                    cout<<x+1<<" "<<y+1<<": "<<bombs[x][y]<<endl;
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

    for (int i = 0; i < rozmiarPola; i++) {
        for (int j= 0; j < rozmiarPola; j++) {
            cout<<bombs[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
    for (int i = 0; i < rozmiarPola; i++) {
        for (int j= 0; j < rozmiarPola; j++) {
            cout<<bombsNearby[i][j]<<" ";
        }
        cout<<endl;
    }
    bool game = true;
    while(game) {
        printPole(pole);
        bool notShot = true;
        int x,y;
        cout<<"\033[0m"<<"Podaj rząd: ";
        cin>>x;
        cout<<"Podaj kolumnę: ";
        cin>>y;
        
        
        if ((x>rozmiarPola) || (x<1) || (y<1) || (y>rozmiarPola)) {
            cout<<"Nie istnieje pole z takimi kordynatami."<<endl;
        } else {
            x = x-1;
            y = y-1;
            if (pole[x][y].compare(" ")==0) {
                cout<<"Już tu strzelałeś."<<endl;
            } else {
                if (strzel(x, y, bombs)) {
                        if (bombs[x][y]==0) {
                            pole[x][y] = " ";
                        } else {
                            pole[x][y] = to_string(bombsNearby[x][y]);
                        }
                        for(int k = -1; k <=1; k++) {
                            for(int l = -1; l <=1; l++) {
                                int xAfter = x-k;
                                int yAfter = y-l;
                                // TEN WARUNEk JEST ZJEBANY
                                if (!((k == 0) && (l == 0)) && !((xAfter < 0) || (yAfter < 0)) && !((xAfter >= rozmiarPola) || (yAfter >= rozmiarPola)) && (pole[xAfter][yAfter].compare("@") == 0))
                                {
                                    if (bombsNearby[xAfter][yAfter]==0) {
                                        pole[xAfter][yAfter] = " ";
                                    } else {
                                        pole[x][y] = to_string(bombsNearby[x][y]);
                                    }
                                }
                            }
                        }
                    score++;

                } else {
                    cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<"You finished with a score of: "<<score<<"!"<<endl;
                    game = false;
                }
            }
        }
    }

    return 1;
}

void printPole(string (&pole)[rozmiarPola][rozmiarPola]) {
    cout<<"\033[34m"<<"-----------------"<<endl;
    cout<<"Your score: "<<score<<endl;
    cout<<"\033[0m"<<"  ";
    for(int i = 1; i <= rozmiarPola; i++) {

        cout<<i<<" ";
    }
    cout<<endl;
    int column = 1;
    for (int i = 0; i < rozmiarPola; i++) {
        cout<<column<<" ";
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
        cout<<endl;
        column++;
    }
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
