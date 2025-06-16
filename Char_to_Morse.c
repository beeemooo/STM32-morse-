#include <stddef.h>
#include "LED.h"
#include "Char_to_Morse.h"

#define UNIT_TIME_MS   200U                // 1 unit = 200 ms

typedef struct { char ch; const char *code; } Morse;

static const Morse table[] = {
    {'A',"._"},   {'B',"-..."}, {'C',"-.-."}, {'D',"-.."},
    {'E',"."},    {'F',"..-."}, {'G',"--."},  {'H',"...."},
    {'I',".."},   {'J',".---"}, {'K',"-.-"},  {'L',".-.."},
    {'M',"--"},   {'N',"-."},   {'O',"---"},  {'P',".--."},
    {'Q',"--.-"}, {'R',".-."},  {'S',"..."},  {'T',"-"},
    {'U',"..-"},  {'V',"...-"}, {'W',".--"},  {'X',"-..-"},
    {'Y',"-.--"}, {'Z',"--.."},
    {'1',".----"},{'2',"..---"},{'3',"...--"},{'4',"....-"},
    {'5',"....."},{'6',"-...."},{'7',"--..."},{'8',"---.."},
    {'9',"----."},{'0',"-----"},
    {0,  NULL}             // terminator
};



const char* morse_lookup(char c)		//This function transfer char to Morse code
{
    if ('a' <= c && c <= 'z') c -= 32;  // to upper
		const Morse *p;
    for (p = table; p->ch; ++p)
        if (p->ch == c) return p->code;
    return NULL;                         // undefined -> skip
}





void unit_delay(uint32_t units)
{
    delay(units * UNIT_TIME_MS);           // ??? unit ??? ??
}


/* send one symbol */
static void send_symbol(char symbol)
{
    LED_On();
    unit_delay((symbol == '.') ? 1 : 3);   // . 1 unit, _ 3 units
    LED_Off();
    unit_delay(1);                         // for internal word 1 unit
}


/* send one word */
static void send_morse_char(char c)
{
    if (c == ' ') {                        // internal symbol
        unit_delay(7);
        return;
    }

    const char *code = morse_lookup(c);    // NULL for not supporting char
    if (!code) return;

		size_t i;
    for (i = 0; code[i] != '\0'; ++i)
        send_symbol(code[i]);

    
    unit_delay(2);
}

/* send entire sentence */
void send_morse_string(const char *str)
{
		size_t i;
    for (i = 0; str[i] != '\0'; ++i)
        send_morse_char(str[i]);
}


