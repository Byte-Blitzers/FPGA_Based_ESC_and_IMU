#include "xgpio.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xiicps.h"

#define GPIO_UH_DEVICE_ID  XPAR_AXI_GPIO_0_DEVICE_ID
#define GPIO_UL_DEVICE_ID  XPAR_AXI_GPIO_1_DEVICE_ID
#define GPIO_VH_DEVICE_ID  XPAR_AXI_GPIO_2_DEVICE_ID
#define GPIO_VL_DEVICE_ID  XPAR_AXI_GPIO_3_DEVICE_ID
#define GPIO_WH_DEVICE_ID  XPAR_AXI_GPIO_4_DEVICE_ID
#define GPIO_WL_DEVICE_ID  XPAR_AXI_GPIO_5_DEVICE_ID

#define I2C_DEVICE_ID      XPAR_XIICPS_0_DEVICE_ID
#define ADS1115_ADDR       0x48

XIicPs IicPs;
XGpio GpioUH, GpioUL, GpioVH, GpioVL, GpioWH, GpioWL;

const u8 commutationTable[6][6] = {
    {1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 1},
    {0, 1, 0, 1, 1, 0}
};

void SetCommutationStep(int step) {
    XGpio_DiscreteWrite(&GpioUH, 1, commutationTable[step][0]);
    XGpio_DiscreteWrite(&GpioUL, 1, commutationTable[step][1]);
    XGpio_DiscreteWrite(&GpioVH, 1, commutationTable[step][2]);
    XGpio_DiscreteWrite(&GpioVL, 1, commutationTable[step][3]);
    XGpio_DiscreteWrite(&GpioWH, 1, commutationTable[step][4]);
    XGpio_DiscreteWrite(&GpioWL, 1, commutationTable[step][5]);
}

s16 ReadADS1115(u8 channel) {
    u8 config[3];
    u8 readBuf[2];
    u16 configVal = 0;

    switch (channel) {
        case 0: configVal = 0xC583; break; // AIN0-GND
        case 1: configVal = 0xD583; break; // AIN1-GND
        case 2: configVal = 0xE583; break; // AIN2-GND
        case 3: configVal = 0xF583; break; // AIN3-GND
        default: return 0;
    }

    // Write config register
    config[0] = 0x01;
    config[1] = (configVal >> 8) & 0xFF;
    config[2] = configVal & 0xFF;
    XIicPs_MasterSendPolled(&IicPs, config, 3, ADS1115_ADDR);
    usleep(1000); // allow conversion time

    // Read conversion result
    config[0] = 0x00; // conversion register
    XIicPs_MasterSendPolled(&IicPs, config, 1, ADS1115_ADDR);
    usleep(1000);
    XIicPs_MasterRecvPolled(&IicPs, readBuf, 2, ADS1115_ADDR);

    return (readBuf[0] << 8) | readBuf[1];
}


int main() {
    XIicPs_Config *config;
    int step = 0;

    // Initialize GPIOs
    XGpio_Initialize(&GpioUH, GPIO_UH_DEVICE_ID);
    XGpio_Initialize(&GpioUL, GPIO_UL_DEVICE_ID);
    XGpio_Initialize(&GpioVH, GPIO_VH_DEVICE_ID);
    XGpio_Initialize(&GpioVL, GPIO_VL_DEVICE_ID);
    XGpio_Initialize(&GpioWH, GPIO_WH_DEVICE_ID);
    XGpio_Initialize(&GpioWL, GPIO_WL_DEVICE_ID);

    // Initialize I2C
    config = XIicPs_LookupConfig(I2C_DEVICE_ID);
    XIicPs_CfgInitialize(&IicPs, config, config->BaseAddress);
    XIicPs_SetSClk(&IicPs, 400000);

    xil_printf("Starting open-loop ADC logging...\n");

    while (1) {
        SetCommutationStep(step);

        s16 A0 = ReadADS1115(0);  // Phase A
        s16 A1 = ReadADS1115(1);  // Phase B
        s16 A2 = ReadADS1115(2);  // Phase C

        xil_printf("Step: %d  |  A0: %d  A1: %d  A2: %d\n", step, A0, A1, A2);

        step = (step + 1) % 6;
        usleep(100); // Adjust speed (~25 Hz commutation)
    }

    return XST_SUCCESS;
}
