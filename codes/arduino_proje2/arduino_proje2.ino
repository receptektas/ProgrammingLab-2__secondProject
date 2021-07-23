#include <tinyFAT.h>
#include <SPI.h>

struct Hizmet
{
  char *HizmetID;
  char *HizmetAd;
  int KalanHizmetAdet;
  int HizmetFiyat;

} hizmet_1, hizmet_2, hizmet_3, hizmet_4;

byte res;
word result;

char dosyaAdi[] = "hizmetle.txt";
char okunanKarakter[31];
char *satirlar[5];
char *satirElemanlari;
char *satirlarSeti[5] = {"2,2,2,2,2", "1, Kopukleme,5, 15 TL", "2, Yikama,5, 10 TL", "3, Kurulama,5, 5 TL", "4, Cilalama,5, 50 TL"};
int kasadakiParalar[5] = {0};
int atilanParalar[5] = {0};
int iadeParalar[5] = {0};

int kalanHizmetler[4] = {0};
int secilenHizmetler[4] = {0};
int hizmetFiyatlar[4] = {0};

char aciklama[50];
char yazilacakSatir1[50];
char yazilacakSatir2[50];
char yazilacakSatir3[50];
char yazilacakSatir4[50];
char yazilacakSatir5[50];
int toplamAtilanPara = 0;
int toplamAlinanHizmet = 0;
int toplamSecilenHizmetFiyat = 0;
int toplamKasaPara = 0;
int paraUstu = 0;
int randomSayi = 0;

bool paraYukle = false;
bool dosyaOkundu = false;
bool ilkParaMesaj = false;
bool ilkServisMesaj = true;

int secimTusu_1 = 22;
int secimTusu_2 = 23;
int secimTusu_3 = 24;
int secimTusu_4 = 25;
int secimTusu_5 = 26;
int onayTusu = 27;
int resetTusu = 28;
int kirmiziLed = 29;
int yesilLed = 30;
int sdcpPin = 53;

int secimDegeri_1, secimDegeri_2, secimDegeri_3, secimDegeri_4, secimDegeri_5, secimDegeri_6, secimDegeri_7;

void setup()
{
  Serial.begin(9600);
  pinMode(secimTusu_1, INPUT);
  pinMode(secimTusu_2, INPUT);
  pinMode(secimTusu_3, INPUT);
  pinMode(secimTusu_4, INPUT);
  pinMode(secimTusu_5, INPUT);
  pinMode(onayTusu, INPUT);
  pinMode(resetTusu, INPUT);
  pinMode(yesilLed, OUTPUT);
  pinMode(kirmiziLed, OUTPUT);
  pinMode(sdcpPin, OUTPUT);
  sdKartYukle();
  delay(1000);
  dosyayaYaz(satirlarSeti);
}

