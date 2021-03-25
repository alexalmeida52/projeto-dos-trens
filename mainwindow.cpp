#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pthread.h>
#include <QMutex>
pthread_mutex_t mutex[5];
QMutex qmutex;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    printf("Iniciando os mutex.\n");
    for(int i = 0; i < 5; i++)
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
        trem1->setVelocidade(ui->horizontalSlider_trem_1->value());
        ui->label_trem1->setGeometry(x,y,20,20);
        break;
    }
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        trem2->setVelocidade(ui->horizontalSlider_trem_2->value());
        ui->label_trem2->setGeometry(x,y,20,20);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        trem3->setVelocidade(ui->horizontalSlider_trem_3->value());
        ui->label_trem3->setGeometry(x,y,20,20);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        trem4->setVelocidade(ui->horizontalSlider_trem_4->value());
        ui->label_trem4->setGeometry(x,y,20,20);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        trem5->setVelocidade(ui->horizontalSlider_trem_5->value());
        ui->label_trem5->setGeometry(x,y,20,20);
        break;
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
