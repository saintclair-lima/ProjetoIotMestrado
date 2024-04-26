# ProjetoIotMestrado

## Justificativa e Objetivo do Projeto
A manutenção de um ambiente com condições adequadas de temperatura e conforto é fundamental para promover o bem-estar e a saúde das pessoas que o habitam. A temperatura ambiente desempenha um papel crucial na regulação do conforto humano, influenciando tanto aspectos físicos quanto psicológicos. Condições extremas de temperatura, seja frio intenso ou calor excessivo, podem levar a desconforto, estresse térmico e até mesmo problemas de saúde, como hipertermia ou hipotermia. Isto posto, percebe-se que a criação e manutenção de ambientes com temperaturas moderadas e confortáveis são essenciais para garantir um ambiente habitável e produtivo.

Para avaliar o conforto térmico de um ambiente, são comumente utilizadas medidas como sensação térmica e índice de calor. Ambas as medidas estão intrinsecamente relacionadas e são indicadores importantes para determinar a percepção subjetiva das pessoas em relação à temperatura. A sensação térmica refere-se à forma como uma pessoa percebe a temperatura, levando em consideração fatores como umidade relativa do ar, velocidade do vento e radiação solar. Por sua vez, o índice de calor é uma medida específica que combina temperatura do ar e umidade relativa para estimar como a temperatura "se sente" para o corpo humano.

O índice de calor, por não requerer a inclusão da velocidade do vento em seu cálculo, é frequentemente considerado mais fácil de medir do que a sensação térmica. Isso se deve ao fato de que a velocidade do vento pode ser uma variável difícil de quantificar com precisão em ambientes internos ou em áreas urbanas onde há obstrução do vento por edifícios e outras estruturas. Assim, ao concentrar-se apenas na temperatura do ar e na umidade relativa, o índice de calor oferece uma avaliação mais direta e simplificada do conforto térmico, tornando-se uma ferramenta valiosa para planejamento urbano, design de edifícios e gestão de espaços interiores.

O propósito do projeto de IoT em questão é monitorar o índice de calor, realizando para isso a coleta de dados de temperatura e umidade relativa do ar, processando-os e indicando (1) a condição atual do índice de calor, (2) calculando as mudanças necessárias no condicionamento do ar (aumentando ou diminuindo a temperatura, bem como ajustando a umidade) e (3) acionando os dispositivos condicionadores de ar que efetivamente realizarão os ajustes de condições para melhorar o índice de calor no ambiente.

## Requisitos
De forma a alcançar o objetivo proposto, o sistema IoT a ser implementado precisa:
1. Realizar a leitura de temperatura no(s) ambiente(s) monitorados;
2. Realizar a leitura de umidade relativa do ar no(s) ambiente(s) monitorados;
3. Realizar o envio dessas informações a uma unidade de concentração de informações, preferencialmente por meio wireless;
4. Processar as informações, utilizando alguma métrica, como a Heat Index Equation (ver https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml);
5. Com base nos valores de temperatura e umidade, bem como no índice de calor, calcular o melhor conjunto de ajustes de temperatura e umidade, de forma a direcionar o índice de calor para níveis mais confortáveis;
6. Armazenar de forma persistente os dados, de forma a se manter um histórico de leituras para análise posterior;
7. Enviar aos dispositivos condicionadores de ar (ar-condicionados/umidificadores) comandos de ajuste de parâmetros de funcionamento, com base nos cálculos realizados;
8. Disponibilizar meios de consulta da situação atual dos ambientes e do histórico de medições realizadas.

Desta forma, uma possível arquitetura seria como a da Figura 01, abaixo. Nela teríamos cinco “nós” que viabilizariam a realização de todas as medidas elencadas.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura1.png?raw=true)

Figura 1: possível arquitetura que atende aos requisitos

O ponto central da arquitetura apresentada seria um servidor em nuvem (rótulo 2, na Figura 1), o qual seria responsável pelos itens 4, 5 e 6 da lista de requisitos (concentração e processamento dos dados, definição da estratégia de correção do índice de calor e armazenamento dos dados). Adicionalmente, proveria meios de inspeção dos dados armazenados, fazendo-o por meio de prover comunicação via requisições HTTP, dando acesso aos dados armazenados (item 8 da lista de requisitos). O acesso aos recursos de consulta providenciados por esse servidor seria feito por meio de qualquer dispositivo capaz de enviar e receber requisições e respostas via HTTP (rótulo 1, na Figura 1).

