#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// Mikrodenetleyici bellek haritalari
#include "inc/hw_memmap.h"

// Donanim tip tanimlari
#include "inc/hw_types.h"

// Sistem saat ayarlari icin DriverLib
#include "driverlib/sysctl.h"

// SysTick zamanlayici surucusu
#include "driverlib/systick.h"

// LCD surucu fonksiyonlari
#include "lcd.h"

// SysTick kesmesi her 1 ms'de bir bu degiskeni artirir
volatile uint32_t tick = 0;

// SysTick kesme fonksiyonu
// SysTick sayaci her doldugunda otomatik calisir
void SysTick_Handler(void)
{
    tick++;
}

// 1 saniyelik gecikme olusturan fonksiyon
// 1000 adet 1 ms'lik SysTick artisini bekler
void delay1s(void)
{
    uint32_t start = tick;
    while((tick - start) < 1000);
}

int main(void)
{
    // Sistem saat ayari
    // PLL aktif
    // 16 MHz harici kristal
    // Saat: 16MHz / 5 * PLL = 40 MHz
    SysCtlClockSet(
        SYSCTL_SYSDIV_5 |
        SYSCTL_USE_PLL |
        SYSCTL_XTAL_16MHZ |
        SYSCTL_OSC_MAIN
    );

    // SysTick periyodu 1 ms olacak sekilde ayarlanir
    SysTickPeriodSet(SysCtlClockGet() / 1000);

    // SysTick sayaci aktif edilir
    SysTickEnable();

    // SysTick kesmesi aktif edilir
    SysTickIntEnable();

    // LCD baslatma fonksiyonu
    Lcd_init();

    // Saat degiskenleri
    int h = 0;
    int m = 0;
    int s = 0;

    // LCD'ye yazilacak saat metni (hh:mm:ss)
    char zaman[9];

    while(1)
    {
        // Saat bilgisini string formatina cevir
        sprintf(zaman, "%02d:%02d:%02d", h, m, s);

        // LCD imlecini 2. satir 9. sutuna getir
        Lcd_Goto(2, 9);

        // Saat bilgisini LCD'ye yaz
        Lcd_Puts(zaman);

        // 1 saniye bekle
        delay1s();

        // Saniyeyi artir
        s++;

        // 60 saniye dolunca dakikayi artir
        if(s == 60)
        {
            s = 0;
            m++;
        }

        // 60 dakika dolunca saati artir
        if(m == 60)
        {
            m = 0;
            h++;
        }

        // 24 saat dolunca sifirla
        if(h == 24)
        {
            h = 0;
        }
    }
}
