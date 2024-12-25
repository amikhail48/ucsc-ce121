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

int32 pot;

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_Start();
    ADC_StartConvert();
    PWM_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Row0Col0_Write(0b001);
    Row0Col1_Write(0b100);
    Row0Col2_Write(0b100);
    Row0Col3_Write(0b001);
    
    Row1Col0_Write(0b001);
    Row1Col1_Write(0b010);
    Row1Col2_Write(0b010);
    Row1Col3_Write(0b001);
    
    Row2Col0_Write(0b001);
    Row2Col1_Write(0b010);
    Row2Col2_Write(0b010);
    Row2Col3_Write(0b001);
    
    Row3Col0_Write(0b001);
    Row3Col1_Write(0b100);
    Row3Col2_Write(0b100);
    Row3Col3_Write(0b001);
    
    for(;;)
    {
        /* Place your application code here. */
        pot = ADC_Read32(); //Get pot value
        if( pot >= 0xFFF0) pot = 0xFFFF; //Pot turned to the rightmost
        if( pot <= 0x0005) pot = 0x0000; //Pot turned to the leftmost
        PWM_WriteCompare( (pot*255)/0xFFFF ); //Change duty cycle from 0 to 255
    
    }
}

/* [] END OF FILE */