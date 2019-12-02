/*
  Transistor Identifier by: Seyed Roohollah marashi
  Srmarashi@yahoo.com    vitapour Gmbh Austria, Wien
   ATT: some special Transistors will not be detect with this project because of when the number of HFE are too close
   to each other. surely the component tester are more advanced and usefull  but this is very fast way to
   identifie Transistors.........Thanks for your time
*/


#define AIN0 PA0
#define AIN1 PA1
#define AIN2 PA2

#define TEST_P1  PA3
#define TEST_P2  PA4
#define TEST_P3  PA5
#define TEST_P4  PA6
#define TEST_P5  PA7

int  No1;
int  No2;
int  No3;

uint8_t case1 = 0;
uint8_t case2 = 0;
uint8_t case3 = 0;
uint8_t case4 = 0;
uint8_t case5 = 0;
uint8_t case6 = 0;
uint8_t case7 = 0;
uint8_t case8 = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  delay(1000);
  Serial.println("Transistor identifier v1.0");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(TEST_P1, OUTPUT);
  pinMode(TEST_P2, OUTPUT);
  pinMode(TEST_P3, OUTPUT);
  pinMode(TEST_P4, OUTPUT);
  pinMode(TEST_P5, OUTPUT);

  Serial.print("case #1 ->");
  digitalWrite(TEST_P2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, HIGH);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);
  //N-channel  Mosfet  S-D-G
  if ((No1 >= 150) && (No2 >= 400) && (No3 >= 800)) case1 = 1;

  //N-channel  Mosfet  G-D-S
  if ((No1 <= 5) and (No2 >= 800) and (No3 >= 800))   case1 = 2;
  if ((No1 >= 800) and (No2 >= 800) and (No3 <= 100)) case1 = 3;


  delay(200);  tone(TEST_P1, 1000);


  Serial.print("case #2 ->");
  digitalWrite(TEST_P2, LOW);    // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, HIGH);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);

  //N-channel  Mosfet  S-D-G
  if ((No1 > 150) and (No2 >= 100) and (No3 > 900)) case2 = 1;
  if ((No1 > 150) and (No2 <= 50) and (No3 <=  50)) case2 = 4;

  //N-channel  Mosfet  G-D-S
  if ((No1 == 0) and (No2 >= 300) and (No3 > 400)) case2 = 2;

  delay(200);  tone(TEST_P1, 1500);

  Serial.print("case #3 ->");
  digitalWrite(TEST_P2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, LOW);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);
  //N-channel  Mosfet  S-D-G
  if ((No1 <= 5) and (No2 <= 5) and (No3 >= 0)) case3 = 1;
  //N-channel  Mosfet  G-D-S
  if ((No1 <= 5) and (No2 >= 1) and (No3 == 0)) case3 = 2;


  delay(200);  tone(TEST_P1, 1800);

  Serial.print("case #4 ->");
  digitalWrite(TEST_P2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, LOW);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);
  //N-channel  Mosfet  S-D-G
  if ((No1 > 200) and (No2 > 200) and (No3 >= 0)) case4 = 1;
  //N-channel  Mosfet  G-D-S
  if ((No1 > 300) and (No2 == 0) and (No3 == 0)) case4 = 2;
  if ((No1 < 200) and (No2 < 300) and (No3 >= 0)) case4 = 5;
  if ((No1 == 0) and (No2 == 0) and (No3 >= 0)) case4 = 6;

  delay(200);  tone(TEST_P1, 2000);


  Serial.print("case #5 ->");
  digitalWrite(TEST_P2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, HIGH);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);

  //N-channel  Mosfet  S-D-G
  if ((No1 > 200) and (No1 < 900) and (No2 > 200) and (No3 > 800)) case5 = 1;

  //N-channel  Mosfet  G-D-D
  if ((No1 > 900) and (No2 > 200) and (No3 > 300)) case5 = 2;
  delay(200);  tone(TEST_P1, 1500);

  Serial.print("case #6 ->");
  digitalWrite(TEST_P2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, HIGH);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);

  //N-channel  Mosfet  S-D-G
  if ((No1 > 500) and (No2 > 900) and (No3 > 900)) case6 = 1;
  //N-channel  Mosfet  G-D-S
  if ((No1 > 800) and (No2 > 800) and (No3 > 800) and (case5 = 2)) case6 = 2;

  delay(200);  tone(TEST_P1, 3000);


  Serial.print("case #7 ->");
  digitalWrite(TEST_P2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, LOW);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);

  //N-channel  Mosfet  S-D-G
  if ((No1 > 900) and (No2 > 900) and (No3 > 0)) case7 = 1;

  //N-channel  Mosfet  G-D-S
  if ((No1 > 700) and (No2 > 400) and (No3 > 200) and (case4 == 2)) case7 = 2;



  delay(200);  tone(TEST_P1, 3100);


  Serial.print("case #8 ->");
  digitalWrite(TEST_P2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(TEST_P3, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(TEST_P4, LOW);
  No1 = analogRead(AIN0);
  No2 = analogRead(AIN1);
  No3 = analogRead(AIN2);
  Serial.print(No1);
  Serial.print("-");
  Serial.print(No2);
  Serial.print("-");
  Serial.println(No3);
  //N-channel  Mosfet  S-D-G
  if ((No1 > 150) and (No2 > 900) and (No3 >= 0)) case8 = 1;

  //N-channel  Mosfet  G-D-S
  if ((No1 > 150) and (No2 > 900) and (No3 == 0)  and (case2 == 2)) case8 = 2;


  noTone(TEST_P1);

  // Print Case # amount
  Serial.print(case1);
  Serial.print("-");
  Serial.print(case2);
  Serial.print("-");
  Serial.print(case3);
  Serial.print("-");
  Serial.print(case4);
  Serial.print("-");
  Serial.print(case5);
  Serial.print("-");
  Serial.print(case6);
  Serial.print("-");
  Serial.print(case7);
  Serial.print("-");
  Serial.println(case8);

  //NO Component or UnKnown item
  if ((case1 == 2) and (case2 == 0) and (case3 == 1) and (case4 == 2) and (case5 == 2) and (case6 == 2) and (case7 == 1) and (case8 == 1))
  {
    Serial.println("UnKnown Component or Socket Empty");
  }

  if ((case1 == 3) and (case2 == 4) and (case3 == 1) and (case4 == 6) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("UnKnown Component or Socket Empty");
  }

  //N-channel  Mosfet  S-D-G ANswer
  if ((case1 == 3) and (case2 == 0) and (case3 == 1) and (case4 == 6) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("N-Channel MOSFET  1=Source 2=Drain 3=Gate");
  }

  //N-channel  Mosfet  G-D-S ANswer
  if ((case1 == 0) and (case2 == 4) and (case3 == 1) and (case4 == 0) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("N-Channel MOSFET  1=Gate 2=Drain 3=Source");
  }


  //P-channel  Mosfet  S-D-G ANswer
  if ((case1 == 3) and (case2 == 0) and (case3 == 1) and (case4 == 5) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("P-Channel MOSFET  1=Source 2=Drain 3=Gate");
  }


  //P-channel  Mosfet  G-D-S ANswer
  if ((case1 == 0) and (case2 == 4) and (case3 == 1) and (case4 == 5) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("P-Channel MOSFET  1=Gate 2=Drain 3=Source");
  }

  //PNP  General Transistor E-B-C ANswer
  if ((case1 == 3) and (case2 == 0) and (case3 == 1) and (case4 == 1) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("PNP General  1=E 2=B 3=C");
  }

  //NPN  General Transistor  E-B-C ANswer
  if ((case1 == 0) and (case2 == 4) and (case3 == 1) and (case4 == 6) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("NPN General  1=E 2=B 3=C");
  }

  if ((case1 == 0) and (case2 == 0) and (case3 == 1) and (case4 == 0) and (case5 == 2) and (case6 == 2) and (case7 == 0) and (case8 == 0))
  {
    Serial.println("5v Regulator 1-in 2-gnd 3-out");
  }
}

void loop() {
  // here is empty because of we need to run script once, when reset button pressed
}
