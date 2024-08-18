#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// LCD ve buton pinleri
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

const int redLed = 10;
const int blueLed = 11;

const int buzzerPin = 12;  // Buzzer için pin

const int button1Pin = 8;  // 1. buton için pin
const int button2Pin = 9;  // 2. buton için pin

int button1Count = 0;  // 1. buton için sayaç
int button2Count = 0;  // 2. buton için sayaç

void setup() {
  Serial.begin(9600);

  // Buton ve buzzer pin ayarları
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT);  // Dahili pull-up direnci kullanarak butonlar için doğru okuma yapılır
  pinMode(button2Pin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  // Display ayarları
  display.begin();
  display.setContrast(57);
  display.clearDisplay();

  // Ekranı temizleyip başlangıç mesajı verelim
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Oyun Basliyor!");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // 1 ile 15 arasında rastgele bir sayı al
  int randomTime = random(1, 16);
  Serial.print("Rastgele sure: ");
  Serial.println(randomTime);

  // Rastgele belirlenen süre kadar bekle
  delay(randomTime * 1000);

  // Buzzer'ı 1 saniye boyunca çal
  tone(buzzerPin, 584);
  delay(500);
  noTone(buzzerPin);

  // Butonlardan hangisine önce basılacağını kontrol et
  bool buttonPressed = false;
  while (!buttonPressed) {
    if (digitalRead(button1Pin) == HIGH) {  // 1. buton basıldıysa
      delay(50);  // Debounce gecikmesi
      if (digitalRead(button1Pin) == HIGH) {  // Basılı olduğundan emin ol
        button1Count++;
        buttonPressed = true;
        Serial.print("Button 1 Basildi. Count: ");
        Serial.println(button1Count);
        digitalWrite(redLed, HIGH);  // Buton 1 basıldıysa kırmızı LED yansın
        delay(1000);  // LED yanık kalsın
        digitalWrite(redLed, LOW);
      }
    }

    if (digitalRead(button2Pin) == HIGH) {  // 2. buton basıldıysa
      delay(50);  // Debounce gecikmesi
      if (digitalRead(button2Pin) == HIGH) {  // Basılı olduğundan emin ol
        button2Count++;
        buttonPressed = true;
        Serial.print("Button 2 Basildi. Count: ");
        Serial.println(button2Count);
        digitalWrite(blueLed, HIGH);  // Buton 2 basıldıysa mavi LED yansın
        delay(1000);  // LED yanık kalsın
        digitalWrite(blueLed, LOW);
      }
    }
  }

  // Sayaçları ekrana yazdıralım (ekranı sadece bir kez temizleyelim)
  display.clearDisplay();
  display.setTextSize(1);  // Daha büyük yazı boyutu ayarlandı

  // Sol Oyuncu
  int solX = (84 - 12 * 6) / 2;  // 12 karakterli metni ortalamak için x pozisyonu
  display.setCursor(solX, 0);
  display.print("Sol: ");
  display.println(button1Count);

  // Sag Oyuncu
  int sagX = (84 - 12 * 6) / 2;  // 12 karakterli metni ortalamak için x pozisyonu
  display.setCursor(sagX, 20);
  display.print("Sag: ");
  display.println(button2Count);

  display.display();

  // Bir sonraki tur için kısa bir gecikme
  delay(2000);
}
