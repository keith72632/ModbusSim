#include "registers.h"

coil read_coil_status(int addr, coil coil_reg[]) {
    return coil_reg[addr];
}

void write_coil(int addr, coil coil_reg[]) {
    coil_reg[addr] = 0x01;
    printf("Coil register %d set to %hhd\n\n", addr, coil_reg[addr]);
}

word read_holding_register(int addr, word holding_reg[]) {

    return holding_reg[addr];
}

void write_holding_register(int addr, word holding_reg[]) {
    FILE *fp = NULL;
    uint32_t reg;
    word val;
    printf("Enter address of holding register to be written to (1 - 1000)\n");
    scanf("%d", &reg);
    printf("Enter value to be written to address\n");
    scanf("%hd", &val);
    holding_reg[reg] = val;
    printf("Holding register %d set to %hd\n\n", reg, val);

    fp = fopen("./holding_registers.txt", "w+");

    if(fp == NULL) {
        perror("Cannot access holding registers\n");
    }


    fclose(fp);

}




void randomize_coils(coil coil_regs[]) {
    printf("Randomizing coils...\n");
    for(size_t i = 0; i <= 1000; i++){
        if(i % 2 == 0) {
            coil_regs[i] = 0;
        } else {
            coil_regs[i] = 1;
        }
    }
}
