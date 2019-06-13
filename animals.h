#pragma once

#ifndef _Animalss_H_
#define _Animalss_H_

class Animals {

    public:

        bool Life; // жизнь животного (0 - мертв, 1 - жив)
        bool Sex; // пол животного (0 - жен, 1 - муж)
        int X; // координата по X
        int Y; // координата по Y
        int Food; // сытостоь / голод животного
        int MaxDays; // максимальная продолжительность жизни животного

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

        } // метод рандомизации хода животных

};

class Rabbits : public Animals {

    public:

        Rabbits (void) : Animals () {

            Food = 30;
            MaxDays = 2190; // 6 лет жизни

        };

        ~Rabbits (void) {};

}; // класс зайцев

class Wolfs : public Animals {

    public:

        Wolfs (void) : Animals () {

            Food = 100;
            MaxDays = 3660; // 10 лет жизни

        };

        ~Wolfs (void) {};

}; // класс волков

#endif // _Animalss_h
