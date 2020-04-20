#include <TinyVB.h>
#include <LED.h>

#define MYPROG \
  "Sub Main() \r\
 Dim a As Integer \r\
 a=100*2 \r\
 Print \"a= \" \r\
 Print a\r\
End Sub\r\0"

char vbprog[] = MYPROG;
void Executable(vector <CSub> Subs);

void setup() {
  // put your setup code here, to run once:
  Led.Init();
  Serial.begin(115200);
  while (!Serial) {};
  delay(1000);
  Serial << "Press any key from serial to run......\n\n";
  while (!Serial.available()) {
    Led.flash(10, 990, 1);
  }

  // put your main code here, to run repeatedly:
  Led.flash(500, 500, 1);
  vector<CSub> m_Subs;
  CMake vbMake(vbprog, sizeof(vbprog)); // 创建Make对象,用来生成class代码
  vbMake.Make(); // Make对象内部进行Make token的工作  ?
  m_Subs = vbMake.m_Subs; // 将Make内部生成的m_Subs传出来
  Executable(m_Subs);
  Serial << "\nrun ok\n";
}

void loop() {
  // put your main code here, to run repeatedly:
  Led.flash(500, 500, 1);
}



