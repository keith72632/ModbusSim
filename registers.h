#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define WORD_SIZE    16
#define MAX_LINE     2048

typedef uint8_t coil, discrete_input;
typedef uint16_t input, word;



// Prototypes
coil read_coil_status(int addr, coil coil_reg[]);
void write_coil(int addr, coil coil_reg[]); 
word read_holding_register(int addr, word holding_reg[]);
void write_holding_register(int addr, word holding_reg[]);

void randomize_coils(coil coil_regs[]);

#endif