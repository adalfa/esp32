#include <Adafruit_NeoPixel.h>


#include  <math.h>
#define RGB_COUNT 64
#define RGB_Control_PIN 14
#define TIMER0_INTERVAL_MS        1000
#define TIMER0_DURATION_MS        5000
Adafruit_NeoPixel pixels(RGB_COUNT, RGB_Control_PIN, NEO_RGB + NEO_KHZ800); 
static volatile bool go=true;
static volatile bool loopcurr=false;
hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR TimerHandler0(void)
{
	if (!loopcurr)
go=!go;
	//timer interrupt toggles pin PIN_D19
	
	

}
void setup() {
  pixels.begin();
//  Serial.begin(115200);
//   while(!Serial);
//   Serial.println("Test");
  // put your setup code here, to run once:
 pixels.setBrightness(10);
Timer0_Cfg = timerBegin(1000000);
    timerAttachInterrupt(Timer0_Cfg, &TimerHandler0);
    timerAlarm(Timer0_Cfg , 1000000*30, true, 0);

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

void timer(int sec){

loopcurr=true;
  int interval=1000;

int ly=floor((sec)/2);
int lr=(sec/100)*8.3;

 unsigned char green[3]={0,255,0};
 unsigned char red[3]={255,0,0};
  unsigned char blue[3]={0,0,255};
  unsigned char black[3]={0,0,0};
  unsigned char colore[3]={0,255,0};


 
 for(int i=0;go&&i<ly;i++){
  colore[0]=map(i,0,ly,0,255);
 //colore[1]=255-i;
 fillcolor(colore);
 delay(interval-150);
 //pulsebright(10, 20, 0,2, colore );
 }

 for(int i=0;go&&i<(ly-lr);i++){
   colore[0]=255;
   colore[1]=255-map(i,0,(ly-lr),0,255);
   
  fillcolor( colore );
   delay(interval-150);
   }
loopcurr=false;
  while (go)
  {
    pulsebright(10, 50, 1,2, red );
  }
  fillcolor(black);
  delay(1000);
}




// x/2 yellow 
void loop() {

  timer(60);

  go=true;
  timer(10);

}

