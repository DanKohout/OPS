#include "mbed.h"

DigitalOut myled(LED1);

// Constants
float pauseTime = 0.5;
int ON = 1;
int OFF = 0;

// Blink for short duration
void dot() {
    myled = ON;
    wait(pauseTime / 4);
    myled = OFF;
    wait(pauseTime);
}

// Blink for long duration
void dash() {
    myled = ON;
    wait(pauseTime);
    myled = OFF;
    wait(pauseTime);
}

// Pause between letters
void pause() {
    myled = OFF;
    wait(pauseTime * 2);
}

// Convert letter to ~string of dots and dashes
char *convert(char letter) {
    switch (letter) {
        case 'A':
            return ".-";
        case 'B':
            return "-...";
        case 'C':
            return "-.-.";
        case 'D':
            return "-..";
        case 'E':
            return ".";
        case 'F':
            return "..-.";
        case 'G':
            return "--.";
        case 'H':
            return "....";
        case 'I':
            return "..";
        case 'J':
            return ".---";
        case 'K':
            return "-.-";
        case 'L':
            return ".-..";
        case 'M':
            return "--";
        case 'N':
            return "-.";
        case 'O':
            return "---";
        case 'P':
            return ".--.";
        case 'Q':
            return "--.-";
        case 'R':
            return ".-.";
        case 'S':
            return "...";
        case 'T':
            return "-";
        case 'U':
            return "..-";
        case 'V':
            return "...-";
        case 'W':
            return ".--";
        case 'X':
            return "-..-";
        case 'Y':
            return "-.--";
        case 'Z':
            return "--..";
        case ' ':
            return " ";
    }
}

// LED blink according to given ~string of dots and dashes
void controller(char *morseCode) {
    int len = strlen(morseCode);
    for (int i = 0; i < len; i++) {
        char symbol = morseCode[i];
        switch (symbol) {
            case ' ':
                pause();
                break;
            case '.':
                dot();
                break;
            case '-':
                dash();
                break;
        }
    }
}

// Word to letters
void wordToLetters(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++)     {
        char letter = word[i];
        controller(convert(letter));
        controller(convert(' '));
    }
}

// Main
int main() {
    while (1) {
        wordToLetters("RADEK   ");
    }
}
