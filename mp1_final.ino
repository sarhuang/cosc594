/*
Stacker VS., an arduino game for two players.
Similar to arcade game stacker but stacking player uses slide potentiometer as input
while a second player controls the block movementspeed using a light source and a photocell.
Draws heavily from
https://github.com/sjsantoro/arduino_stacker/blob/master/arduino_stacker.ino
*/

//Pins and hardware
int photocellPin = A6;
int sliderPin = A7;

//slider variables
int sliderDirection = 0; //0 is right, 1 is left

//Game variables
int gameStatus = 0;
int score = 0;
//Dots
int dotDirection = 0;
int dotPosition = 0;  //0 is far right, 7 is far left
int currentRow = 0;

//Using byte because it's more memory efficient than int
// 00000000
byte dotArray[8] = {//Manages game state
  0x07, 
  0x00, //2nd row
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00  //8th row
};

byte lossArray[8] = {//Displays an 'L'
  0x7E,
  0x7E,
  0x60,
  0x60,
  0x60,
  0x60,
  0x60,
  0x60
};

byte winArray[8] = {
  0x7E,
  0x7E,
  0xDB,
  0xDB,
  0xDB,
  0xDB,
  0xC3,
  0x42
};//Displays a 'W'

//Used when updating game state
byte current_dots = dotArray[0];
byte tmp_byte;
int reset;

int pressed = 0;


void setup() {
  Serial.begin(9600);
  //Set up the LED matrix pins
  for(int i = 3; i <= 18; i++){
    pinMode(i, OUTPUT);
  }
}

void loop(){
  if(gameStatus == 0){
    gameLoop();
    displayGame();
  }
  else if(gameStatus == 1){
    gameWin();
    displayGame();
  }
  else if(gameStatus == 2){
    gameLose();
    displayGame();
  }
}

//Tracks slide potentiometer input and returns HIGH when slider hits alternating extremes
int sliderRead() {
  if(analogRead(A7) > 950 && sliderDirection == 0) {
    sliderDirection = 1;
    return HIGH;
  }
  if(analogRead(A7) < 2 && sliderDirection == 1) {
    sliderDirection = 0;
    return HIGH;
  }
  return LOW;
}

//Reads photocell to determine speed that block travels at
float luxRead() {
  int reading = analogRead(A6);

  Serial.println((-2.628 * float(reading)) + 1730);

  return (-2.36 * float(reading)) + 1730;
}

//Handles all game logic
void gameLoop() {
  static unsigned long lastMoveTime = 0; // Variable to store the time of the last dot movement
  unsigned long currentTime = millis(); // Get the current time
  
  // Check if enough time has passed since the last dot movement (determined by photocell)
  if (currentTime - lastMoveTime >= rint(luxRead())) {
    // Moves the dot back and forth
    if (dotDirection == 0) { // started at far right <--
      dotPosition++;
      // switch directions if at wall
      if (dotPosition == 7) {
        dotDirection = 1;
      }
    } else if (dotDirection == 1) { // started at far left -->
      dotPosition--;
      // switch directions if it hits a wall
      if (dotPosition == 0) {
        dotDirection = 0;
      }
    }

    // change the position
    dotArray[currentRow] = (current_dots << dotPosition);    

    // Reset the last move time to the current time
    lastMoveTime = currentTime;
  }

  //Check for user input after updating display
  if (sliderRead() == HIGH) {
    Serial.println("Buttt!");

    // Check for intersection between the current and next rows
    if (currentRow == 0 || (dotArray[currentRow] & dotArray[currentRow - 1]) > 0) {
      Serial.println("Intersection detected");

      // Check if the player reached the top row
      if (currentRow == 7) {
        // Set game status to 1 (win)
        gameStatus = 1;
        return;
      }
      else if(currentRow == 0) {
        currentRow++;
        dotArray[currentRow] |= dotArray[currentRow - 1];
      } 
      else {

        //Subtract off overhang
        dotArray[currentRow] &= dotArray[currentRow - 1];
        tmp_byte = dotArray[currentRow];
        for(int i = 0; i < 8; i++) {
          if(((tmp_byte >> i) & 1) == 1) {
            reset = i;
            break;
          }
        }

        //update number of player blocks left
        current_dots = dotArray[currentRow] >> reset;
          
        // Move up to the next row
         currentRow++;

        // Copy current row to next row
        dotArray[currentRow] |= dotArray[currentRow - 1];
      }
    }else {//Player had missed blocks and game enters loss state
      currentRow++;
      dotArray[currentRow] |= dotArray[currentRow - 1];
      gameStatus = 2;
      return;
    }
  }
}

//Updates display with pattern for win state
void gameWin(){
  for(int i = 0; i < 8; i++){
    dotArray[i] = winArray[i];
  }
}

//Updates display with pattern for loss state
void gameLose(){
  for(int i = 0; i < 8; i++){
    dotArray[i] = lossArray[i];
  }
}


//Manages displaying of whatever the pattern currently is using scanning technique
void displayGame() {
  for(int row = 0; row < 8; row++) {
    //Set only the active row low
    for(int crow = 0; crow < 8; crow++){
      if(crow == row) digitalWrite(crow + 11, LOW);
      else digitalWrite(crow+11,HIGH);
    }
    //Set columns high for leds that correspond to grid blocks that have a game block on them
    for(int col = 0; col < 8; col++) digitalWrite(col + 3, (dotArray[row] >> (7-col)) & 1);
    //Refresh rate
    delay(1);
  }
}
