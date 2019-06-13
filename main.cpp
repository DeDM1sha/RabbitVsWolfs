#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <queue>

#define Void_Block 100
#define Grass_Block 101
#define Rabbit_Grass 102
#define Rabbit_Block 103
#define Hare_Grass 104
#define Hare_Block 105
#define Rabbit_Hare 106
#define Rabbit_Rabbit 107
#define Hare_Hare 108
#define Wolf_Grass 109
#define Wolf_Block 110
#define BitchWolf_Grass 111
#define BitchWolf_Block 112
#define Wolf_Hare 113
#define Wolf_Wolf 114
#define BitchWolf_BitchWolf 115
#define Wolf_Rabbit 116
#define BitchWolf_Rabbit 117
#define BitchWolf_Hare 118
#define Wolf_BitchWolf 119
#define cls system ("cls");
#define Male true
#define Female false

#include "gameprocess.h"
#include "animals.h"

using namespace std;

class ModelProcess {

    public:

        int N; // ����������� ���� - ���-�� �����
        int M; // ����������� ���� - ���-�� ��������
        int** Field; // ���� ������
        bool** Grass_Map; // ������������ ����� �� �����
        int Days; // ���-�� ����, �� ������ ������ ������
        int CountGrass; // ���-�� ����� �� �����
        int HowRabbitsMan_OnMap; // ���-�� ������ �� �����
        int HowRabbitsWoman_OnMap; // ���-�� ������ �� �����
        int HowWolfsMan_OnMap; // ���-�� ������ �� �����
        int HowWolfsWoman_OnMap; // ���-�� ������ �� �����
        string TimeOfYear; // ����� ����

        ModelProcess (int Rows, int Columns) {

            this->N = Rows;
            this->M = Columns;

            Field = new int* [N];
            Grass_Map = new bool* [N];

                for (int i = 0; i < N; i++) {

                    Field[i] = new int [M];
                    Grass_Map[i] = new bool [M];

                        for (int c = 0; c < M; c++) {

                            Field[i][c] = Void_Block;
                            Grass_Map[i][c] = false;

                        }

                }

            this->Days = 0;
            this->CountGrass = 0;
            HowRabbitsMan_OnMap = 0;
            HowRabbitsWoman_OnMap = 0;
            HowWolfsMan_OnMap = 0;
            HowWolfsWoman_OnMap = 0;
            TimeOfYear = "\0";

        }

        void Show_Coordinates (Animals& Object) {

            cout << "\nX: " << Object.X;
            cout << "\nY: " << Object.Y;

        }

        ~ModelProcess (void) {

            for (int i = 0; i < N; i++) {

                delete [] Field[i];
                delete [] Grass_Map[i];

            }

             delete Field;
             delete Grass_Map;

        }

        void Field_Clear (void) {

            int Old_Field[N][M];

                for (int i = 0; i < this->N; i++) {

                    for (int c = 0; c < this->M; c++) {

                        Old_Field[i][c] = Void_Block;
                        Grass_Map[i][c] = false;

                            if (Field[i][c] == Grass_Block || Field[i][c] == Rabbit_Grass || Field[i][c] == Hare_Grass || Field[i][c] == Wolf_Grass || Field[i][c] == BitchWolf_Grass) {

                                Old_Field[i][c] = Grass_Block;
                                Grass_Map[i][c] = true;

                            }

                        Field[i][c] = Void_Block;

                    }

                }

            for (int i = 0; i < this->N; i++)
                for (int c = 0; c < this->M; c++)
                    Field[i][c] = Old_Field[i][c];

        } // ����� ������� ����

        void Default_Settings (void) {

            srand (time (NULL));

            COORD coord;
            coord=GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);
            ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
            keybd_event(VK_MENU,0x38,0,0);
            keybd_event(VK_RETURN,0x1c,0,0);
            keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
            keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
            SetCursorPos(0, 5000);

            void *handle = GetStdHandle (STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO structCursorInfo;
            GetConsoleCursorInfo (handle, &structCursorInfo);
            structCursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo (handle, &structCursorInfo); // ���������� �������

            setlocale (LC_CTYPE, "Russian"); // ��������� � �������
            system ("title ����� ������ ������"); // ��������� ���������
            system ("color B"); // ������-������� ���� ������

        } // ����� ��������� ����������


