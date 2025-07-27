// 2-Bit Comparator Implementation
// Include required header files
#include<stdio.h>
#include<debug.h>
#include<ch32v00x.h>

// GPIO Configuration Function
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // Enable clock for GPIOD and GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // Configure input pins (PD1-PD4) for 2-bit inputs A and B
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-up
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // Configure output pins (PC4-PC6) for comparison results
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Output push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// Main function
int main()
{
    uint8_t A1, A0, B1, B0;
    uint8_t A_greater_B, A_less_B, A_equal_B;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();
    
    while(1)
    {
        // Read input values
        A1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1); // MSB of A
        A0 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2); // LSB of A
        B1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3); // MSB of B
        B0 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4); // LSB of B
        
        // 2-bit comparison logic
        // A = B condition
        A_equal_B = ((A1 == B1) && (A0 == B0));
        
        // A > B condition
        A_greater_B = ((A1 > B1) || ((A1 == B1) && (A0 > B0)));
        
        // A < B condition  
        A_less_B = ((A1 < B1) || ((A1 == B1) && (A0 < B0)));
        
        // Set outputs (Active LOW LEDs)
        GPIO_WriteBit(GPIOC, GPIO_Pin_4, A_greater_B ? RESET : SET); // A>B LED
        GPIO_WriteBit(GPIOC, GPIO_Pin_5, A_less_B ? RESET : SET);    // A<B LED
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, A_equal_B ? RESET : SET);   // A=B LED
        
        Delay_Ms(100); // Small delay for debouncing
    }
}
