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

uint8 red[4][4];
uint8 green[4][4];
uint8 blue[4][4];
uint8 color;

int i, j, k, row=0, col=0;

CY_ISR(timerInterrupt){
    i = row++ %4;
    outputEnable_Write(1); /* Clear display */
    rowSelect_Write(i);
    for(j=0; j<4; j++){
        color = 0b000;
        if(red[i][j]) color = 0b001;
        if(green[i][j]) color = 0b010;
        if(blue[i][j]) color = 0b100;
        color_Write(color);   
            
        clock_Write(0b1);
        clock_Write(0b0);
    }
    color_Write(0b000); /*Blank out rest of columns*/    
    for(k = 0; k < 28; k++){ /*Clock high to low for rest of 28*/
        clock_Write(0b1);
        clock_Write(0b0);
    }
    latch_Write(0b1);
    latch_Write(0b0);
    outputEnable_Write(0);
}

int main()
{
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            red[i][j] = 0;
            green[i][j] = 0;
            blue[i][j] = 0;
        }
    }
        
        red[0][0] = 1;
        red[0][1] = 1;
        red[0][2] = 1;
        red[0][3] = 1;
        /*
        red[1][0] = 1;
        red[1][1] = 1;
        red[1][2] = 1;
        red[1][3] = 1;
        
        red[2][0] = 1;
        red[2][1] = 1;
        red[2][2] = 1;
        red[2][3] = 1;
        */
        red[3][0] = 1;
        red[3][1] = 1;
        red[3][2] = 1;
        red[3][3] = 1;
        
        //------------------
        /*
        green[0][0]=1;
        green[0][1]=1;
        green[0][2]=1;
        green[0][3]=1;
        */
        green[1][0]=1;
        green[1][1]=1;
        green[1][2]=1;
        green[1][3]=1;
        
        green[2][0] = 1;
        green[2][1] = 0;
        green[2][2] = 0;
        green[2][3] = 1;
        /*
        green[3][0] = 1;
        green[3][1] = 1;
        green[3][2] = 1;
        green[3][3] = 1;
        */
       //---------------------
        
        blue[0][0] = 1;
        blue[0][1] = 1;
        blue[0][2] = 1;
        blue[0][3] = 1;
        /*
        blue[1][0]=1;
        blue[1][1]=1;
        blue[1][2]=1;
        blue[1][3]=1;
        
        blue[2][0]=1;
        blue[2][1]=1;
        blue[2][2]=1;
        blue[2][3]=1;
        
        blue[3][0] = 1;
        blue[3][1] = 1;
        blue[3][2] = 1;
        blue[3][3] = 1;
        */
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timer_Start();
    isr_StartEx(timerInterrupt);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
