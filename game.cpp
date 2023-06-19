#include "game.h"
#include "ui_game.h"
#include <QScreen>

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

}

game::~game()
{
    delete ui;
}


void game::set_all_cards()
{
    for (int i = 0 ; i < 8 ; i++)
    {
        all_cards[i].set_value(i+1);
        all_cards[i].set_type(parrot);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 8 ; i < 16 ; i++)
    {
        all_cards[i].set_value(i-7);
        all_cards[i].set_type(gold);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 16 ; i < 24 ; i++)
    {
        all_cards[i].set_value(i-15);
        all_cards[i].set_type(map);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 24 ; i < 32 ; i++)
    {
        all_cards[i].set_value(i-23);
        all_cards[i].set_type(flag);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 32 ; i < 36 ; i++)
    {
        all_cards[i].set_value(i-31);
        all_cards[i].set_type(pirate);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 36 ; i < 39 ; i++)
    {
        all_cards[i].set_value(i-35);
        all_cards[i].set_type(king);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
    for (int i = 39 ; i < 42 ; i++)
    {
        all_cards[i].set_value(i-38);
        all_cards[i].set_type(queen);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
    }
}

void game::forecast(int input)
{
    int i;
    if(input==1)
        i=0;
    else
        i=all_forecast_btn.size();
    for(i ; i <= input ; i++)
    {
        customized_button *new_button = new customized_button(i);
        new_button->change_obj_name();
        ui->hl_forecast_btn->addWidget(new_button);
        new_button->setFixedSize(60,60);
        QString temp="QPushButton{border-image: url(:/photos/" + QString::number(i) + ".png);}QPushButton:pressed{border-image: url(:/photos/click " + QString::number(i) + ".png);}";
        new_button->setStyleSheet(temp);
        all_forecast_btn.append(new_button);
        connect(new_button,SIGNAL(sig_button_clicked(int)),this,SLOT(slo_forecast(int)));
    }
}

void game::slo_forecast(int input)
{
    //get number of hands
}


void game::first_round()
{
    srand(time(NULL));
    int index[2] = {0,0} ;
    while(index[0]==index[1])
    {
        index[0] = rand()%8;
        index[1] = ((rand() + 13)*13)%8;
    }
    for(int i = 0 ; i < 2 ; i++)
    {
        customized_button *new_button = new customized_button(this);
        new_button->setObjectName(QString::number(i));
        //new_button->button_number=i;
        ui->hl_all_cards_btn->addWidget(new_button);
        const int x = 200 , a = (744/606);
        new_button->setFixedSize(x,a*x);
        QString temp="QPushButton{border-image: url(:/photos/back-of-card.png);}";
        new_button->setStyleSheet(temp);
        all_forecast_btn.append(new_button);
        //connect(new_button,SIGNAL(sig_button_clicked(int)),this,SLOT(slo_forecast(int)));
    }
}