Outro ponto crucial em todo o fluxo de informações (marcado com rótulo 3, na Figura 1) seria um dispositivo concentrador de leituras de informações. Visto que há a possibilidade de monitoramento de vários ambientes isolados, mas que fazem parte da mesma estrutura (pressupondo vários pontos de leitura espalhados, mas com certo grau de correlação), em vez de fazer o envio de cada sensor individualmente para o servidor, coloca-se um dispositivo que atua como um broker, um intermediário entre os sensores individuais e o servidor em si.
Esse concentrador receberia as leituras coletadas pelos dispositivos na ponta de toda a arquitetura (rótulo 4, na Figura 1), preferencialmente sem fio, conforme item 3 da lista de requisitos. As leituras coletadas tratariam de abarcar temperatura e umidade em cada ambiente servido por equipamentos de condicionamento de ar, de forma a garantir uma imagem atualizada do nível de conforto no entorno. Isso seria feito por meio de sensores de temperatura e umidade (quer seja individualmente utilizados ou algum sensor que leia os dois valores simultaneamente).

Também viria pelo concentrador o resultado do processamento dos dados feito pelo servidor, na forma de comandos de ajuste de parâmetros de funcionamento dos aparelhos de condicionamento de ar (rótulo 5, na Figura 1) para modificar o índice de calor, quando necessário.

## Especificações
Em virtude de restrições de componentes de hardware e estrutura disponíveis, a arquitetura adotada para construção do projeto prático dá conta somente de uma parte do sistema como um todo. Em vez de uma estrutura em nuvem para atuar como servidor, a qual se comunica intensamente com um broker, foi feita a aglutinação de ambos em um só elemento (rótulo 2, na Figura 2).
Ademais, dado que não houve a disponibilidade de um sensor de umidade do ar, manteve-se apenas o sensor de temperatura (rótulo 3, na Figura 2). Igualmente perceptível é a ausência dos aparelhos condicionadores de ar, pelo que se configura, este recorte do sistema, somente em um monitor de temperatura atual e de série histórica.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura2.png?raw=true)

Figura 2: Esquema de Implementação do Projeto

A forma de implementação efetiva utiliza como componente centralizador de dados um Raspberry Pi atuando como receptor de requisições HTTP, as quais são recebidas por uma API criada e executada no Node-Red. Os dados são coletados e transmitidos ao Raspberry Pi por um Módulo WiFi ESP8266 NodeMcu, utilizando um Termistor de 10K Ohms como sensor de temperatura.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura3.png?raw=true)

Figura 3: Tecnologias utilizadas na implementação

O fluxo de informações primariamente se inicia no cliente HTTP, seja ele o ESP8266, com o envio das leituras de temperatura coletadas, ou o requisitante de relatórios das informações já existentes no banco. A Figura 4, abaixo, representa o fluxo de informações descrito.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura4.png?raw=true)

Figura 4: Fluxo de Dados do Projeto

## Especificação do Nível de IoT
A proposta inicial de arquitetura, apresentada na Figura 1, envolvia o emprego de diversos equipamentos nas franjas do sistema IOT (os sensores de temperatura/umidade e os aparelhos de condicionamento de ar), os quais teriam o envio de dados e tráfego de instruções concentrados localmente em um dispositivo broker. Esse dispositivo concentrador seria o responsável para enviar os dados para o servidor na nuvem. Desta forma se enquadraria num IoT Level 4.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura5.png?raw=true)

Figura 5: Representação do IoT Level 4

Com as adaptações feitas, resultando na implementação (Figura 2), contudo, o enquadramento do sistema se faz no IoT Level 3.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura6.png?raw=true)

Figura 6: Representação do IoT Level 3

## Prototipação: Integração de Dispositivos e Componentes
No que concerne a integração de equipamentos de hardware, além do Raspberry Pi em si, utilizou-se o já mencionado Módulo WiFi ESP8266 NodeMcu. A ele foi atrelado um termistor de 10K Ohms, junto com um resistor de 10K Ohms, conforme Figura 7, abaixo.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura7.png?raw=true)

Figura 7: Esquema de composição do elemento de leitura e transmissão de valor

Visto que o ESP8266 possui conexão WiFi integrada, o envio é feito sem fio para o Raspberry Pi.

## Aplicação - Um esboço
Como forma de acesso e consulta aos dados registrados pelo sistema, há um esboço de uma aplicação de inspeção e análise.
### Relatório de Leituras
A primeira funcionalidade recupera um relatório completo com todas as leituras registradas pela aplicação, plotando uma série histórica por dispositivo registrante.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura8.png?raw=true)

Figura 8: Tela de relatório mostrando série de leituras de um único dispositivo

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura9.png?raw=true)

Figura 9: Tela de relatório mostrando série de leituras de vários dispositivos


### Display da Última Leitura
A segunda funcionalidade permite acessar a leitura mais recente feita por um dispositivo específico, juntamente com informações sobre a data e horário da leitura registrada.

![alt text](https://github.com/saintclair-lima/ProjetoIotMestrado/blob/main/images/Figura10_.png?raw=true)

Figura 10: Tela de apresentação mostrando a leitura de temperatura mais recente de um dispositivo específico
