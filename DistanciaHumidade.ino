#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include <Fonts/FreeSans9pt7b.h>
#include "DHT.h"

// Definição dos pinos do display ST7735S
#define TFT_CS     D8
#define TFT_RST    D2
#define TFT_DC     D1
#define TFT_MOSI   D7   // Data out
#define TFT_SCLK   D5   // Clock out

// Definição do sensor DHT22
#define DHTPIN D3     // Pino digital conectado ao sensor DHT
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

// Definição do display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Definição dos pinos do sensor de distância
#define TRIG_PIN D4
#define ECHO_PIN D6  // Alterado para D6

// Variável para rastrear a tela atual
int telaAtual = 0;

// Função para desenhar a imagem JPEG no display
void drawJPEG(const char *filename, int16_t xpos, int16_t ypos) {
  // Abre o arquivo JPEG
  fs::File jpegFile = SPIFFS.open(filename, "r");
  if (!jpegFile) {
    Serial.print("Erro ao abrir ");
    Serial.println(filename);
    return;
  }

  JpegDec.decodeFsFile(jpegFile);

  uint16_t *pImg = JpegDec.pImage;
  int16_t mcu_w = JpegDec.MCUWidth;
  int16_t mcu_h = JpegDec.MCUHeight;
  int32_t max_x = JpegDec.width;
  int32_t max_y = JpegDec.height;
  int32_t min_w = min((int32_t)mcu_w, max_x % mcu_w);
  int32_t min_h = min((int32_t)mcu_h, max_y % mcu_h);

  for (uint16_t row = 0; row < max_y; row += mcu_h) {
    for (uint16_t col = 0; col < max_x; col += mcu_w) {
      uint16_t w = (col + mcu_w <= max_x) ? mcu_w : min_w;
      uint16_t h = (row + mcu_h <= max_y) ? mcu_h : min_h;
      JpegDec.read();
      tft.drawRGBBitmap(xpos + col, ypos + row, pImg, w, h);
    }
  }
}

// Função para ler a distância do sensor ultrassônico
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Convertendo para centímetros
  return distance;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando display e DHT22...");

  if (!SPIFFS.begin()) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  dht.begin();

  // Configuração dos pinos do sensor de distância
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  tft.initR(INITR_BLACKTAB); // Inicializa o display ST7735S
  tft.setRotation(3);        // Ajusta a orientação do display
  tft.fillScreen(ST7735_BLACK); // Preenche a tela com a cor preta

  tft.setTextWrap(false);    // Desabilita a quebra de texto automática
  tft.setFont(&FreeSans9pt7b); // Define a fonte para FreeSans

  // Exibe o logo "logo_senac_default.png"
  drawJPEG("/logo_senac_default.png", 15, 5);
}

void loop() {
  // Leitura do sensor DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Verifica se a leitura falhou e sai antecipadamente (para tentar novamente)
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Falha ao ler do sensor DHT!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  // Leitura do sensor de distância
  float distance = readDistance();

  // Exibe os dados no display em telas diferentes
  tft.fillScreen(ST7735_BLACK);

  switch (telaAtual) {
    case 0:
      drawJPEG("/logo_senac_default.png", 15, 5);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(35, 50); // Ajustar a posição para "Senac Lapa"
      tft.print("Senac Lapa");
      tft.setCursor(50, 65); // Ajustar a posição para "Tito"
      tft.print("Tito");
      break;
    case 1:
      tft.setTextColor(ST7735_RED);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Temp: ");
      tft.print(t);
      tft.print(" C");
      break;
    case 2:
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Temp: ");
      tft.print(f);
      tft.print(" F");
      break;
    case 3:
      tft.setTextColor(ST7735_BLUE);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Umidade: ");
      tft.print(h);
      tft.print("%");
      break;
    case 4:
      tft.setTextColor(ST7735_YELLOW);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Ind. Calor: ");
      tft.print(hic);
      tft.print(" C");
      break;
    case 5:
      tft.setTextColor(ST7735_CYAN);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Ind. Calor: ");
      tft.print(hif);
      tft.print(" F");
      break;
    case 6:
      tft.setTextColor(ST7735_ORANGE);
      tft.setCursor(10, 55); // Ajustar a posição vertical
      tft.print("Distancia: ");
      tft.print(distance);
      tft.print(" cm");
      break;
  }

  telaAtual = (telaAtual + 1) % 7; // Alterna entre as telas

  delay(2000); // Aguardar alguns segundos antes de mudar para a próxima tela
}
