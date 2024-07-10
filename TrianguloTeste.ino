#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Definição dos pinos do display ST7735S
#define TFT_CS     D8
#define TFT_RST    D2
#define TFT_DC     D1
#define TFT_MOSI   D7   // Data out
#define TFT_SCLK   D5   // Clock out

// Definição do display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando display...");

  tft.initR(INITR_BLACKTAB); // Inicializa o display ST7735S
  tft.setRotation(1);        // Ajusta a orientação do display
  tft.fillScreen(ST7735_BLACK); // Preenche a tela com a cor preta

  Serial.println("Display inicializado.");
}

void loop() {
  // Desenha um triângulo para testar o display
  tft.fillScreen(ST7735_BLACK);
  tft.drawTriangle(30, 30, 60, 90, 90, 30, ST7735_WHITE); // Desenha um triângulo branco

  Serial.println("Triângulo desenhado.");
  delay(2000); // Pausa de 2 segundos
}
