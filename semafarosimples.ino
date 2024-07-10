
#define LEDverde 10
#define LEDamarelo 9
#define LEDvermelho 8


void setup()
{
  pinMode (LEDvermelho, OUTPUT);
  pinMode (LEDamarelo, OUTPUT);
  pinMode (LEDverde, OUTPUT);
}

void loop()
{
  //ativação do LED verde
  digitalWrite (LEDvermelho, LOW);
  digitalWrite(LEDverde, HIGH);
  delay(2000);
  digitalWrite(LEDverde, LOW);
  delay(500);
  
  //ativação do LED amarelo (oscilante)
  for (int i =  0; i < 3; i++){
    digitalWrite(LEDamarelo, HIGH);
    delay(500);
    digitalWrite(LEDamarelo, LOW);
    delay(500);
  }
  
  //ativação do LED vermelho
  digitalWrite(LEDvermelho, HIGH);
  delay(2000);
  digitalWrite(LEDvermelho, LOW);
  delay(500);
}