#include <Arduino.h>

// Definição dos pinos dos componentes
const int buttonPanic = D4;  // Botão Vermelho (Pânico)
const int buttonWater = D3;  // Botão Azul (Água)
const int buttonFood = D6;   // Botão Verde (Comida)
const int buzzerPin = D7;    // Pino do Buzzer

// Pinos para os LEDs
const int ledPanic = D1;     // LED Vermelho (Pânico)
const int ledWater = D2;     // LED Azul (Água)
const int ledFood = D5;      // LED Verde (Comida)

// Frequências das notas
const int freqDo = 523;      // Frequência do Dó (C)
const int freqRe = 587;      // Frequência do Ré (D)
const int freqMi = 622;      // Frequência do Mi (E)

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos como INPUT_PULLUP para os botões e OUTPUT para os LEDs e buzzer
  pinMode(buttonPanic, INPUT_PULLUP);
  pinMode(buttonWater, INPUT_PULLUP);
  pinMode(buttonFood, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPanic, OUTPUT);
  pinMode(ledWater, OUTPUT);
  pinMode(ledFood, OUTPUT);

  // Inicializa LEDs como apagados
  digitalWrite(ledPanic, LOW);
  digitalWrite(ledWater, LOW);
  digitalWrite(ledFood, LOW);

  Serial.println("Setup completo. Esperando interação com os botões...");
}

void loop() {
  // Leitura do estado dos botões
  int panicState = digitalRead(buttonPanic);
  int waterState = digitalRead(buttonWater);
  int foodState = digitalRead(buttonFood);

  // Verificação dos botões pressionados
  if (panicState == LOW) {
    // Botão de pânico pressionado
    digitalWrite(ledPanic, HIGH);
    tone(buzzerPin, freqDo);  // Frequência do Dó (C)
    Serial.println("Alerta: Pânico!");
    delay(500);
  } else {
    digitalWrite(ledPanic, LOW);
  }

  if (waterState == LOW) {
    // Botão de água pressionado
    digitalWrite(ledWater, HIGH);
    tone(buzzerPin, freqRe);  // Frequência do Ré (D)
    Serial.println("Alerta: Preciso de Água!");
    delay(500);
  } else {
    digitalWrite(ledWater, LOW);
  }

  if (foodState == LOW) {
    // Botão de comida pressionado
    digitalWrite(ledFood, HIGH);
    tone(buzzerPin, freqMi);  // Frequência do Mi (E)
    Serial.println("Alerta: Preciso de Comida!");
    delay(500);
  } else {
    digitalWrite(ledFood, LOW);
  }

  // Desliga o buzzer
  noTone(buzzerPin);

  // Pequena pausa para estabilidade
  delay(50);
}
