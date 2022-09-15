//https://www.tinkercad.com/things/gGj7aXdwG7V?sharecode=vTjTepKPuNAGcUZLQYs1xim6Ys4MOyUuq8BhcMvmypM

#include <Adafruit_LiquidCrystal.h>

#define redButton       7
#define greenButton     6
#define blueButton      5
#define yellowButton    4

#define redLed       13
#define greenLed     12
#define blueLed      11
#define yellowLed    10

Adafruit_LiquidCrystal lcd_1(0);

int machineColorOrder[10];
int playerOrder[10];

const int ledColor[] = {redLed, greenLed, blueLed, yellowLed};

const int buttonColor[] = {redButton, greenButton, blueButton, yellowButton};

int color = 0;
int gameLevel = 0;

void setup() {
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Game level:");

  randomSeed(analogRead(0));

  pinMode(buttonColor[0], INPUT);     //Red Button In
  pinMode(buttonColor[1], INPUT);     //Green Button In
  pinMode(buttonColor[2], INPUT);     //Blue Button In
  pinMode(buttonColor[3], INPUT);     //Yellow Button In

  pinMode(ledColor[0], OUTPUT);       //Red LED Out
  pinMode(ledColor[1], OUTPUT); 	  //Green LED Out
  pinMode(ledColor[2], OUTPUT); 	  //Blue LED Out
  pinMode(ledColor[3], OUTPUT); 	  //Yellow LED Out
}

void loop() {
  gameStart();
}

//Functions ------------------------------

void turnLedOn(int color) {
  digitalWrite(ledColor[color], HIGH);
}

void turnLedOff(int color) {
  digitalWrite(ledColor[color], LOW);
}

int pressedButton(int color) {
  return digitalRead(buttonColor[color]);
  delay(1000);
}

void shuffleMachineColorOrder() {
  for (int i = 0; i < (sizeof(machineColorOrder) / sizeof(machineColorOrder[0])); i++) {
      machineColorOrder[i] = random(4);
  }
}

void gameStart() {
  shuffleMachineColorOrder();
  gameLevel = 1;
  nextLevel();
}

void nextLevel() {
  lcd_1.setCursor(12, 0);
  lcd_1.print(gameLevel);
  for (int i = 0; i < gameLevel; i++) {
    //lcd_1.setCursor(0, 1);
  	//lcd_1.print(i);
    machineTurn(i);
  }
  
  for (int i = 0; i < gameLevel; i++) {
    playerTurn(i);
    turnCheck(i);
  }
  
  gameLevel++;
  nextLevel();
}

void machineTurn(int i) {
  lcd_1.setCursor(0, 1);
  lcd_1.print(machineColorOrder[i] + 1);
  turnLedOn(machineColorOrder[i]);
  delay(1000);
  turnLedOff(machineColorOrder[i]);
}

void playerTurn(int i) {
  while (1) {
      if (pressedButton(0) == HIGH) {
        playerOrder[i] = 0;
        return;
      }

      if (pressedButton(1) == HIGH) {
        playerOrder[i] = 1;
        return;
      }
      
      if (pressedButton(2) == HIGH) {
        playerOrder[i] = 2;
        return;
      }
      
      if (pressedButton(3) == HIGH) {
        playerOrder[i] = 3;
        return;
      }
  }
}

void turnCheck(int i) {
    if (machineColorOrder[i] != playerOrder[i]) {
      gameOver();  
    }
}

void gameOver() {
  turnLedOn(0);
  turnLedOn(1);
  turnLedOn(2);
  turnLedOn(3);
  delay(2000);
  turnLedOff(0);
  turnLedOff(1);
  turnLedOff(2);
  turnLedOff(3);
  delay(2000);
  gameReset();
}

void gameReset() {
    machineColorOrder[10] = {};
    playerOrder[10] = {};
    gameStart();
}
