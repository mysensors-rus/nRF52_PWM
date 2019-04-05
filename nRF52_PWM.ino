/**
Пример испльзования ШИМ (диммера) с возможностью изменения частоты

*/

//#define MY_DEBUG
#define MY_RADIO_NRF5_ESB
#define MY_PASSIVE_NODE
#define MY_NODE_ID 0
#define MY_LED 8

#include <MySensors.h>
#define CHILD_ID 1   // Id of the sensor child


void preHwInit() {
pinMode(MY_LED, OUTPUT);  
digitalWrite(MY_LED, LOW);
}

void before()
{
NRF_POWER->DCDCEN = 1; // закоментировать если E73
//NRF_UART0->ENABLE = 0;  
}

void presentation()
{
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Dimmer node", "1.0");

  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID, S_DIMMER);
}

void setup() {
//  analogWriteResolution(10);

}

void loop() {

}

void receive(const MyMessage &message)
{
	// We only expect one type of message from controller. But we better check anyway.
	if (message.type==V_PERCENTAGE) {
		// Change relay state
		analogWrite(MY_LED, message.getByte());
		// Store state in eeprom
		saveState(message.sensor, message.getByte());
		#ifdef MY_DEBUG
			// Write some debug info
			Serial.print("Incoming change for sensor:");
			Serial.print(message.sensor);
			Serial.print(", New status: ");
			Serial.println(message.getBool());
		#endif
	}
}