        void CardLegend (GameProcess& Game, int Line) {

            unsigned short int Number = 0;
            string Str1 = "\0", Str2 = "\0";

                switch (Line) {

                    case 1: Str1 = "               ������� �����";  Str2 = "\0";            Number = 11; break;
                    case 2: Str1 = "               **";             Str2 = " - �����";      Number = 10; break;
                    case 3: Str1 = "               &&";             Str2 = " - ����";       Number = 15; break;
                    case 4: Str1 = "               &&";             Str2 = " - �������";    Number = 14; break;
                    case 5: Str1 = "               @@";             Str2 = " - ����";       Number = 12; break;
                    case 6: Str1 = "               @@";             Str2 = " - �������";    Number = 13; break;
                    default: Str1 = "\0";                           Str2 = "\0";            Number = 0;  break;

                }

            SetConsoleTextAttribute (hConsole, (WORD) ((0 << 4) | Number));
            cout << Str1;
            Game.Set_BackgroundColor ();
            cout << Str2;

        } // ����� ��������� ������� �����

        string Determine_TimeOfYear (void) {

            int DaysCount = this->Days;

                while (DaysCount > 364)
                    DaysCount -= 364;

                if (DaysCount > 336 || DaysCount < 63)
                    TimeOfYear = "����";

                else if (DaysCount > 62 && DaysCount < 155)
                    TimeOfYear = "�����";

                else if (DaysCount > 154 && DaysCount < 247)
                    TimeOfYear = "����";

                else
                    TimeOfYear = "�����";

            return this->TimeOfYear;

        } // �����, ������������ ����� ����

        void Random_Grass (void) {

            for (int i = 0; i < this->N; i++) {

                for (int c = 0; c < this->M; c++) {

                    if (Field[i][c] == Void_Block) {

                        unsigned short int Number = 0 + rand () % 101;

                            if (Number > 97)
                                this->Field[i][c] = Grass_Block;

                    }

                }

            }


        } // ����� ������������ ����� ����� �� �����

        bool Random_Sex (void) {

            unsigned short int Number = 0 + rand () % 101;

                if (Number < 50)
                    return false;

            return true;

        } // ����� ������������ ���� ���������

}; // ����� ������

int Minimum_Count (int& DefaultCount, int& StartCount) {

        if (DefaultCount < StartCount)
            return DefaultCount;

    return StartCount;

} // �������, ������������ ����������� �������� ����� RabbitsCount / WolfsCount � StartAnimalCount �������������

