#include <OneButton.h>

#define on_off_btn 19
#define color_btn 4
#define bright_up_btn 27
#define bright_down_btn 26


#define warm_light 21
#define neutral_light 22
#define cool_light 23

int color_number = 0;
int brightness   = 1; //from 1 to 5 (10, 25, 50, 75, 100)
int on_off_flag = 0; //on off flags


OneButton on_off = OneButton(on_off_btn, true, false);
OneButton color = OneButton(color_btn, true, false);
OneButton bright_up = OneButton(bright_up_btn, true, false);
OneButton bright_down = OneButton(bright_down_btn, true, false);

//PWM SETTINGS
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  // put your setup code here, to run once:
   ledcSetup(ledChannel, freq, resolution);
   Serial.begin(115200);
  on_off.attachClick(toggle_power);
  color.attachClick(change_color);
  bright_up.attachClick(increase_brightness);
  bright_down.attachClick(decrease_brightness);

  /* pinMode( warm_light, OUTPUT);
   pinMode( neutral_light, OUTPUT);
   pinMode( cool_light, OUTPUT);*/
   
   ledcAttachPin(warm_light, ledChannel);
   ledcAttachPin(neutral_light, ledChannel);
   ledcAttachPin(cool_light, ledChannel);
} 

void loop() {
  // put your main code here, to run repeatedly:
      on_off.tick();
      color.tick();
      bright_up.tick();
      bright_down.tick();
      
   if(on_off_flag)
  {
    Serial.println("On and Running");
   int dutycycle = 0;
   /**********************************/
   //setting the duty cycle according to the brightness level selected
   switch(brightness){
    case 1 :
    dutycycle = 25;
    break;

    case 2 :
    dutycycle = 63;
    break;

    case 3 :
    dutycycle = 128;
    break;

    case 4 :
    dutycycle = 192;
    break;

    case 5 :
    dutycycle = 255;
    break;
    }
   /********************************************/

   if (color_number == 0)
   {
      ledcWrite(warm_light, dutycycle);
      Serial.println("Warm light");
    }
   else if(color_number == 1){
    ledcWrite(neutral_light , dutycycle);
    Serial.println("Neutral light");
    }

    else{
      ledcWrite(cool_light , dutycycle);
      Serial.println("Cool light");
      }
  }
 else{
  return;
  
 }
 
}
void toggle_power(){
  if (on_off_flag == 0){
    on_off_flag = 1;
    }
  else{
    on_off_flag = 0;
    }
}
void change_color (){
    // 0 1 2
    if(color_number > 2)
    {
      color = 0;
    }
    else{
        color_number++;
      }
  }
void increase_brightness (){
   if(brightness > 5){
     brightness = 5 ;
   }
  else{
     brightness++;
    }
}

void decrease_brightness (){
   if(brightness < 0){
     brightness = 0 ;
   }
  else{
     brightness--;
    }
}
  
