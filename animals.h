#pragma once

#ifndef _Animalss_H_
#define _Animalss_H_

class Animals {

    public:

        bool Life; // ����� ��������� (0 - �����, 1 - ���)
        bool Sex; // ��� ��������� (0 - ���, 1 - ���)
        int X; // ���������� �� X
        int Y; // ���������� �� Y
        int Food; // �������� / ����� ���������
        int MaxDays; // ������������ ����������������� ����� ���������

        Animals (void) {

            Life = false;
            Sex = false;
            X = 0;
            Y = 0;

        }

        ~Animals (void) {}

        void Move (void) {

            unsigned short int Number = 1 + rand () % 101;

                if ((X == 0 && Y == 0) || (X == 9 && Y == 0) || (X == 0 && Y == 9) || (X == 9 && Y == 9) || (X >= 1 && X <= 8 && Y == 0) || (X >= 1 && X <= 8 && Y == 9) || (Y >= 1 && Y <= 8 && X == 0) || (Y >= 1 && Y <= 8 && X == 9)) {

                    if (X == 0 && Y == 0) {

                        if (Number >= 33 && Number <= 66)
                            X = 1;

                        else if (Number >= 67)
                            Y = 1;

                    }

                    else if (X == 9 && Y == 0) {

                        if (Number >= 33 && Number <= 66)
                            X = 8;

                        else if (Number >= 67)
                            Y = 1;

                    }

                    else if (X == 0 && Y == 9) {

                        if (Number >= 33 && Number <= 66)
                            X = 1;

                        else if (Number >= 67)
                            Y = 8;

                    }

                    else if (X == 9 && Y == 9) {

                        if (Number >= 33 && Number <= 66)
                            X = 8;

                        else if (Number >= 67)
                            Y = 8;

                    }

                    else if (X >= 1 && X <= 8 && Y == 0) {

                        if (Number >= 25 && Number <= 50)
                            X -= 1;

                        else if (Number >= 51 && Number <= 75)
                            Y = 1;

                        else if (Number >= 76)
                            X += 1;

                    }

                    else if (X >= 1 && X <= 8 && Y == 9) {

                        if (Number >= 25 && Number <= 50)
                           X -= 1;

                        else if (Number >= 51 && Number <= 75)
                            Y = 8;

                        else if (Number >= 76)
                            X += 1;

                    }

                    else if (Y >= 1 && Y <= 8 && X == 0) {

                        if (Number >= 25 && Number <= 50)
                            Y -= 1;

                        else if (Number >= 51 && Number <= 75)
                            X = 1;

                        else if (Number >= 76)

                            Y += 1;

                    }

                    else if (Y >= 1 && Y <= 8 && X == 9) {

                        if (Number >= 25 && Number <= 50)
                            Y -= 1;

                        else if (Number >= 51 && Number <= 75)
                            X = 8;

                        else if (Number >= 76)
                            Y += 1;

                    }

                }

                else {

                    if (Number >= 21 && Number <= 40)
                        Y -= 1;

                    if (Number >= 41 && Number <= 60)
                        X += 1;

                    if (Number >= 61 && Number <= 80)
                        Y += 1;

                    if (Number >= 81)
                        X -= 1;

                }

        } // ����� ������������ ���� ��������

};

class Rabbits : public Animals {

    public:

        Rabbits (void) : Animals () {

            Food = 30;
            MaxDays = 2190; // 6 ��� �����

        };

        ~Rabbits (void) {};

}; // ����� ������

class Wolfs : public Animals {

    public:

        Wolfs (void) : Animals () {

            Food = 100;
            MaxDays = 3660; // 10 ��� �����

        };

        ~Wolfs (void) {};

}; // ����� ������

#endif // _Animalss_h
