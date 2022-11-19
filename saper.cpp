#include <iostream>
#include<cstdlib>

using namespace std;

const int rozmiarPola = 8;

void printPole(string pole[][rozmiarPola]);
bool strzel(int x, int y, int bombs[][rozmiarPola]);

int main() {
    srand((unsigned) time(NULL));

    string pole[rozmiarPola][rozmiarPola];
    for (int i = 0; i < rozmiarPola; i++) {
        for (int j= 0; j < rozmiarPola; j++) {
            pole[i][j] = "@";
        }
    }

    int numberOfBombs = 10;
    int bombs[rozmiarPola][rozmiarPola];
    for (int i = 0; i < rozmiarPola; i++) {
        for (int j= 0; j < rozmiarPola; j++) {
            bombs[i][j]=0;
        }
    }
    // PLANT BOMBS
    int planted = 0;
    while (planted <= numberOfBombs) {
        for (int i = 0; i < rozmiarPola; i++) {
            if (planted > numberOfBombs) {
                    break;
            }
            for (int j= 0; j < rozmiarPola; j++) {
                int x = rand() % rozmiarPola;
                int y = rand() % rozmiarPola;
                if (planted > numberOfBombs) {
                    break;
                }
                if (bombs[x][y] != 1) {
                    bombs[x][y] = 1;
                    planted++;
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
            if (pole[x][y] == " ") {
                cout<<"Już tu strzelałeś."<<endl;
            } else {
                if (strzel(x, y, bombs)) {
                    pole[x-1][y-1] = " ";
                } else {
                    cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<"You lost!";
                    game = false;
                }
            }
        }
    }

    return 0;
}

void printPole(string pole[][rozmiarPola]) {
    cout<<"----------------------------"<<endl;
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
    if (bombs[x-1][y-1] == 1) {
        return false;
    // Nie trafiona
    } else {
        return true;
    }
}
