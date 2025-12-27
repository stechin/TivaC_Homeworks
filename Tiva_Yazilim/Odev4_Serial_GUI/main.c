#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "lcd.h"

// Saat, dakika ve saniye bilgisini tutan global degiskenler
// volatile kullanimi kesme fonksiyonunda degistirildikleri icin gereklidir
volatile uint8_t saat = 0, dakika = 0, saniye = 0;

// LCD'nin guncellenmesi gerekip gerekmedigini tutan bayrak
volatile bool ekranGuncelle = true;

// LCD'de gosterilecek 3 karakterlik ozel metin
char ozelMetin[4] = "   ";

// ADC donusum sonucunu tutan dizi
uint32_t adcDegeri[1];

// Timer kesmesi ile main dongusu arasinda senkronizasyon saglayan bayrak
volatile bool veriGonder = false;

// Milisaniye cinsinden gecikme olusturan fonksiyon
// Sistem saatine bagli olarak SysCtlDelay kullanir
void delayMs(uint32_t ms) {
    SysCtlDelay((SysCtlClockGet() / 3000) * ms);
}

// UART uzerinden string veri gonderen fonksiyon
// String sonuna gelene kadar karakterleri tek tek yollar
void UART_Puts(char *s) {
    while(*s) {
        UARTCharPut(UART0_BASE, *s++);
    }
}

// UART uzerinden veri gelene kadar bekleyen guvenli okuma fonksiyonu
char UART_GetC_Safe(void){
    while(!UARTCharsAvail(UART0_BASE));
    return UARTCharGet(UART0_BASE);
}

// Timer0 tasma kesmesi geldiginde calisan kesme fonksiyonu
// Her 1 saniyede bir zaman bilgisini gunceller
void Timer0IntHandler(void)
{
    // Timer kesme bayragini temizle
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Saniyeyi bir arttir
    saniye++;

    // 60 saniye dolunca dakikayi arttir
    if(saniye >= 60){
        saniye = 0;
        dakika++;

        // 60 dakika dolunca saati arttir
        if(dakika >= 60){
            dakika = 0;
            saat++;

            // 24 saat dolunca basa don
            if(saat >= 24) saat = 0;
        }
    }

    // LCD guncellemesini tetikle
    ekranGuncelle = true;

    // PC'ye veri gonderimini tetikle
    veriGonder = true;
}

int main(void) {

    // Sistem saatini PLL kullanarak ayarla
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // UART, GPIO, TIMER ve ADC cevre birimlerini aktif et
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // PF1 pinini LED cikisi olarak ayarla
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    // PF4 pinini buton girisi olarak ayarla
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    // PF4 pini icin dahili pull-up direncini aktif et
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // PE3 pinini ADC analog girisi olarak ayarla
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    // ADC0 modulunde sequencer 3'u tek ornek alacak sekilde ayarla
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    // ADC sequencer adimini AIN0 kanali, kesme ve son adim olarak ayarla
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    // ADC sequencer'i aktif et
    ADCSequenceEnable(ADC0_BASE, 3);

    // ADC kesme bayragini temizle
    ADCIntClear(ADC0_BASE, 3);

    // UART pinlerini alternatif fonksiyon olarak ayarla
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // PA0 ve PA1 pinlerini UART modu olarak ayarla
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // UART'i 9600 baud, 8 bit veri, 1 stop biti ve paritesiz olarak ayarla
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // LCD'yi baslat ve ilk mesaji goster
    Lcd_init();
    Lcd_Temizle();
    Lcd_Puts("Sistem Aciliyor");
    delayMs(1000);
    Lcd_Temizle();

    // Timer0'i periyodik modda ayarla
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Timer'i 1 saniyelik periyot icin yukle
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1);

    // Timer0 kesmesini Timer0IntHandler fonksiyonu ile eslestir
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

    // Timer0 kesmesini NVIC uzerinde aktif et
    IntEnable(INT_TIMER0A);

    // Timer tasma kesmesini aktif et
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Global kesmeleri aktif et
    IntMasterEnable();

    // Timer0'i baslat
    TimerEnable(TIMER0_BASE, TIMER_A);

    // UART'tan gelen komut karakterini tutar
    char gelenKarakter;

    // Saat ayari icin gelen karakterleri tutar
    char buffer[10];

    // PC'ye gonderilecek veri paketini tutar
    char gidenPaket[50];

    while(1) {

        // UART uzerinden veri gelip gelmedigini kontrol et
        if(UARTCharsAvail(UART0_BASE)){

            // UART verisi geldiginde LED'i yak
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

            // Ilk karakteri oku
            gelenKarakter = UARTCharGet(UART0_BASE);

            // 'Z' komutu geldiyse saat ayari yap
            if(gelenKarakter == 'Z'){
                buffer[0] = UART_GetC_Safe();
                buffer[1] = UART_GetC_Safe();
                buffer[2] = UART_GetC_Safe();
                buffer[3] = UART_GetC_Safe();
                buffer[4] = UART_GetC_Safe();
                buffer[5] = UART_GetC_Safe();

                // ASCII karakterleri sayisal degere cevir
                saat   = (buffer[0]-'0')*10 + (buffer[1]-'0');
                dakika = (buffer[2]-'0')*10 + (buffer[3]-'0');
                saniye = (buffer[4]-'0')*10 + (buffer[5]-'0');

                // LCD guncellemesini tetikle
                ekranGuncelle = true;
            }

            // 'M' komutu geldiyse ozel metni guncelle
            else if(gelenKarakter == 'M'){
                ozelMetin[0] = UART_GetC_Safe();
                ozelMetin[1] = UART_GetC_Safe();
                ozelMetin[2] = UART_GetC_Safe();
                ozelMetin[3] = '\0';

                // LCD guncellemesini tetikle
                ekranGuncelle = true;
            }

            // Kisa bir gecikme ver
            delayMs(50);

            // LED'i sondur
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        }

        // LCD'nin guncellenmesi gerekiyorsa ekrani yeniden ciz
        if(ekranGuncelle){
            ekranGuncelle = false;

            // Ilk satira saat bilgisini yaz
            Lcd_Goto(1,1);
            Lcd_Puts("Saat: ");
            Lcd_Putch(saat/10 + '0');
            Lcd_Putch(saat%10 + '0');
            Lcd_Putch(':');
            Lcd_Putch(dakika/10 + '0');
            Lcd_Putch(dakika%10 + '0');
            Lcd_Putch(':');
            Lcd_Putch(saniye/10 + '0');
            Lcd_Putch(saniye%10 + '0');

            // Ikinci satira ozel metni yaz
            Lcd_Goto(2,1);
            Lcd_Puts("Metin: ");
            Lcd_Puts(ozelMetin);
        }

        // Timer kesmesi veri gonderimini tetiklediyse
        if(veriGonder){
            veriGonder = false;

            // ADC donusumunu baslat
            ADCProcessorTrigger(ADC0_BASE, 3);

            // ADC donusumu tamamlanana kadar bekle
            while(!ADCIntStatus(ADC0_BASE, 3, false));

            // ADC sonucunu oku
            ADCSequenceDataGet(ADC0_BASE, 3, adcDegeri);

            // PF4 buton durumunu oku ve mantiksal olarak tersle
            int btnDurum = (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0) ? 1 : 0;

            // Saat, ADC ve buton bilgisini iceren veri paketini olustur
            sprintf(gidenPaket, "#%02d:%02d:%02d,%d,%d\n",
                    saat, dakika, saniye, (int)adcDegeri[0], btnDurum);

            // Olusturulan paketi UART uzerinden gonder
            UART_Puts(gidenPaket);
        }
    }
}
