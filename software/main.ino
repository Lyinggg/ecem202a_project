#include <ArduinoBLE.h>
#include <stdio.h>
#define GapValue 468      // used to adjust the accuracy

// some code comes from arudino example and https://zhuanlan.zhihu.com/p/355553546

extern unsigned long HX711_Read(void);
extern long Get_Weight();
extern String data2str(int a, int b, int c);
extern int cmd2data(const byte s[]);
extern void myStep();
extern void oneCircle();
extern void quarterCircle();

float Weight = 0;
int HX711_SCK = 2;    // output
int HX711_DT = 3;     // input
long HX711_Buffer = 0;
long Weight_self = 0;
long Weight_obj = 0;
String localData = "00 000 000";
short tankRemain = 0;
short bowlRemain = 0;
unsigned short count = 0;

bool flag = false;

unsigned long previousMillis;
//const long interval = 600000; // get the remaing food of bowl and tank very 10 mins
const long interval = 2000; // get the remaing food of bowl and tank very 10 mins


BLEService localService("19B10000-E8F2-537E-4F6C-D1042021202A"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEStringCharacteristic localDataSender("202A", BLERead | BLEWrite, 11);

const int ledPin = LED_BUILTIN; // pin to use for the LED, TODO change to the feeder part 

void setup() {
  // ###############################SETUP BLUETOOTH###########################
  Serial.begin(9600);
  Serial1.begin(9600);
  //while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  BLE.begin();

  // begin initialization
//  if (!BLE.begin()) {
//    Serial.println("starting BLE failed!");
//
//    while (1);
//  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(localService);

  // add the characteristic to the service
  localService.addCharacteristic(localDataSender);

  // add service
  BLE.addService(localService);

  // set the initial value for the characeristic:
  localDataSender.writeValue(localData);

  // start advertising
  BLE.advertise();

  //Serial.println("BLE LED Peripheral");
  Serial.print("Loacl addrss is: ");
  Serial.println(BLE.address());


  //############################################SETUP load module#########################
  pinMode(HX711_SCK, OUTPUT);  ///SCK 为输出口 ---输出脉冲
  pinMode(HX711_DT, INPUT); ///  DT为输入口  ---读取数据
  //Serial.println("Load Cell Initialization in progess...");
  delay(3000);
  Weight_self = HX711_Read();
  previousMillis = millis();
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:p
      if (localDataSender.written()) {
        String cmd = localDataSender.value();
        Serial.println(cmd);
        Serial1.print(",");
        Serial1.print(cmd);
      }

      unsigned long curMillis = millis();
      if(curMillis - previousMillis > interval){ // send the loacl data to rasberry pi
          bowlRemain = int(Get_Weight());
          count = (count + 1) % 10;
          localDataSender.writeValue(data2str(count, tankRemain, bowlRemain));
          Serial.println(bowlRemain);
          previousMillis = curMillis;
        }
    }

    // when the central disconnects, print it out:
    //Serial.print(F("Disconnected from central: "));
    //Serial.println(central.address());
  }
}


  
String data2str(int a, int b, int c){
    char s[11];

    sprintf(s, "%d %d %d", a, b, c);
    //Serial.println(s);
    return String(s);
  }

//称重函数
long Get_Weight()
{
  HX711_Buffer = HX711_Read();    ///读取此时的传感器输出值
  Weight_obj = HX711_Buffer;     ///将传感器的输出值储存
  Weight_obj = Weight_obj - Weight_self; //获取实物的AD采样数值。
  Weight_obj = (long)((float)Weight_obj/GapValue);    //AD值转换为重量（g）
  return Weight_obj; 
}
unsigned long HX711_Read(void) //选择芯片工作方式并进行数据读取
{
  unsigned long count;   ///储存输出值  
  unsigned char i;     
   ////high--高电平 1  low--低电平 0  
  digitalWrite(HX711_DT, HIGH);   ////  digitalWrite作用： DT=1；
  delayMicroseconds(1); ////延时 1微秒  
  digitalWrite(HX711_SCK, LOW);  ////  digitalWrite作用： SCK=0；
  delayMicroseconds(1);   ////延时 1微秒  
  count=0; 
  while(digitalRead(HX711_DT));    //当DT的值为1时，开始ad转换
  for(i=0;i<24;i++)   ///24个脉冲，对应读取24位数值
  { 
   digitalWrite(HX711_SCK, HIGH);  ////  digitalWrite作用： SCK=0；
                                /// 利用 SCK从0--1 ，发送一次脉冲，读取数值
   delayMicroseconds(1);  ////延时 1微秒  
   count=count<<1;    ///用于移位存储24位二进制数值
   digitalWrite(HX711_SCK, LOW);   //// digitalWrite作用： SCK=0；为下次脉冲做准备
   delayMicroseconds(1);
   if(digitalRead(HX711_DT))    ///若DT值为1，对应count输出值也为1
    count++; 
  } 
  digitalWrite(HX711_SCK, HIGH);    ///再来一次上升沿 选择工作方式  128增益
 count ^= 0x800000;   //按位异或  不同则为1   0^0=0; 1^0=1;
///对应二进制  1000 0000 0000 0000 0000 0000  作用为将最高位取反，其他位保留原值
 delayMicroseconds(1);
 digitalWrite(HX711_SCK, LOW);      /// SCK=0；     
 delayMicroseconds(1);  ////延时 1微秒  
 return(count);     ///返回传感器读取值
}
