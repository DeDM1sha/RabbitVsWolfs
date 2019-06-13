#pragma once

#ifndef _header_H_
#define _header_H_

#define hConsole GetStdHandle(STD_OUTPUT_HANDLE)
#define Black 0
#define DarkBlue 1
#define Green 2
#define Blue 3
#define Red 4
#define Purple 5
#define Yellow 6
#define White 7
#define Grey 8
#define LightDarkBlue 9
#define LightGreen 10
#define LightBlue 11
#define LightRed 12
#define LightPurple 13
#define LightYellow 14
#define BrightWhite 15

using namespace std;

class GameProcess {

    public:

        unsigned short int TextColor; // цвет текста
        unsigned short int FieldSize; // размерность поля
        string* Field; // поле модели

        GameProcess (void) {

            TextColor = LightBlue;
            FieldSize = 100;
            Field = new string [FieldSize];

                for (int i = 0; i < FieldSize; i++)
                    Field[i] = "\0";

        }

        ~GameProcess (void) {

            delete Field;

        }

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
            system ("color B"); // Светло-голубой цвет текста
            //system ("mode con cols=126 lines=31"); // Отключение боковой меню с прокрукой
            system ("title Зайцы против волков"); // Заголовок программы

        } // метод настройки приложения

        void Center (string Stroke) {

            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            GetConsoleScreenBufferInfo ( (GetStdHandle( STD_OUTPUT_HANDLE )), &consoleInfo);

                for (unsigned short int i = 0; i < ((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1) / 2 - strlen(Stroke.c_str()) / 2); i++)
                    std::cout << " ";

            cout << Stroke;

        } // Функция для размещения введенного нами текста по центру экрана

        void Preview (void) {

            cls;
            Center("iMMMMMMMMMMMMMMMMMMMMMMM   1MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
            Center("7M@WB$W@MMM@W$$#WWMMMM$Qi;iIWMMMME$MMMBbMMMMM@8MMMMMMbMMMMMMMMMMMMM0QMMbMMMMWB$WEMMMMMMMMMMMMMW$$$$$WMMMMMMBQ#B$W$MMMMMMMWQB@MMMWEMMMM9MMMMEQMMM@EMM\n");
            Center("YM      MMM       YMMM  MMM7 EMMM  MMM  MMMMM: 0MMMM6 YMMMMMMMM@MMM  Mb YMMM     iMMMMMMMMMMMM       MMMMMA       MMM@MMM   ,MMM  MMMz ;MMM  MMM, MM\n");
            Center("vMWQ#0 .MMM. B#@t YMMM  MMMY WMMM  MMM  MMMMM; @MMMM9 YMMMMMMMMMMMM  M0 7MMM  @Wb#MMMMMMMMMMMM  @#@: ..MMM6 i$0W  MMMMMi.QU .MMM  MM iI#MMM  MMM: MM\n");
            Center("YMMMMM .MMM. MMMM tMMM  MMMX BMMM .MMM  MMMMMv @MMMM0 tMMMMMMMMMMMM  M$ 1MMM  MMMMMMMMMMMMMMMM  MMMI   MMMb EMMM  MMMMM  MM :MMM  MM .MMMMM  MMMv MM\n");
            Center("vM.    ,MMM.      CMMM  M@   #MMM .MMM  MMMMMY     M0 CMMM     YMMM  M@ CMMM     oMMM     YMMM       MMMMM6 oMMM  MMM; BMMM ,MMM    MMMMMMM  MQ   MM\n");
            Center("YM; .. .MMM  ...  CMMM  M6.  BMMM .MMM  MMMMMv .i  MB CMMM     tMMM  MI tMMM,.,  7MMM     zMMM  ,.:  bMMMM9 zMMM  MMM, @MMM ,MMM  .:@@MMMMM  M2.  MM\n");
            Center(";MMMMM ,MMM. MMM@ tMMM   .MU $MMM iMMM, MMMMM7 MM  MW tMMMMMMMMMMMM     YMMMMMMM zMMMMMMMMMMMM .MMM0   MMMb EMMM  MMM; @MMM ,MMM  MM .MMMMM   ,M7 MM\n");
            Center("YMoiY;  MMM  MMM0 YMMM  Z0M; 0MMM  Yv7  i;MMMi iz  MQ YMMMMMMMM@MMMI1  6$MMMiiC. CMMMMMMMMMMMM  tYt  v2MMM6 .cvv  MMM, BMM@ .MMM  MMt;,8MMM  9BM: MM\n");
            Center("vM     .MMM  MMMZ cMMM  MMM; QMMM         MMM;     Mb YMMMMMMMMMMMMMM :MMMMM     1MMMMMMMM@MMM       MMMMMU       MMMi $MM# .MMM  MMM9 YMMM  MMM: MM\n");
            Center("CMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
            Center(".#bQEQQZISAZbUoAoQ261UbbIo2AEUo22Qb$bB0WEbUoI9QQ0Q86U0IUnznSz1onzooI2EU61ISUbQQE0AIoSznItUCI1AbQQQWE0Uo21A2WbB0QE8UoIAbAo22EUA169EUo2AEA2z2E9AnAI0bB\n\n\n\n");

        } // метод отрисовки шапки

        void Set_BackgroundColor (void) {

            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | TextColor));

        } // метод, меняющий цвет текста

        void DrawBlock (unsigned short int TypeBlock) {

            unsigned short int Number1 = 0, Number2 = 0;
            string Str1 = "\0", Str2 = "\0";

                switch (TypeBlock) {

                    case 0:  Str1 = "     "; Str2 = "\0"; Number1 = 0;  Number2 = 0;  break;  // пустая клетка                  - Void_Block
                    case 1:  Str1 = "** **"; Str2 = "\0"; Number1 = 10; Number2 = 0;  break;  // клетка с травой (без животных) - Grass_Block
                    case 2:  Str1 = "&& ";   Str2 = "**"; Number1 = 15; Number2 = 10; break;  // заяц в клетке с травой         - Rabbit_Grass
                    case 3:  Str1 = "&&   "; Str2 = "\0"; Number1 = 15; Number2 = 0;  break;  // заяц в пустой клетке           - Rabbit_Block
                    case 4:  Str1 = "&& ";   Str2 = "**"; Number1 = 14; Number2 = 10; break;  // зайчиха в клетке с травой      - Hare_Grass
                    case 5:  Str1 = "&& ";   Str2 = "**"; Number1 = 14; Number2 = 0;  break;  // зайчиха в пустой клетке        - Hare_Block
                    case 6:  Str1 = "&& ";   Str2 = "&&"; Number1 = 15; Number2 = 14; break;  // заяц в клетке с зайчихой       - Rabbit_Hare
                    case 7:  Str1 = "&& &&"; Str2 = "\0"; Number1 = 15; Number2 = 0;  break;  // зайцы в одной клетке           - Rabbit_Rabbit
                    case 8:  Str1 = "&& &&"; Str2 = "\0"; Number1 = 14; Number2 = 0;  break;  // зайчихи в одной клетке         - Hare_Hare
                    case 9:  Str1 = "@@ ";   Str2 = "**"; Number1 = 12; Number2 = 10; break;  // волк в клетке с травой         - Wolf_Grass
                    case 10: Str1 = "@@ ";   Str2 = "  "; Number1 = 12; Number2 = 0;  break;  // волк в пустой клетке           - Wolf_Block
                    case 11: Str1 = "@@ ";   Str2 = "**"; Number1 = 13; Number2 = 10; break;  // волчиха в клетке с травой      - BitchWolf_Grass
                    case 12: Str1 = "@@ ";   Str2 = "  "; Number1 = 13; Number2 = 0;  break;  // волчиха в пустой клетке        - BitchWolf_Block
                    case 13: Str1 = "@@ ";   Str2 = "&&"; Number1 = 12; Number2 = 14; break;  // волк с зайчихой                - Wolf_Hare
                    case 14: Str1 = "@@ @@"; Str2 = "\0"; Number1 = 12; Number2 = 0;  break;  // два волка в одной клетке       - Wolf_Wolf
                    case 15: Str1 = "@@ @@"; Str2 = "\0"; Number1 = 13; Number2 = 0;  break;  // две волчихи в одной клетке     - BitchWolf_BitchWolf
                    case 16: Str1 = "@@ ";   Str2 = "&&"; Number1 = 12; Number2 = 15; break;  // волк с зайцем                  - Wolf_Rabbit
                    case 17: Str1 = "@@ ";   Str2 = "&&"; Number1 = 13; Number2 = 15; break;  // волчиха с зайцем               - BitchWolf_Rabbit
                    case 18: Str1 = "@@ ";   Str2 = "&&"; Number1 = 13; Number2 = 14; break;  // волчиха с зайчихой             - BitchWolf_Hare
                    case 19: Str1 = "@@ ";   Str2 = "@@"; Number1 = 12; Number2 = 13; break;  // волк с волчихой                - Wolf_BitchWolf
                    default: Str1 = "\0";    Str2 = "\0"; Number1 = 0;  Number2 = 0;  break;  // значения по умолчанию

                }

            cout << "     |";
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | Number1));
            cout << Str1;
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | Number2));
            cout << Str2;
            Set_BackgroundColor ();
            cout << "|";

        } // метод отрисовки блоков на карте со всеми возможными вариациами

        void CardLegend (int iMax) {

            unsigned short int Number = 0;
            string Str1 = "\0", Str2 = "\0";

                switch (iMax) {

                    case 20: Str1 = "               Легенда карты";                      Number = 11; break;
                    case 30: Str1 = "               **";            Str2 = " - Трава";   Number = 10; break;
                    case 40: Str1 = "               &&";            Str2 = " - Заяц";    Number = 15; break;
                    case 50: Str1 = "               &&";            Str2 = " - Зайчиха"; Number = 14; break;
                    case 60: Str1 = "               @@";            Str2 = " - Волк";    Number = 12; break;
                    case 70: Str1 = "               @@";            Str2 = " - Волчиха"; Number = 13; break;
                    default: Str1 = "\0";                           Str2 = "\0";         Number = 0;  break;

                }

            SetConsoleTextAttribute (hConsole, (WORD) ((0 << 4) | Number));
            cout << Str1;
            Set_BackgroundColor ();
            cout << Str2;

        } // функция отрисовки легенды карты

        void RandomGrass (void) {



        } // метод рандомизации роста травы на карте


}; // класс игрового процесса

#endif // _header_H_
