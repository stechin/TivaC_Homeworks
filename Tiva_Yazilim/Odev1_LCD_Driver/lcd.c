#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "lcd.h"

// Mikro saniye cinsinden gecikme olusturan fonksiyon
// LCD enable palsi ve zamanlama icin kullanilir
static void delayUs(int n){
    SysCtlDelay((SysCtlClockGet()/3000000)*n);
}

// Mili saniye cinsinden gecikme olusturan fonksiyon
// LCD baslatma ve temizleme sureleri icin kullanilir
static void delayMs(int n){
    SysCtlDelay((SysCtlClockGet()/3000)*n);
}

// LCD'ye 4 bitlik veri (nibble) yazan dusuk seviye fonksiyon
// D4-D7 pinleri uzerinden veri gonderir ve enable palsi olusturur
static void Lcd_YazNibble(unsigned char d){

    // Veri pinlerini sifirla
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, 0);

    // Gonderilecek nibble icindeki bitlere gore ilgili pinleri set et
    if(d & 0x10) GPIOPinWrite(LCDPORT, D4, D4);
    if(d & 0x20) GPIOPinWrite(LCDPORT, D5, D5);
    if(d & 0x40) GPIOPinWrite(LCDPORT, D6, D6);
    if(d & 0x80) GPIOPinWrite(LCDPORT, D7, D7);

    // Enable pinini 1 yaparak LCD'ye veriyi kilitle
    GPIOPinWrite(LCDPORT, E, E);
    delayUs(40);

    // Enable pinini 0 yaparak yazma islemini tamamla
    GPIOPinWrite(LCDPORT, E, 0);
}

// LCD'ye komut gonderen fonksiyon
// RS=0 yapilarak komut modu secilir
void Lcd_Komut(unsigned char k){

    // RS pinini sifirla (komut modu)
    GPIOPinWrite(LCDPORT, RS, 0);

    // Komutun once ust 4 biti gonderilir
    Lcd_YazNibble(k & 0xF0);

    // Ardindan alt 4 bit gonderilir
    Lcd_YazNibble((k << 4) & 0xF0);

    // Temel komutlar icin uzun, digerleri icin kisa gecikme verilir
    if(k < 4)
        delayMs(2);
    else
        delayUs(40);
}

// LCD'ye tek karakter yazan fonksiyon
// RS=1 yapilarak veri modu secilir
void Lcd_Putch(unsigned char c){

    // RS pinini set et (veri modu)
    GPIOPinWrite(LCDPORT, RS, RS);

    // Karakterin ust 4 bitini gonder
    Lcd_YazNibble(c & 0xF0);

    // Karakterin alt 4 bitini gonder
    Lcd_YazNibble((c << 4) & 0xF0);

    // LCD yazma suresi icin kisa gecikme
    delayUs(40);
}

// LCD'yi 4 bit modda calisacak sekilde baslatan fonksiyon
void Lcd_init(void){

    // LCD portunun saat sinyalini aktif et
    SysCtlPeripheralEnable(LCDPORTENABLE);

    // Port hazir olana kadar bekle
    while(!SysCtlPeripheralReady(LCDPORTENABLE));

    // RS, E ve veri pinlerini cikis olarak ayarla
    GPIOPinTypeGPIOOutput(LCDPORT, RS | E | D4 | D5 | D6 | D7);

    // LCD'nin guclenmesini bekle
    delayMs(20);

    // RS ve E pinlerini sifirla
    GPIOPinWrite(LCDPORT, RS | E, 0);

    // LCD'yi 8 bit moddan 4 bit moda gecis icin ozel baslatma dizisi
    Lcd_YazNibble(0x30); delayMs(5);
    Lcd_YazNibble(0x30); delayUs(100);
    Lcd_YazNibble(0x30);
    Lcd_YazNibble(0x20);

    // 4 bit, 2 satir, 5x8 font ayari
    Lcd_Komut(0x28);

    // Ekrani ac, imleci kapat
    Lcd_Komut(0x0C);

    // Yazma yonunu saga dogru ayarla
    Lcd_Komut(0x06);

    // Ekrani temizle
    Lcd_Komut(0x01);
    delayMs(2);
}

// LCD ekranini temizleyen fonksiyon
void Lcd_Temizle(void){
    Lcd_Komut(0x01);
    delayMs(2);
}

// LCD uzerinde imleci istenen satir ve sutuna goturen fonksiyon
void Lcd_Goto(char r, char c){

    // Birinci satir icin DDRAM adresi ayari
    if(r == 1)
        Lcd_Komut(0x80 + (c - 1));

    // Ikinci satir icin DDRAM adresi ayari
    if(r == 2)
        Lcd_Komut(0xC0 + (c - 1));
}

// LCD'ye null sonlandirmali string yazan fonksiyon
void Lcd_Puts(char *s){
    while(*s)
        Lcd_Putch(*s++);
}
