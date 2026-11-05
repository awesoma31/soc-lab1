#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"

#define N              10

#define LED_ADDR       XPAR_AXI_GPIO_0_BASEADDR

#define LED_LD0        0x0001
#define LED_LD1        0x0002


#ifdef SIMULATION
#define LED_DELAY_US   2U
#define LED_GAP_US     1U
#else
#define LED_DELAY_US   1000000U
#define LED_GAP_US     250000U
#endif

int A[N][N] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 1},
    {3, 1, 4, 1, 5, 9, 2, 6, 5, 3},
    {2, 7, 1, 8, 2, 8, 1, 8, 2, 8},
    {1, 4, 1, 4, 2, 1, 3, 5, 6, 2},
    {5, 7, 7, 2, 1, 5, 6, 6, 4, 9},
    {9, 8, 7, 6, 5, 4, 3, 2, 1, 9},
    {1, 1, 2, 3, 5, 8, 1, 3, 2, 1},
    {6, 2, 8, 3, 1, 8, 5, 3, 7, 1},
    {4, 6, 6, 9, 2, 2, 9, 7, 1, 3},
    {8, 3, 5, 9, 7, 9, 3, 2, 3, 8}
};

int B[N][N] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {2, 3, 4, 5, 6, 7, 8, 9, 10, 1},
    {3, 4, 5, 6, 7, 8, 9, 10, 1, 2},
    {4, 5, 6, 7, 8, 9, 10, 1, 2, 3},
    {5, 6, 7, 8, 9, 10, 1, 2, 3, 4},
    {6, 7, 8, 9, 10, 1, 2, 3, 4, 5},
    {7, 8, 9, 10, 1, 2, 3, 4, 5, 6},
    {8, 9, 10, 1, 2, 3, 4, 5, 6, 7},
    {9, 10, 1, 2, 3, 4, 5, 6, 7, 8},
    {10, 1, 2, 3, 4, 5, 6, 7, 8, 9}
};

int C[N][N];

int main(void)
{
    int i, j, k;

    Xil_Out16(LED_ADDR, 0);

    Xil_Out16(LED_ADDR, LED_LD0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = B[i][j];
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * A[k][j];
            }
        }
    }

    Xil_Out16(LED_ADDR, LED_LD1);
    usleep(LED_DELAY_US);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Xil_Out16(LED_ADDR, (u16)C[i][j]);
            usleep(LED_DELAY_US);
            Xil_Out16(LED_ADDR, 0);
            usleep(LED_GAP_US);
        }
    }

    Xil_Out16(LED_ADDR, LED_LD1);

    while (1) {
    }

    return 0;
}
