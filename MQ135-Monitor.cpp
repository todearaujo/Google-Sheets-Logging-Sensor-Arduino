// Exemplo de envio de dados do NodeMCU para Google Sheets

// Este exemplo foi criado pa partir do exemplo no link a seguir 
// TUTORIAL AQUI: https://github.com/carolinex/Google-Sheets-Logging-MQ135
#include <Arduino.h> // biblioteca
#include <ESP8266WiFi.h> // biblioteca
#include "HTTPSRedirect.h" // biblioteca 

// Substitua esses valores pelo nome e
// senha da sua rede de WiFi
const char* ssid     = "Baldfi";
const char* password = "XXXXXXXX";

// Coloque aqui o id do seu Google Apps Script
const char *GScriptId = "XXXXXXXXXXX";
String place = "tode";

// Comando (insert_row ou append_row) e nome da planilha no Google Sheets (padrão é Sheet1):
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"registros\", \"values\": ";
String payload = "";

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// variável que irá guardar o valor do sensor
int value = 0;

void setup() {

  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Conecta ao WiFi
  WiFi.begin(ssid, password);             
  Serial.print("Conectando à rede Wifi ");
  Serial.print(ssid); Serial.println(" ...");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  
  // continua tentando conectar até conseguir
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);   
    delay(200); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(200); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);      
    digitalWrite(LED_BUILTIN, LOW);   
  }
  // Mensagem de sucesso no Serial Monitor
  Serial.println('\n');
  Serial.println("Conexão estabelecida!");  
  Serial.print("IP:\t");
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Conectando a ");
  Serial.println(host);

  // Tenta conectar até 5 vezes
  bool flag = false;
  for (int i=0; i<5; i++){ 
    int retval = client->connect(host, httpsPort);
    if (retval == 1){
       flag = true;
       Serial.println("NodeMCU conectado ao host");
        digitalWrite(LED_BUILTIN, LOW);   
        delay(1000); 
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);   
        digitalWrite(LED_BUILTIN, LOW);   
        delay(1000); 
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000); 
        digitalWrite(LED_BUILTIN, LOW); 
       break;
    }else{
      Serial.println("Conexão falhou. Tentando novamente...");
    }
  }
  
  if (!flag){
    Serial.print("Não foi possível conectar ao servidor: ");
    Serial.println(host);
    return;
  }
  delete client;
  client = nullptr;
}


void loop() {
  // pega dados analógicos do sensor
  value = analogRead(A0);

  static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
    }
  }
  else{
    Serial.println("Erro ao criar cliente https.");
  }
  
  // Cria um objeto json par enviar à Google Sheets
  payload = payload_base + "\"" + value + "," + place + "\"}";
  
  // Publish data to Google Sheets
  Serial.println("Publicando dados...");
  Serial.println(payload);
  if(client->POST(url, host, payload)){ 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);                    
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);                    
    digitalWrite(LED_BUILTIN, LOW);   
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("Erro na conexão com o script");
  }
  // espere 10 minuto antes de enviar um novo valor   
  delay(600000);
}
