#include "stdint.h"
#include "stdbool.h"

// Tiva C serisi mikrodenetleyiciler icin donanim kesme tanimlari
#include "inc/hw_ints.h"

// Donanim tip tanimlarini icerir
#include "inc/hw_types.h"

// Mikrodenetleyicinin bellek haritalarini tanimlar
#include "inc/hw_memmap.h"

// Sistem saat ayarlari ve PLL konfigurasyonu icin kullanilir
#include "driverlib/sysctl.h"

// GPIO port kontrol fonksiyonlarini icerir
#include "driverlib/gpio.h"

// LCD surucu fonksiyonlarinin tanimlandigi baslik dosyasi
#include "Lcd.h"

int main(void)
{
        // Sistem saatini ayarla
        // PLL aktif edilir
        // Harici 16 MHz kristal kullanilir
        // Saat frekansi 16MHz / 4 = 40 MHz olarak ayarlanir
        SysCtlClockSet(
                        SYSCTL_SYSDIV_4 |
                        SYSCTL_USE_PLL |
                        SYSCTL_XTAL_16MHZ |
                        SYSCTL_OSC_MAIN
                      );

        // LCD donanimini ve portlarini baslat
        Lcd_init();_
