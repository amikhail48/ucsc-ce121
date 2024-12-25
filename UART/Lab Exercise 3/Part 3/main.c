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
int errorflag, loc;

CY_ISR(txInterrupt){
    /* TX Interrupt on TX FIFO Empty
       Size of TX FIFO is 4 bytes so we put 4 bytes in */
        for(i=0;i<4;i++){
        UART_PutChar(txData[txCount]);
        txCount++;
    }    
    if(txCount == 4096) isr_Stop();
    txCountISR++;
}
CY_ISR(timerInterrupt){
    if((UART_ReadRxStatus()&UART_RX_STS_OVERRUN)||(UART_ReadRxStatus()&UART_RX_STS_PAR_ERROR)
    ||(UART_ReadRxStatus()&UART_RX_STS_STOP_ERROR)) 
        errorflag++;
   // if(UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY){
        rxData[rxCount] = UART_GetChar();
        rxCount++;
    //}  
    /* Using the if statement above checks if byte recieved
       However, it needs to be commented out for Part 3a. The TX FIFO trasmits 
       all of its data before the RX FIFO is able to recieve it*/
    //LCD_PrintNumber(txCount);
    //LCD_PrintString(" ");
    
    if(rxCount == 4096){
        Timer_Stop();
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
    Timer_Start();
    for(i=0;i<4096;i++){
        txData[i] = i;
        rxData[i] = 0;
    }    
    isr_StartEx(txInterrupt);
    isr_1_StartEx(timerInterrupt);
    while(flag != 1){}; //Idle until all the data is recieved
    
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
        LCD_PrintString("Errflag:");
        LCD_PrintNumber(errorflag);
        CyDelay(200);
    }
}

/* [] END OF FILE */
