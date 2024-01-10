#include <conio.h> 
#include <iostream> 
#include <windows.h> 
using namespace std;

// wymiary planszy 
const int width = 80;
const int height = 20;

// koordy głowy
int x, y;
//owoc
int fruitCordX, fruitCordY;
//punkty
int playerScore;
//ogon
int snakeTailX[100], snakeTailY[100];
//dlugosc ogona 
int snakeTailLen;
// kierunek ruchu 
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
// zmienna ruchu 
snakesDirection sDir;
// czy gra sie skonczyla 
bool isGameOver;

//poczatek
void GameInit()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}
//generowanie planszy
void GameRender(string playerName)
{
    system("cls"); // wyczyszczenie konsoli

    //górna ściana
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            //boczne ściany
            if (j == 0 || j == width)
                cout << "|";
            // generowanie głowy węża
            if (i == y && j == x)
                cout << "O";
            // generowanie owocu 
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            // generowanie ogona 
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j
                        && snakeTailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // dolna ściana
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

 
    cout <<"Punkty gracza " << playerName<<":" << playerScore
        << endl;
}

// aktualizowanie stanu gry po każdym ruchu
void UpdateGame()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // czy wąż uderzył w ścianę
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // czy wąż uderzył w ogon
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }

    // zjedzenie owocu
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}

// poziom trudności
int SetDifficulty()
{
    int dfc, choice;
    cout << "\nWybierz poziom trudnosci\n1: Trudny\n2: Sredni\n3: Latwy "
        "\nWazne: jezeli nie wybrano lub wpisano inna liczbe "
        "poziom trudnosci zostanie automatycznie ustawiony na sredni "
        "\nWybrany poziom trudnosci: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 50;
        break;
    case '2':
        dfc = 100;
        break;
    case '3':
        dfc = 150;
        break;
    default:
        dfc = 100;
    }
    return dfc;
}

// input usera
void UserInput()
{
    // czy klawisz jest wciśnięty
    if (_kbhit()) {
        // wczytywanie klawisza
        switch (_getch()) {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}


int main()
{
    string playerName;
    cout << "Wpisz swoje imie: ";
    cin >> playerName;
    int dfc = SetDifficulty();

    GameInit();
    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        // opoźnienie dla poziomu trudności
        Sleep(dfc);
    }

    return 0;
}
