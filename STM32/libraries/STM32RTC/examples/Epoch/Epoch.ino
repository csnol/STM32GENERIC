/**
  ******************************************************************************
    @file    Epoch.ino
    @author  WI6LABS
    @version V1.0.0
    @date    12-December-2017
    @brief   RTC epoch example

  ******************************************************************************
    @attention

    <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.
      2. Redistributions in binary form must reproduce the above copyright notice,
         this list of conditions and the following disclaimer in the documentation
         and/or other materials provided with the distribution.
      3. Neither the name of STMicroelectronics nor the names of its contributors
         may be used to endorse or promote products derived from this software
         without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  ******************************************************************************
*/
#include <STM32RTC.h>
/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

/* get compute datetime to set the current initial time */
const byte seconds = BUILD_SEC;
const byte minutes = BUILD_MIN;
const byte hours = BUILD_HOUR;

/* get compute datetime to set the current initial date */
const byte days = BUILD_DAY;
const byte months = BUILD_MONTH;
const byte years = (BUILD_YEAR) % 100;

void setup() {
  Serial.begin(115200);

  //select clock souce:  RTC_LSI_CLOCK/RTC_LSE_CLOCK/RTC_HSE_CLOCK/RTC_HSI_CLOCK, default RTC_LSI_CLOCK
  //default STM32RTC::RTC_LSI_CLOCK
  rtc.setClockSource(STM32RTC::RTC_LSE_CLOCK);

  rtc.begin(); // initialize RTC 24H format

  //check bkreg and set the data/time
  if (rtc.getRegister(RTC_BKP_DR1) != 0x32F2) {
    setdata();
    settime();
    rtc.setRegister(RTC_BKP_DR1, 0x32F2);
  } else {
    //   settime()
#ifdef STM32F1
    setdata();
#endif
  }

  //  rtc.setEpoch(1451606400); // Jan 1, 2016
}

void loop() {
  Serial.print("Unix time = ");
  Serial.println(rtc.getEpoch());

  Serial.print("Seconds since Jan 1 2000 = ");
  Serial.println(rtc.getY2kEpoch());

  // Print date...
  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());
  Serial.print("\t");

  // ...and time
  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());

  Serial.println();

  delay(1000);
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

//  set the time
void settime(void) {
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
}

// Set the date
void setdata(void) {
  rtc.setDay(days);
  rtc.setMonth(months);
  rtc.setYear(years);
}
