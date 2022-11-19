#include <iostream>
#include<cstdlib>

using namespace std;

const int rozmiarPola = 8;
int score = 0;
void printPole(string pole[][rozmiarPola]);
bool strzel(int x, int y, int bombs[][rozmiarPola]);

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
                cout<<x<<" "<<y;
                if (bombs[x][y] != 1) {
                    planted++;

                    if (planted > numberOfBombs) {
                        break;
                    }

                    bombs[x][y] = 1;
                    cout<<": "<<bombs[x][y]<<endl;
                    for(int k = -1; k <=1; k++) {
                        for(int l = -1; l <=1; l++) {
                            if(!((k==0) && (l==0)) && (x-k >= 0) && (y-l >= 0)) {
                                bombsNearby[x-k][y-l]++;
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
        cout<<"Podaj rząd: ";
        cin>>x;
        cout<<"Podaj kolumnę: ";
        cin>>y;
        
        
        if ((x>rozmiarPola) || (x<1) || (y<1) || (y>rozmiarPola)) {
            cout<<"Nie istnieje pole z takimi kordynatami."<<endl;
        } else {
            x = x-1;
            y = y-1;
            if (pole[x][y] == " ") {
                cout<<"Już tu strzelałeś."<<endl;
            } else {
                if (strzel(x, y, bombs)) {
                    if (bombsNearby[x][y]==0) {
                        pole[x][y] = " ";
                    } else {
                        pole[x][y] = to_string(bombsNearby[x][y]);
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

void printPole(string pole[][rozmiarPola]) {
    cout<<"----------------------"<<endl;
    cout<<"Your score: "<<score<<endl;
    cout<<"  ";
    for(int i = 1; i <= rozmiarPola; i++) {
        cout<<i<<" ";
    }
    cout<<endl;
    int column = 1;
    for (int i = 0; i < rozmiarPola; i++) {
        cout<<column<<" ";
        for (int j= 0; j < rozmiarPola; j++) {
            cout<<pole[i][j]<<" ";
        }
        cout<<endl;
        column++;
    }
}

bool strzel(int x, int y, int bombs[][rozmiarPola]) {

    // Trafiona
    if (bombs[x][y] == 1) {
        return false;
    // Nie trafiona
    } else {
        return true;
    }
}
