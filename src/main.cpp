#include "mbed.h"

enum states{DOWN, UP, FALL, MIN, RISE, MAX}; //States enumeration
int state = UP; // Defining first state as UP
PwmOut lights[]={(p5), (p6)}; //LED ports definition, associated with the enum // p5 - Orange p6 - Blue
InterruptIn bot(p7); 
Ticker btt,times;
int i = 0; //contador de tempo para botao apertado
float intense = 1.0; // intensidade da luz

void ChangeState();
void InState();
void Changetick();
void Count();

int main() {

    bot.rise(&ChangeState);
    bot.fall(&Changetick);
    times.attach(&InState,1.0);
}
void Count(){
    i++;
}
void Changetick(){
    i = 0;
    btt.detach();
    if(state == MAX && i == 1.0){
        state = DOWN;
    }else if(state == MIN && i == 0.0){
        state = UP;
    }else if(state == RISE && i < 0.0){
        state = UP;
    }else if(state == FALL && i > 0.0){
        state = DOWN;
    }
}
void ChangeState(){
    btt.attach(&Count,1.0);
    if(i < 1 && state == UP){
        State = DOWN;
    }else if(i < 1 && state == DOWN){
        state = UP;
    }else if(i >= 1 && intense > 0.0 && state == DOWN){
        state = FALL;
    }else if(state == UP && i >= 1 && intense < 1.0){
        state = RISE;
    }else if(state == FALL && intense == 0.0){
        state = MIN;
    }else if(state == RISE && intense == 1.0){
        state = MAX;
    }else if(state == RISE && intense < 1.0){
        state = RISE;
    }else if(state == FALL && intense > 0.0){
        state = FALL;
    }
}
void InState(){
    switch(State){
        case DOWN:
            lights[0] = 1.0;
            lights[1] = 0.0;
            break;
        case UP:
            lights[0] = 0.0;
            lights[1] = 1.0;
            break;
        case FALL:
            lights[0] = intense - 0.05;
            intense = lights[0];
            lights[0] = 0;
            wait(200);
            lights[0] = intense;
            break;
        case MIN:
            lights[0] = 0.0;
            intense = 0.0;
            break;
        case RISE:
            lights[1] = intense + 0.05;
            intense = lights[1];
            lights[1] = 0;
            wait(200);
            lights[1] = intense;
            break;
        case MAX:
            lights[1] = 1.0;
            intense = 1.0;
            break;
    }
}
