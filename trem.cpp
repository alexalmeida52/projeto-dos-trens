#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, pthread_mutex_t * mut){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    mutex = mut;
    passo = 10;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1s
            // TRAVA
            if(x == 310 && y == 30){
                // TRAVANDO O MUTEX 0
//                if(passo < 0){
//                    pthread_mutex_unlock(&mutex[0]);
//                    emit updateGUI(ID, x,y);
//                    break;
//                }
//                passo = 10;
                pthread_mutex_lock(&mutex[0]);
            }

            if(x == 330 && y == 130) {
                // TRAVANDO O MUTEX 2
                pthread_mutex_lock(&mutex[2]);
            }

            // DESTRAVA
            if(x == 310 && y == 150){
                // DESTRAVANDO O MUTEX 0
                pthread_mutex_unlock(&mutex[0]);
            }

            if(x == 180 && y == 150){
                // DESTRAVANDO O MUTEX 2
                pthread_mutex_unlock(&mutex[2]);
            }

            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <330)
                x+=passo;
            else if (passo < 0 && y == 30 && x ==330)
                x+=passo;
            else if (x == 330 && y < 150)
                y+=passo;
            else if (x > 60 && y == 150)
                x-=passo;
            else
                y-=passo;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if(x == 350 && y == 150){
                // TRAVANDO O MUTEX 0
                pthread_mutex_lock(&mutex[0]);
            }

            if(x == 490 && y == 150){
                // TRAVANDO O MUTEX 3
                pthread_mutex_lock(&mutex[3]);
            }

            // DESTRAVA
            if(x == 350 && y == 30){
                // DESTRAVANDO O MUTEX 0
                pthread_mutex_unlock(&mutex[0]);
            }
            if(x == 330 && y == 130){
                // DESTRAVANDO O MUTEX 3
                pthread_mutex_unlock(&mutex[3]);
            }


            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <600)
                x+=passo;
            else if (x == 600 && y < 150)
                y+=passo;
            else if (x > 330 && y == 150)
                x-=passo;
            else
                y-=passo;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
//            // TRAVA
//            printf("(%d, %d)\n", x, y);
//            if(x == 200 && y == 267){
//                // DESTRAVANDO O MUTEX 3
//                printf("Travando o mutex3...");
//                pthread_mutex_lock(mutex3);
//            }

//            // DESTRAVA
//            if(x == 330 && y == 267){
//                // TRAVANDO O MUTEX 3
//                printf("Destravando o mutex3");
//                pthread_mutex_lock(mutex3);
//            }
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <870)
                x+=passo;
            else if (x == 870 && y < 150)
                y+=passo;
            else if (x > 600 && y == 150)
                x-=passo;
            else
                y-=passo;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4

            // TRAVA
            if(x == 200 && y == 170){
                // TRAVANDO O MUTEX 2
                pthread_mutex_lock(&mutex[2]);
            }

            if(x == 310 && y == 150){
                // TRAVANDO O MUTEX 3
                pthread_mutex_lock(&mutex[3]);
            }

            // DESTRAVA
            if(x == 350 && y == 150){
                // DESTRAVANDO O MUTEX 2
                pthread_mutex_unlock(&mutex[2]);
            }

            if(x == 470 && y == 170){
                // DESTRAVANDO O MUTEX 3
                pthread_mutex_unlock(&mutex[3]);
            }


            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 150 && x <470)
                x+=passo;
            else if (x == 470 && y < 270)
                y+=passo;
            else if (x > 200 && y == 270)
                x-=passo;
            else
                y-=passo;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 150 && x <740)
                x+=passo;
            else if (x == 740 && y < 270)
                y+=passo;
            else if (x > 470 && y == 270)
                x-=passo;
            else
                y-=passo;
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

void Trem::inverter_passo(){
    passo = passo*(-1);
}

int Trem::get_passo(){
    return passo;
}

void Trem::reset_passo(){
    passo = 10;
}
