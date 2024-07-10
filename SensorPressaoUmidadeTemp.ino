void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Inicializa o LED na placa
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Liga o LED
  delay(1000); // Espera por um segundo
  digitalWrite(LED_BUILTIN, LOW); // Desliga o LED
  delay(1000); // Espera por um segundo
}
