#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1s
//            if(x == 310 && y == 30){
//                printf("Bloqueado pelo trem 1\n");
//                pthread_mutex_lock(&mutex);
//            }
//            if(x == 330 && y == 150){
//                printf("Bloqueado pelo trem 1\n");
//                pthread_mutex_unlock(&mutex);
//            }
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <330)
                x+=10;
            else if (x == 330 && y < 150)
                y+=10;
            else if (x > 60 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
//            if(x == 350 && y == 150){
//                printf("Bloqueado pelo trem 2\n");
//                pthread_mutex_lock(&mutex);
//            }
//            if(x == 330 && y == 30){
//                printf("Bloqueado pelo trem 2\n");
//                pthread_mutex_unlock(&mutex);
//            }
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <600)
                x+=10;
            else if (x == 600 && y < 150)
                y+=10;
            else if (x > 330 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <870)
                x+=10;
            else if (x == 870 && y < 150)
                y+=10;
            else if (x > 600 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 150 && x <470)
                x+=10;
            else if (x == 470 && y < 270)
                y+=10;
            else if (x > 200 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 150 && x <740)
                x+=10;
            else if (x == 740 && y < 270)
                y+=10;
            else if (x > 470 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;

        default:
            break;
        }
        msleep(velocidade);
    }
}

// Setar velocidade
void Trem::setVelocidade(int v){
    if(v <= 0){
        velocidade = 0;
        return;
    }
    velocidade = 99*7/v;
}


