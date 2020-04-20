/*
* This example emulate a rotary encoder output
* 模拟一个旋转编码器输出信号；
* KE1 ON add
* KE2 ON dec
*/

#define  key0 BUTTON
#define  key1 BUTTON1
#define  ENCODEROUT_A  PA5
#define  ENCODEROUT_B  PA6
void setup() {

    Serial.begin(115200);
	Serial.println("emulate rotary encoder output");
	
	pinMode(ENCODEROUT_A,OUTPUT);
	pinMode(ENCODEROUT_A,OUTPUT);
}

void loop() {
    uint32_t start = Timerx.getCompare(1);
    uint32_t end;
    do {
        //Wait for next rising edge
        end = Timerx.getCompare(1);
    } while(end == start);

    uint32_t diff;
    if (end > start) {
        diff = end - start;
    } else {
        diff = (Timerx.getOverflow() - start) + end;
    }
    uint32_t timerFrequency = Timerx.getBaseFrequency() / (Timerx.getPrescaleFactor() + 1);

    Serial.print("Input frequency: ");
    Serial.print((float)timerFrequency / diff, 6);
    Serial.println(" Hz");

    delay(1000);
}

void encoderEmu(uint8_t pa, uint8_t pb){
	digitalWrite(pa, )
}