#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>

boolean mensagem;
boolean estado_sensor;


//Define o endereço MAC que será utilizado
byte mac[] = {0x8E,0x0F,0x83,0xB1,0xEA,0xCD};

//Inicia o cliente Ethernet
EthernetClient client;

PubSubClient mqttClient(client);

void setup() {
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);
    pinMode(2,INPUT_PULLUP);
    
    mqttClient.setServer("54.173.148.114",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop() {

  estado_sensor = digitalRead(2);
  

  // Nome do cliente que será acessado remotamente.
  mqttClient.connect("portafechada");

  if(estado_sensor == 0) {   
          
        mensagem = mqttClient.publish("portafechada", "FECHADO");
        Serial.println("RACK FECHADO!");
        
    } else {        
        mensagem = mqttClient.publish("portafechada", "ABERTO");
        Serial.println("RACK ABERTO!");
        
        
    }

  
  mqttClient.loop();

 
}
