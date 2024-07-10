#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Fonts/FreeSans9pt7b.h>  // Inclui a fonte FreeSans

// Definição dos pinos do display
#define TFT_CS     D8
#define TFT_RST    D2
#define TFT_DC     D1
#define TFT_MOSI   D7   // Data out
#define TFT_SCLK   D5   // Clock out

// Define cores para facilitar
#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF

// Definição de cores adicionais
#define ORANGE    0xFD20
#define INDIGO    0x4810
#define VIOLET    0xF81F

// Array de cores do arco-íris
uint16_t rainbowColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

// Definição do display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void drawRainbow() {
  int numColors = sizeof(rainbowColors) / sizeof(rainbowColors[0]);
  int stripeHeight = tft.height() / numColors;

  for (int offset = 0; offset < stripeHeight; offset++) {
    for (int i = 0; i < numColors; i++) {
      tft.fillRect(0, i * stripeHeight - offset, tft.width(), stripeHeight, rainbowColors[i]);
    }
    delay(50);
  }
}

void drawChangingColorText(const char* text, int16_t y) {
  int numColors = sizeof(rainbowColors) / sizeof(rainbowColors[0]);
  for (int i = 0; i < numColors; i++) {
    tft.fillScreen(BLACK);
    tft.setTextColor(rainbowColors[i]);
    tft.setCursor(10, y);
    tft.print(text);
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando display...");

  tft.initR(INITR_MINI160x80); // Inicializa o display ST7735S 80x160
  tft.setRotation(3);          // Ajusta a orientação do display
  tft.fillScreen(BLACK);       // Preenche a tela com a cor preta

  tft.setTextWrap(false);      // Desabilita a quebra de texto automática
  tft.setFont(&FreeSans9pt7b); // Define a fonte para FreeSans
}

void loop() {
  // Efeito de arco-íris em movimento
  drawRainbow();
  delay(1000); // Pausa após o arco-íris

  // Exibe o texto "Senac Lapa Tito" com cores mudando
  drawChangingColorText("Senac Tito", 50);
  delay(1000); // Pausa após o texto

  // Efeito de arco-íris em movimento
  drawRainbow();
  delay(1000); // Pausa após o arco-íris

  // Exibe o texto "na Comic Con" com cores mudando
  drawChangingColorText("na Comic Con", 50);
  delay(1000);  // Pausa após o texto
}
