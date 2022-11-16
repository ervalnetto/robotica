#include <RGBLed.h>
//Follow us on other social media

//https://www.youtube.com/c/ZinTechIdeas
//https://www.facebook.com/zin.techideas.3
//https://www.instagram.com/zintechideas/
//https://twitter.com/Zintechideas
//https://zintechideas.ir/
#define Rpin 11
#define Gpin 10
#define Bpin 9
#define sensorPin A0
int vermelho, verde, azul;
RGBLed led(11, 10, 9, RGBLed::COMMON_CATHODE);
float sensorValue = 0, filteredSignal = 0,sensorValue1=0,
    filteredSignalValues[] = {3.4, 3.1, 2.7, 2.13, 2.1, 1.7, 1.3, 0.9, 0.4};
    

void setup () {

  Serial.begin (9600);
  led.off();
}

void loop () {

  MainFunction();
  delay(5);
}

void MainFunction() {

  sensorValue = (float) analogRead(sensorPin) * (5.0 / 1024.0);
sensorValue1 = (float) analogRead(sensorPin);
if(sensorValue1<524 || sensorValue1>526){
  FilterSignal(sensorValue);
  Serial.print(sensorValue1);
  Serial.print(sensorValue);

  Serial.print(" ");
  Serial.println(filteredSignal);

  CompareSignalFiltered(filteredSignal);
}
}

void FilterSignal(float sensorSignal) {
 
  filteredSignal = (0.945 * filteredSignal) + (0.0549 * sensorSignal);


  if(filteredSignal>=2.48){
    filteredSignal=0;
  }
 
}

void CompareSignalFiltered(float filteredSignal) {

  if (filteredSignal > filteredSignalValues[0]) {
    faiderColor(0, 0, 255);
    Serial.println("Blue");
  } else if (filteredSignal <= filteredSignalValues[0] && filteredSignal > filteredSignalValues[1]) {
    Serial.println("Azure");
    RGBColor(0, 255, 255);
  } else if (filteredSignal <= filteredSignalValues[1] && filteredSignal > filteredSignalValues[2]) {
    RGBColor(0, 127, 255);
    Serial.println("Cyan");
  } else if (filteredSignal <= filteredSignalValues[2] && filteredSignal > filteredSignalValues[3]) {
    RGBColor(0, 255, 127);
    Serial.println("Aqua marine");
  } else if (filteredSignal <= filteredSignalValues[3] && filteredSignal > filteredSignalValues[4]) {
    RGBColor(0, 255, 0);
    Serial.println("Green");
    //faiderColor(0, 0, 255);
  } else if (filteredSignal <= filteredSignalValues[4] && filteredSignal > filteredSignalValues[5]) {
    RGBColor(255, 255, 0);
    Serial.println("Yellow");
  } else if (filteredSignal <= filteredSignalValues[5] && filteredSignal > filteredSignalValues[6]) {
    RGBColor(255, 0, 255);
    Serial.println("Magenta");
  } else if (filteredSignal <= filteredSignalValues[6] && filteredSignal > filteredSignalValues[7]) {
    RGBColor(255, 0, 127);
    Serial.println("Rose");
  } else if (filteredSignal <= filteredSignalValues[7] && filteredSignal > filteredSignalValues[8]) {
    RGBColor(255, 127, 0);
    fade();
    Serial.println("Orange");
  } else if (filteredSignal <= filteredSignalValues[8]) {
    RGBColor(255, 0, 0);
    Serial.println("Red");
    flash();
  } else {
   // led.off();
    RGBColor(0, 0, 255);
    Serial.println("Default: Blue");
  }
}

void RGBColor(int Rcolor, int Gcolor, int Bcolor) {

  analogWrite(Rpin, Rcolor);
  analogWrite(Gpin, Gcolor);
  analogWrite(Bpin, Bcolor);

 
} 
//faz um degrade das cores
void faiderColor(int Rcolor, int Gcolor, int Bcolor){
   for (vermelho = 0; vermelho <= 255; vermelho++){
      analogWrite(Rpin, vermelho);
      delay(2);
  }
  for (azul = 255; azul >= 0; azul--){
    analogWrite(Bpin, azul);
    delay(2);
  }
//incrementa a cor verde gradativamente, atingindo a cor amarela
  for (verde = 0; verde <= 255; verde++){
    analogWrite(Gpin, verde);
    delay(2);
  }
//remove a cor vermelha gradativamente, atingindo a cor verde pura
  for (vermelho = 255; vermelho >= 0; vermelho--){
    analogWrite(Rpin, vermelho);
    delay(2);
  }
//adiciona a cor azul gradativamente, atingindo a cor ciano
  for (azul = 0; azul <= 255; azul++){
    analogWrite(Bpin, azul);
    analogWrite(Rpin, azul);
    delay(2);
  }
//remove a cor verde gradativamente, atingindo a cor azul pura
  for (verde = 255; verde >= 0; verde--){
    analogWrite(Gpin, verde);
    analogWrite(Rpin, verde);
    delay(2);
  }

}

void flash(){
  // Flash red color, interval 100ms
	led.flash(RGBLed::RED, 100);

	// Flash green color, interval 100ms
	led.flash(0, 255, 0, 100);

	// Flash red color, during 250ms with interval 100ms
	led.flash(RGBLed::RED, 250, 100);

	// Flash green color, during 250ms with interval 100ms
	led.flash(0, 255, 0, 250, 100);
}

void fade(){

  // Fade out red color, with 5 steps during 100ms
	led.fadeOut(RGBLed::RED, 5, 100);

	// Fade out green color, with 5 steps during 100ms
	led.fadeOut(0, 255, 0, 5, 100);

	// Fade in red color, with 5 steps during 100ms
	led.fadeIn(RGBLed::RED, 5, 100);

	// Fade in green color, with 5 steps during 100ms
	led.fadeIn(0, 255, 0, 5, 100);
}
