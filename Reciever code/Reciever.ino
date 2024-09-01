#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   D4
#define CSN_PIN  D3

const byte address[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[32]; // this must match dataToSend in the TX
int counter = 0;
long int current;
long int delay0;

//===========

void setup() {
    Serial.begin(9600);

    while (!Serial) { }

    Serial.println("SimpleRx Starting");
    Serial.println("SimpleRx Starting");
    Serial.println("SimpleRx Starting");

    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MIN, 0);
    radio.setChannel(0); // 2400 MHz
    radio.setAddressWidth(5);
    radio.printDetails();
    radio.openReadingPipe(1, address);
    radio.startListening();
}
//=============

void loop() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        counter++; 
    }
    // printed to ensure that the receiver is fucntioning
    Serial.println(counter);
}