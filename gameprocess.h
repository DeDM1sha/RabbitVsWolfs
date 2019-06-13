#pragma once

#ifndef _gameprocess_H_
#define _gameprocess_H_

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

        unsigned short int TextColor; // ���� ������
        int RabbitsCount; // ������������ ���-�� ������ �� �����
        int WolfsCount; // ������������ ���-�� ������
        unsigned short int Rows_Count; // ���-�� ����� � ������� ����
        unsigned short int Columns_Count; // ���-�� �������� � ������� ����
        int StartAnimalCount; // ��������� ����� �������� (��� ����� �����)

        GameProcess (void) {

            TextColor = LightBlue;
            RabbitsCount = 0;
            WolfsCount = 0;
            Rows_Count = 10;
            Columns_Count = 10;
            StartAnimalCount = 0;

        }

        ~GameProcess (void) {}

        void Set_BackgroundColor (void) {

            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | this->TextColor));

        } // �����, �������� ���� ������

        void Center (string Stroke) {

            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            GetConsoleScreenBufferInfo ( (GetStdHandle( STD_OUTPUT_HANDLE )), &consoleInfo);

                for (unsigned short int i = 0; i < ((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1) / 2 - strlen(Stroke.c_str()) / 2); i++)
                    std::cout << " ";

            cout << Stroke;

        } // ������� ��� ���������� ���������� ���� ������ �� ������ ������

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

        } // ����� ��������� �����

        void DrawBlock (unsigned short int TypeBlock) {

            unsigned short int Number1 = 0, Number2 = 0;
            string Str1 = "\0", Str2 = "\0";

                switch (TypeBlock) {

                    case 100:   Str1 = "     "; Str2 = "\0"; Number1 = Black;       Number2 = Black;        break;  // ������ ������                  - Void_Block
                    case 101:   Str1 = "** **"; Str2 = "\0"; Number1 = LightGreen;  Number2 = Black;        break;  // ������ � ������ (��� ��������) - Grass_Block
                    case 102:   Str1 = "&& ";   Str2 = "**"; Number1 = BrightWhite; Number2 = LightGreen;   break;  // ���� � ������ � ������         - Rabbit_Grass
                    case 103:   Str1 = "&&   "; Str2 = "\0"; Number1 = BrightWhite; Number2 = Black;        break;  // ���� � ������ ������           - Rabbit_Block
                    case 104:   Str1 = "&& ";   Str2 = "**"; Number1 = LightYellow; Number2 = LightGreen;   break;  // ������� � ������ � ������      - Hare_Grass
                    case 105:   Str1 = "&& ";   Str2 = "**"; Number1 = LightYellow; Number2 = Black;        break;  // ������� � ������ ������        - Hare_Block
                    case 106:   Str1 = "&& ";   Str2 = "&&"; Number1 = BrightWhite; Number2 = LightYellow;  break;  // ���� � ������ � ��������       - Rabbit_Hare
                    case 107:   Str1 = "&& &&"; Str2 = "\0"; Number1 = BrightWhite; Number2 = Black;        break;  // ����� � ����� ������           - Rabbit_Rabbit
                    case 108:   Str1 = "&& &&"; Str2 = "\0"; Number1 = LightYellow; Number2 = Black;        break;  // ������� � ����� ������         - Hare_Hare
                    case 109:   Str1 = "@@ ";   Str2 = "**"; Number1 = LightRed;    Number2 = LightGreen;   break;  // ���� � ������ � ������         - Wolf_Grass
                    case 110:   Str1 = "@@ ";   Str2 = "  "; Number1 = LightRed;    Number2 = Black;        break;  // ���� � ������ ������           - Wolf_Block
                    case 111:   Str1 = "@@ ";   Str2 = "**"; Number1 = LightPurple; Number2 = LightGreen;   break;  // ������� � ������ � ������      - BitchWolf_Grass
                    case 112:   Str1 = "@@ ";   Str2 = "  "; Number1 = LightPurple; Number2 = Black;        break;  // ������� � ������ ������        - BitchWolf_Block
                    case 113:   Str1 = "@@ ";   Str2 = "&&"; Number1 = LightRed;    Number2 = LightYellow;  break;  // ���� � ��������                - Wolf_Hare
                    case 114:   Str1 = "@@ @@"; Str2 = "\0"; Number1 = LightRed;    Number2 = Black;        break;  // ��� ����� � ����� ������       - Wolf_Wolf
                    case 115:   Str1 = "@@ @@"; Str2 = "\0"; Number1 = LightPurple; Number2 = Black;        break;  // ��� ������� � ����� ������     - BitchWolf_BitchWolf
                    case 116:   Str1 = "@@ ";   Str2 = "&&"; Number1 = LightRed;    Number2 = BrightWhite;  break;  // ���� � ������                  - Wolf_Rabbit
                    case 117:   Str1 = "@@ ";   Str2 = "&&"; Number1 = LightPurple; Number2 = BrightWhite;  break;  // ������� � ������               - BitchWolf_Rabbit
                    case 118:   Str1 = "@@ ";   Str2 = "&&"; Number1 = LightPurple; Number2 = LightYellow;  break;  // ������� � ��������             - BitchWolf_Hare
                    case 119:   Str1 = "@@ ";   Str2 = "@@"; Number1 = LightRed;    Number2 = LightPurple;  break;  // ���� � ��������                - Wolf_BitchWolf
                    default:    Str1 = "\0";    Str2 = "\0"; Number1 = Black;       Number2 = Black;        break;  // �������� �� ���������

                }

            cout << "     |";
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | Number1));
            cout << Str1;
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | Number2));
            cout << Str2;
            Set_BackgroundColor ();
            cout << "|";

        } // ����� ��������� ������ �� ����� �� ����� ���������� ����������

}; // ����� �������� ��������

#endif // _gameprocess_H_
