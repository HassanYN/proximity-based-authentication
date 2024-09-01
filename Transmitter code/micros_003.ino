#include <RF24.h>

#define CE_PIN   D4
#define CSN_PIN  D3

const byte ADDRESS[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio


double timeOfSending;
double timeACKReceived;
double sum;
double sumOfAverages;
double average;
double averageOfAverages;
bool rslt;
bool failed;
int counter;
int list[20];
char dataToSend[32] = "HelloHelloHelloHelloHelloHello";

int correct;
int iteration;

double start;
double end;

void setup() {

    Serial.begin(9600);

    while (!Serial) { }

    Serial.println("SimpleRx Starting");
    Serial.println("SimpleRx Starting");
    Serial.println("SimpleRx Starting");

    radio.begin();
    
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_LOW);
    radio.setChannel(0); // 2400 MHz
    radio.setAddressWidth(5);
    // this will print all the setting of transceiver
    radio.printDetails();
    radio.openWritingPipe(ADDRESS);

    correct = 0;
    iteration = 0;
}

int openCounter;
int notOpenConter;

void loop() {
    failed = false;
    openCounter = 0;
    notOpenConter = 0;
    for (int i = 0; i < 10; i++) {
      counter = 0;
      sum = 0;
      for (int j = 0; j < 25; j++) {
        timeOfSending = micros();
        rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        if (rslt) {
            timeACKReceived = micros();
            sum = sum + (timeACKReceived - timeOfSending);
            counter++;
        }
        else {
            Serial.println("  Tx failed");
            failed = true;
        }
        delay(10);
      }
    
      average = sum / counter;
      if (failed) {
        Serial.println("failed transmission");
      } else {
      if (average < 2150)
        openCounter++;
      else
        notOpenConter++;
      }
    }
    
    iteration++;
    if (openCounter > 7) {
      Serial.println("OK");
      correct++;
    }
    else
      Serial.println("NOT");
    Serial.println(iteration);
    Serial.println("##############");
}

//===================================
