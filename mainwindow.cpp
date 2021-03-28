#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pthread.h>
pthread_mutex_t mutex[6];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    printf("Iniciando os mutex.\n");
    for(int i = 0; i < 6; i++)
        pthread_mutex_init(&mutex[i], NULL);

    // Valores das velocidades dos trens
    int velocidade_trem_1 = 5;
    int velocidade_trem_2 = 10;
    int velocidade_trem_3 = 15;
    int velocidade_trem_4 = 20;
    int velocidade_trem_5 = 25;

    // Setando o valor inicial do controle de velocidade dos trens
    ui->horizontalSlider_trem_1->setValue(velocidade_trem_1);
    ui->horizontalSlider_trem_2->setValue(velocidade_trem_2);
    ui->horizontalSlider_trem_3->setValue(velocidade_trem_3);
    ui->horizontalSlider_trem_4->setValue(velocidade_trem_4);
    ui->horizontalSlider_trem_5->setValue(velocidade_trem_5);

    //Cria o trem com seu (ID, posição X, posição Y)

    trem1 = new Trem(1,60,30, mutex);
    trem2 = new Trem(2,330,30, mutex);
    trem3 = new Trem(3,600,30, mutex);
    trem4 = new Trem(4,200,150, mutex);
    trem5 = new Trem(5,470,150, mutex);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));



}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: { //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        int t2_pos_x = ui->label_trem2->x();
        int t2_pos_y = ui->label_trem2->y();
        bool t2_na_regiao_critica = ( (t2_pos_x >= 330) && (t2_pos_x <= 470) && (t2_pos_y == 150) );
        int t4_pos_x = ui->label_trem4->x();
        int t4_pos_y = ui->label_trem4->y();
        bool t4_na_regiao_critica = ( (t4_pos_x >= 200) && (t4_pos_x <= 330) && (t4_pos_y == 150) );

        int t5_pos_x = ui->label_trem5->x();
        int t5_pos_y = ui->label_trem5->y();

        if(t2_na_regiao_critica && t4_na_regiao_critica) {
            if(x == 330 && trem1->get_passo() > 0 ){
                trem1->inverter_passo();
            }
        }

        if(x == 330 && y >= 30 && t4_pos_x >= 310 && t4_pos_y == 150 && t2_pos_x <= 600 && t2_pos_y == 150 && t5_pos_x == 470 && t5_pos_y == 170 && trem1->get_passo() > 0){
            trem1->inverter_passo();
        }

        trem1->setVelocidade(ui->horizontalSlider_trem_1->value());
        ui->label_trem1->setGeometry(x,y,20,20);
        break;
    }
    case 2: { //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        int t3_pos_x = ui->label_trem3->x();
        int t3_pos_y = ui->label_trem3->y();
        bool t3_na_regiao_critica = ( (t3_pos_x >= 600) && (t3_pos_x <= 740) && (t3_pos_y == 150) );
        int t5_pos_x = ui->label_trem5->x();
        int t5_pos_y = ui->label_trem5->y();
        bool t5_na_regiao_critica = ( (t5_pos_x >= 470) && (t5_pos_x <= 600) && (t5_pos_y <= 150) );
//        int t4_pos_x = ui->label_trem4->x();
//        int t4_pos_y = ui->label_trem4->y();
//        int t1_pos_x = ui->label_trem1->x();
//        int t1_pos_y = ui->label_trem1->y();

        if(t3_na_regiao_critica && t5_na_regiao_critica) {
            if(x == 600 && trem2->get_passo() > 0 ){
                trem2->inverter_passo();
            }
        }

//        if(t1_pos_x == 330 && t1_pos_y == 130 && t4_pos_x == 310 && t4_pos_y == 150 && x >= 350 && x <= 360 && y == 150) {
//            trem2->inverter_passo();
//        }

        trem2->setVelocidade(ui->horizontalSlider_trem_2->value());
        ui->label_trem2->setGeometry(x,y,20,20);
        break;
    }
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        trem3->setVelocidade(ui->horizontalSlider_trem_3->value());
        ui->label_trem3->setGeometry(x,y,20,20);
        break;
    case 4: {//Atualiza a posição do objeto da tela (quadrado) que representa o trem4

        int t2_pos_x = ui->label_trem2->x();
        int t2_pos_y = ui->label_trem2->y();
        bool t2_na_regiao_critica = ( (t2_pos_x <= 490) && (t2_pos_y == 150) );
        int t1_pos_x = ui->label_trem1->x();
        int t1_pos_y = ui->label_trem1->y();
        bool t1_na_regiao_critica = ( (t1_pos_x == 330) && (t1_pos_y == 130) );
        int t5_pos_x = ui->label_trem5->x();
        int t5_pos_y = ui->label_trem5->y();
        bool t5_na_regiao_critica = ( (t5_pos_x == 330) && (t5_pos_y <= 130) );

        if(t2_na_regiao_critica && t1_na_regiao_critica) {
            if(x >= 200 && x <= 330 && y == 150 && trem4->get_passo() > 0 ){
                trem4->inverter_passo();
            }
        }

        if((t5_pos_y == 170 && t5_pos_x == 470) && (t2_pos_x >= 470 && t2_pos_x <= 600 && t2_pos_y == 150)) {
//            printf("Opaaaaaa.\n(%d, %d)\n", x, y);
            if( (x >= 330 && x <= 470 && y == 150) && trem4->get_passo() > 0 ){
                trem4->inverter_passo();
            }
        }

        trem4->setVelocidade(ui->horizontalSlider_trem_4->value());
        ui->label_trem4->setGeometry(x,y,20,20);
        break;
   }
    case 5: { //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        int t2_pos_x = ui->label_trem2->x();
        int t2_pos_y = ui->label_trem2->y();
        bool t2_na_regiao_critica = ( (t2_pos_x >= 470) && (t2_pos_x <= 600) && (t2_pos_y == 150) );
        int t4_pos_x = ui->label_trem4->x();
        int t4_pos_y = ui->label_trem4->y();
        bool t4_na_regiao_critica = ( (t4_pos_x >= 330) && (t4_pos_x <= 470) && (t4_pos_y == 150) );
        int t3_pos_x = ui->label_trem3->x();
        int t3_pos_y = ui->label_trem3->y();

        if(t2_na_regiao_critica && t4_na_regiao_critica) {
            if(x == 470 && trem5->get_passo() > 0 ){
                trem5->inverter_passo();
            }
        }

        if((x >= 470 && x <= 600 && y == 150) && (t2_pos_x == 600 && t2_pos_y == 130) && (t3_pos_x >= 600 && t3_pos_x <= 740 && t3_pos_y == 150)) {
            if(trem5->get_passo() > 0 ){
                trem5->inverter_passo();
            }
        }

        trem5->setVelocidade(ui->horizontalSlider_trem_5->value());
        ui->label_trem5->setGeometry(x,y,20,20);
        break;
    }
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
}
