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
                if(passo < 0){
                    pthread_mutex_unlock(&mutex[0]);
                    passo = 10;
                    emit updateGUI(ID, x,y);
                    break;
                }
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
//                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
//                    // EXECUTA O UNLOCK PARA LIBERAR O ACESSO PARA O TREM 4 QUE TAMBÉM FAZ USO DA REGIÃO 4
//                    pthread_mutex_unlock(&mutex[3]);
//                    passo = 10; // TREM VOLTA ANDAR PRA FRENTE APÓS A VIA SER LIBERADA
//                    emit updateGUI(ID, x,y);
//                    break;
//                }
                pthread_mutex_lock(&mutex[3]);
            }

            if(x == 580 && y == 30){
                // TRAVANDO O MUTEX 1
                if(passo < 0){
                    pthread_mutex_unlock(&mutex[1]);
                    passo = 10;
                    emit updateGUI(ID, x,y);
                    break;
                }
                pthread_mutex_lock(&mutex[1]);
            }

            if(x == 600 && y == 130){
                // TRAVANDO O MUTEX 4
                pthread_mutex_lock(&mutex[4]);
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
            if(x == 580 && y == 150){
                pthread_mutex_unlock(&mutex[1]);
            }

            if(x == 450 && y == 150){
                // DESTRAVANDO O MUTEX 4

//                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
//                    // EXECUTA O LOCK PARA EVITAR DE BATER NO TREM 5 QUE TAMBÉM FAZ USO DA REGIÃO 5
//                    pthread_mutex_lock(&mutex[4]);
//                    emit updateGUI(ID, x,y);
//                } else {
                    pthread_mutex_unlock(&mutex[4]);
//                }
            }

            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (y == 30 && x <600)
                x+=passo;
            else if (passo < 0 && y == 30 && x == 600)
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
            if(x == 620 && y == 30) {
                pthread_mutex_unlock(&mutex[1]);
            }

            if(x == 760 && y == 150){
                pthread_mutex_lock(&mutex[5]);
            }
//            // DESTRAVA
            if(x == 620 && y == 150) {
                pthread_mutex_lock(&mutex[1]);
            }
            if(x == 600 && y == 130){
                pthread_mutex_unlock(&mutex[5]);
            }

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
                if(passo < 0){
                    pthread_mutex_unlock(&mutex[2]);
                    passo = 10;
                    emit updateGUI(ID, x,y);
                    break;
                }
                pthread_mutex_lock(&mutex[2]);
            }

            if(x == 310 && y == 150){
                // TRAVANDO O MUTEX 3
                if(passo < 0){
                    pthread_mutex_unlock(&mutex[3]);
                    passo = 10;
                    emit updateGUI(ID, x,y);
                    break;
                }
                pthread_mutex_lock(&mutex[3]);
            }

            if(x == 450 && y == 150){
                // TRAVANDO O MUTEX 6
                pthread_mutex_lock(&mutex[6]);
            }

            // DESTRAVA
            if(x == 350 && y == 150){
                // DESTRAVANDO O MUTEX 2
                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
                    // EXECUTA O LOCK PARA EVITAR DE BATER NO TREM 1 QUE TAMBÉM FAZ USO DA REGIÃO 3
                    pthread_mutex_lock(&mutex[2]);
                    emit updateGUI(ID, x,y);
                } else {
                    pthread_mutex_unlock(&mutex[2]);
                }
            }

            if(x == 470 && y == 170){
                // DESTRAVANDO O MUTEX 3
                pthread_mutex_unlock(&mutex[3]);
            }

            if(x == 450 && y == 270){
                // DESTRAVANDO O MUTEX 6
                pthread_mutex_unlock(&mutex[6]);
            }

            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (passo < 0 && y == 150 && x == 200)
                y-=passo;
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
            // ------- INICIO DOS LOCKS DO TREM 5 --------

            if(x == 580 && y == 150){ // CASO ESTIVER ENTRANDO NA REGIÃO 6
                pthread_mutex_lock(&mutex[5]); // BLOQUEIA A REGIÃO 6 PRO TREM 3 NÃO PASSAR
            }

            if(x == 470 && y == 170){ // CASO ESTIVER ENTRANDO NA REGIÃO 5
                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
                    // EXECUTA O UNLOCK PARA LIBERAR O ACESSO PARA O TREM 2 QUE TAMBÉM FAZ USO DA REGIÃO 7
                    pthread_mutex_unlock(&mutex[4]);
                    passo = 10; // TREM VOLTA ANDAR PRA FRENTE APÓS A VIA SER LIBERADA
                    emit updateGUI(ID, x,y);
                    break;
                }
                pthread_mutex_lock(&mutex[4]); // BLOQUEIA A REGIÃO 5 PRO TREM 2 NÃO PASSAR
            }

            if(x == 490 && y == 270){ // CASO ESTIVER ENTRANDO NA REGIÃO 7
                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
                    // EXECUTA O UNLOCK PARA LIBERAR O ACESSO PARA O TREM 4 QUE TAMBÉM FAZ USO DA REGIÃO 7
                    pthread_mutex_unlock(&mutex[6]);
                    passo = 10; // TREM VOLTA ANDAR PRA FRENTE APÓS A VIA SER LIBERADA
                    emit updateGUI(ID, x,y);
                    break;
                }
                pthread_mutex_lock(&mutex[6]); // BLOQUEIA A REGIÃO 7 PRO TREM 4 NÃO PASSAR
            }

            // ----------- FIM DOS LOCKS -----------

            // INICIO DOS UNLOCKS DO TREM 5

            if(x == 740 && y == 170){ // CASO ESTEJA SAINDO DA REGIÃO 6
                // LIBERA A REGIÃO 6 PRO TREM 3
                pthread_mutex_unlock(&mutex[5]);
            }

            if(x == 620 && y == 150){ // CASO ESTEJA SAINDO DA REGIÃO 5
                // LIBERA A REGIÃO 5 PRO TREM 2
                pthread_mutex_unlock(&mutex[4]);
            }


            if(x == 490 && y == 150){ // CASO ESTIVER SAINDO DA REGIÃO 7
                // DESTRAVANDO O MUTEX 6
                if(passo < 0){ // CASO ESTEJA DANDO "RÉ"
                    // EXECUTA O LOCK PARA EVITAR DE BATER NO TREM 4 QUE TAMBÉM FAZ USO DA REGIÃO 7
                    pthread_mutex_lock(&mutex[6]);
                    emit updateGUI(ID, x,y);
                } else { // CASO NÃO ESTEJA DANDO RÉ LIBERA A REGIÃO 7 PRO TREM 4
                    pthread_mutex_unlock(&mutex[6]);
                }

            }

            // O TREM NÃO ANDA SE A VELOCIDADE FOR IGUAL A ZERO
            if(velocidade == 0){
                emit updateGUI(ID, x,y);
                break;
            }
            else if (passo < 0 && y == 150 && x == 470)
                y-=passo;
            else if (y == 150 && x <740)
                x+=passo;
            else if (x == 740 && y < 270)
                y+=passo;
            else if (x > 470 && y == 270)
                x-=passo;
            else if (passo < 0 && y == 270 && x == 470)
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
