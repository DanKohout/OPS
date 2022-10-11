#include "mbed.h"

DigitalOut myled(LED1);

float pauseTime = 0.5;

int ON=1;
int OFF=0;
void tecka() {
  myled = ON;           // LED is ON
  wait(pauseTime / 4); // 200 ms
  myled = OFF;           // LED is OFF
  wait(pauseTime);     // 2 sec
}
void carka() {
  myled = ON;       // LED is ON
  wait(pauseTime); // 200 ms
  myled = OFF;       // LED is OFF
  wait(pauseTime); // 2 sec
}
void pauza() {
  myled = OFF; // LED is OFF
  wait(pauseTime * 2);
}

char* convert(char letter) {

    switch(letter) {
        case 'A': return ".-";
        case 'B': return "-...";
        case 'C': return "-.-.";
        case 'D': return "-..";
        case 'E': return ".";
        case 'F': return "..-.";
        case 'G': return "--.";
        case 'H': return "....";
        case 'I': return "..";
        case 'J': return ".---";
        case 'K': return "-.-";
        case 'L': return ".-..";
        case 'M': return "--";
        case 'N': return "-.";
        case 'O': return "---";
        case 'P': return ".--.";
        case 'Q': return "--.-";
        case 'R': return ".-.";
        case 'S': return "...";
        case 'T': return "-";
        case 'U': return "..-";
        case 'V': return "...-";
        case 'W': return ".--";
        case 'X': return "-..-";
        case 'Y': return "-.--";
        case 'Z': return "--..";
        case ' ': return " ";
    }

}

void ovladac(char* stringos){
    int len=strlen(stringos);
    for(int i=0;i<len;i++){
        char letter=stringos[i];

        switch (letter) {
            case ' ':
                pauza();
                break;
            case '.':
                tecka();
                break;
            case '-':
                carka();
                break;
        }
    }
}

void wordToLetters(char* word){
    int len=strlen(word);
    for(int i=0;i<len;i++){
        char letter=word[i];
        ovladac(convert(letter));
        ovladac(convert(' '));
    }
}


int main() {  
    while(1) {
        wordToLetters("RADEK   ");

    }
}


