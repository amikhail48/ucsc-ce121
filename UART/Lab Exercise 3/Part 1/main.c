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

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint8 value = 0x45;
    uint8 value2 = 0x5A;
    uint8 txData[4096];
    uint8 rxData[4096];
    int time;
    int i, j, txFifoNotFull, rxFifoNotEmpty, error=0;
    UART_Start();
    LCD_Start();

    /*Intialize Transfer and Receive Data Arrays*/
    for(i=0;i<4096;i++){
        txData[i] = i;
        rxData[i] = 0;
    }
    i = 0;
    j = 0;
    while(i<4096){
        rxFifoNotEmpty = UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY;
        if(rxFifoNotEmpty){
            rxData[i] = UART_GetChar();             
            if(i == 0) Timer_Start();
            if(i == 4095) Timer_Stop(); //Best Place to Stop Timer
            i++;
        }
        txFifoNotFull = UART_ReadTxStatus() & UART_TX_STS_FIFO_NOT_FULL;
        if(txFifoNotFull){
            UART_PutChar(txData[j]);
            j++;
        }
    }    
    for(i=0;i<4096;i++){
        if(txData[i] != rxData[i]) error++;
    }
    
    for(;;)
    {
        /* Place your application code here. */
        //UART_PutChar(value);
        //UART_PutChar(value2);
        
        LCD_ClearDisplay();
        LCD_PrintString("Errors:");
        LCD_PrintNumber(error);
        LCD_Position(1,0);
        LCD_PrintString("Time:");
        time = (4294967296-Timer_ReadCounter())/24000;
        LCD_PrintNumber(time);
        CyDelay(200);
    }
}

/* [] END OF FILE */
