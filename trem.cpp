#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 1000/5;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){

        case 1: // (60,30) → (330,30) → (330,240) → (60,240)
            if (y <= 30 && x <= 330)
                x += 2;
            else if (x == 330 && y <= 240)
                y += 2;
            else if (y >= 240 && x >= 60)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        case 2: // (330,30) → (600,30) → (600,428) → (330,428)
            if (y <= 30 && x < 600)
                x += 2;
            else if (x >= 600 && y < 428)
                y += 2;
            else if (y >= 428 && x > 330)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        case 3: // (600,30) → (870,30) → (870,240) → (600,240)
            if (y <= 30 && x < 870)
                x += 2;
            else if (x >= 870 && y < 240)
                y += 2;
            else if (y >= 240 && x > 600)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        case 4: // (600,240) → (870,240) → (870,560) → (600,560)
            if (y <= 240 && x < 870)
                x += 2;
            else if (x >= 870 && y < 560)
                y += 2;
            else if (y >= 560 && x > 600)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        case 5: // (330,428) → (600,428) → (600,560) → (330,560)
            if (y <= 428 && x < 600)
                x += 2;
            else if (x >= 600 && y < 560)
                y += 2;
            else if (y >= 560 && x > 330)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        case 6: // (60,240) → (330,240) → (330,560) → (60,560)
            if (y <= 240 && x < 330)
                x += 2;
            else if (x >= 330 && y < 560)
                y += 2;
            else if (y >= 560 && x > 60)
                x -= 2;
            else
                y -= 2;
            emit updateGUI(ID, x, y);
            break;

        default:
            break;
        }
        msleep(velocidade);
    }
}