void loop()
{
tekrar:
  delay(200);
  byte res;
  word result = 0;
  secimDegeri_1 = digitalRead(secimTusu_1);
  secimDegeri_2 = digitalRead(secimTusu_2);
  secimDegeri_3 = digitalRead(secimTusu_3);
  secimDegeri_4 = digitalRead(secimTusu_4);
  secimDegeri_5 = digitalRead(secimTusu_5);
  secimDegeri_6 = digitalRead(onayTusu);
  secimDegeri_7 = digitalRead(resetTusu);

  if (!dosyaOkundu)
  {
    int i = 0;
    res = file.openFile(dosyaAdi, FILEMODE_TEXT_READ);
    if (res == NO_ERROR)
    {
      while (result != EOF and result != FILE_IS_EMPTY)
      {
        result = file.readLn(okunanKarakter, 30);
        satirElemanlari = (char *)okunanKarakter;
        if (i == 0)
        {
          kasadakiParalar[0] = atoi(strtok(satirElemanlari, ","));
          kasadakiParalar[1] = atoi(strtok(NULL, ","));
          kasadakiParalar[2] = atoi(strtok(NULL, ","));
          kasadakiParalar[3] = atoi(strtok(NULL, ","));
          kasadakiParalar[4] = atoi(strtok(NULL, ","));

          Serial.println("-------------------------------------------------------");
          Serial.println("*** Kasadaki Para Miktari ***");

          String cumleBir = "5TL:";
          String cumleIki = "\n  10TL:";
          String cumleUc = "\n  20TL:";
          String cumleDort = "  50TL:";
          String cumleBes = "  100TL:";
          String paragrafParalar = cumleBir + kasadakiParalar[0] + cumleIki + kasadakiParalar[1] + cumleUc + kasadakiParalar[2] + cumleDort + kasadakiParalar[3] + cumleBes + kasadakiParalar[4];
          Serial.println(paragrafParalar);

          Serial.println("-------------------------------------------------------");
        }
        else if (i == 1)
        {
          hizmet_1.HizmetID = strtok(satirElemanlari, ",");
          hizmet_1.HizmetAd = strtok(NULL, ",");
          hizmet_1.KalanHizmetAdet = atoi(strtok(NULL, ","));
          hizmet_1.HizmetFiyat = atoi(strtok(NULL, ", "));
        }
        else if (i == 2)
        {
          hizmet_2.HizmetID = strtok(satirElemanlari, ",");
          hizmet_2.HizmetAd = strtok(NULL, ",");
          hizmet_2.KalanHizmetAdet = atoi(strtok(NULL, ","));
          hizmet_2.HizmetFiyat = atoi(strtok(NULL, ", "));
        }
        else if (i == 3)
        {
          hizmet_3.HizmetID = strtok(satirElemanlari, ",");
          hizmet_3.HizmetAd = strtok(NULL, ",");
          hizmet_3.KalanHizmetAdet = atoi(strtok(NULL, ","));
          hizmet_3.HizmetFiyat = atoi(strtok(NULL, ", "));
        }
        else if (i == 4)
        {
          hizmet_4.HizmetID = strtok(satirElemanlari, ",");
          hizmet_4.HizmetAd = strtok(NULL, ",");
          hizmet_4.KalanHizmetAdet = atoi(strtok(NULL, ","));
          hizmet_4.HizmetFiyat = atoi(strtok(NULL, ", "));
        }

        if (result == FILE_IS_EMPTY)
        {
          Serial.println("Dosya Bos Hatatasi");
        }
        i++;
      }
      kalanHizmetler[0] = hizmet_1.KalanHizmetAdet;
      kalanHizmetler[1] = hizmet_2.KalanHizmetAdet;
      kalanHizmetler[2] = hizmet_3.KalanHizmetAdet;
      kalanHizmetler[3] = hizmet_4.KalanHizmetAdet;

      hizmetFiyatlar[0] = hizmet_1.HizmetFiyat;
      hizmetFiyatlar[1] = hizmet_2.HizmetFiyat;
      hizmetFiyatlar[2] = hizmet_3.HizmetFiyat;
      hizmetFiyatlar[3] = hizmet_4.HizmetFiyat;

      String cumleAlti = "Kopukleme:";
      String cumleYedi = "  Yikama:";
      String cumleSekiz = "  Kurulama:";
      String cumleDokuz = "  Cilalama:";

      Serial.println("*** Kalan Hizmet Miktarlari ***");
      String paragrafHizmetler = cumleAlti + kalanHizmetler[0] + cumleYedi + kalanHizmetler[1] + cumleSekiz + kalanHizmetler[2] + cumleDokuz + kalanHizmetler[3];
      Serial.println(paragrafHizmetler);
      Serial.println("-------------------------------------------------------");
      file.closeFile();
    }
    else
    {
      Serial.println("Dosya okuma hatasi");
    }
    dosyaOkundu = true;
  }

  if (!ilkParaMesaj)
  {
    Serial.println("");
    Serial.println("Butonlar Ile Para Yatirin.");
    Serial.println("");
    ilkParaMesaj = true;
  }
  if (!ilkServisMesaj)
  {
    Serial.println("");
    Serial.println("Butonlar Ile Hizmet Secin.");
    Serial.println("");
    ilkServisMesaj = true;
  }

  if (secimDegeri_1 == HIGH)
  {
    if (!paraYukle)
    {
      atilanParalar[0]++;
      //Serial.println();
      sprintf(aciklama, "%d\n adet 5 TL eklediniz.", atilanParalar[0]);
      Serial.println(aciklama);
    }
    else
    {
      if (secilenHizmetler[0] < kalanHizmetler[0])
      {
        secilenHizmetler[0]++;
        sprintf(aciklama, "%d\n adet kopukleme hizmeti istediniz.", secilenHizmetler[0]);
        Serial.println(aciklama);
      }
      else
      {
        Serial.println("Sectiginiz hizmet kalmamis!");
      }
    }
  }
  else if (secimDegeri_2 == HIGH)
  {
    if (!paraYukle)
    {
      atilanParalar[1]++;
      sprintf(aciklama, "%d\n adet 10 TL eklediniz.", atilanParalar[1]);
      Serial.println(aciklama);
    }
    else
    {
      if (secilenHizmetler[1] < kalanHizmetler[1])
      {
        secilenHizmetler[1]++;
        sprintf(aciklama, "%d\n adet yikama hizmeti istediniz.", secilenHizmetler[1]);
        Serial.println(aciklama);
      }
      else
      {
        Serial.println("Sectiginiz hizmet kalmamis!");
      }
    }
  }
  else if (secimDegeri_3 == HIGH)
  {
    if (!paraYukle)
    {
      atilanParalar[2]++;
      sprintf(aciklama, "%d\n adet 20 TL eklediniz.", atilanParalar[2]);
      Serial.println(aciklama);
    }
    else
    {
      if (secilenHizmetler[2] < kalanHizmetler[2])
      {
        secilenHizmetler[2]++;
        sprintf(aciklama, "%d\n adet kurulama hizmeti istediniz.", secilenHizmetler[2]);
        Serial.println(aciklama);
      }
      else
      {
        Serial.println("Sectiginiz hizmet kalmamis!");
      }
    }
  }
  else if (secimDegeri_4 == HIGH)
  {
    if (!paraYukle)
    {
      atilanParalar[3]++;
      sprintf(aciklama, "%d\n adet 50 TL eklediniz.", atilanParalar[3]);
      Serial.println(aciklama);
    }
    else
    {
      if (secilenHizmetler[3] < kalanHizmetler[3])
      {
        secilenHizmetler[3]++;
        sprintf(aciklama, "%d\n adet cilalama hizmeti istediniz.", secilenHizmetler[3]);
        Serial.println(aciklama);
      }
      else
      {
        Serial.println("Sectiginiz hizmet kalmamis!");
      }
    }
  }
  else if (secimDegeri_5 == HIGH)
  {
    if (!paraYukle)
    {
      atilanParalar[4]++;
      sprintf(aciklama, "%d\n adet 100 TL eklediniz.", atilanParalar[4]);
      Serial.println(aciklama);
    }
    else
    {
      Serial.println("Foksiyonsuz tus");
    }
  }
  else if (secimDegeri_6 == HIGH)
  {
    // bitti işlemi
    if (!paraYukle)
    {
      toplamAtilanPara = 0;
      for (int j = 0; j < 5; ++j) // kasadaki mevcut para toplamı (para sıkışınca iadede kullanılabilecek miktar)
      {
        if (j == 0)
        {
          toplamKasaPara += kasadakiParalar[j] * 5;
        }
        if (j == 1)
        {
          toplamKasaPara += kasadakiParalar[j] * 10;
        }
        if (j == 2)
        {
          toplamKasaPara += kasadakiParalar[j] * 20;
        }
        if (j == 3)
        {
          toplamKasaPara += kasadakiParalar[j] * 50;
        }
        if (j == 4)
        {
          toplamKasaPara += kasadakiParalar[j] * 100;
        }
      }

      for (int j = 0; j < 5; ++j) // eklenen para miktar ve toplam değeri
      {
        if (atilanParalar[j] > 0)
        {
          if (j == 0)
          {
            toplamAtilanPara += atilanParalar[j] * 5;
            kasadakiParalar[j] += atilanParalar[j];
            toplamKasaPara += atilanParalar[j] * 5; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı

          }
          if (j == 1)
          {
            toplamAtilanPara += atilanParalar[j] * 10;
            kasadakiParalar[j] += atilanParalar[j];
            toplamKasaPara += atilanParalar[j] * 10; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı

          }
          if (j == 2)
          {
            toplamAtilanPara += atilanParalar[j] * 20;
            kasadakiParalar[j] += atilanParalar[j];
            toplamKasaPara += atilanParalar[j] * 20; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı

          }
          if (j == 3)
          {
            toplamAtilanPara += atilanParalar[j] * 50;
            kasadakiParalar[j] += atilanParalar[j];
            toplamKasaPara += atilanParalar[j] * 50; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı

          }
          if (j == 4)
          {
            toplamAtilanPara += atilanParalar[j] * 100;
            kasadakiParalar[j] += atilanParalar[j];
            toplamKasaPara += atilanParalar[j] * 100; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı

          }
        }
      }

      if (toplamAtilanPara > 0)
      {
        sprintf(aciklama, "%d\n TL para attiniz", toplamAtilanPara);
        Serial.println(aciklama);
      }
      else
      {
        Serial.println("Para atmadiniz. Para atiniz.");
        paraYukle = false;
        ilkParaMesaj = false;
        ilkServisMesaj = true;
        toplamKasaPara = 0;
        goto tekrar;
      }
    }
    else
    {
      for (int j = 0; j < 4; ++j)
      {
        toplamAlinanHizmet += secilenHizmetler[j];
        kalanHizmetler[j] -= secilenHizmetler[j];
      }

      if (toplamAlinanHizmet > 0)
      {
        for (int j = 0; j < 4; ++j)
        {
          toplamSecilenHizmetFiyat += secilenHizmetler[j] * hizmetFiyatlar[j];
        }
      }
      else
      {
        Serial.println("Hizmet secmediniz. En az bir hizmet seciniz.");
        paraYukle = true;
        ilkParaMesaj = true;
        ilkServisMesaj = false;
        goto tekrar;
      }
    }

    if (!paraYukle)
    {
      paraYukle = true;
      ilkParaMesaj = true;
      ilkServisMesaj = false;
    }
    else
    {
      paraYukle = false;
      ilkParaMesaj = false;
      ilkServisMesaj = true;
    }

    if (toplamAtilanPara > 0 and toplamAlinanHizmet > 0)
    {
      if (toplamSecilenHizmetFiyat > toplamAtilanPara) // atilan paralar seçilen hizmet bedellerine yetmiyor ise
      {
        Serial.println("");
        String cumleOn = "Secilen hizmetlerin bedeli ";
        String paragrafHizmetTutar = cumleOn + toplamSecilenHizmetFiyat + " TL dir.";
        Serial.println(paragrafHizmetTutar);
        sprintf(aciklama, "Siz ise %d\n TL para attiniz.", toplamAtilanPara);
        Serial.println(aciklama);
        Serial.println("Attiginiz para yetersizdir. Para yatiriniz.");

        paraYukle = false;
        ilkParaMesaj = false;
        ilkServisMesaj = true;
        /*for (int j = 0; j < 5; ++j)
        {
          atilanParalar[j] = {0}; // eklenen para bilgileri siliniyor
        }*/

        for (int j = 0; j < 5; ++j) // eklenen para miktar ve toplam değeri
          {
            if (atilanParalar[j] > 0)
            {
              if (j == 0)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 5; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 1)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 10; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 2)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 20; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 3)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 50; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 4)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 100; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
            }
          }
        
        goto tekrar;
      }
      else // atilan paralar seçilen hizmet bedellerine yetiyor ise
      {
         paraYukle = false;
        ilkParaMesaj = false;
        ilkServisMesaj = true;

        //randomSayi = random(1, 4);
        randomSayi = millis()%5;
        if(randomSayi == 0)
        {
          randomSayi++;
        }
        Serial.println("");
        String textRandom = "Random Sayi: ";
        String randomSonuc = textRandom + randomSayi;
        Serial.println(randomSonuc);
        Serial.println("");
        String cumleOnBir, paragrafGeriOdenen;
        if (randomSayi == 2)
        {
          digitalWrite(kirmiziLed, HIGH);
          digitalWrite(yesilLed, LOW);
          Serial.println("Bir ariza olustu. Sistem reset bekliyor.");
          Serial.println("");
          cumleOnBir = "Attiginiz toplam ";
          paragrafGeriOdenen =  cumleOnBir + toplamAtilanPara + " TL geri iade ediliyor.";

          for (int a = 0; a < 4; ++a)
          {
            kalanHizmetler[a] += secilenHizmetler[a]; // düşülen servisler geri ekleniyor
          }
          paraUstu = toplamAtilanPara; // random = 2 durumunda iade edilecek miktar atılan tüm paradır

          while (digitalRead(resetTusu) == LOW)
          {

          }

          for (int j = 0; j < 5; ++j) // eklenen para miktar ve toplam değeri
          {
            if (atilanParalar[j] > 0)
            {
              if (j == 0)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 5; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 1)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 10; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 2)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 20; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 3)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 50; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
              if (j == 4)
              {
                kasadakiParalar[j] -= atilanParalar[j];
                toplamKasaPara -= atilanParalar[j] * 100; // normal işlemlerde iadelerde kullanılabilecek kasa para miktarı
              }
            }
          }

          Serial.println(paragrafGeriOdenen);
        }
        else
        {
          String cumleOn = "Secilen hizmetlerin bedeli ";
          String paragrafHizmetTutar = cumleOn + toplamSecilenHizmetFiyat + " TL dir.";
          Serial.println(paragrafHizmetTutar);
          paraUstu = toplamAtilanPara - toplamSecilenHizmetFiyat; // random != 2 durumunda ise iade edilecek miktar atılan tüm paradan seçilen hizmet bedelleri düşüldükten sonra kalan paradır.
          digitalWrite(kirmiziLed, LOW);
          digitalWrite(yesilLed, HIGH);

          cumleOnBir = "Hizmet bedelinden artan ";
          if (paraUstu > 0)
          {
            paragrafGeriOdenen = cumleOnBir + paraUstu + " TL geri odeniyor.";
          }
          else
          {
            paragrafGeriOdenen = cumleOnBir + paraUstu + " TL";
          }
          Serial.println(paragrafGeriOdenen);
        }


        int yuzluk = 0, ellilik = 0, yirmilik = 0, onluk = 0, beslik = 0;

        if (kasadakiParalar[4] > 0 && paraUstu >= 100)
        {
          yuzluk = paraUstu / 100;
          paraUstu %= 100;
          if (yuzluk > kasadakiParalar[4])
          {
            paraUstu += ((yuzluk - kasadakiParalar[4]) * 100);
            yuzluk = kasadakiParalar[4];
          }
        }

        if (kasadakiParalar[3] > 0 && paraUstu >= 50)
        {
          ellilik = paraUstu / 50;
          paraUstu %= 50;
          if (ellilik > kasadakiParalar[3])
          {
            paraUstu += ((ellilik - kasadakiParalar[3]) * 50);
            ellilik = kasadakiParalar[3];
          }
        }

        if (kasadakiParalar[2] > 0 && paraUstu >= 20)
        {
          yirmilik = paraUstu / 20;
          paraUstu %= 20;
          if (yirmilik > kasadakiParalar[2])
          {
            paraUstu += ((yirmilik - kasadakiParalar[2]) * 20);
            yirmilik = kasadakiParalar[2];
          }
        }

        if (kasadakiParalar[1] > 0 && paraUstu >= 10)
        {
          onluk = paraUstu / 10;
          paraUstu %= 10;
          if (onluk > kasadakiParalar[1])
          {
            paraUstu += ((onluk - kasadakiParalar[1]) * 10);
            onluk = kasadakiParalar[1];
          }
        }

        if (kasadakiParalar[0] > 0 && paraUstu >= 5)
        {
          beslik = paraUstu / 5;
          paraUstu %= 5;
          if (beslik > kasadakiParalar[0])
          {
            paraUstu += ((beslik - kasadakiParalar[0]) * 5);
            beslik = kasadakiParalar[0];
          }
        }
        if (paraUstu > 0)
        {
          String sonuc = "Kasada yeterli para yok! ";
          Serial.println(sonuc + paraUstu + " TL odenemedi.");

        }
        Serial.println("");
        Serial.println("");
        iadeParalar[0] -= beslik;
        iadeParalar[1] -= onluk;
        iadeParalar[2] -= yirmilik;
        iadeParalar[3] -= ellilik;
        iadeParalar[4] -= yuzluk;

        for (int j = 0; j < 5; ++j)
        {
          kasadakiParalar[j] += iadeParalar[j];
        }
      }

      dosyaGuncelle(kasadakiParalar, kalanHizmetler);


      ilkParaMesaj = false;
      ilkServisMesaj = true;

      dosyaOkundu = false;
      aciklama[0] = '\0';
      yazilacakSatir1[0] = '\0';
      yazilacakSatir2[0] = '\0';
      yazilacakSatir3[0] = '\0';
      yazilacakSatir4[0] = '\0';
      yazilacakSatir5[0] = '\0';
      toplamAtilanPara = 0;
      toplamAlinanHizmet = 0;
      toplamKasaPara = 0;
      paraUstu = 0;
      toplamSecilenHizmetFiyat = 0;
      for (int j = 0; j < 5; ++j)
      {
        atilanParalar[j] = {0}; // eklenen para bilgileri siliniyor
        iadeParalar[j] = {0}; // iadeler reset
      }
      for (int j = 0; j < 4; ++j)
      {
        secilenHizmetler[j] = {0};
      }
      digitalWrite(kirmiziLed, LOW);
      digitalWrite(yesilLed, LOW);
    }
  }
  else if (secimDegeri_7 == HIGH)
  {

    for (int j = 0; j < 5; ++j)
    {
      atilanParalar[j] = {0}; // eklenen para bilgileri siliniyor
      iadeParalar[j] = {0}; // iade bilgisi siliniyor
    }

    for (int j = 0; j < 4; ++j)
    {
      secilenHizmetler[j] = {0}; //eklenen servisler siliniyor
    }

    paraYukle = false;
    ilkParaMesaj = false;
    ilkServisMesaj = true;

    Serial.println("Sistem reset edildi.");
  }
}


