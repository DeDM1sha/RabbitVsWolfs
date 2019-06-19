#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <queue>
#include <iomanip>
#include <sstream>
#include <fstream>

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

string Int_To_String (int Number) {

    ostringstream NumToString;
    NumToString << Number;

    return NumToString.str();

} // функция перевода из int в string

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

                    case 0: Str1 = "               Легенда карты";  Str2 = "\0";            Number = 11; break;
                    case 1: Str1 = "               **";             Str2 = " - Трава";      Number = 10; break;
                    case 2: Str1 = "               &&";             Str2 = " - Заяц";       Number = 15; break;
                    case 3: Str1 = "               &&";             Str2 = " - Зайчиха";    Number = 14; break;
                    case 4: Str1 = "               @@";             Str2 = " - Волк";       Number = 12; break;
                    case 5: Str1 = "               @@";             Str2 = " - Волчиха";    Number = 13; break;
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

                            if (Number > 90)
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

                    if (Number >= 0 && Number <= 33)
                        return 1;

                    else if (Number >= 34 && Number <= 66)
                        return 2;

                    else if (Number >= 67 && Number <= 100)
                        return 3;

                } // для зайцев - от 1 до 5 особей

                else if (Animal == "Wolf") {

                    if (Number >= 0 && Number <= 50)
                        return 1;

                    else if (Number >= 51 && Number <= 100)
                        return 2;

                } // для волков - от 1 до 5 особей

            return 0;

        } // метод рандомизации кол-ва особей при рождении

        int Data_Input (GameProcess& Game, string TypeDate) {

            int Number = 0; // вводимое число
            int LeftLimit = -1; // левая граница отрезка (левый предел)
            int RightLimit = 0; // правая граница отрезка (правый предел)

                if (TypeDate == "StartCount")
                    RightLimit = 1001;

                else if (TypeDate == "Coordinates")
                    RightLimit = 10;

                        while (true) {

                            while (! (cin >> Number) || (cin.peek() != '\n')) {

                                cin.clear();

                                    while (cin.get() != '\n');
                                        Game.Center(": ");

                            }

                            if (Number > LeftLimit && Number < RightLimit)
                                break;

                            else {

                                Game.Center(": ");
                                cout << "Введите значение в диапазоне от " << LeftLimit + 1 << " до " << RightLimit - 1 << ": ";

                            }

                        }

            return Number;

        } // метод для корректного ввода данных

}; // класс модели

class ModelLogs {

    public:

        string Event_A; // первое событие - скрещивание волков
        string Event_B; // второе событие - скрещивание зайцев
        string Event_C; // третье событие - поедание волком зайца
        int CountEvents_A; // кол-во первых событий
        int CountEvents_B; // кол-во вторых событий
        int CountEvents_C; // кол-во третих событий

        ModelLogs (void) {

        	ClearEvents ();

        	ofstream Write_CountRabbits ("Rabbits.txt");
        	Write_CountRabbits << "\0";
        	Write_CountRabbits.close ();

        	ofstream Write_CountWolfs ("Wolfs.txt");
        	Write_CountWolfs << "\0";
        	Write_CountWolfs.close ();

        	ofstream Write_CountGrass ("Grass.txt");
        	Write_CountGrass << "\0";
        	Write_CountGrass.close ();

        }

        ~ModelLogs (void) {}

        void ClearEvents (void) {

        	Event_A = "\0";
        	Event_B = "\0";
        	Event_C = "\0";
        	CountEvents_A = 0;
        	CountEvents_B = 0;
        	CountEvents_C = 0;

        } // очистка значений

        void Show_Events (GameProcess& Game, int Line) {

            unsigned short int Number = 0;
            string Str1 = "\0", Str2 = "\0";

                if (CountEvents_A > 0 || CountEvents_B > 0 || CountEvents_C > 0) {

                    switch (Line) {

                        case 6: Str1 = "                 События:";  Str2 = "\0";            Number = 11; break;
                        case 7: Str1 = "       "; Str2 = Event_A; Number = 15; break;
                        case 8: Str1 = "       "; Str2 = Event_B; Number = 15; break;
                        case 9: Str1 = "       "; Str2 = Event_C; Number = 15; break;
                        default: Str1 = "\0";                           Str2 = "\0";            Number = 0;  break;

                    }

                    SetConsoleTextAttribute (hConsole, (WORD) ((0 << 4) | Number));
                    cout << Str1;
                    cout << Str2;
                    Game.Set_BackgroundColor ();

                }

        } // метод отображения событий

