#include "game.h"
#include "ui_game.h"
#include <QScreen>
#include <QLabel>
#include <QPixmap>

#define BACK "QPushButton{border-image: url(:/photos/back-of-card.png);}"

// size of card :
const int w = 100 , a = (600/400) , h = a*w;
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
    for (int i = 0 ; i < 11 ; i++)
    {
        all_cards[i].set_value(i+1);
        all_cards[i].set_type(parrot);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 11 ; i < 22 ; i++)
    {
        all_cards[i].set_value(i-10);
        all_cards[i].set_type(gold);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 22 ; i < 33 ; i++)
    {
        all_cards[i].set_value(i-21);
        all_cards[i].set_type(map);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 33 ; i < 44 ; i++)
    {
        all_cards[i].set_value(i-32);
        all_cards[i].set_type(flag);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 44 ; i < 48 ; i++)
    {
        all_cards[i].set_value(i-43);
        all_cards[i].set_type(pirate);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 48 ; i < 52 ; i++)
    {
        all_cards[i].set_value(i-47);
        all_cards[i].set_type(king);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int i = 52 ; i < 56 ; i++)
    {
        all_cards[i].set_value(i-51);
        all_cards[i].set_type(queen);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(int)),this,SLOT(slo_selected_card(card)));
    }
    for (int j = 0 ; j < 56 ; j++)
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
    if(n == 0)
    {
        int *index = new int[2];
        do{
            index[0] = rand()%11;
            index[1] = ((rand() + 13)*13)%11;
        }while(index[0]==index[1]);
        player1.cards.append(all_cards_btn[index[0]]);
        change_StyleSheet(all_cards_btn[index[0]]);
        all_cards_btn[index[0]]->setParent(ui->centralwidget);
        all_cards_btn[index[0]]->show();
        player2.cards.append(all_cards_btn[index[1]]);
        all_cards_btn[index[1]]->setStyleSheet(BACK);
        all_cards_btn[index[1]]->setParent(ui->centralwidget);
        all_cards_btn[index[1]]->show();
        delete[] index;
    }
    else
    {
        int *index = new int[4*n];
        for(int i = 0 ; i < 4*n ; i++)
        {
            index[i] = rand()%56;
            for(int j = 0 ; j < i ; j++)
            {
                if(index[i] == index[j])
                {
                    i--;
                    break;
                }
            }
        }
        for(int i = 0 ; i < 2*n ; i++)
        {
            player1.cards.append(all_cards_btn[index[i]]);
            change_StyleSheet(all_cards_btn[index[i]]);
            all_cards_btn[index[i]]->setParent(ui->centralwidget);
            all_cards_btn[index[i]]->show();
        }
        for(int i = 2*n ; i < 4*n ; i++)
        {
            player2.cards.append(all_cards_btn[index[i]]);
            all_cards_btn[index[i]]->setStyleSheet(BACK);
            all_cards_btn[index[i]]->setParent(ui->centralwidget);
            all_cards_btn[index[i]]->show();
        }
        delete[] index;
    }
}

void game::change_StyleSheet(customized_button* input)
{
    card temp = input->get_btn_card();
    QString p;
    p = "QPushButton{border-image: url(:/photos/" + temp.get_type_string() + " " + QString::number(temp.get_value()) + ".png);}";
    input->setStyleSheet(p);
}

void game::dealer_animation()
{
    int size = player1.cards.size();
    for(int i = 0 ; i < size ; i++){
        QPropertyAnimation *player1_animation = new QPropertyAnimation(player1.cards[i],"geometry");
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");
        player1_animation->setDuration(1000+(i+1)*100);
        player1_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player1_animation->setEndValue(QRect((width()/2-w/2), height()-h-90, w, h));
        all_move_animation.append(player1_animation);
        player2_animation->setDuration(1000+(i+1)*100);
        player2_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player2_animation->setEndValue(QRect((width()/2-w/2), 60, w, h));
        all_move_animation.append(player2_animation);
        player1_animation->start();
        player2_animation->start();
        if ( i == size - 1)
            connect(player1_animation,SIGNAL(finished()),this,SLOT(slo_arrange_card()));
    }
}

void game::slo_arrange_card()
{
    int size = all_move_animation.size();
    for (int i = 0 ; i < size ; i++)
        delete all_move_animation[i];
    all_move_animation.clear();

    size = player1.cards.size();
    for (int i = 0 ; i < size ; i++)
    {
        QPropertyAnimation *player1_animation = new QPropertyAnimation(player1.cards[i],"geometry");
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");

        player1_animation->setDuration(1000);
        int x = (width()/2)-((size+1)*(w/4))+(i*w/2);
        player1_animation->setStartValue(QRect((width()/2-w/2),height()-h-90, w, h));
        player1_animation->setEndValue(QRect(x,height()-h-90,w,h));
        all_move_animation.append(player1_animation);
        player2_animation->setDuration(1000);
        player2_animation->setStartValue(QRect((width()/2-w/2), 60, w, h));
        player2_animation->setEndValue(QRect(x,60,w,h));
        all_move_animation.append(player2_animation);
        player1_animation->start();
        player2_animation->start();
    }
}


void game::start()
{
    round(1);
}