void dosyaGuncelle(int kasadakiParalar[5], int kalanHizmetler[4])
{
  sprintf(yazilacakSatir1, "%d,%d,%d,%d,%d", kasadakiParalar[0], kasadakiParalar[1], kasadakiParalar[2], kasadakiParalar[3], kasadakiParalar[4]);
  sprintf(yazilacakSatir2, "1, Kopukleme,%d, 15 TL", kalanHizmetler[0]);
  sprintf(yazilacakSatir3, "2, Yikama,%d, 10 TL", kalanHizmetler[1]);
  sprintf(yazilacakSatir4, "3, Kurulama,%d, 5 TL", kalanHizmetler[2]);
  sprintf(yazilacakSatir5, "4, Cilalama,%d, 50 TL", kalanHizmetler[3]);

  char *dosyayaYazilecekSatirler[5] = {yazilacakSatir1, yazilacakSatir2, yazilacakSatir3, yazilacakSatir4, yazilacakSatir5};
  dosyayaYaz(dosyayaYazilecekSatirler);
}

int *arrayEditor(int *arr)
{
  int counter = 0;
  while (counter < 25)
  {
    if (arr[3] > 1)
    {
      arr[4] += (int)arr[3] / 2;
      arr[3] = arr[3] % 2;
    }
    if (arr[2] > 1 && arr[1] > 0)
    {
      while (arr[2] > -1 && arr[1] > -1)
      {
        arr[2] -= 2;
        arr[1] -= 1;
        arr[3] += 1;
      }
    }
    if (arr[1] > 1)
    {
      arr[2] += (int)arr[1] / 2;
      arr[1] = arr[1] % 2;
    }
    if (arr[0] > 1)
    {
      arr[1] += (int)arr[0] / 2;
      arr[0] = arr[0] % 2;
    }
    counter += 1;
  }

  return arr;
}

void sdKartYukle()
{

  byte res;
  file.setSSpin(sdcpPin);
  res = file.initFAT();
  if (res != NO_ERROR)
  {
    Serial.print("SD kart okunamadi.");
    while (true)
    {
    };
  }


  if (file.exists(dosyaAdi))
    file.delFile(dosyaAdi);

  file.create(dosyaAdi);
  // Serial.println("SD karta baglandi.");
}

void dosyayaYaz(char *gelensatirlar[])
{
  if (file.exists(dosyaAdi))
    file.delFile(dosyaAdi);

  file.create(dosyaAdi);
  byte res;
  res = file.openFile(dosyaAdi, FILEMODE_TEXT_WRITE);

  if (res == NO_ERROR)
  {
    for (int i = 0; i < 5; ++i)
    {
      char *satir = gelensatirlar[i];
      file.writeLn(satir);
    }
    //Serial.println("Dosya yazma islemi basarili.");
    file.closeFile();
  }
  else
  {
    Serial.println("Dosya yazma islemi basarisiz.");
  }
} /*  */
