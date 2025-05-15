#include "FS.h"
#include "SD_MMC.h" // Use SD_MMC instead of SD

const char* filename = "/data.csv";
unsigned long lastWrite = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (!SD_MMC.begin("/sdcard", true)) { // true = 1-bit mode (safe). false = 4-bit mode (faster)
    Serial.println("Falha na inicialização do cartão SD via SDIO!");
    while (!SD_MMC.begin("/sdcard", true)) {
      Serial.println("Tentando inicializar SDIO novamente...");
      delay(1000);
    }
  }

  Serial.println("Cartão SD inicializado com sucesso via SDIO.");

  if (!SD_MMC.exists(filename)) {
    File file = SD_MMC.open(filename, FILE_WRITE);
    if (file) {
      file.println("Tempo(ms),ValorAleatorio"); // cabeçalho
      file.close();
      Serial.println("Arquivo data.csv criado com cabeçalho.");
    }
  }
}

void loop() {
  if (millis() - lastWrite >= 1000) {
    lastWrite = millis();

    int valorAleatorio = random(100); // exemplo aleatório
    File file = SD_MMC.open(filename, FILE_APPEND);
    if (file) {
      file.printf("%lu,%d\n", millis(), valorAleatorio);
      file.close();
      Serial.println("Dados gravados no arquivo.");
    } else {
      Serial.println("Falha ao abrir o arquivo para escrita.");
    }
  }
}
