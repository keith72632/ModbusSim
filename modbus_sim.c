#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t coil, discrete_input;
typedef uint16_t input, word;

coil coil_regs[10000], coil_res;
discrete_input discrete_input_regs[10000];
input input_regs[10000];
word holding_regs[10000];

// Prototypes
coil read_coil_status();
void write_coil();
void write_holding_register();

int main() {
    while(1){
        int action;
        printf("Pick Address\n");
        printf("\t1. Read Coil Status\n\t2. Read Input Status\n\t3. Read Holding Register\n\t4. Read Internal Register\n\t5. Force Single Coil\n\t6. Write Single Register\n\t15. Force Multiple Coils\n\t16. Mask Write Register\n");
        scanf("%d", &action);
        switch(action){
            case 1:
                printf("Read Coil Status\n");
                coil_res = read_coil_status();
                printf("Read Coil Result: %hd\n", coil_res);
                break;
            case 2: 
                printf("Read Input Status\n");
                break;
            case 3:
                printf("Read Holding Register\n");
                break;
            case 4:
                printf("Read Internal Register\n");
                break;
            case 5:
                printf("Force Single Coil\n");
                write_coil();
                break;
            case 6:
                printf("Write Single Register\n");
                write_holding_register();
                break;
            case 15:
                printf("Force Multiple Coils");
                break;
            case 16:
                printf("Masked Write Register\n");
                break;
            default: 
                printf("Invalid input\n");
                break;            
        }
    }
}

coil read_coil_status() {
    uint32_t reg;
    printf("Enter address of coil to be read (1 - 10000)\n\n");
    scanf("%d", &reg);
    return coil_regs[reg];
}

void write_coil() {
    uint32_t reg;
    printf("Enter address of coil to be written to (1 - 10000)\n");
    scanf("%d", &reg);
    coil_regs[reg] |= 0x01;
    printf("Coil register %d set to %hhd\n\n", reg, coil_regs[reg]);
}

word read_holding_register() {
    uint32_t reg;
    printf("Enter address of holding register to be read (1 - 10000)\n");
    scanf("%d", &reg);
    return holding_regs[reg];
}

void write_holding_register() {
    uint32_t reg;
    word val;
    printf("Enter address of holding register to be written to (1 - 10000)\n");
    scanf("%d", &reg);
    printf("Enter value to be written to address\n");
    scanf("%hd", &val);
    holding_regs[reg] = val;
    printf("Holding register %d set to %hd\n\n", reg, val);
}