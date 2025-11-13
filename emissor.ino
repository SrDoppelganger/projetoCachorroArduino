#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 

#define CE_PIN 48 
#define CSN_PIN 53
#define INTERVAL_MS_TRANSMISSION 250 
RF24 radio(CE_PIN, CSN_PIN); 
const byte address[6] = "00001"; 
//NRF24L01 buffer limit is 32 bytes (max struct size) 
//data1 = comando para os receptores
//a-andar, g-girar, t-trotar, p-pular,z-parar
struct payload { 
	 char data1;  
}; 
payload payload; 

//botões e seus respectivos estados
const int andarPin = 2;
int lastAndarState; 
int currentAndarState;

const int girarPin = 3;
int lastGirarState; 
int currentGirarState;

const int trotarPin = 4;
int lastTrotarState; 
int currentTrotarState;

void setup() 
{ 
	 Serial.begin(115200); 

   //setup dos botões
   pinMode(andarPin, INPUT_PULLUP);
   currentAndarState = digitalRead(andarPin);
  
   
   pinMode(girarPin, INPUT_PULLUP);
   currentGirarState = digitalRead(girarPin);

   pinMode(trotarPin, INPUT_PULLUP);
   currentGirarState = digitalRead(girarPin);


   //setup do wifi
	 radio.begin(); 
	 //Append ACK packet from the receiving radio back to the transmitting radio 
	 radio.setAutoAck(false); //(true|false) 
	 //Set the transmission datarate 
	 radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS) 
	 //Greater level = more consumption = longer distance 
	 radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX) 
	 //Default value is the maximum 32 bytes 
	 radio.setPayloadSize(sizeof(payload)); 
	 //Act as transmitter 
	 radio.openWritingPipe(address); 
	 radio.stopListening(); 
} 
void loop() 
{ 
	lastAndarState = currentAndarState; 
  currentAndarState = digitalRead(andarPin);

  lastGirarState = currentGirarState; 
  currentGirarState = digitalRead(girarPin);

  lastTrotarState = currentTrotarState; 
  currentTrotarState = digitalRead(trotarPin);

  //chama a função correspondente para cada botão
  if(lastAndarState == HIGH && currentAndarState == LOW) {
    Serial.println("The button is pressed");
    // envia os dados
    sendAndar();
  }
  if(lastGirarState == HIGH && currentGirarState == LOW) {
    Serial.println("The button is pressed");
    // envia os dados
    sendGirar();
  }
  if(lastTrotarState == HIGH && currentTrotarState == LOW) {
    Serial.println("The button is pressed");
    // envia os dados
    sendTrotar();
  }
} 

void sendAndar(){
  payload.data1 = 'a'; 
	radio.write(&payload, sizeof(payload)); 
	Serial.print("Data1:"); 
	Serial.println(payload.data1);
	Serial.println("Sent"); 
	delay(INTERVAL_MS_TRANSMISSION); 
}

void sendGirar(){
  payload.data1 = 'g'; 
	radio.write(&payload, sizeof(payload)); 
	Serial.print("Data1:"); 
	Serial.println(payload.data1); 
	Serial.println("Sent"); 
	delay(INTERVAL_MS_TRANSMISSION); 
}

void sendTrotar(){
  payload.data1 = 't'; 
	radio.write(&payload, sizeof(payload)); 
	Serial.print("Data1:"); 
	Serial.println(payload.data1); 
	Serial.println("Sent"); 
	delay(INTERVAL_MS_TRANSMISSION); 
}

