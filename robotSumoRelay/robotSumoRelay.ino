#include <Ps3Controller.h>

#define M1A 32
#define M1B 33
#define M2A 25
#define M2B 26

#define B 23

int lx , ly ;

void setupMotor(){
pinMode( M1A, OUTPUT);
pinMode( M1B, OUTPUT);
pinMode( M2A, OUTPUT);
pinMode( M2B, OUTPUT);
pinMode( B, OUTPUT);

}

void notify()
{
  if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
    lx = Ps3.data.analog.stick.rx;
    ly = Ps3.data.analog.stick.ry;
    stop();
    kinematik(lx , ly);
  }else{ 
    if( Ps3.event.button_down.up )
       maju();
    if( Ps3.event.button_up.up )
        stop();

    if( Ps3.event.button_down.right )
        kanan();
    if( Ps3.event.button_up.right )
        stop();

    if( Ps3.event.button_down.down )
        mundur();
    if( Ps3.event.button_up.down )
        stop();

    if( Ps3.event.button_down.left )
        kiri();
    if( Ps3.event.button_up.left )
        stop();
  }
  
    //------------- Digital shoulder button events -------------
    if( Ps3.event.button_down.r1 ) digitalWrite(B , HIGH);
    if( Ps3.event.button_up.r1 ) digitalWrite(B , LOW );

    if( Ps3.event.button_down.l1 ){
    
      if ( Ps3.event.button_up.l1 ){} 
    }
}

void onConnect(){
}

void setup()
{
    // Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("5a:2b:c9:01:43:54");
    setupMotor();
}

void loop()
{
    if(!Ps3.isConnected())
        return;

}


void kinematik(int x , int y){
  if(abs(x) > abs(y) ){
    if(x > 125)kanan();
    else if(x < -125)kiri();
    else stop();
 
  }else if(abs(x) < abs(y) ){
    if(y > 125)mundur();
    else if(y < -125)maju();
    else stop();
 
  }
}


void maju(){
digitalWrite(M1A , HIGH);
digitalWrite(M1B , LOW);
digitalWrite(M2A , HIGH);
digitalWrite(M2B , LOW);
// Serial.println("maju");
}

void mundur(){
digitalWrite(M1A , LOW);
digitalWrite(M1B , HIGH);
digitalWrite(M2A , LOW);
digitalWrite(M2B , HIGH);  
// Serial.println("mundur");
}

void kanan(){
digitalWrite(M1A , LOW);
digitalWrite(M1B , HIGH);
digitalWrite(M2A , HIGH);
digitalWrite(M2B , LOW);
// Serial.println("kanan");
  
}
void kiri(){
digitalWrite(M1A , HIGH);
digitalWrite(M1B , LOW);
digitalWrite(M2A , LOW);
digitalWrite(M2B , HIGH);
// Serial.println("kiri");
  
}
void stop(){
digitalWrite(M1A , LOW);
digitalWrite(M1B , LOW);
digitalWrite(M2A , LOW);
digitalWrite(M2B , LOW);
// Serial.println("stop ");
  
}