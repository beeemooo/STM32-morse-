// Char_to_Morse.h
#ifndef CHAR_TO_MORSE_H
#define CHAR_TO_MORSE_H

const char *morse_lookup(char c);
void send_morse_string(const char *str);
void unit_delay(uint32_t units);

#endif
