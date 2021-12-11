#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

int Steps = 0;
boolean Direction = true;
int q;

extern void myStep();
extern void oneCircle();
extern void quarterCircle();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void loop() {
    while(Serial1.available()>0){
        q = Serial1.parseInt();
        Serial.println(q);
        for(int i = 0; i<q; ++i){
            quarterCircle();
          }
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        
    }
}

void oneCircle(){
    for (int i = 0; i<64*8*3; ++i){
        myStep();
      }
  }

void quarterCircle(){
    for (int i = 0; i<64*6; ++i){
        myStep();
      }
  }

void gearCircle(){ // 120 degree
    for(int i = 0; i<64*8; ++i){
        myStep();
      }
  }

void motorCircle(){ //5.625 degree
  for(int i = 0; i<8; ++i){
      myStep();
    }  
}

void myStep(){
  for(int i = 0; i< 8; ++i){
    switch(i){
      case 0:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
      case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
      case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
      case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
      case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      case 5:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      case 6:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
      default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
     }
     delayMicroseconds(2000);
  }  
}
