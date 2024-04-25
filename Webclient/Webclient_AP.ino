
void inicializarAP(){
    Serial.println();
    Serial.println("Inicializando Ponto de Acesso: Rede Temporária - senha 12345678");
    WiFi.mode(WIFI_AP_STA);
    IPAddress ip(1,2,3,4);
    IPAddress gateway(1,2,3,1);
    IPAddress subnet(255,255,255,0);
    WiFi.softAPConfig(ip, gateway, subnet);
    WiFi.softAP("Rede Temporaria", "12345678");
    delay(1000);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Ponto de Acesso Inicializado com IP ");
    Serial.println(myIP);
}

void inicializarServidor(){
    Serial.println("Inicializando Servidor");
    server.on("/",               handleRoot);
    server.on("/configurarRede", handleConfigurar);
    server.on("/supercalifragilistic", handleSupercalifragilistic);
    server.begin();
    Serial.println("Servidor Inicializado");
}

void encerrarServidorAP(){
    server.stop();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);
    Serial.println("Configurações Feitas");
    Serial.println("Servidor e Ponto de Acesso Encerrados");
}
