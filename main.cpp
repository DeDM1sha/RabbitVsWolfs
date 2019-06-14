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

        int N; // размерность поля - кол-во строк
        int M; // размерность поля - кол-во столбцов
        int** Field; // поле модели
        bool** Grass_Map; // расположение травы на карте
        int Days; // кол-во дней, от начала работы модели
        int CountGrass; // кол-во травы на карте
        int HowRabbitsMan_OnMap; // кол-во зайцев на карте
        int HowRabbitsWoman_OnMap; // кол-во зайчих на карте
        int HowWolfsMan_OnMap; // кол-во волков на карте
        int HowWolfsWoman_OnMap; // кол-во волчих на карте
        string TimeOfYear; // время года

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

        /*void Show_Coordinates (Animals& Object) {

            cout << "\nX: " << Object.X;
            cout << "\nY: " << Object.Y;

        }*/

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

        } // метод очистки поля

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
            SetConsoleCursorInfo (handle, &structCursorInfo); // Отключение каретки

            setlocale (LC_CTYPE, "Russian"); // Кириллица в консоли
            system ("title Зайцы против волков"); // Заголовок программы
            system ("color B"); // Светло-голубой цвет текста

        } // метод настройки приложения


        void CardLegend (GameProcess& Game, int Line) {

            unsigned short int Number = 0;
            string Str1 = "\0", Str2 = "\0";

                switch (Line) {

                    case 1: Str1 = "               Легенда карты";  Str2 = "\0";            Number = 11; break;
                    case 2: Str1 = "               **";             Str2 = " - Трава";      Number = 10; break;
                    case 3: Str1 = "               &&";             Str2 = " - Заяц";       Number = 15; break;
                    case 4: Str1 = "               &&";             Str2 = " - Зайчиха";    Number = 14; break;
                    case 5: Str1 = "               @@";             Str2 = " - Волк";       Number = 12; break;
                    case 6: Str1 = "               @@";             Str2 = " - Волчиха";    Number = 13; break;
                    default: Str1 = "\0";                           Str2 = "\0";            Number = 0;  break;

                }

            SetConsoleTextAttribute (hConsole, (WORD) ((0 << 4) | Number));
            cout << Str1;
            Game.Set_BackgroundColor ();
            cout << Str2;

        } // метод отрисовки легенды карты

        string Determine_TimeOfYear (void) {

            int DaysCount = this->Days;

                while (DaysCount > 364)
                    DaysCount -= 364;

                if (DaysCount > 336 || DaysCount < 63)
                    TimeOfYear = "Зима";

                else if (DaysCount > 62 && DaysCount < 155)
                    TimeOfYear = "Весна";

                else if (DaysCount > 154 && DaysCount < 247)
                    TimeOfYear = "Лето";

                else
                    TimeOfYear = "Осень";

            return this->TimeOfYear;

        } // метод, определяющий месяц года

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


        } // метод рандомизации роста травы на карте

        bool Random_Sex (void) {

            unsigned short int Number = 0 + rand () % 101;

                if (Number < 50)
                    return false;

            return true;

        } // метод рандомизации пола животного

        int Random_Reproduction (string Animal) {

            unsigned short int Number = 0 + rand () % 101;

                if (Animal == "Rabbit") {

                    if (Number >= 0 && Number <= 20)
                        return 1;

                    else if (Number >= 21 && Number <= 40)
                        return 2;

                    else if (Number >= 41 && Number <= 60)
                        return 3;

                    else if (Number >= 61 && Number <= 80)
                        return 4;

                    else if (Number >= 81 && Number <= 100)
                        return 5;

                } // для зайцев - от 1 до 5 особей

                else if (Animal == "Wolf") {

                    if (Number >= 0 && Number <= 33)
                        return 1;

                    else if (Number >= 34 && Number <= 66)
                        return 2;

                    else if (Number >= 67 && Number <= 100)
                        return 3;

                } // для волков - от 1 до 5 особей

            return 0;

        } // метод рандомизации кол-ва особей при рождении

}; // класс модели

int Minimum_Count (int& DefaultCount, int& StartCount) {

        if (DefaultCount < StartCount)
            return DefaultCount;

    return StartCount;

} // функция, возвращающая минимальное значение среди RabbitsCount / WolfsCount и StartAnimalCount соответствено

