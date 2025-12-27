using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO.Ports;

namespace bb3
{
    public partial class MainForm : Form
    {
        // Seri porttan gelen veriyi arayuz thread'inde gostermek icin kullanilan delegate
        // DataReceived olayi farkli bir thread'de calistigi icin zorunludur
        delegate void VeriGosterDelegate(string s);

        // Form olusturulurken calisan yapici metot
        public MainForm()
        {
            InitializeComponent();
        }

        // Seri portu acma butonuna basildiginda calisir
        void ButtonPortAcClick(object sender, EventArgs e)
        {
            try
            {
                // Port zaten aciksa tekrar acma
                if(serialPort1.IsOpen) return;

                // Kullanicinin girdigi port adini ayarla
                serialPort1.PortName = TextBoxPortNo.Text.Trim().ToUpper();

                // Haberlesme hizini 9600 baud olarak ayarla
                serialPort1.BaudRate = 9600;

                // Seri portu ac
                serialPort1.Open();

                // Buton durumlarini guncelle
                ButtonPortAc.Enabled = false;
                ButtonPortKapat.Enabled = true;

                // Kullaniciya bilgi ver
                MessageBox.Show("Baglanti Basarili!");
            }
            catch (Exception ex)
            {
                // Port acma sirasinda olusan hatalari goster
                MessageBox.Show("Hata: " + ex.Message);
            }
        }

        // Seri portu kapatma butonuna basildiginda calisir
        void ButtonPortKapatClick(object sender, EventArgs e)
        {
            // Port aciksa kapat
            if(serialPort1.IsOpen)
            {
                serialPort1.Close();

                // Buton durumlarini eski haline getir
                ButtonPortAc.Enabled = true;
                ButtonPortKapat.Enabled = false;
            }
        }

        // Mikrodenetleyiciye saat bilgisini gonderen buton olayi
        void ButtonSaatGonderClick(object sender, EventArgs e)
        {
            // Port acik degilse islem yapma
            if(!serialPort1.IsOpen) return;

            // Kullanicinin girdigi saat metnini al
            string girilenSaat = TextBoxSaat.Text;

            // Sadece rakamlari tutmak icin kullanilan string
            string temizSaat = "";

            // Girilen metin icinden sadece sayilari ayikla
            foreach(char c in girilenSaat)
                if(char.IsDigit(c))
                    temizSaat += c;

            // Saat bilgisi 6 haneli degilse hatali kabul et
            if(temizSaat.Length != 6)
            {
                MessageBox.Show("Hatali saat formati!");
                return;
            }

            // 'Z' komutu ile birlikte saat bilgisini seri porttan gonder
            serialPort1.Write("Z" + temizSaat);
        }

        // LCD'de gosterilecek metni gonderen buton olayi
        void ButtonMetinGonderClick(object sender, EventArgs e)
        {
            // Port acik degilse islem yapma
            if(!serialPort1.IsOpen) return;

            // Kullanicinin girdigi metni al
            string metin = TextBoxMetin.Text;

            // Metin 3 karakterden kisa ise saga bosluk ekle
            if(metin.Length < 3)
                metin = metin.PadRight(3);

            // Metin 3 karakterden uzunsa ilk 3 karakteri al
            else if(metin.Length > 3)
                metin = metin.Substring(0, 3);

            // 'M' komutu ile birlikte metni seri porttan gonder
            serialPort1.Write("M" + metin);
        }

        // Form kapatilirken calisan olay
        void MainFormFormClosing(object sender, FormClosingEventArgs e)
        {
            // Program kapanmadan once seri port aciksa kapat
            if(serialPort1.IsOpen)
                serialPort1.Close();
        }

        // Seri porttan veri geldigi anda otomatik olarak calisan olay
        // Bu olay arayuz disi bir thread'de calisir
        void SerialPort1DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                // Mikrodenetleyiciden gelen satirin tamamini oku
                // Format: #12:34:56,2048,1
                string gelenSatir = serialPort1.ReadLine();

                // Gelen veriyi arayuz thread'ine aktar
                this.BeginInvoke(
                    new VeriGosterDelegate(ArayuzuGuncelle),
                    new object[] { gelenSatir }
                );
            }
            catch
            {
                // Okuma sirasinda olusan hatalar sessizce yoksayilir
            }
        }

        // Gelen veriye gore arayuzu guncelleyen fonksiyon
        void ArayuzuGuncelle(string veri)
        {
            // Veri bos ise veya protokol baslangic karakteri yoksa cik
            if(string.IsNullOrEmpty(veri) || !veri.StartsWith("#"))
                return;

            // Baslangic karakterini at ve bosluklari temizle
            veri = veri.Trim().Substring(1);

            // Veriyi virgul karakterine gore parcalara ayir
            // [0] = Saat, [1] = ADC, [2] = Buton durumu
            string[] parcalar = veri.Split(',');

            // Beklenen paket formati saglanmiyorsa cik
            if(parcalar.Length == 3)
            {
                // Saat bilgisini ekranda goster
                TextBoxGelenSaat.Text = parcalar[0];

                // ADC degerini ekranda goster
                TextBoxGelenADC.Text = parcalar[1];

                // Buton durumu 1 ise basili olarak yorumla
                if(parcalar[2] == "1")
                {
                    TextBoxGelenButon.Text = "Butona BASILDI";
                    TextBoxGelenButon.BackColor = Color.Red;
                    TextBoxGelenButon.ForeColor = Color.White;
                }
                else
                {
                    // Buton basili degilse normal durum
                    TextBoxGelenButon.Text = "Normal";
                    TextBoxGelenButon.BackColor = Color.White;
                    TextBoxGelenButon.ForeColor = Color.Black;
                }
            }
        }
    }
}
