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
    ADC_Start();
    ADC_StartConvert();
    PWM_Start(); 
    LCD_Start();
    Clock_Start();
    int32 ans;
    int32 ans1;
    for(;;)
    {
        /* Place your application code here. */
        /*PART 0
        Turning on the LED*/
        LED_Write(1); /*Component API Method*/
        CyDelay(500);
        LED_Write(0);
        CyDelay(500);
       
        CyPins_SetPin(CYREG_PRT6_PC2); /*Per-Pin Method*/
        CyDelay(500);
        CyPins_ClearPin(CYREG_PRT6_PC2);
        CyDelay(500);
        
        Control_Reg_1_Write(1); /*Control Register Method*/
        CyDelay(500);
        Control_Reg_1_Write(0);
        CyDelay(500);
        
        /*PART 1 */
        CyDelay(200);
        LCD_ClearDisplay();
        ans = ADC_Read16(); //Reading Pot value as 16 bit number
        if(ans >= 0xFFFF) ans=0xFFFF;
        if(ans <= 0x0000) ans=0x0000;
        LCD_PrintInt16(ans);
        PWM_WriteCompare(ans * 999 / ((1 << 16)));
        
        LCD_Position(1,0);
        ans1 = ADC_Read32(); //Reading Pot value as 32 bit number
        if(ans1 >= 0xFFFF) ans1=0xFFFF;
        if(ans1 <= 0x0000) ans1=0x0000;
        LCD_PrintInt32(ans1);
        CyDelay(200);   
    }
}

/* [] END OF FILE */
