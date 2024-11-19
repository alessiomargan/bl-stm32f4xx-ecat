#include <stdint.h>

#ifndef __MORSE_H
#define __MORSE_H

typedef enum {
  SPACING,
  TICKING,
  ENDING
} m_state_t;

typedef enum {
  LOW,
  HIGH,
  END
} m_out_t;

typedef enum {
  CHAR,
  SPACE,
  EOS
} m_next_t;

// initialise one of these with the init-function below.
struct morser {
  int8_t tick_count;
  m_state_t state;
  uint8_t char_pos;
  uint8_t char_length;
  uint8_t string_pos;
  char *string;
}; 

void do_morse_led(void);

#endif
