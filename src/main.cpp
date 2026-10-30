#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

//* ========= CONFIGURACOES DO ACCESS POINT =========
const char * SSID = "tchombles";
const char * SENHA = "123456789";

WebServer servidorWeb(80); //* instancia um objeto para criar um webserver

//* funcao para gerar a pagina html que aparece no navegador
void paginaInicial()
{
  String status = digitalRead(48) ? "LIGADO" : "DESLIGADO";

  String na_html =
  "<meta name='viewport' content='width=device-width'>"
  "<p>LED: <b>"+ status +"</b></p>"
  "<a href='/on'><button>LIGAR</button></a>"
  "<a href='/off'><button>DESLIGAR</button></a>";

  servidorWeb.send(200, "text/html", na_html);
}

void ligar()
{
  rgbLedWrite(48, 255, 0, 0);
  paginaInicial();
}

void desligar()
{
  rgbLedWrite(48, 0, 0, 0);
  paginaInicial();
}

void setup() 
{
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); //* habilita do modo ap para criar uma rede wifi
  // AP = access point - ponto de acesso wifi
  WiFi.softAP(SSID, SENHA); //* cria a rede wifi

  Serial.println();
  Serial.println("---MODO AP ATIVO---");
  Serial.printf("REDE (SSID): %s\n\r", SSID);
  Serial.printf("SENHA: %s\n\r", SENHA);
  Serial.printf("IP: %s\n\r", WiFi.softAPIP().toString().c_str());
  Serial.printf("MAC ADDRESS: %s\n\r", WiFi.softAPmacAddress().c_str());

  //* ensina o servidor qual a funcao chamar dependendo da URL que o usuario acessar
  servidorWeb.on("/", paginaInicial);
  servidorWeb.on("/on", ligar);
  servidorWeb.on("/off", desligar);
  servidorWeb.begin();
}

void loop() 
{
  servidorWeb.handleClient(); //* atualiza a pagina do servidor web
}
