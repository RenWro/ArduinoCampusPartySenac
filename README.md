# Arduino Campus Party

Alguns exercícios em Arduino levados para o stand do Senac na Campus Party 2024
Os projetos foram, em maioria, realizados em uma placa Esp8266 tipo Wemos D1, exceto o Semáforo Simples (que foi realizado em uma placa Arduino UNO)

![image](https://github.com/RenWro/ArduinoCampusPartySenac/assets/134458911/c20a24dc-2cca-4d3e-bfe1-aaebe7486326)


Foram realizados os seguintes projetos:
<ul>
  <li>Semáforo simples</li>
  <li>Teste de Tela com triângulo simples</li>
  <li>Tela LCD simples</li>
  <li>Sensor de Umidade, Temperatura e distância com Tela LCD de visualização</li>
  <li>Botão de pânico triplo(Pânico, Alimentação e </li>
</ul>

O projeto do semáforo foi elaborado com leds e resistências e depois reproduzido com um módulo semáforo para exercício.

![image](https://github.com/RenWro/ArduinoCampusPartySenac/assets/134458911/c4d19a1c-fde3-41fc-87a9-5761e36dbac7)

O projeto Botão de pânico teve que contar com um microswitch. A respeito desse, foi possível perceber que existem as entradas normais 2 e 3, que conferem ao botão os estados de Normally Open ou Normally Closed, além da entrada comum. Segue a imagem do microswitch utilizado, Normally Open: 

![image](https://github.com/user-attachments/assets/4ff3e650-8b61-4f80-965d-03f5709fdd6e)
![image](https://github.com/user-attachments/assets/56216f2f-3cc5-42f9-80dc-efe472c698a9)


Os leds tivem que ser conectados separadamente na protoboard, para que, uma vez que os botões fossem disparados, os leds acendessem.
Outros tipos de microswitches estão representados no esquema abaixo:

![image](https://github.com/user-attachments/assets/71e678f1-5f4e-4677-853a-58874b2f7191)


Os projetos do sensor e do Botão de pânico deveriam utilizar Broker MTQQ para enviar mensagens reportando estado e mudança de estado, porém foi um desafio garantir que a rede não iimpedisse por razões de segurança tal conexão, deixando a conexão como um desafio para os próximos projetos.



