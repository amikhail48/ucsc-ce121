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

uint32 freq, count, previous, diff, dutyCycle;
int32 ans, period;
double timerPeriod;

CY_ISR(InterruptHandler){
   
    count = Counter_ReadCounter(); //Clear Counter after reading
    timerPeriod = .002;
    freq = count/timerPeriod;
    Timer_ReadStatusRegister();
    Counter_WriteCounter(0x0000);
 
    /*
    count = Counter_ReadCounter(); //Remember previous count 
    diff = count - previous;
    previous = count;
    timerPeriod = .002;
    freq = diff/timerPeriod;
    Timer_ReadStatusRegister();
    */
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Start();
    isr_StartEx(InterruptHandler);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_Start();
    ADC_StartConvert();
    PWM_Start(); 
    LCD_Start();
    Counter_Start();
    Timer_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        /*PART 2*/
        LCD_ClearDisplay();
        LCD_PrintInt32(freq);
        ans = ADC_Read32(); //Get pot value
        if( ans > 0xFFF0){ //Pot turned to the rightmost
            period = 1;
            PWM_WritePeriod(period);
            PWM_WriteCompare(period);
        }else if(ans < 0x0005){ //Pot turned to the leftmost
            period = 24000;
            PWM_WritePeriod(period);
            PWM_WriteCompare(period);
        }else{
            period = 24000-(ans*0.36621);
            PWM_WritePeriod(period/4);
            PWM_WriteCompare(period/4);
        }
        LCD_Position(1,0);
        LCD_PrintInt32(24000000/(1+PWM_ReadPeriod())); //Expected frequency
        CyDelay(300);
    }
}

/* [] END OF FILE */
