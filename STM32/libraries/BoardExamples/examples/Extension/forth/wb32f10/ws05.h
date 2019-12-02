// ws05.h // having wordset 05 for digital input
#ifndef WS05_H
#define WS05_H
void _21(){pinMode(V.dsPop(),INPUT)         ;} const Word W21 PROGMEM={       LAST,"inp",_21};
void _22(){V.dsPush(digitalRead(V.dsPop())) ;} const Word W22 PROGMEM={(Word*)&W21,"p@" ,_22};
#define LAST (Word*)&W22
#endif WS05_H
