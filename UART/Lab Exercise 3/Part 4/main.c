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
int temp, temp2;
int txThroughPut, rxThroughPut;

CY_ISR(txInterrupt){
    //Size of TX FIFO is 4 bytes so we put 4 bytes in 
    for(i=0;i<4;i++){
        UART_PutChar(txData[txCount]);
        txCount++;
    }
    //Reset Count back to 0 to keep transmitting
    if(txCount == 4096) txCount=0;
     //   isr_Stop();
}
CY_ISR(rxInterrupt){
    //Check for any Errors
    if((UART_ReadRxStatus()&UART_RX_STS_OVERRUN)||(UART_ReadRxStatus()&UART_RX_STS_PAR_ERROR)
    ||(UART_ReadRxStatus()&UART_RX_STS_STOP_ERROR))
        error++;
    //Check if byte recieved and if it matches transmit array
    if(UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY){
        rxData[rxCount] = UART_GetChar();
        if(rxData[rxCount] != txData[rxCount]) error++;
        rxCount++;
    }
    //Reset Count back to 0 to keep recieving   
    if(rxCount == 4096){
       rxCount = 0;
        // Timer_Stop();
        //flag = 1;
        //isr_1_Stop();
    }
}
CY_ISR(timerInterrupt){
    //Print out error and throughput every second
    LCD_ClearDisplay();
    txThroughPut = (txCount)*1000;
    rxThroughPut = (rxCount)*1000;

    LCD_PrintString("Error:");
    LCD_PrintNumber(error);
    LCD_Position(1,0);
    LCD_PrintString("T:");
    LCD_PrintNumber(txThroughPut);
    LCD_Position(1,8);
    LCD_PrintString("R:");
    LCD_PrintNumber(rxThroughPut);

}
 void main()
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
    isr_1_StartEx(rxInterrupt);
    isr_2_StartEx(timerInterrupt);
    
    //while(flag != 1); //Idle until all the data is recieved

}

/* [] END OF FILE */
