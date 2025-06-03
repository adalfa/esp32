#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>



#include  <math.h>
#define RGB_COUNT 64
#define RGB_Control_PIN 14
#define TIMER0_INTERVAL_MS        1000
#define TIMER0_DURATION_MS        5000
#define SERVICE_UUID        "4fba7af5-64ca-49a7-809e-3b3cf437490a"
#define SENSOR_CHARACTERISTIC_UUID "f35dd846-0e1a-4b37-94ce-f0c5c2e47927"

Adafruit_NeoPixel pixels(RGB_COUNT, RGB_Control_PIN, NEO_RGB + NEO_KHZ800); 
static volatile bool go=false;
static volatile bool loopcurr=false;
static volatile int sec=0;
unsigned char blue[3]={0,0,255};
hw_timer_t *Timer0_Cfg = NULL;
BLEServer* pServer = NULL;
BLECharacteristic* pSensorCharacteristic = NULL;
BLECharacteristic* pLedCharacteristic = NULL;
volatile bool deviceConnected = false;
volatile bool oldDeviceConnected = false;
uint32_t value = 0;
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pLedCharacteristic) {
    String value = pLedCharacteristic->getValue();
    sec=value.toInt();
    go=true;
   // Serial.printf("letto %s\n",value.c_str());

      
    
  }
};

void IRAM_ATTR TimerHandler0(void)
{
	if (!loopcurr)
go=!go;
	//timer interrupt toggles pin PIN_D19
	
	

}
void setup() {
  
//  Serial.begin(115200);
//  while(!Serial);
//  Serial.println("Test");
  // put your setup code here, to run once:
  pixels.begin();
 pixels.setBrightness(10);
Timer0_Cfg = timerBegin(1000000);
    timerAttachInterrupt(Timer0_Cfg, &TimerHandler0);
    timerAlarm(Timer0_Cfg , 1000000*30, true, 0);

//  BLEDevice::init("ESP32");

  // Create the BLE Server
  // pServer = BLEDevice::createServer();
  // pServer->setCallbacks(new MyServerCallbacks());

//   // Create the BLE Service
  // BLEService *pService = pServer->createService(SERVICE_UUID);

//   // Create a BLE Characteristic
  // pSensorCharacteristic = pService->createCharacteristic(
  //                     SENSOR_CHARACTERISTIC_UUID,
  //                     BLECharacteristic::PROPERTY_READ   |
  //                     BLECharacteristic::PROPERTY_WRITE  |
  //                     BLECharacteristic::PROPERTY_NOTIFY |
  //                     BLECharacteristic::PROPERTY_INDICATE
  //                   );

//   // Create the ON button Characteristic
//   pLedCharacteristic = pService->createCharacteristic(
//                       LED_CHARACTERISTIC_UUID,
//                       BLECharacteristic::PROPERTY_WRITE
//                     );

//   // Register the callback for the ON button characteristic
//   pLedCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

//   // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
//   // Create a BLE Descriptor
//   pSensorCharacteristic->addDescriptor(new BLE2902());
//   pLedCharacteristic->addDescriptor(new BLE2902());

//   // Start the service
//   pService->start();

//   // Start advertising
//   BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//   pAdvertising->addServiceUUID(SERVICE_UUID);
//   pAdvertising->setScanResponse(false);
//   pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
//  BLEDevice::startAdvertising();

}

void fillcolor(unsigned char col[3])
{
  for(int i=0;i<=RGB_COUNT;i++){
  pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

    pixels.show();
  }  
}
void pulsebright( int min,int max,int idelay,int step,unsigned char col[3] )
 {
int pause=idelay/2;
pause=pause/sqrt(max-min);
for(int k=min;k<=max;k+=sqrt(k))
{
 pixels.setBrightness(k);  
  for(int i=0;i<=RGB_COUNT;i+=3){
  pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

    pixels.show();
  }  
  for(int i=0;i<=RGB_COUNT;i+=2){
  pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

  pixels.show();
  }
  for(int i=0;i<=RGB_COUNT;i+=1){
  pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

  pixels.show();
  }
//delay(pause);
}
for(int k=max;k>=min;k-=sqrt(k))
{
 pixels.setBrightness(k);
 for(int i=0;i<=RGB_COUNT;i+=3){
pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

pixels.show();
}  
for(int i=0;i<=RGB_COUNT;i+=2){
pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

pixels.show();
}
for(int i=0;i<=RGB_COUNT;i+=1){
pixels.setPixelColor(i,pixels.Color(col[0],col[1],col[2]));

pixels.show();
}
//delay(pause);
}
}

void timer(){

loopcurr=true;
  int interval=1000;

int ly=floor((sec)/2);
int lr=(sec/100)*8.3;

 unsigned char green[3]={0,255,0};
 unsigned char red[3]={255,0,0};

  unsigned char black[3]={0,0,0};
  unsigned char colore[3]={0,255,0};


// Serial.println("primo ciclo");
 for(int i=0;go&&i<ly;i++){
 // Serial.printf("%d\n",i);
  colore[0]=map(i,0,ly,0,255);
 //colore[1]=255-i;
 fillcolor(colore);
 delay(interval-150);
 //pulsebright(10, 20, 0,2, colore );
 }
// Serial.println("secondo ciclo");
 for(int i=0;go&&i<(ly-lr);i++){
   colore[0]=255;
   colore[1]=255-map(i,0,(ly-lr),0,255);
   
  fillcolor( colore );
   delay(interval-150);
   }
loopcurr=false;
// Serial.println("pulsazione");
  while (go)
  {
    pulsebright(10, 50, 1,2, red );
  }
  fillcolor(black);
 
}




// x/2 yellow 
void loop() {
fillcolor(blue);

// while (!deviceConnected)
// {
//   //Serial.println("sleep");
//   delay(1000);
// }

// if (deviceConnected) {
//     pSensorCharacteristic->setValue(String(value).c_str());
//     pSensorCharacteristic->notify();
//     value++;
//     // Serial.print("New value notified: ");
//     // Serial.println(value);
//     delay(3000); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
//   }
//   // disconnecting
//   if (!deviceConnected && oldDeviceConnected) {
//     //Serial.println("Device disconnected.");
//     delay(500); // give the bluetooth stack the chance to get things ready
//     pServer->startAdvertising(); // restart advertising
//    // Serial.println("Start advertising");
//     oldDeviceConnected = deviceConnected;
//   }
//   // connecting
//   if (deviceConnected && !oldDeviceConnected) {
//     // do stuff here on connecting
//     oldDeviceConnected = deviceConnected;
//    //Serial.println("Device Connected");
//   }
 //Serial.println("start timer");
  if (go)
  timer();

  // go=true;
  // timer(10);

}

