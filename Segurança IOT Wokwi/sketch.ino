#include <Arduino.h>
#include <DHT.h>

// NexaHome: simulador educacional ESP32. Nao usa rede externa.
#define DHT_PIN 15
#define LED_SEGURO 18
#define LED_RISCO 19
#define BOTAO 21
DHT dht(DHT_PIN, DHT22);

bool modoSeguro = false;
bool botaoAnterior = HIGH;
unsigned long ultimoSensor = 0;

void atualizarLeds() {
  digitalWrite(LED_SEGURO, modoSeguro ? HIGH : LOW);
  digitalWrite(LED_RISCO, modoSeguro ? LOW : HIGH);
}

void menu() {
  Serial.println("\n========== NEXAHOME - LABORATORIO IoT ==========");
  Serial.println("1 = Testar credencial padrao (caso Mirai)");
  Serial.println("2 = Mostrar telemetria e riscos da comunicacao");
  Serial.println("3 = Mostrar interfaces e debug (UART)");
  Serial.println("4 = Alternar ANTES/DEPOIS (hardening)");
  Serial.println("5 = Mostrar riscos e mitigacoes");
  Serial.println("Pressione o botao azul para alternar o modo.");
  Serial.println("================================================\n");
}

void credencial() {
  Serial.println("\n[CASO REAL PESQUISADO: MIRAI 2016]");
  Serial.println("Mirai explorava, entre outros problemas, senhas padrao/fracas em IoT.");
  Serial.println("Aqui o teste e LOCAL e FICTICIO: nao ha login nem ataque real.");
  if (!modoSeguro) {
    Serial.println("ANTES: senha ficticia 'admin' -> ACEITA (regra simulada)");
    Serial.println("RISCO: uma senha conhecida pode facilitar acesso indevido.");
  } else {
    Serial.println("DEPOIS: senha ficticia 'admin' -> REJEITADA (regra simulada)");
    Serial.println("MITIGACAO: senha individual, autenticacao e limite de tentativas.");
  }
}

void telemetria() {
  float t = dht.readTemperature();
  float u = dht.readHumidity();
  if (isnan(t) || isnan(u)) { t = 24.5; u = 56.0; Serial.println("Sensor indisponivel: valores ilustrativos."); }
  Serial.println("\n[COMUNICACAO - SIMULACAO SERIAL LOCAL]");
  Serial.print("{\"dispositivo\":\"NexaSense-LAB-01\",\"temperatura\":");
  Serial.print(t, 1);
  Serial.print(",\"umidade\":");
  Serial.print(u, 1);
  Serial.println("}");
  if (!modoSeguro) {
    Serial.println("ANTES: payload visivel em texto claro no monitor serial.");
    Serial.println("RISCO HIPOTETICO: se transmitido sem TLS, pode ser lido na rede.");
  } else {
    Serial.println("DEPOIS: politica proposta = usar TLS + autenticacao.");
    Serial.println("AVISO: este simulador NAO implementa TLS nem trafego de rede.");
  }
}

void interfaces() {
  Serial.println("\n[HARDWARE / INTERFACES]");
  Serial.println("ESP32: UART do monitor serial e demonstrada; JTAG nao foi testada.");
  if (!modoSeguro) Serial.println("ANTES: logs detalhados podem expor configuracoes.");
  else Serial.println("DEPOIS: limitar logs e restringir interfaces de depuracao.");
  Serial.println("Interface presente NAO significa vulnerabilidade comprovada.");
}

void riscos() {
  Serial.println("\n[MAPA DE RISCOS - HIPOTESES DO LABORATORIO]");
  Serial.println("F01: senha padrao -> acesso indevido -> credencial unica.");
  Serial.println("F02: telemetria legivel -> exposicao -> TLS em producao.");
  Serial.println("F03: logs debug -> vazamento -> restringir depuracao.");
  Serial.println("ESP32 real: avaliar Secure Boot e Flash Encryption.");
  Serial.println("Referencia: OWASP ISTG, NIST IR 8259A, ETSI EN 303 645.");
}

void alternarModo() {
  modoSeguro = !modoSeguro;
  atualizarLeds();
  Serial.println(modoSeguro ? "\n>>> MODO DEPOIS: PROTECOES PROPOSTAS (VERDE)" : "\n>>> MODO ANTES: CONFIGURACAO INSEGURA SIMULADA (VERMELHO)");
  Serial.println("LEDs representam o cenario, nao protecao real implementada.");
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_SEGURO, OUTPUT);
  pinMode(LED_RISCO, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  atualizarLeds();
  delay(1200);
  Serial.println("NexaHome - avaliacao educacional de seguranca IoT");
  Serial.println("Dispositivo: ESP32 + sensor DHT22 + LEDs + botao.");
  Serial.println("Escopo: simulacao sem acesso a dispositivos externos.");
  menu();
  credencial();
  telemetria();
}

void loop() {
  bool atual = digitalRead(BOTAO);
  if (botaoAnterior == HIGH && atual == LOW) { alternarModo(); delay(180); }
  botaoAnterior = atual;
  while (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case '1': credencial(); break;
      case '2': telemetria(); break;
      case '3': interfaces(); break;
      case '4': alternarModo(); break;
      case '5': riscos(); break;
      case 'm': case 'M': menu(); break;
      default: break;
    }
  }
  if (millis() - ultimoSensor > 15000) {
    ultimoSensor = millis();
    Serial.println("\n[STATUS PERIODICO]");
    telemetria();
  }
}