int main (void) {

    GameProcess Game;
    ModelProcess* Model;
    Model = new ModelProcess (Game.Rows_Count, Game.Columns_Count);

    Model->Default_Settings ();

    unsigned short int Button = 0; // ������� ������
    bool Start = false;

        while (true) { // ��������� ���� ���������

            Game.Preview ();
            Game.Center("_________________________________________\n");
            Game.Center("| Enter. ������ ������������� ������     |\n");
            Game.Center("|----------------------------------------|\n");
            Game.Center("| Esc. ����� �� ���������                |\n");
            Game.Center("|________________________________________|\n");

                while (true) {

                    Button = getch ();

                        if (Button == 27) {

                            Model->~ModelProcess();
                            return 0;

                        }

                        else if (Button == 13)
                            break;

                }

                if (Button == 13) {

                while (true) {

                    Button = 0;
                    Start = false;
                    queue <int> Field_Draw;

                    cout.flush (); // ������� ������ � �������
                    Game.Preview ();
                    Game.Center ("�������� ������ ���������� ������ �������� � ������\n");
                    Game.Center ("_____________________________________________\n");
                    Game.Center ("| 1. ������ �������                         |\n");
                    Game.Center ("|-------------------------------------------|\n");
                    Game.Center ("| 2. ��������������� ����������             |\n");
                    Game.Center ("|-------------------------------------------|\n");
                    Game.Center ("| Esc. ��������� � ����                     |\n");
                    Game.Center ("|___________________________________________|\n");

                         while (true) {

                            Button = getch ();

                                if (Button == 49 || Button == 50 || Button == 27 || Button == 55)
                                    break;
                        }

                        if (Button == 27)
                            break;

                    cls;
                    Game.Preview ();

                    Game.Center ("������� ��������� �������� ��� ���������� ��������:\n\n");
                    Game.Center ("������������ ���������� ������ � ������: ");

                        while (! (cin >> Game.RabbitsCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }

                    /*cout << "\n\n";
                    Game.Center ("������������ ���������� ������ � ������: ");

                        while (! (cin >> Game.WolfsCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }*/

                    cout << "\n\n";
                    Game.Center ("��������� ���������� ����������� �������� �� �����: ");

                        while (! (cin >> Game.StartAnimalCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }

                    Rabbits Rabbit[Game.RabbitsCount]; // ������ �������� ������
                    Wolfs Wolf[Game.WolfsCount]; // ������ �������� ������

                        while (true) { // ��������� ���� ������

                                if (Start == false) { // ���� ��� ������ ������

                                    if (Button == 49) { // ������ ���������� �������� �������

                                        cls;
                                        Game.Preview();

                                        Game.Center ("������� ��������� ���������� ������������ ��� ���� ");
                                        cout << Game.RabbitsCount << " ������ � "  << Game.WolfsCount << " ������ (����� " << Game.Rows_Count << "x" << Game.Columns_Count << "):\n\n";
                                        Game.Center ("������������ ������:\n");

                                            for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.StartAnimalCount); i++) {

                                                Game.Center ("");
                                                cout << "X[" << i + 1 << "]: ";
                                                cin >> Rabbit[i].X;
                                                Game.Center ("");
                                                cout << "Y[" << i + 1 << "]: ";
                                                cin >> Rabbit[i].Y;
                                                cout << "\n";

                                            }

                                        cls;
                                        Game.Preview ();
                        // �������������� � ������
                                        /*Game.Center ("������� ��������� ���������� ������������ ��� ���� ");
                                        cout << Game.RabbitsCount << " ������ � "  << Game.WolfsCount << " ������ (����� " << Game.Rows_Count << "x" << Game.Columns_Count << "):\n\n";
                                        Game.Center ("������������ ������:\n");

                                            for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.StartAnimalCount); i++) {

                                                Game.Center ("");
                                                cout << "X[" << i + 1 << "]: ";
                                                cin >> Wolf[i].X;
                                                Game.Center ("");
                                                cout << "Y[" << i + 1 << "]: ";
                                                cin >> Wolf[i].Y;
                                                cout << "\n";
                                                Wolf[i].Life = true;

                                            }*/

                                    } // ����� ���������� �������� �������

                                    else if (Button == 50) { // ��������� ���������� ��������

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.StartAnimalCount); i++) {

                                            Rabbit[i].X = 0 + rand () % 10;
                                            Rabbit[i].Y = 0 + rand () % 10;

                                        } // ������������ ��� ������
                            // �������������� � ������
                                        /*for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.StartAnimalCount); i++) {

                                            Wolf[i].X = 0 + rand () % 10;
                                            Wolf[i].Y = 0 + rand () % 10;
                                            Wolf[i].Life = true;
                                            Wolf[i].Sex = Model->Random_Sex ();

                                        } // ������������ ��� ������*/

                                    } // ����� ���������� ���������� ��������

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.StartAnimalCount); i++) {

                                            Rabbit[i].Life = true;
                                            Rabbit[i].Sex = Model->Random_Sex ();

                                        } // ����� ���������� �������� ��� ������

                                        for (int i = 0; i < Model->N; i++) {

                                            for (int c = 0; c < Model->M; c++)
                                                Model->Field[i][c] = Void_Block;

                                        }

                                    Model->Days = 0;
                                    Start = true;

                                }
                    // ������������
                                if (Button == 55) {

                                    Rabbit[0].Life = true;
                                    Rabbit[0].Sex = false;
                                    Rabbit[0].X = 9;
                                    Rabbit[0].Y = 9;
                                    Rabbit[1].Life = true;
                                    Rabbit[1].Sex = true;
                                    Rabbit[1].X = 9;
                                    Rabbit[1].Y = 9;

                                }

                    // ������ ������ ������

                            Model->CountGrass = 0;
                            Model->HowRabbitsMan_OnMap = 0;
                            Model->HowRabbitsWoman_OnMap = 0;
                            Model->HowWolfsMan_OnMap = 0;
                            Model->HowWolfsWoman_OnMap = 0;
                            cls;
                            Model->Random_Grass ();
                            Model->Field_Clear();

                                //for (int g = 0; g < Game.RabbitsCount; g++)
                                   // Rabbit[g].HasMoved = false;

                                for (int i = 0; i < Model->N; i++) {

                                        for (int k = 0; k < Model->M; k++)
                                            cout << "     _______";

                                    cout << "\n";

                                        for (int c = 0; c < Model->M; c++) {

                                                for (int g = 0; g < Game.RabbitsCount; g++) {

                                                        if (Rabbit[g].Life == true) { // ���� ���� ��� - ����������

                                                                if (Rabbit[g].X == i && Rabbit[g].Y == c) { // ���� ���������� ����� ������������� ������ �� �����

                                                                    if (Model->Grass_Map[i][c] == true) {

                                                                        Rabbit[g].Food += 11;
                                                                        Model->Field[i][c] = Void_Block;
                                                                        Model->Grass_Map[i][c] = false; // ���� ���� - ���� ��� ������ � ������

                                                                    } // � ���� ���� �����, ����� �� ������

                                                                    if (g == 0) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true)) && (Rabbit[g].X == Rabbit[g + 1].X && Rabbit[g].Y == Rabbit[g + 1].Y)) {

                                                                            Model->Field[i][c] = Rabbit_Hare;
                                                                            continue;

                                                                        }

                                                                    } // � ����� ������ ������

                                                                    else if (g > 0 && g < Game.RabbitsCount - 1) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Rabbit[g].X == Rabbit[g + 1].X && Rabbit[g].Y == Rabbit[g + 1].Y) || (Rabbit[g].X == Rabbit[g - 1].X && Rabbit[g].Y == Rabbit[g - 1].Y))) {

                                                                            Model->Field[i][c] = Rabbit_Hare;
                                                                            continue;

                                                                        }

                                                                    }

                                                                    else if (g == Game.RabbitsCount - 1) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && (Rabbit[g].X == Rabbit[g - 1].X && Rabbit[g].Y == Rabbit[g - 1].Y)) {

                                                                            Model->Field[i][c] = Rabbit_Hare;
                                                                            continue;

                                                                        }

                                                                    } // � ����� ������ ������

                                                            // ������ ����� ���� � �������� � ����� �����

                                                                if (Model->Field[i][c] != Rabbit_Hare) { // ���� ��� ������ �� ������ ������ � ��������

                                                                    if (Rabbit[g].Sex == true) { // ���� ��� ���� �������� ����

                                                                        if (g == 0) { // ��� ����� ������ ������

                                                                            if ( (Rabbit[g].Sex == true && Rabbit[g + 1].Sex == true) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // ��� ����� � ����� �����

                                                                        else if (g > 0 && g < Game.RabbitsCount - 1) { // ��� ���� ���������

                                                                            if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // ��� ����� � ����� �����

                                                                        else if (g == Game.RabbitsCount - 1) { // ��� ����� ��������� ������

                                                                            if ( (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == true) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // ��� ����� � ����� �����

                                                                        if ( Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass) // ���� � ������ ��� ���� �����
                                                                            Model->Field[i][c] = Rabbit_Grass;

                                                                        else if (Model->Field[i][c] != Rabbit_Grass || Model->Field[i][c] == Void_Block) // ���� � ������ ��� �����
                                                                            Model->Field[i][c] = Rabbit_Block;

                                                                    } // ����� �������� ���� ������

                                                                    else if (Rabbit[g].Sex == false) { // ���� ��� ������� �������� ����

                                                                        if (g == 0) { // ��� ����� ������ ������

                                                                            if ( (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == false) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // ��� ������� � ����� �����

                                                                        else if (g > 0 && g < Game.RabbitsCount - 1) { // ��� ���� ���������

                                                                            if ( ((Rabbit[g].Sex == false && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == false)) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // ��� ������� � ����� �����

                                                                        else if (g == Game.RabbitsCount - 1) { // ��� ����� ��������� ������

                                                                            if ( (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == false) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // ��� ������� � ����� �����

                                                                        if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass) // ���� � ������ ��� ���� �����
                                                                            Model->Field[i][c] = Hare_Grass;

                                                                        else if (Model->Field[i][c] != Rabbit_Grass || Model->Field[i][c] == Void_Block) // ���� � ������ ��� �����
                                                                            Model->Field[i][c] = Hare_Block;

                                                                    } // ����� ������� �������� ����

                                                        /////////////////////////////////////// ���� �������� ����� � �������� � ����� ������

                                                                   /* if (i == 0 && c == 0) { // ��� ����� ������ ������

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                    } // ���� � �������� � ����� �����

                                                                    else if (i != 9 && c != 9) { // ��� ���� ��������� �����

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                    } // ���� � �������� � ����� �����

                                                                    else if (i == 9 && c == 9) { // ��� ����� ��������� ������

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;


                                                                    } // ���� � �������� � ����� �����

                                                        /////////////////////////////////////// ���� �������� ����� � �������� � ����� ������
                                                                    */
                                                                } // ����� ��������, ��� ���� �� ��������� � ����� ������ � ��������

                                                                } // ����� �������� ����������� ������ � �����

                                                            /*if (Rabbit[g].HasMoved == false) {

                                                                Rabbit[g].Move();
                                                                Rabbit[g].HasMoved = true;

                                                            }*/

                                                        } // ����� �������� ����� �����

                                                    } // ����� ����� �������� ������

                                        // �������������� � ������
                                            Field_Draw.push(Model->Field[i][c]);

                                                if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass || Model->Field[i][c] == Hare_Grass || Model->Field[i][c] == Wolf_Grass || Model->Field[i][c] == BitchWolf_Grass)
                                                    Model->CountGrass++;

                                        } // ����� �������� �� ��������

                                        while (!Field_Draw.empty ()) {

                                            Game.DrawBlock (Field_Draw.front ());
                                            Field_Draw.pop ();

                                        }

                                   Model->CardLegend (Game, i);
                                   cout << "\n";

                                        for (int k = 0; k < Model->M; k++)
                                            cout << "     |_____|";

                                    cout << "\n\n";


                                } // ����� �������� ����� ����

                                for (int g = 0; g < Game.RabbitsCount; g++) {

                                    if (Rabbit[g].Life == true) {

                                        if (Rabbit[g].Sex == true)
                                            Model->HowRabbitsMan_OnMap++;

                                        else if (Rabbit[g].Sex == false)
                                            Model->HowRabbitsWoman_OnMap++;

                                    Rabbit[g].Move();
                                    Rabbit[g].MaxDays -= 10;

                                        if (Rabbit[g].MaxDays <= 0)
                                            Rabbit[g].Life = false; // ������ �� ��������

                                    Rabbit[g].Food--; // ���������� ������ ���� � ���������

                                        if (Rabbit[g].Food <= 0)
                                            Rabbit[g].Life = false; // ������ �� ������

                                    }

                                } // ��������� ������ �� ���� ������, ��� ������������ ����������

                            Model->Days += 10;
                            Model->Determine_TimeOfYear ();
                            cout << "\n������ ����: " << Model->Days << "               ����� ����: " << Model->TimeOfYear << "\n\n";
                            cout << "���������� ������: " << Model->HowRabbitsMan_OnMap << "           ���������� ������: " << Model->HowWolfsMan_OnMap << "\n\n";
                            cout << "���������� ������: " << Model->HowRabbitsWoman_OnMap << "           ���������� ������: " << Model->HowWolfsWoman_OnMap << "\n\n";
                            cout << "���������� ������ � ������: " << Model->CountGrass;
                       //if (RabbitSum == 0 && RabbitGirlSum == 0 && WolfSum == 0 && WolfGirlSum == 0)
                         //   cout << "      | �����, ������� ���!";
                       /*else
                       {
                           if (RabbitSum == 0 && RabbitGirlSum == 0)
                                cout << "      | ����� ������, ����� ��������!";
                           if (WolfSum == 0 && WolfGirlSum == 0)
                                cout << "      | ����� ������, ����� ��������!";
                       }*/



                                while (true) {

                                    Button = getch ();

                                        if (Button == 27 || Button == 13)
                                            break;

                                } // ����������� / ���������� ������ ������

                                if (Button == 27)
                                    break;

                        } // ����� ���������� ����� ������

                } // ����� Button == 13

                } // ����� ������� ������

        } // ����� ���������� ����� ���������

}
