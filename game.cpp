#include "game.h"
#include "ui_game.h"
#include <QScreen>
#include <QLabel>
#include <QPixmap>

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"

// size of card :
const int w = 200 , a = (500/400) , h = a*w;
//

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
    set_all_cards();
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
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 8 ; i < 16 ; i++)
    {
        all_cards[i].set_value(i-7);
        all_cards[i].set_type(gold);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 16 ; i < 24 ; i++)
    {
        all_cards[i].set_value(i-15);
        all_cards[i].set_type(map);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 24 ; i < 32 ; i++)
    {
        all_cards[i].set_value(i-23);
        all_cards[i].set_type(flag);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 32 ; i < 36 ; i++)
    {
        all_cards[i].set_value(i-31);
        all_cards[i].set_type(pirate);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 36 ; i < 39 ; i++)
    {
        all_cards[i].set_value(i-35);
        all_cards[i].set_type(king);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int i = 39 ; i < 42 ; i++)
    {
        all_cards[i].set_value(i-38);
        all_cards[i].set_type(queen);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
//        all_cards_btn[i]->setParent(ui->centralwidget);
    }
    for (int j = 0 ; j < 42 ; j++)
        all_cards_btn[j]->setFixedSize(w,h);
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
    // get number of hands :
}

void game::slo_selected_card(card input)
{
    // get selected card :
}


void game::round(int n)
{
    make_card(n);
    dealer_animation();
}

void game::make_card(int n)
{
    srand(time(NULL));
    int *index = new int[2*n];
    if(n == 1)
    {
        do{
            index[0] = rand()%8;
            index[1] = ((rand() + 13)*13)%8;
        }while(index[0]==index[1]);
    }
    else
    {
        for(int i = 0 ; i < 2*n ; i++)
        {
            index[i] = rand()%42;
            for(int j = 0 ; j < i ; j++)
            {
                if(index[i] == index[j])
                {
                    i--;
                    break;
                }
            }
        }
    }
    for(int i = 0 ; i < n ; i++)
    {
        player1.cards.append(all_cards_btn[index[i]]);
        all_cards_btn[index[i]]->setStyleSheet(BACK);
        all_cards_btn[index[i]]->setParent(ui->centralwidget);
        all_cards_btn[index[i]]->show();
    }
    for(int i = n ; i < 2*n ; i++)
    {
        player2.cards.append(all_cards_btn[index[i]]);
        all_cards_btn[index[i]]->setStyleSheet(BACK);
        all_cards_btn[index[i]]->setParent(ui->centralwidget);
        all_cards_btn[index[i]]->show();
    }
    delete[] index;
}

void game::dealer_animation()
{
    int s = player1.cards.size();

    for(int i = 0 ; i < s ; i++){
        QPropertyAnimation *player1_animation = new QPropertyAnimation(player1.cards[i],"geometry");
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");
        player1_animation->setDuration(1000+(i+1)*100);
        player1_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player1_animation->setEndValue(QRect((width()/2-w/2), height()-h-50, w, h));
        all_move_animation.append(player1_animation);
        player2_animation->setDuration(1000+(i+1)*100);
        player2_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player2_animation->setEndValue(QRect((width()/2-w/2), 20, w, h));
        all_move_animation.append(player2_animation);

        player2_animation->start();
        player1_animation->start();
    }
}

void game::start()
{
    round(7);
}

