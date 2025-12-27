#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// Donanim bellek haritalari
#include "inc/hw_memmap.h"

// Donanim tip tanimlari
#include "inc/hw_types.h"

// Kesme numaralari
#include "inc/hw_ints.h"

// Sistem saat ayarlari
#include "driverlib/sysctl.h"

// GPIO surucusu
#include "driverlib/gpio.h"

// ADC surucusu
#include "driverlib/adc.h"

// Timer surucusu
#include "driverlib/timer.h"

// Kesme kontrol surucusu
#include "driverlib/interrupt.h"

// LCD surucu fonksiyonlari
#include "Lcd.h"

// ADC0' dan okunacak deger dizisi
uint32_t ui32ADC0Value[1];

// Saat degiskenleri (kesme icinde kullanildigi icin volatile)
volatile uint8_t hours = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;

// Ekranin guncellenmesi gerektigini belirten bayrak
volatile bool updateScreen = false;

// LCD ikinci satir icin buffer (16 karakter + null)
char bufferLine2[17];

// Timer0 kesme fonksiyonu
// Her 1 saniyede bir otomatik calisir
void Timer0IntHandler(void)
{
    // Timer kesme bayragini temizle
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Saniyeyi artir
    seconds++;

    // 60 saniyede dakikayi artir
    if (seconds > 59)
    {
        seconds = 0;
        minutes++;

        // 60 dakikada saati artir
        if (minutes > 59)
        {
            minutes = 0;
            hours++;

            // 24 saat sonunda sifirla
            if (hours > 23)
            {
                hours = 0;
            }
        }
    }

    // Ana donguye LCD guncelleme sinyali ver
    updateScreen = true;
}

int main(void)
{
    // Sistem saat ayari
    // PLL aktif
    // Harici 16 MHz kristal
    // Saat frekansi: 40 MHz
    SysCtlClockSet(
        SYSCTL_SYSDIV_2_5 |
        SYSCTL_USE_PLL |
        SYSCTL_OSC_MAIN |
        SYSCTL_XTAL_16MHZ
    );

    // LCD baslat
    Lcd_init();

    // LCD ekranini temizle
    Lcd_Temizle();

    // ADC0 periferigini aktif et
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // ADC pini icin GPIOE aktif et
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // PE3 pinini ADC girisi yap (AIN0)
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    // ADC0 Sequence 3 konfigure edilir
    // Yazilim tetiklemeli
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    // Tek adimli ADC okuma
    // Kanal 0
    // Kesme aktif
    // Sequence sonu
    ADCSequenceStepConfigure(
        ADC0_BASE,
        3,
        0,
        ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END
    );

    // ADC sequence aktif edilir
    ADCSequenceEnable(ADC0_BASE, 3);

    // Olası eski ADC kesme bayraklarini temizle
    ADCIntClear(ADC0_BASE, 3);

    // Timer0 periferigini aktif et
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Timer0 periyodik modda ayarlanir
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Timer periyodu 1 saniye olacak sekilde ayarlanir
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1);

    // Timer0 kesme fonksiyonu baglanir
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

    // Timer0 kesmesi NVIC uzerinden aktif edilir
    IntEnable(INT_TIMER0A);

    // Timer timeout kesmesi aktif edilir
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Global kesmeler aktif edilir
    IntMasterEnable();

    // Timer0 baslatilir
    TimerEnable(TIMER0_BASE, TIMER_A);

    // LCD ilk satira isim yaz
    Lcd_Goto(1, 1);
    Lcd_Puts("Said Tekin");

    while (1)
    {
        // Timer kesmesi ekran guncelleme izni verdiyse
        if (updateScreen)
        {
            // ADC donusumunu baslat
            ADCProcessorTrigger(ADC0_BASE, 3);

            // ADC donusumu bitene kadar bekle
            while(!ADCIntStatus(ADC0_BASE, 3, false)) {}

            // ADC kesme bayragini temizle
            ADCIntClear(ADC0_BASE, 3);

            // ADC sonucunu oku
            ADCSequenceDataGet(ADC0_BASE, 3, ui32ADC0Value);

            // Saat ve ADC degerini tek satirda formatla
            sprintf(
                bufferLine2,
                "%02d:%02d:%02d    %04u",
                hours,
                minutes,
                seconds,
                (unsigned int)ui32ADC0Value[0]
            );

            // LCD ikinci satira yaz
            Lcd_Goto(2, 1);
            Lcd_Puts(bufferLine2);

            // Guncelleme bayragini sifirla
            updateScreen = false;
        }
    }
}
