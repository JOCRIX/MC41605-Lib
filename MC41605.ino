#define RS 4
#define RW 5
#define E 6
#define DB0 7
#define DB1 8
#define DB2 9
#define DB3 10
#define DB4 11
#define DB5 12
#define DB6 13
#define DB7 3
#define N 1
#define F 0
#define DL 1


void setup (){
    Serial.begin(9600);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, INPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    displayInit();

}

void loop(){
    //Serial.println("test");
    //delay(500);
}

void displayInit(){
    //Power on
    delay(40);//wait for vcc
    //Stage 1 init FUNCTION SET 1
    digitalWrite(RS, LOW);
    digitalWrite(RW, LOW);
    digitalWrite(DB7, LOW);
    digitalWrite(DB6, LOW);
    digitalWrite(DB5, HIGH);
    digitalWrite(DB4, HIGH);
    digitalWrite(DB3, N);
    digitalWrite(DB2, F);
    digitalWrite(DB1, LOW); //Dont care
    digitalWrite(DB0, LOW); //Dont care
    while (displayCheckBF(RS, RW) == true){
        Serial.println("Stage 1: Waiting for BF..");
    }
    delayMicroseconds(37);
    
    //stage 2 init repeat FUNCTION SET 2
    digitalWrite(RS, LOW);
    digitalWrite(RW, LOW);
    digitalWrite(DB7, LOW);
    digitalWrite(DB6, LOW);
    digitalWrite(DB5, HIGH);
    digitalWrite(DB4, HIGH);
    digitalWrite(DB3, N);
    digitalWrite(DB2, F);
    digitalWrite(DB1, LOW); //Dont care
    digitalWrite(DB0, LOW); //Dont care
        while (displayCheckBF(RS, RW) == true){
        Serial.println("Stage 2: Waiting for BF..");
    }
    delayMicroseconds(37);

    //stage 3 init  DISLAY ON/OFF CONTROL
    digitalWrite(RS, LOW);
    digitalWrite(RW, LOW);
    digitalWrite(DB7, LOW);
    digitalWrite(DB6, LOW);
    digitalWrite(DB5, LOW);
    digitalWrite(DB4, LOW);
    digitalWrite(DB3, HIGH);
    digitalWrite(DB2, HIGH); //Display ON
    digitalWrite(DB1, HIGH); //Cursor ON
    digitalWrite(DB0, HIGH); //Blink Cursor ON
        while (displayCheckBF(RS, RW) == true){
        Serial.println("Stage 3: Waiting for BF..");
    }
    delayMicroseconds(37);
    //stage 4 init DISPLAY CLEAR
    digitalWrite(RS, LOW);
    digitalWrite(RW, LOW);
    digitalWrite(DB7, LOW);
    digitalWrite(DB6, LOW);
    digitalWrite(DB5, LOW);
    digitalWrite(DB4, LOW);
    digitalWrite(DB3, LOW);
    digitalWrite(DB2, LOW); //Display ON
    digitalWrite(DB1, LOW); //Cursor ON
    digitalWrite(DB0, HIGH); //Blink Cursor ON
    delay(1);
    delayMicroseconds(520);
            while (displayCheckBF(RS, RW) == true){
        Serial.println("Stage 4: Waiting for BF..");
    }
    //Stage 5 Entry mode set
    digitalWrite(RS, LOW);
    digitalWrite(RW, LOW);
    digitalWrite(DB7, LOW);
    digitalWrite(DB6, LOW);
    digitalWrite(DB5, LOW);
    digitalWrite(DB4, LOW);
    digitalWrite(DB3, LOW);
    digitalWrite(DB2, HIGH); //Display ON
    digitalWrite(DB1, HIGH); //Cursor ON
    digitalWrite(DB0, LOW); //Blink Cursor ON


}
bool displayCheckBF(uint8_t rsPin, uint8_t rwPin){
    bool state;
    pinMode(rsPin, INPUT);
    pinMode(rwPin, INPUT);
    pinMode(DB7, INPUT);
    if(digitalRead(DB7) == HIGH){
    
    //if((digitalRead(rsPin) == 0) && (digitalRead(rwPin) == 1)){
        
        state = true;
    }
    else{
        state = false;
        pinMode(rsPin, OUTPUT);
        pinMode(rwPin, OUTPUT);
        pinMode(DB7, OUTPUT);
    }
    return state;
}