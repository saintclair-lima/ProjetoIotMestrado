

void handleConfigurar(){
  configuracaoAtiva = false;
  
  server.arg("ssid").toCharArray(ssid, 100);
  server.arg("senha").toCharArray(password, 100);
  ipServidor = server.arg("ipServidor");
  nomeServidor = "http://"+ ipServidor +":1880/registrar-temperatura";
  Serial.println("Dados recebidos do Formulario");
  Serial.println("Saindo do modo de configurações");
  String pagina = "<ul>";
        pagina += "<li><b>Configuração ativa:</b>";
        pagina += configuracaoAtiva;
        pagina += "</li>";
        pagina += "<li><b>SSID:</b>";
        pagina += ssid;
        pagina += "</li>";
        pagina += "<li><b>Senha:</b>";
        pagina += password;
        pagina += "</li>";
        pagina += "</ul>";
  server.send(200, "text/html", pagina);
}

void handleSupercalifragilistic(){
  String pagina = "<ul>";
         pagina += "<li><b>Configuração ativa:</b>";
         pagina += configuracaoAtiva;
         pagina += "</li>";
         pagina += "<li><b>SSID:</b>";
         pagina += ssid;
         pagina += "</li>";
         pagina += "<li><b>Senha:</b>";
         pagina += password;
         pagina += "</li>";
         pagina += "</ul>";
  server.send(200, "text/html", pagina);
}

void handleRoot() {
  char* pagina = "<html  lang='pt-BR'>"
                  "<meta charset='UTF-8'>"
                  "<head>"
                      "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                      "<style>"
                      ""
                      "@import url(https://fonts.googleapis.com/css?family=Roboto:400,300,600,400italic);"
                      "* {"
                      "  margin: 0;"
                      "  padding: 0;"
                      "  box-sizing: border-box;"
                      "  -webkit-box-sizing: border-box;"
                      "  -moz-box-sizing: border-box;"
                      "  -webkit-font-smoothing: antialiased;"
                      "  -moz-font-smoothing: antialiased;"
                      "  -o-font-smoothing: antialiased;"
                      "  font-smoothing: antialiased;"
                      "  text-rendering: optimizeLegibility;"
                      "}"
                      ""
                      "body {"
                      "  font-family: 'Roboto', Helvetica, Arial, sans-serif;"
                      "  font-weight: 100;"
                      "  font-size: 12px;"
                      "  line-height: 30px;"
                      "  color: #777;"
                      "  background: #4CAF50;"
                      "}"
                      ""
                      ".container {"
                      "  max-width: 400px;"
                      "  width: 100%;"
                      "  margin: 0 auto;"
                      "  position: relative;"
                      "}"
                      ""
                      "#configRedeCliente input[type='text'],"
                      "#configRedeCliente input[type='password'] {"
                      "  font: 400 12px/16px 'Roboto', Helvetica, Arial, sans-serif;"
                      "}"
                      ""
                      "#configRedeCliente {"
                      "  background: #F9F9F9;"
                      "  padding: 25px;"
                      "  margin: 150px 0;"
                      "  box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);"
                      "}"
                      ""
                      "#configRedeCliente h3 {"
                      "  display: block;"
                      "  font-size: 30px;"
                      "  font-weight: 300;"
                      "  margin-bottom: 10px;"
                      "}"
                      ""
                      "#configRedeCliente h4 {"
                      "  margin: 5px 0 15px;"
                      "  display: block;"
                      "  font-size: 13px;"
                      "  font-weight: 400;"
                      "}"
                      ""
                      "fieldset {"
                      "  border: medium none !important;"
                      "  margin: 0 0 10px;"
                      "  min-width: 100%;"
                      "  padding: 0;"
                      "  width: 100%;"
                      "}"
                      ""
                      "#configRedeCliente input[type='text'],"
                      "#configRedeCliente input[type='password'] {"
                      "  width: 100%;"
                      "  border: 1px solid #ccc;"
                      "  background: #FFF;"
                      "  margin: 0 0 5px;"
                      "  padding: 10px;"
                      "}"
                      ""
                      "#configRedeCliente input[type='text']:hover,"
                      "#configRedeCliente input[type='email']:password {"
                      "  -webkit-transition: border-color 0.3s ease-in-out;"
                      "  -moz-transition: border-color 0.3s ease-in-out;"
                      "  transition: border-color 0.3s ease-in-out;"
                      "  border: 1px solid #aaa;"
                      "}"
                      ""
                      "#configRedeCliente button[type='submit'] {"
                      "  cursor: pointer;"
                      "  width: 100%;"
                      "  border: none;"
                      "  background: #4CAF50;"
                      "  color: #FFF;"
                      "  margin: 0 0 5px;"
                      "  padding: 10px;"
                      "  font-size: 15px;"
                      "}"
                      ""
                      "#configRedeCliente button[type='submit']:hover {"
                      "  background: #43A047;"
                      "  -webkit-transition: background 0.3s ease-in-out;"
                      "  -moz-transition: background 0.3s ease-in-out;"
                      "  transition: background-color 0.3s ease-in-out;"
                      "}"
                      ""
                      "#configRedeCliente button[type='submit']:active {"
                      "  box-shadow: inset 0 1px 3px rgba(0, 0, 0, 0.5);"
                      "}"
                      ""
                      "#configRedeCliente input:focus {"
                      "  outline: 0;"
                      "  border: 1px solid #aaa;"
                      "}"
                      ""
                      "::-webkit-input-placeholder {"
                      "  color: #888;"
                      "}"
                      ""
                      ":-moz-placeholder {"
                      "  color: #888;"
                      "}"
                      ""
                      "::-moz-placeholder {"
                      "  color: #888;"
                      "}"
                      ""
                      ":-ms-input-placeholder {"
                      "  color: #888;"
                      "}"
                      "</style>"
                      "<script>"
                      "function mostrarSenha() {"
                      "  var x = document.getElementById('senha');"
                      "  if (x.type === 'password') {"
                      "    x.type = 'text';"
                      "  } else {"
                      "    x.type = 'password';"
                      "  }"
                      "}"
                      "</script>"
                      "</head>"
                      ""
                      "<body>"
                      "  <div class='container'>  "
                      "    <form id='configRedeCliente' action='configurarRede' method='post'>"
                      "      <h3>Configurar Rede</h3>"
                      "      <h4>Informe os dados de sua rede e de cadastro no sistema</h4>"
                      "      <fieldset>"
                      "        <input name='ssid' id='ssid' placeholder='Nome da sua rede' type='text' tabindex='1' required autofocus>"
                      "      </fieldset>"
                      "      <fieldset>"
                      "        <input name='senha' id='senha' placeholder='Senha da sua rede' type='password' tabindex='2' required>"
                      "        <input type='checkbox' onclick='mostrarSenha()'> Mostrar senha"
                      "      </fieldset>"
                      "      <fieldset>"
                      "        <input name='ipServidor' id='ipServidor' placeholder='Endereço de IP do servidor' type='text' tabindex='3' required>"
                      "      </fieldset>"
                      "      <fieldset>"
                      "        <button name='enviarDados' type='submit' id='configRedeCliente-enviarDados' data-submit='...Salvando...'>Salvar</button>"
                      "      </fieldset>"
                      "    </form>"
                      "  </div>"
                      "</body>"
                      "</html>";
  
    server.send(200, "text/html", pagina); //Send web page
}