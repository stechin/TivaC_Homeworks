#ifndef LCD_H_
#define LCD_H_

#define LCDPORT                          GPIO_PORTB_BASE
#define LCDPORTENABLE    				 SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7

void Lcd_Komut(unsigned char);  //Lcd ye komut gondermeye yarar
void Lcd_Temizle(void);                 //Lcd ekranini temizler
void Lcd_Puts(char*);                   //String ifade yazdiriyor
void Lcd_Goto(char,char);               //Kursoru istenilen yere gonderir
void Lcd_init(void);                    //Lcd baslangic ayarlari
void Lcd_Putch(unsigned char);  //Tek karekter yazdiriyor

#endif /* LCD_H_ */
