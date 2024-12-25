/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int i, flag=0, error, txCountISR=0, rxCountISR=0;
int txCount=0, rxCount=0;
uint8 txData[4096];
uint8 rxData[4096];

CY_ISR(txInterrupt){
    //Size of TX FIFO is 4 bytes so we put 4 bytes in 
    for(i=0;i<4;i++){
        UART_PutChar(txData[txCount]);
        txCount++;
    }
    if(txCount == 4096) isr_Stop();
    txCountISR++;
}
CY_ISR(rxInterrupt){
    rxData[rxCount] = UART_GetChar();
    rxCount++;
    if(rxCount == 4096){
        flag = 1;
        isr_1_Stop();
    }
    rxCountISR++;
}
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    LCD_Start();

    for(i=0;i<4096;i++){
        txData[i] = i;
        rxData[i] = 0;
    }    
    isr_StartEx(txInterrupt);
    isr_1_StartEx(rxInterrupt);
    while(flag != 1); //Idle until all the data is recieved
    for(i=0;i<4096;i++){
        if(txData[i] != rxData[i]) error++;
    }    
    for(;;)
    {
        /* Place your application code here. */
        LCD_ClearDisplay();
        LCD_PrintString("Error:");
        LCD_PrintNumber(error);
        LCD_Position(1,0);
        LCD_PrintString("TX:");
        LCD_PrintNumber(txCountISR);
        LCD_Position(1,8);
        LCD_PrintString("RX:");
        LCD_PrintNumber(rxCountISR);
        CyDelay(200);
    }
}

/* [] END OF FILE */
