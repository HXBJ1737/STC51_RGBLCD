#include <REGX52.h>
#include "Delay.h"
#define KEY0 P3_1
#define KEY1 P3_0
#define KEY2 P3_2
#define KEY3 P3_3
unsigned char keyv[] = {0,
                        '1', '2', '3', 'A',
                        '4', '5', '6', 'B',
                        '7', '8', '9', 'C',
                        '*', '0', '#', 'D',
                        'Q', 'W', 'E', 'R'};
unsigned char keyget()
{

    unsigned char KeyNumber = 0;

    P1   = 0xFF;
    P1_3 = 0;
    if (P1_7 == 0) {
        Delay(20);
        while (P1_7 == 0);
        Delay(20);
        KeyNumber = 1;
    }
    if (P1_6 == 0) {
        Delay(20);
        while (P1_6 == 0);
        Delay(20);
        KeyNumber = 5;
    }
    if (P1_5 == 0) {
        Delay(20);
        while (P1_5 == 0);
        Delay(20);
        KeyNumber = 9;
    }
    if (P1_4 == 0) {
        Delay(20);
        while (P1_4 == 0);
        Delay(20);
        KeyNumber = 13;
    }

    P1   = 0xFF;
    P1_2 = 0;
    if (P1_7 == 0) {
        Delay(20);
        while (P1_7 == 0);
        Delay(20);
        KeyNumber = 2;
    }
    if (P1_6 == 0) {
        Delay(20);
        while (P1_6 == 0);
        Delay(20);
        KeyNumber = 6;
    }
    if (P1_5 == 0) {
        Delay(20);
        while (P1_5 == 0);
        Delay(20);
        KeyNumber = 20;
    }
    if (P1_4 == 0) {
        Delay(20);
        while (P1_4 == 0);
        Delay(20);
        KeyNumber = 14;
    }

    P1   = 0xFF;
    P1_1 = 0;
    if (P1_7 == 0) {
        Delay(20);
        while (P1_7 == 0);
        Delay(20);
        KeyNumber = 3;
    }
    if (P1_6 == 0) {
        Delay(20);
        while (P1_6 == 0);
        Delay(20);
        KeyNumber = 7;
    }
    if (P1_5 == 0) {
        Delay(20);
        while (P1_5 == 0);
        Delay(20);
        KeyNumber = 11;
    }
    if (P1_4 == 0) {
        Delay(20);
        while (P1_4 == 0);
        Delay(20);
        KeyNumber = 15;
    }

    P1   = 0xFF;
    P1_0 = 0;
    if (P1_7 == 0) {
        Delay(20);
        while (P1_7 == 0);
        Delay(20);
        KeyNumber = 4;
    }
    if (P1_6 == 0) {
        Delay(20);
        while (P1_6 == 0);
        Delay(20);
        KeyNumber = 8;
    }
    if (P1_5 == 0) {
        Delay(20);
        while (P1_5 == 0);
        Delay(20);
        KeyNumber = 12;
    }
    if (P1_4 == 0) {
        Delay(20);
        while (P1_4 == 0);
        Delay(20);
        KeyNumber = 16;
    }

    if (KEY0 == 0) {
        Delay(20);
        while (KEY0 == 0);
        KeyNumber = 17;
    }
    if (KEY1 == 0) {
        Delay(20);
        while (KEY1 == 0);
        KeyNumber = 18;
    }
    if (KEY2 == 0) {
        Delay(20);
        while (KEY2 == 0);
        KeyNumber = 19;
    }
    if (KEY3 == 0) {
        Delay(20);
        while (KEY3 == 0);
        KeyNumber = 20;
    }
    return keyv[KeyNumber];
}
unsigned char keyget2()
{

    unsigned char KeyNumber = 0;

    P1   = 0xFF;
    P1_3 = 0;
    if (P1_7 == 0) { KeyNumber = 1; }
    if (P1_6 == 0) { KeyNumber = 5; }
    if (P1_5 == 0) { KeyNumber = 9; }
    if (P1_4 == 0) { KeyNumber = 13; }

    P1   = 0xFF;
    P1_2 = 0;
    if (P1_7 == 0) { KeyNumber = 2; }
    if (P1_6 == 0) { KeyNumber = 6; }
    if (P1_5 == 0) { KeyNumber = 20; }
    if (P1_4 == 0) { KeyNumber = 14; }

    P1   = 0xFF;
    P1_1 = 0;
    if (P1_7 == 0) { KeyNumber = 3; }
    if (P1_6 == 0) { KeyNumber = 7; }
    if (P1_5 == 0) { KeyNumber = 11; }
    if (P1_4 == 0) { KeyNumber = 15; }

    P1   = 0xFF;
    P1_0 = 0;
    if (P1_7 == 0) { KeyNumber = 4; }
    if (P1_6 == 0) { KeyNumber = 8; }
    if (P1_5 == 0) { KeyNumber = 12; }
    if (P1_4 == 0) { KeyNumber = 16; }

    if (KEY0 == 0) {

        KeyNumber = 17;
    }
    if (KEY1 == 0) {

        KeyNumber = 18;
    }
    if (KEY2 == 0) {

        KeyNumber = 19;
    }
    if (KEY3 == 0) {

        KeyNumber = 20;
    }
    return KeyNumber;
}
