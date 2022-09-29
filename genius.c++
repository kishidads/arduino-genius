#include <Adafruit_LiquidCrystal.h>

#define redLed       13
#define greenLed     12
#define blueLed      11
#define yellowLed    10

#define redButton     7
#define greenButton   6
#define blueButton    5
#define yellowButton  4

Adafruit_LiquidCrystal lcd_1(0);

int machineColorOrder[10];
int playerColorOrder[10];

const int ledColor[] = {redLed, greenLed, blueLed, yellowLed};

const int buttonColor[] = {redButton, greenButton, blueButton, yellowButton};

int color = 0;
int gameLevel = 0;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  pinMode(ledColor[0], OUTPUT);   //Red LED Out
  pinMode(ledColor[1], OUTPUT);   //Green LED Out
  pinMode(ledColor[2], OUTPUT);   //Blue LED Out
  pinMode(ledColor[3], OUTPUT);   //Yellow LED Out

  pinMode(buttonColor[0], INPUT); //Red Button In
  pinMode(buttonColor[1], INPUT); //Green Button In
  pinMode(buttonColor[2], INPUT); //Blue Button In
  pinMode(buttonColor[3], INPUT); //Yellow Button In
}

void loop() {
  gameStart();
}

//Functions ------------------------------

void ledTurnOn(int color) {
  digitalWrite(ledColor[color], HIGH);
}

void ledTurnOff(int color) {
  digitalWrite(ledColor[color], LOW);
}

int buttonPress(int color) {
  return digitalRead(buttonColor[color]);
}

void shuffleMachineColorOrder() {
  for (int i = 0; i < (sizeof(machineColorOrder) / sizeof(machineColorOrder[0])); i++) {
    machineColorOrder[i] = random(4);

    Serial.print(machineColorOrder[i] + 1);
  }
  Serial.print('\n');
}

void gameStart() {
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Game level:");

  shuffleMachineColorOrder();
  gameLevel = 1;
  nextLevel();
}

void nextLevel() {
  lcd_1.setCursor(12, 0);
  lcd_1.print(gameLevel);

  for (int i = 0; i < gameLevel; i++) {
    machineTurn(i);
  }
  
  for (int i = 0; i < gameLevel; i++) {
    playerTurn(i);

    Serial.print(playerColorOrder[i] + 1);

    turnCheck(i);
  }
  
  Serial.print('\n');

  gameLevel++;
  delay(1000);
  nextLevel();
}

void machineTurn(int i) {
  ledTurnOn(machineColorOrder[i]);
  delay(500);
  ledTurnOff(machineColorOrder[i]);
  delay(1000);
}

void playerTurn(int i) {
  while (1) {
    if (buttonPress(0) == HIGH) {
      ledTurnOn(0);
      delay(50);
      if(buttonPress(0) == LOW) {
        ledTurnOff(0);
        playerColorOrder[i] = 0;
        return;
      }
    }

    if (buttonPress(1) == HIGH) {
      ledTurnOn(1);
      delay(50);
      if(buttonPress(1) == LOW) {
        ledTurnOff(1);
        playerColorOrder[i] = 1;
        return;
      }
    }
      
    if (buttonPress(2) == HIGH) {
      ledTurnOn(2);
      delay(50);
      if(buttonPress(2) == LOW) {
        ledTurnOff(2);
        playerColorOrder[i] = 2;
        return;
      }
    }
      
    if (buttonPress(3) == HIGH) {
      ledTurnOn(3);
      delay(50);
      if(buttonPress(3) == LOW) {
        ledTurnOff(3);
        playerColorOrder[i] = 3;
        return;
      }
    }
  }
}

void turnCheck(int i) {
  if (machineColorOrder[i] != playerColorOrder[i]) {
    gameOver();  
  }
}

void gameOver() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Game Over");

  ledTurnOn(0);
  ledTurnOn(1);
  ledTurnOn(2);
  ledTurnOn(3);
  delay(2000);
  ledTurnOff(0);
  ledTurnOff(1);
  ledTurnOff(2);
  ledTurnOff(3);
  delay(2000);
  gameReset();
}

void gameReset() {
  machineColorOrder[10] = {};
  playerColorOrder[10] = {};

  gameStart();
}