        void Save_Logs_Output (ModelProcess& Model) {

            ofstream Write_CountRabbits ("Rabbits.txt", ios::app);
        	Write_CountRabbits << Model.HowRabbitsMan_OnMap + Model.HowRabbitsWoman_OnMap << "\n";
        	Write_CountRabbits.close ();

        	ofstream Write_CountWolfs ("Wolfs.txt", ios::app);
        	Write_CountWolfs << Model.HowWolfsMan_OnMap + Model.HowWolfsWoman_OnMap << "\n";;
        	Write_CountWolfs.close ();

        	ofstream Write_CountGrass ("Grass.txt", ios::app);
        	Write_CountGrass << Model.CountGrass << "\n";
        	Write_CountGrass.close ();

        } // сохранение данных модели во внешний файл


}; // класс логов модели

int Minimum_Count (int& DefaultCount, int& StartCount) {

        if (DefaultCount < StartCount)
            return DefaultCount;

    return StartCount;

} // функция, возвращающая минимальное значение среди RabbitsCount / WolfsCount и StartAnimalCount соответствено

int main (void) {

    GameProcess Game;
    ModelProcess* Model = new ModelProcess (Game.Rows_Count, Game.Columns_Count);
    ModelLogs Log;

    Model->Default_Settings ();

    unsigned short int Button = 0; // нажатая кнопка
    bool Start = false; // первый запуск модели с новыми входными параметрами

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
                            free (Model);
                            exit (0);

                        }

                        else if (Button == 13)
                            break;

                }

                if (Button == 13) {

                while (true) {

                    Button = 0;
                    Start = false;
                    queue <int> Field_Draw; // очередь на отрисовку поля
                    queue <int> Rabbit_Reproduction; // очередь на размножение зайцев
                    queue <int> Wolf_Reproduction; // очередь на размножение волков

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
                    Game.RabbitsCount = Model->Data_Input (Game, "StartCount");
                    cout << "\n\n";

                    Game.Center ("Максимальное количество волков в модели: ");
                    Game.WolfsCount = Model->Data_Input (Game, "StartCount");
                    cout << "\n\n";

                    Game.Center ("Стартовое количество зайцев на карте: ");
                    Game.Rabbit_StartCount = Model->Data_Input (Game, "StartCount");
                    cout << "\n\n";

                    Game.Center ("Стартовое количество волков на карте: ");
                    Game.Wolf_StartCount = Model->Data_Input (Game, "StartCount");

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

                                            for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.Rabbit_StartCount); i++) {

                                                Game.Center ("");
                                                cout << "X[" << i + 1 << "]: ";
                                                Rabbit[i].X = Model->Data_Input (Game, "Coordinates");

                                                Game.Center ("");
                                                cout << "Y[" << i + 1 << "]: ";
                                                Rabbit[i].Y = Model->Data_Input (Game, "Coordinates");
                                                cout << "\n";

                                            }

                                        cls;
                                        Game.Preview ();

                                        Game.Center ("Расположение волков:\n");

                                            for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.Wolf_StartCount); i++) {

                                                Game.Center ("");
                                                cout << "X[" << i + 1 << "]: ";
                                                Wolf[i].X = Model->Data_Input (Game, "Coordinates");

                                                Game.Center ("");
                                                cout << "Y[" << i + 1 << "]: ";
                                                Wolf[i].Y = Model->Data_Input (Game, "Coordinates");
                                                cout << "\n";

                                            }

                                    } // конец размещения животных вручную

                                    else if (Button == 50) { // рандомное размещение животных

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.Rabbit_StartCount); i++) {

                                            Rabbit[i].X = 0 + rand () % 10;
                                            Rabbit[i].Y = 0 + rand () % 10;

                                        } // рандомизация для зайцев

                                        for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.Wolf_StartCount); i++) {

                                            Wolf[i].X = 0 + rand () % 10;
                                            Wolf[i].Y = 0 + rand () % 10;

                                        } // рандомизация для волков

                                    } // конец рандомного размещения животных

                                        for (int i = 0; i < Minimum_Count(Game.RabbitsCount, Game.Rabbit_StartCount); i++) {

                                            Rabbit[i].Life = true;
                                            Rabbit[i].Sex = Model->Random_Sex ();

                                        } // общие стартовые значения для зайцев

                                        for (int i = 0; i < Minimum_Count(Game.WolfsCount, Game.Wolf_StartCount); i++) {

                                            Wolf[i].Life = true;
                                            Wolf[i].Sex = Model->Random_Sex ();


                                        } // общие стартовые значения для волков

                                        for (int i = 0; i < Model->N; i++) {

                                            for (int c = 0; c < Model->M; c++)
                                                Model->Field[i][c] = Void_Block;

                                        }

                                    Model->Days = 100; // старт дней с весны
                                    Game.Rabbit_Breeding = true;
                                    Game.Wolf_Breeding = true;
                                    Start = true;

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
                            Log.ClearEvents ();

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

                                                                        if (Model->TimeOfYear != "Зима" && Rabbit[g].Food > 5 && (Rabbit[g].MaxDays > 10 && Rabbit[g].MaxDays < 2100)) { // зимой размножения не будет

                                                                             for (int k = 0; k < Model->Random_Reproduction("Rabbit"); k++) {

                                                                                    Rabbit_Reproduction.push(Rabbit[g].X);
                                                                                    Rabbit_Reproduction.push(Rabbit[g].Y);

                                                                                }

                                                                            Log.Event_B = "Скрещевание зайцев в ячейке [" + Int_To_String(Rabbit[g].X + 1) + "][" + Int_To_String(Rabbit[g].Y + 1) + "]";
                                                                            Log.CountEvents_B++;

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

                                                                } // конец проверки, что заяц не находится в одной клетке с зайчихой

                                                                } // конец проверки координатов зайцев с полем

                                                        } // конец проверки жизни зайца

                                                    } // конец цикла перебора зайцев

                                ////////////////////////////////////////////////////////////

                                                for (int g = 0; g < Game.WolfsCount; g++) {

                                                        if (Wolf[g].Life == true) { // если волк жив - существует

                                                                if (Wolf[g].X == i && Wolf[g].Y == c) { // если координата зайца соответствует ячейке на карте

                                                                        if ((Model->Field[i][c] == Rabbit_Grass || Model->Field[i][c] == Rabbit_Block || Model->Field[i][c] == Rabbit_Hare || Model->Field[i][c] == Rabbit_Rabbit) && (Wolf[g].X == Rabbit[g].X && Wolf[g].Y == Rabbit[g].Y)) {

                                                                                if (Wolf[g].Sex == true)
                                                                                    Model->Field[i][c] = Wolf_Rabbit;

                                                                                else if (Wolf[g].Sex == false)
                                                                                    Model->Field[i][c] = BitchWolf_Rabbit;

                                                                            Rabbit[g].Life = false; // зайца съедают
                                                                            Wolf[g].Food += 20; // волк кушает
                                                                            Log.Event_C = "Волк съел зайца в ячейке [" + Int_To_String(Wolf[g].X + 1) + "][" + Int_To_String(Wolf[g].Y + 1) + "]";
                                                                            Log.CountEvents_C++;

                                                                        }

                                                                        else if ((Model->Field[i][c] == Hare_Grass || Model->Field[i][c] == Hare_Block || Model->Field[i][c] == Hare_Hare) && (Wolf[g].X == Rabbit[g].X && Wolf[g].Y == Rabbit[g].Y)) {

                                                                            if (Wolf[g].Sex == true)
                                                                                    Model->Field[i][c] = Wolf_Hare;

                                                                                else if (Wolf[g].Sex == false)
                                                                                    Model->Field[i][c] = BitchWolf_Hare;

                                                                            Rabbit[g].Life = false; // зайца съедают
                                                                            Wolf[g].Food += 20; // волк кушает
                                                                            Log.Event_C = "Волк съел зайца в ячейке [" + Int_To_String(Wolf[g].X + 1) + "][" + Int_To_String(Wolf[g].Y + 1) + "]";
                                                                            Log.CountEvents_C++;


                                                                        }

                                                                     // волк с зайцем - в одной клетке

                                                                if (Model->Field[i][c] != Wolf_Rabbit && Model->Field[i][c] != Wolf_Hare && Model->Field[i][c] != BitchWolf_Rabbit && Model->Field[i][c] != BitchWolf_Hare) {

                                                                    if (g == 0) {

                                                                        if (((Wolf[g].Sex == true && Wolf[g + 1].Sex == false) || (Wolf[g].Sex == false && Wolf[g + 1].Sex == true)) && (Wolf[g].X == Wolf[g + 1].X && Wolf[g].Y == Wolf[g + 1].Y)) {

                                                                            Model->Field[i][c] = Wolf_BitchWolf;

                                                                        }

                                                                    } // в самой первой ячейке

                                                                    else if (g > 0 && g < Game.WolfsCount - 1) {

                                                                        if (((Wolf[g].Sex == true && Wolf[g + 1].Sex == false) || (Wolf[g].Sex == false && Wolf[g + 1].Sex == true) || (Wolf[g].Sex == true && Wolf[g - 1].Sex == false) || (Wolf[g].Sex == false && Wolf[g - 1].Sex == true)) && ((Wolf[g].X == Wolf[g + 1].X && Wolf[g].Y == Wolf[g + 1].Y) || (Wolf[g].X == Wolf[g - 1].X && Wolf[g].Y == Wolf[g - 1].Y))) {

                                                                            Model->Field[i][c] = Wolf_BitchWolf;

                                                                        }

                                                                    }

                                                                    else if (g == Game.WolfsCount - 1) {

                                                                        if (((Wolf[g].Sex == true && Wolf[g - 1].Sex == false) || (Wolf[g].Sex == false && Wolf[g - 1].Sex == true)) && (Wolf[g].X == Wolf[g - 1].X && Wolf[g].Y == Wolf[g - 1].Y)) {

                                                                            Model->Field[i][c] = Wolf_BitchWolf;

                                                                        }

                                                                    } // в самой первой ячейке

                                                            // случай когда волк с волчихой в одном блоке

                                                                    if (Model->Field[i][c] == Wolf_BitchWolf) {

                                                                        if (Model->TimeOfYear != "Зима" && Wolf[g].Food > 15 && (Wolf[g].MaxDays > 500 && Wolf[g].MaxDays < 3600)) { // зимой размножения не будет

                                                                                for (int k = 0; k < Model->Random_Reproduction("Wolf"); k++) {

                                                                                        Wolf_Reproduction.push(Wolf[g].X);
                                                                                        Wolf_Reproduction.push(Wolf[g].Y);

                                                                                }

                                                                                Log.Event_A = "Скрещевание волков в ячейке [" + Int_To_String(Wolf[g].X + 1) + "][" + Int_To_String(Wolf[g].Y + 1) + "]";
                                                                                Log.CountEvents_A++;

                                                                            }

                                                                        continue;

                                                                    } // раз волк в клетке с волчихой, значит будут размножаться

                                                                    else if (Model->Field[i][c] != Wolf_BitchWolf) { // если эта клетка не занята волком и волчихой

                                                                        if (Wolf[g].Sex == true) { // если это волк мужского пола

                                                                            if (g == 0) { // для самой первой ячейки

                                                                                if ( (Wolf[g].Sex == true && Wolf[g + 1].Sex == true) && ((Model->Field[i][c] == Wolf_Block) || (Model->Field[i][c] == Wolf_Grass) || (Model->Field[i][c] == Wolf_Wolf)) ) {

                                                                                    Model->Field[i][c] = Wolf_Wolf;
                                                                                    continue;

                                                                                }

                                                                            } // два волка в одном блоке

                                                                            else if (g > 0 && g < Game.WolfsCount - 1) { // для всех остальных

                                                                                if ( ((Wolf[g].Sex == true && Wolf[g + 1].Sex == true) || (Wolf[g].Sex == true && Wolf[g - 1].Sex == true)) && ((Model->Field[i][c] == Wolf_Block) || (Model->Field[i][c] == Wolf_Grass) || (Model->Field[i][c] == Wolf_Wolf)) ) {

                                                                                    Model->Field[i][c] = Wolf_Wolf;
                                                                                    continue;

                                                                                }

                                                                            } // два волка в одном блоке

                                                                            else if (g == Game.WolfsCount - 1) { // для самой последней ячейки

                                                                                if ( (Wolf[g].Sex == true && Wolf[g - 1].Sex == true) && ((Model->Field[i][c] == Wolf_Block) || (Model->Field[i][c] == Wolf_Grass) || (Model->Field[i][c] == Wolf_Wolf)) ) {

                                                                                    Model->Field[i][c] = Wolf_Wolf;
                                                                                    continue;

                                                                                }

                                                                            } // два волка в одном блоке

                                                                            if ( Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Wolf_Grass) // если в ячейке уже есть трава
                                                                                Model->Field[i][c] = Wolf_Grass;

                                                                            else if (Model->Field[i][c] != Wolf_Grass || Model->Field[i][c] == Void_Block) // если в ячейке нет травы
                                                                                Model->Field[i][c] = Wolf_Block;

                                                                        } // конец мужского пола волка

                                                                        else if (Wolf[g].Sex == false) { // если это волчихи женского пола

                                                                            if (g == 0) { // для самой первой ячейки

                                                                                if ( (Wolf[g].Sex == false && Wolf[g + 1].Sex == false) && ((Model->Field[i][c] == BitchWolf_Block) || (Model->Field[i][c] == BitchWolf_Grass) || (Model->Field[i][c] == BitchWolf_BitchWolf)) ) {

                                                                                    Model->Field[i][c] = BitchWolf_BitchWolf;
                                                                                    continue;

                                                                                }

                                                                            } // две волчихи в одном блоке

                                                                            else if (g > 0 && g < Game.WolfsCount - 1) { // для всех остальных

                                                                                if ( ((Wolf[g].Sex == false && Wolf[g + 1].Sex == false) || (Wolf[g].Sex == false && Wolf[g - 1].Sex == false)) && ((Model->Field[i][c] == BitchWolf_Block) || (Model->Field[i][c] == BitchWolf_Grass) || (Model->Field[i][c] == BitchWolf_BitchWolf)) ) {

                                                                                    Model->Field[i][c] = BitchWolf_BitchWolf;
                                                                                    continue;

                                                                                }

                                                                            } // две волчихи в одном блоке

                                                                            else if (g == Game.WolfsCount - 1) { // для самой последней ячейки

                                                                                if ( (Wolf[g].Sex == false && Wolf[g - 1].Sex == false) && ((Model->Field[i][c] == BitchWolf_Block) || (Model->Field[i][c] == BitchWolf_Grass) || (Model->Field[i][c] == BitchWolf_BitchWolf)) ) {

                                                                                    Model->Field[i][c] = BitchWolf_BitchWolf;
                                                                                    continue;

                                                                                }

                                                                            } // две волчихи в одном блоке

                                                                            if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Wolf_Grass) // если в ячейке уже есть трава
                                                                                Model->Field[i][c] = BitchWolf_Grass;

                                                                            else if (Model->Field[i][c] != Wolf_Grass || Model->Field[i][c] == Void_Block) // если в ячейке нет травы
                                                                                Model->Field[i][c] = BitchWolf_Block;

                                                                        } // конец волчихи женского пола

                                                                    } // конец проверки, что волк не находится в одной клетке с волчихой

                                                                } // конец проверки, что это не блок волков с зайцем

                                                            } // конец проверки координатов волков с полем

                                                        } // конец проверки жизни волков

                                                    } // конец цикла перебора волков

                                                ////////////////////////////////////////////////////////////

                                            Field_Draw.push(Model->Field[i][c]);

                                                if (Model->Field[i][c] == Grass_Block || Model->Field[i][c] == Rabbit_Grass || Model->Field[i][c] == Hare_Grass || Model->Field[i][c] == Wolf_Grass || Model->Field[i][c] == BitchWolf_Grass)
                                                    Model->CountGrass++;

                                        } // конец просчета по столбцам

                                        while (!Field_Draw.empty ()) {

                                            Game.DrawBlock (Field_Draw.front ());
                                            Field_Draw.pop ();

                                        }

                                   Model->CardLegend (Game, i);
                                   Log.Show_Events (Game, i);
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

                                    else if (Game.Rabbit_Breeding == true && Rabbit[g].Life != true && !Rabbit_Reproduction.empty()) {

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

                                for (int g = 0; g < Game.WolfsCount; g++) {

                                    if (Wolf[g].Life == true) {

                                            if (Wolf[g].Sex == true)
                                                Model->HowWolfsMan_OnMap++;

                                            else if (Wolf[g].Sex == false)
                                                Model->HowWolfsWoman_OnMap++;

                                        Wolf[g].Move();
                                        Wolf[g].Move();
                                        Wolf[g].Move();
                                        Wolf[g].MaxDays -= 10;

                                            if (Wolf[g].MaxDays <= 0)
                                                Wolf[g].Life = false; // смерть от старости

                                        Wolf[g].Food -= 1; // уменьшение запаса пищи в организме

                                            if (Wolf[g].Food <= 0)
                                                Wolf[g].Life = false; // смерть от голода

                                    }

                                    else if (Game.Wolf_Breeding == true && Wolf[g].Life != true && !Wolf_Reproduction.empty()) {

                                        Wolf[g].Life = true;
                                        Wolf[g].Sex = Model->Random_Sex ();
                                        Wolf[g].X = Wolf_Reproduction.front ();
                                        Wolf_Reproduction.pop ();
                                        Wolf[g].Y = Wolf_Reproduction.front ();
                                        Wolf_Reproduction.pop ();
                                        Wolf[g].Food = 50;
                                        Wolf[g].MaxDays = 3700;

                                    }

                                } // повторный проход по всем волкам, для произведения вычислений

                            Log.Save_Logs_Output (*Model);

                            Model->Days += 10;
                            Model->Determine_TimeOfYear ();
                            cout << "\nПрошло дней: " << Model->Days - 100 << setw (10) << "           Время года: " << Model->TimeOfYear << "\n\n";
                            cout << "Количество зайцев: " << Model->HowRabbitsMan_OnMap << setw (10) << "      Количество волков: " << Model->HowWolfsMan_OnMap << "\n\n";
                            cout << "Количество зайчих: " << Model->HowRabbitsWoman_OnMap << setw (10) << "      Количество волчих: " << Model->HowWolfsWoman_OnMap << "\n\n";
                            cout << "Количество блоков с травой: " << Model->CountGrass;

                                if (Model->HowRabbitsMan_OnMap == 0 && Model->HowRabbitsWoman_OnMap == 0 && Model->HowWolfsMan_OnMap == 0 && Model->HowWolfsWoman_OnMap == 0)
                                    cout << "      | Ничья, погибли все!";

                                else {

                                    if (Model->HowRabbitsMan_OnMap == 0 && Model->HowRabbitsWoman_OnMap == 0)
                                        cout << "      | Зайцы умерли, волки победили!";

                                    else if (Model->HowWolfsMan_OnMap == 0 && Model->HowWolfsWoman_OnMap == 0)
                                        cout << "      | Волки умерли, зайцы победили!";

                                }

                                if (Game.Rabbit_Breeding == true && (Model->HowRabbitsMan_OnMap == 0 || Model->HowRabbitsWoman_OnMap == 0))
                                    Game.Rabbit_Breeding = false;

                                if (Game.Wolf_Breeding == true && (Model->HowWolfsMan_OnMap == 0 || Model->HowWolfsWoman_OnMap == 0))
                                    Game.Wolf_Breeding = false;

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