int main (void) {

    GameProcess Game;
    ModelProcess* Model;
    Model = new ModelProcess (Game.Rows_Count, Game.Columns_Count);

    Model->Default_Settings ();

    unsigned short int Button = 0; // нажатая кнопка
    bool Start = false; // первый запуск модели с новыми входными параметрами
    int Counter = 0; // счетчик для родов

        while (true) { // жизненный цикл программы

            Game.Preview ();
            Game.Center("_________________________________________\n");
            Game.Center("| Enter. Запуск биологической модели     |\n");
            Game.Center("|----------------------------------------|\n");
            Game.Center("| Esc. Выход из программы                |\n");
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
                    queue <int> Rabbit_Reproduction;
                    queue <int> Wolf_Reproduction;

                    cout.flush (); // очистка буфера в консоли
                    Game.Preview ();
                    Game.Center ("Выберите способ размещения первых животных в модели\n");
                    Game.Center ("_____________________________________________\n");
                    Game.Center ("| 1. Задать вручную                         |\n");
                    Game.Center ("|-------------------------------------------|\n");
                    Game.Center ("| 2. Рандомизировать размещение             |\n");
                    Game.Center ("|-------------------------------------------|\n");
                    Game.Center ("| Esc. Вернуться в меню                     |\n");
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

                    Game.Center ("Задайте начальные значения для размещения животных:\n\n");
                    Game.Center ("Максимальное количество зайцев в модели: ");

                        while (! (cin >> Game.RabbitsCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }

                    /*cout << "\n\n";
                    Game.Center ("Максимальное количество волков в модели: ");

                        while (! (cin >> Game.WolfsCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }*/

                    cout << "\n\n";
                    Game.Center ("Стартовое количество разнотипных животных на карте: ");

                        while (! (cin >> Game.StartAnimalCount) || (cin.peek() != '\n')) {

                            cin.clear();

                                while (cin.get() != '\n');
                                    Game.Center(": ");

                        }

                    Rabbits Rabbit[Game.RabbitsCount]; // массив объектов зайцев
                    Wolfs Wolf[Game.WolfsCount]; // массив объектов волков

                        while (true) { // жизненный цикл модели

                                if (Start == false) { // если это первый запуск

                                    if (Button == 49) { // начало размещения животных вручную

                                        cls;
                                        Game.Preview();

                                        Game.Center ("Задайте начальные координаты расположения для всех ");
                                        cout << Game.RabbitsCount << " зайцев и "  << Game.WolfsCount << " волков (карта " << Game.Rows_Count << "x" << Game.Columns_Count << "):\n\n";
                                        Game.Center ("Расположение зайцев:\n");

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
                        // перекопировать с зайцев
                                        /*Game.Center ("Задайте начальные координаты расположения для всех ");
                                        cout << Game.RabbitsCount << " зайцев и "  << Game.WolfsCount << " волков (карта " << Game.Rows_Count << "x" << Game.Columns_Count << "):\n\n";
                                        Game.Center ("Расположение волков:\n");

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

                                    } // конец размещения животных вручную

                                    else if (Button == 50) { // рандомное размещение животных

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.StartAnimalCount); i++) {

                                            Rabbit[i].X = 0 + rand () % 10;
                                            Rabbit[i].Y = 0 + rand () % 10;

                                        } // рандомизация для зайцев
                            // перекопировать с зайцев
                                        /*for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.StartAnimalCount); i++) {

                                            Wolf[i].X = 0 + rand () % 10;
                                            Wolf[i].Y = 0 + rand () % 10;
                                            Wolf[i].Life = true;
                                            Wolf[i].Sex = Model->Random_Sex ();

                                        } // рандомизация для волков*/

                                    } // конец рандомного размещения животных

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.StartAnimalCount); i++) {

                                            Rabbit[i].Life = true;
                                            Rabbit[i].Sex = Model->Random_Sex ();

                                        } // общие страртовые значения для зайцев

                                        for (int i = 0; i < Model->N; i++) {

                                            for (int c = 0; c < Model->M; c++)
                                                Model->Field[i][c] = Void_Block;

                                        }

                                    Model->Days = 0;
                                    Start = true;

                                }
                    // тестирование
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

                    // начало работы модели

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

                                                        if (Rabbit[g].Life == true) { // если заяц жив - существует

                                                                if (Rabbit[g].X == i && Rabbit[g].Y == c) { // если координата зайца соответствует ячейке на карте

                                                                    if (Model->Grass_Map[i][c] == true) {

                                                                        Rabbit[g].Food += 11;
                                                                        Model->Field[i][c] = Void_Block;
                                                                        Model->Grass_Map[i][c] = false; // один заяц - есть всю клетку с травой

                                                                    } // в блок есть трава, зайцы ее съедят

                                                                    if (g == 0) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true)) && (Rabbit[g].X == Rabbit[g + 1].X && Rabbit[g].Y == Rabbit[g + 1].Y)) {

                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                        }

                                                                    } // в самой первой ячейке

                                                                    else if (g > 0 && g < Game.RabbitsCount - 1) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Rabbit[g].X == Rabbit[g + 1].X && Rabbit[g].Y == Rabbit[g + 1].Y) || (Rabbit[g].X == Rabbit[g - 1].X && Rabbit[g].Y == Rabbit[g - 1].Y))) {

                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                        }

                                                                    }

                                                                    else if (g == Game.RabbitsCount - 1) {

                                                                        if (((Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && (Rabbit[g].X == Rabbit[g - 1].X && Rabbit[g].Y == Rabbit[g - 1].Y)) {

                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                        }

                                                                    } // в самой первой ячейке

                                                            // случай когда заяц с зайяихой в одном блоке

                                                                if (Model->Field[i][c] == Rabbit_Hare) {

                                                                        if (Counter > 0)
                                                                            Counter--;

                                                                        else if (Model->TimeOfYear != "Зима") { // зимой размножения не будет

                                                                            Counter = 10;

                                                                                for (int k = 0; k < Model->Random_Reproduction("Rabbit"); k++) {

                                                                                    Rabbit_Reproduction.push(Rabbit[g].X);
                                                                                    Rabbit_Reproduction.push(Rabbit[g].Y);

                                                                                }

                                                                        }

                                                                    continue;

                                                                } // раз заяц в клетке с зайчихой, значит будут размножаться

                                                                else if (Model->Field[i][c] != Rabbit_Hare) { // если эта клетка не занята зайцем и зайчихой

                                                                    if (Rabbit[g].Sex == true) { // если это заяц мужского пола

                                                                        if (g == 0) { // для самой первой ячейки

                                                                            if ( (Rabbit[g].Sex == true && Rabbit[g + 1].Sex == true) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // два зайца в одном блоке

                                                                        else if (g > 0 && g < Game.RabbitsCount - 1) { // для всех остальных

                                                                            if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // два зайца в одном блоке

                                                                        else if (g == Game.RabbitsCount - 1) { // для самой последней ячейки

                                                                            if ( (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == true) && ((Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Rabbit)) ) {

                                                                                Model->Field[i][c] = Rabbit_Rabbit;
                                                                                continue;

                                                                            }

                                                                        } // два зайца в одном блоке

                                                                        if ( Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass) // если в ячейке уже есть трава
                                                                            Model->Field[i][c] = Rabbit_Grass;

                                                                        else if (Model->Field[i][c] != Rabbit_Grass || Model->Field[i][c] == Void_Block) // если в ячейке нет травы
                                                                            Model->Field[i][c] = Rabbit_Block;

                                                                    } // конец мужского пола зайцев

                                                                    else if (Rabbit[g].Sex == false) { // если это зайчиха женского пола

                                                                        if (g == 0) { // для самой первой ячейки

                                                                            if ( (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == false) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // две зайчихи в одном блоке

                                                                        else if (g > 0 && g < Game.RabbitsCount - 1) { // для всех остальных

                                                                            if ( ((Rabbit[g].Sex == false && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == false)) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // две зайчихи в одном блоке

                                                                        else if (g == Game.RabbitsCount - 1) { // для самой последней ячейки

                                                                            if ( (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == false) && ((Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Hare)) ) {

                                                                                Model->Field[i][c] = Hare_Hare;
                                                                                continue;

                                                                            }

                                                                        } // две зайчихи в одном блоке

                                                                        if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass) // если в ячейке уже есть трава
                                                                            Model->Field[i][c] = Hare_Grass;

                                                                        else if (Model->Field[i][c] != Rabbit_Grass || Model->Field[i][c] == Void_Block) // если в ячейке нет травы
                                                                            Model->Field[i][c] = Hare_Block;

                                                                    } // конец зайчихи женского пола

                                                        /////////////////////////////////////// блок проверки зайца с зайчихой в одной клетке

                                                                   /* if (i == 0 && c == 0) { // для самой первой ячейки

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                    } // заяц с зайчихой в одном блоке

                                                                    else if (i != 9 && c != 9) { // для всех остальных ячеек

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g + 1].Sex == false) || (Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g + 1].Sex == true) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;

                                                                    } // заяц с зайчихой в одном блоке

                                                                    else if (i == 9 && c == 9) { // для самой последней ячейки

                                                                        if ( ((Rabbit[g].Sex == true && Rabbit[g - 1].Sex == false) || (Rabbit[g].Sex == false && Rabbit[g - 1].Sex == true)) && ((Model->Field[i][c] == Rabbit_Grass) || (Model->Field[i][c] == Rabbit_Block) || (Model->Field[i][c] == Rabbit_Rabbit) || (Model->Field[i][c] == Hare_Grass) || (Model->Field[i][c] == Hare_Block) || (Model->Field[i][c] == Rabbit_Hare) || (Model->Field[i][c] == Hare_Hare)) )
                                                                            Model->Field[i][c] = Rabbit_Hare;


                                                                    } // заяц с зайчихой в одном блоке

                                                        /////////////////////////////////////// блок проверки зайца с зайчихой в одной клетке
                                                                    */
                                                                } // конец проверки, что заяц не находится в одной клетке с зайчихой

                                                                } // конец проверки координатов зайцев с полем

                                                            /*if (Rabbit[g].HasMoved == false) {

                                                                Rabbit[g].Move();
                                                                Rabbit[g].HasMoved = true;

                                                            }*/

                                                        } // конец проверки жизни зайца

                                                    } // конец цикла перебора зайцев

                                        // перекопировать с зайцев
                                            Field_Draw.push(Model->Field[i][c]);

                                                if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass || Model->Field[i][c] == Hare_Grass || Model->Field[i][c] == Wolf_Grass || Model->Field[i][c] == BitchWolf_Grass)
                                                    Model->CountGrass++;

                                        } // конец просчета по столбцам

                                        while (!Field_Draw.empty ()) {

                                            Game.DrawBlock (Field_Draw.front ());
                                            Field_Draw.pop ();

                                        }

                                   Model->CardLegend (Game, i);
                                   cout << "\n";

                                        for (int k = 0; k < Model->M; k++)
                                            cout << "     |_____|";

                                    cout << "\n\n";


                                } // конец просчета всего поля

                                for (int g = 0; g < Game.RabbitsCount; g++) {

                                    if (Rabbit[g].Life == true) {

                                        if (Rabbit[g].Sex == true)
                                            Model->HowRabbitsMan_OnMap++;

                                        else if (Rabbit[g].Sex == false)
                                            Model->HowRabbitsWoman_OnMap++;

                                    Rabbit[g].Move();
                                    Rabbit[g].MaxDays -= 10;

                                        if (Rabbit[g].MaxDays <= 0)
                                            Rabbit[g].Life = false; // смерть от старости

                                    Rabbit[g].Food--; // уменьшение запаса пищи в организме

                                        if (Rabbit[g].Food <= 0)
                                            Rabbit[g].Life = false; // смерть от голода

                                    }

                                    else if (Rabbit[g].Life != true && !Rabbit_Reproduction.empty()) {

                                        Rabbit[g].Life = true;
                                        Rabbit[g].Sex = Model->Random_Sex ();
                                        Rabbit[g].X = Rabbit_Reproduction.front ();
                                        Rabbit_Reproduction.pop ();
                                        Rabbit[g].Y = Rabbit_Reproduction.front ();
                                        Rabbit_Reproduction.pop ();
                                        Rabbit[g].Food = 30;
                                        Rabbit[g].MaxDays = 2200;

                                    }

                                } // повторный проход по всем зайцам, для произведения вычислений

                            Model->Days += 10;
                            Model->Determine_TimeOfYear ();
                            cout << "\nПрошло дней: " << Model->Days << "               Время года: " << Model->TimeOfYear << "\n\n";
                            cout << "Количество зайцев: " << Model->HowRabbitsMan_OnMap << "           Количество волков: " << Model->HowWolfsMan_OnMap << "\n\n";
                            cout << "Количество зайчих: " << Model->HowRabbitsWoman_OnMap << "           Количество волчих: " << Model->HowWolfsWoman_OnMap << "\n\n";
                            cout << "Количество блоков с травой: " << Model->CountGrass;
                       //if (RabbitSum == 0 && RabbitGirlSum == 0 && WolfSum == 0 && WolfGirlSum == 0)
                         //   cout << "      | Ничья, погибли все!";
                       /*else
                       {
                           if (RabbitSum == 0 && RabbitGirlSum == 0)
                                cout << "      | Зайцы умерли, волки победили!";
                           if (WolfSum == 0 && WolfGirlSum == 0)
                                cout << "      | Волки умерли, зайцы победили!";
                       }*/



                                while (true) {

                                    Button = getch ();

                                        if (Button == 27 || Button == 13)
                                            break;

                                } // продолжение / завершение работы модели

                                if (Button == 27)
                                    break;

                        } // конец жизненного цикла модели

                } // конец Button == 13

                } // конец запуска модели

        } // конец жизненного цикла программы

}
