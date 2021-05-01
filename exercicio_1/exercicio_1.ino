/*
  Programa: Blink
  Autor: Vijay Kapoor
  Data: 30/04/2021
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // Inicializa os pins
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

// Loop principal para executar o programa
void loop() {
  // Liga o led no pin 13
  digitalWrite(13, HIGH);
  // Espera 1s
  delay(1000);          
  // Desliga o led no pin 13
  digitalWrite(13, LOW);
  // Espera 1s
  delay(1000);

  // Liga o led no pin 11
  digitalWrite(11, HIGH);
  // Espera 1s
  delay(1000);
  // Desliga o led no pin 11
  digitalWrite(11, LOW);
  delay(1000);
  // Espera 1s
}
