#include "trem.h"
#include <QtCore>
//#include <iostream>

//Construtor
Trem::Trem(int ID, int x, int y, TCAS *sistemaTcas){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->tcas = sistemaTcas;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){

        // aguarda até que a velocidade mude
        if (velocidade == 0) {
            msleep(100);
            continue;
        }

        switch(ID){
        case 1: // (60,30) → (330,30) → (330,240) → (60,240)

            // detecção de zona crítica (entrada)
            if (x == 310 && y == 30) tcas->pontosCriticos[0].lock();    // evita colisão com T2
            if (x == 330 && y == 270) tcas->pontosCriticos[2].lock();   // evita colisão com T6

            // movimentação do trem
            if (x < 330 && y == 30)
                x += 2;
            else if (x == 330 && y < 290)
                y += 2;
            else if (x > 60 && y == 290)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 310 && y == 290) tcas->pontosCriticos[0].unlock();
            if (x == 60 && y == 270) tcas->pontosCriticos[2].unlock();

            emit updateGUI(ID, x, y);
            break;

        case 2: // (330,30) → (600,30) → (600,428) → (330,428)

            // detecção de zona crítica (entrada)
            if (x == 580 && y == 30) tcas->pontosCriticos[1].lock();    // evita colisão com T3
            if (x == 600 && y == 270) tcas->pontosCriticos[5].lock();   // evita colisão com T4
            if (x == 600 && y == 408) tcas->pontosCriticos[6].lock();   // evita colisão com T5
            if (x == 350 && y == 428) tcas->pontosCriticos[4].lock();   // evita colisão com T6
            if (x == 330 && y == 310) tcas->pontosCriticos[0].lock();   // evita colisão com T1

            // movimentação do trem
            if (x < 600 && y == 30)
                x += 2;
            else if (x == 600 && y < 428)
                y += 2;
            else if (x > 330 && y == 428)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 580 && y == 428) tcas->pontosCriticos[5].unlock();
            if (x == 600 && y == 310) tcas->pontosCriticos[1].unlock();
            if (x == 330 && y == 408) tcas->pontosCriticos[6].unlock();
            if (x == 350 && y == 30) tcas->pontosCriticos[0].unlock();
            if (x == 330 && y == 270) tcas->pontosCriticos[4].unlock();

            emit updateGUI(ID, x, y);
            break;

        case 3: // (600,30) → (870,30) → (870,240) → (600,240)

            /*
             * detecção de zona crítica (entrada)
             * a chave de seleção reserva a região 1 e 3,
             * permitindo a passagem do T3 sem causar
             * deadlocks com T2 e T4
             */
            if (x == 870 && y == 270) {
                tcas->pontosCriticos[1].lock();
                tcas->pontosCriticos[3].lock();
            }

            // movimentação do trem
            if (x < 870 && y == 30)
                x += 2;
            else if (x == 870 && y < 290)
                y += 2;
            else if (x > 600 && y == 290)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 600 && y == 270) tcas->pontosCriticos[3].unlock();
            if (x == 620 && y == 30) tcas->pontosCriticos[1].unlock();

            emit updateGUI(ID, x, y);
            break;

        case 4: // (600,240) → (870,240) → (870,560) → (600,560)

            /*
             * detecção de zona crítica (entrada)
             * a chave de seleção reserva a região 5 e 8,
             * permitindo a passagem do T4 sem causar
             * deadlocks com T2, T3 e T5
             */
            if (x == 620 && y == 560) {
                tcas->pontosCriticos[5].lock();
                tcas->pontosCriticos[8].lock();
            }
            if (x == 600 && y == 310) tcas->pontosCriticos[3].lock(); // evia colisão com T3

            // movimentação do trem
            if (x < 870 && y == 290)
                x += 2;
            else if (x == 870 && y < 560)
                y += 2;
            else if (x > 600 && y == 560)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 600 && y == 408) tcas->pontosCriticos[8].unlock();
            if (x == 620 && y == 290) tcas->pontosCriticos[5].unlock();
            if (x == 870 && y == 310) tcas->pontosCriticos[3].unlock();

            emit updateGUI(ID, x, y);
            break;

        case 5: // (330,428) → (600,428) → (600,560) → (330,560)

            /*
             * detecção de zona crítica (entrada)
             * a chave de seleção reserva a região 6 e 7,
             * permitindo a passagem do T5 sem causar
             * deadlocks com T2 e T4
             */
            if (x == 350 && y == 560) {
                tcas->pontosCriticos[6].lock();
                tcas->pontosCriticos[7].lock();
            }
            if (x == 580 && y == 428) tcas->pontosCriticos[8].lock(); // evita colisão com T4

            // movimentação do trem
            if (x < 600 && y == 428)
                x += 2;
            else if (x == 600 && y < 560)
                y += 2;
            else if (x > 330 && y == 560)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 350 && y == 428) tcas->pontosCriticos[7].unlock();
            if (x == 600 && y == 448) tcas->pontosCriticos[6].unlock();
            if (x == 580 && y == 560) tcas->pontosCriticos[8].unlock();

            emit updateGUI(ID, x, y);
            break;

        case 6: // (60,240) → (330,240) → (330,560) → (60,560)

            /*
             * detecção de zona crítica (entrada)
             * a chave de seleção reserva a região 2 e 3,
             * permitindo a passagem do T6 sem causar
             * deadlocks com T1 e T2
             */
            if (x == 60 && y == 310) {
                tcas->pontosCriticos[4].lock();
                tcas->pontosCriticos[2].lock();
            }
            if (x == 330 && y == 408) tcas->pontosCriticos[7].lock(); // evita colisão com T5

            // movimentação do trem
            if (x < 330 && y == 290)
                x += 2;
            else if (x == 330 && y < 560)
                y += 2;
            else if (x > 60 && y == 560)
                x -= 2;
            else
                y -= 2;

            // detecção de zona crítica (saída)
            if (x == 330 && y == 310) tcas->pontosCriticos[2].unlock();
            if (x == 330 && y == 448) tcas->pontosCriticos[4].unlock();
            if (x == 310 && y == 560) tcas->pontosCriticos[7].unlock();

            emit updateGUI(ID, x, y);
            break;

        default:
            break;
        }

        int delay = 201 - velocidade; // vel. máxima = 1 ms de sleep
        //std::cout << ID << " " << "Vel: " << velocidade << " " << "delay: " << delay << std::endl;
        msleep(delay);

    }
}

// Atualiza a velocidade de acordo com o valor do slider
void Trem::updateVelocidade(int valorSlider){
    this->velocidade = valorSlider;
}