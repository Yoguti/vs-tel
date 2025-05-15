#include <SPI.h>
#include <SD.h>

const int chipSelect = 5; // ou 5 vou ter que testar
const char* filename = "/data.csv";
unsigned long lastWrite = 0;

void setup() {
  Serial.begin(115200); // mesmo baud rate do sensor.ino
  while (!Serial) delay(10);

  if (!SD.begin(chipSelect)) {
    Serial.println("Falha na inicialização do cartão SD!");
    while (!SD.begin(chipSelect)) {
      Serial.println("Tentando inicializar...");
      delay(1000);
    }
  }
  Serial.println("Cartão SD inicializado com sucesso.");

  if (!SD.exists(filename)) {
    File file = SD.open(filename, FILE_WRITE);
    if (file) {
      file.println("Tempo(ms),ValorAleatorio"); // cabeçalho
      file.close();
      Serial.println("Arquivo data.csv criado com cabeçalho.");
    }
  }
}

void loop() {
  if (millis() - lastWrite >= 1000) { // escreve a cada 1 segundo usando o clock interno
    lastWrite = millis();

    int valorAleatorio = random(100); // exemplo aleatório
    File file = SD.open(filename, FILE_APPEND);
    if (file) {
      file.printf("%lu,%d\n", millis(), valorAleatorio);
      file.close();
      Serial.println("Dados gravados no arquivo.");
    } else {
      Serial.println("Falha ao abrir o arquivo para escrita.");
    }
  }
}
