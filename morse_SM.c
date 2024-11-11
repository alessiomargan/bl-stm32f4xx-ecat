/*
 * morse_SM.c
 *
 *  Created on: Oct 19, 2024
 *      Author: amargan
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>  // for usleep

#include "user_code.h"

// LED control functions (replace these with actual hardware control functions)
void led_on() {
    // Code to turn on the LED (replace with actual hardware-specific code)
    //printf("LED ON\n");
    LED_1_ON;
}

void led_off() {
    // Code to turn off the LED (replace with actual hardware-specific code)
    //printf("LED OFF\n");
    LED_1_OFF;
}

// Morse timings (in microseconds)
#define DOT_TIME 200000      // 200 ms
#define DASH_TIME 600000     // 600 ms
#define BETWEEN_PARTS 200000 // 200 ms between parts of the same letter
#define BETWEEN_LETTERS 600000 // 600 ms between letters
#define BETWEEN_WORDS 1400000  // 1400 ms between words
#define STEP_TIME 100000      // 100 ms small time steps

// Morse code lookup table (letters and digits)
const char *morse_code[] = {
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",   "....", "..",   // A-I
    ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.",  "--.-", ".-.",  // J-R
    "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--",  "--..",         // S-Z
    "-----",".----","..---","...--","....-",".....","-....","--...","---..","----." // 0-9
};

// State variables
const char *current_morse = NULL;  // Current Morse code string being processed
int current_char_index = 0;        // Index of the current character in the message
int current_dot_dash_index = 0;    // Index of the current dot/dash in the Morse code string
unsigned long current_time = 0;    // Time spent in the current dot/dash/space
int led_state = 0;                 // 0 for off, 1 for on
int current_delay = 0;             // Delay time for the current dot/dash/space

// Function to get Morse code for a letter
const char* get_morse(char c) {
    if (c >= 'A' && c <= 'Z') {
        return morse_code[c - 'A']; // Letters A-Z
    } else if (c >= 'a' && c <= 'z') {
        return morse_code[c - 'a']; // Letters a-z (treated same as A-Z)
    } else if (c >= '0' && c <= '9') {
        return morse_code[c - '0' + 26]; // Numbers 0-9
    }
    return ""; // For non-alphabetic characters, return empty string (no Morse code)
}

// Function to update the LED state based on the Morse code
void update_led(const char *message) {
    char c = message[current_char_index];

    if (current_morse == NULL) {
        // If there's no current Morse code, get the next character's Morse code
        if (c == ' ') {
            // Handle space between words
            current_delay = BETWEEN_WORDS;
            current_char_index++;
            current_dot_dash_index = 0;
            led_off();
        } else if (c != '\0') {
            current_morse = get_morse(c);
            current_dot_dash_index = 0;
        } else {
            // End of the message, reset to start
            current_char_index = 0;
        }
    }

    if (current_morse != NULL && current_time >= current_delay) {
        char morse_char = current_morse[current_dot_dash_index];

        // Turn on/off LED based on dot/dash
        if (morse_char == '.') {
            led_on();
            current_delay = DOT_TIME;
            current_dot_dash_index++;
        } else if (morse_char == '-') {
            led_on();
            current_delay = DASH_TIME;
            current_dot_dash_index++;
        }

        // If we reached the end of the Morse code for this letter, move to the next
        if (current_morse[current_dot_dash_index] == '\0') {
            led_off();
            current_morse = NULL;
            current_delay = BETWEEN_LETTERS;
            current_char_index++;
        } else {
            // Turn off after a part of a letter
            led_off();
            current_delay = BETWEEN_PARTS;
        }
        current_time = 0;  // Reset the time for the next Morse element
    }

    // Increment time by the step interval
    current_time += STEP_TIME;
}
