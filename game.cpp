#include "game.h"
#include "ui_game.h"
#include <QScreen>
#include <QLabel>
using namespace std;

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
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 11 ; i < 22 ; i++)
    {
        all_cards[i].set_value(i-10);
        all_cards[i].set_type(gold);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 22 ; i < 33 ; i++)
    {
        all_cards[i].set_value(i-21);
        all_cards[i].set_type(card_type::map);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 33 ; i < 44 ; i++)
    {
        all_cards[i].set_value(i-32);
        all_cards[i].set_type(flag);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 44 ; i < 48 ; i++)
    {
        all_cards[i].set_value(i-43);
        all_cards[i].set_type(pirate);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 48 ; i < 52 ; i++)
    {
        all_cards[i].set_value(i-47);
        all_cards[i].set_type(queen);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int i = 52 ; i < 56 ; i++)
    {
        all_cards[i].set_value(i-51);
        all_cards[i].set_type(king);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
        connect(new_button,SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_card(customized_button*)));
    }
    for (int j = 0 ; j < 56 ; j++)
        all_cards_btn[j]->setFixedSize(w,h);
}


void game::sort_btn_cards(QVector<customized_button*>& cards)
{
    int s  = cards.size();
    for (int i = 0 ; i < s - 1 ; i++)
    {
        for (int j = i + 1 ; j < s ; j++)
        {
            if (cards[i]->get_btn_card().get_number() > cards[j]->get_btn_card().get_number())
            {
                customized_button* temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;
            }
        }
    }
}


void game::slo_selected_card(customized_button* input)
{
    inactive_click();
    input->get_btn_card().set_selected(true);
    player1.set_selected_card(input);
    iter it = player1.find_card(input);
    player1.cards.erase(it);
    clear_move_animations();
    QPropertyAnimation *animation = new QPropertyAnimation(input,"geometry");
    animation->setDuration(500);
    QRect s = input->geometry();
    animation->setStartValue(s);
    animation->setEndValue(QRect(width()/2-w/2, (height()/2-h/2), w, h));
    all_move_animation.append(animation);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(slo_p1_arrange_card()));
    emit sig_send_one_card(input->get_btn_card());
}


void game::clear_move_animations()
{
    int size = all_move_animation.size();
    for (int i = 0 ; i < size ; i++)
        delete all_move_animation[i];
    all_move_animation.clear();
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
            player1.cards.append(all_cards_btn[index[i]]);

        for(int i = 2*n ; i < 4*n ; i++)
            player2.cards.append(all_cards_btn[index[i]]);

        delete[] index;
    }
    sort_btn_cards(player1.cards);
    sort_btn_cards(player2.cards);
    for (int i = 0 ; i < player1.cards.size() ; i++)
    {
        change_StyleSheet(player1.cards[i]);
        player1.cards[i]->setParent(ui->centralwidget);
        player1.cards[i]->show();
    }
    for (int i = 0 ; i < player2.cards.size() ; i++)
    {
        player2.cards[i]->setStyleSheet(BACK);
        player2.cards[i]->setParent(ui->centralwidget);
        player2.cards[i]->show();
    }
     emit sig_send_card();
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
    clear_move_animations();
    int size = player1.cards.size();
    for(int i = 0 ; i < size ; i++)
    {
        QPropertyAnimation *player1_animation = new QPropertyAnimation(player1.cards[i],"geometry");
        player1_animation->setDuration(1000+(i+1)*100);
        player1_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player1_animation->setEndValue(QRect((width()/2-w/2), height()-h-90, w, h));
        all_move_animation.append(player1_animation);
        player1_animation->start();
        if ( i == size - 1)
        {
            connect(player1_animation,SIGNAL(finished()),this,SLOT(slo_p1_arrange_card()));
        }
    }
    for(int i = 0 ; i < size ; i++)
        {
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");
        player2_animation->setDuration(1000+(i+1)*100);
        player2_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player2_animation->setEndValue(QRect((width()/2-w/2), 60, w, h));
        all_move_animation.append(player2_animation);
        player2_animation->start();
        if ( i == size - 1)
        {
            connect(player2_animation,SIGNAL(finished()),this,SLOT(slo_p2_arrange_card()));
        }
    }
}

void game::slo_p1_arrange_card()
{
    clear_move_animations();
    int size = player1.cards.size();
    for (int i = 0 ; i < size ; i++)
    {
        QRect temp = player1.cards[i]->geometry();
        QPropertyAnimation *player1_animation = new QPropertyAnimation(player1.cards[i],"geometry");
        player1_animation->setDuration(1000);
        int x = (width()/2)-((size+1)*(w/4))+(i*w/2);
        player1_animation->setStartValue(temp);
        player1_animation->setEndValue(QRect(x,height()-h-90,w,h));
        all_move_animation.append(player1_animation);
        player1_animation->start();
        if (i == size - 1)
            connect(player1_animation,SIGNAL(finished()),this,SLOT(slo_active_click()));
    }
}

void game::slo_p2_arrange_card()
{
    clear_move_animations();
    int size = player2.cards.size();
    for (int i = 0 ; i < size ; i++)
    {
        QRect temp = player2.cards[i]->geometry();
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");
        player2_animation->setDuration(1000);
        int x = (width()/2)-((size+1)*(w/4))+(i*w/2);
        player2_animation->setStartValue(temp);
        player2_animation->setEndValue(QRect(x,60,w,h));
        all_move_animation.append(player2_animation);
        player2_animation->start();
        if (i == size - 1)
            connect(player2_animation,SIGNAL(finished()),this,SLOT(slo_active_click()));
    }
}



void game::slo_active_click()
{
    int s = player1.cards.size();
    for (int i = 0 ; i < s ; i++)
    {
        player1.cards[i]->setEnabled(true);
    }
}

void game::inactive_click()
{
    int s = player1.cards.size();
    for (int i = 0 ; i < s ; i++)
    {
        player1.cards[i]->setEnabled(false);
    }
}


void game::game_server_start()
{
    make_card(7);
    while(fl)
    {

    }
    dealer_animation();
}

void game::game_client_start()
{
    while(fl)
    {

    }
    for(int i=0 ; i < player1.cards.size() ; i++)
    {
        player2.cards[i]->setStyleSheet(BACK);
        change_StyleSheet(player1.cards[i]);
    }
    dealer_animation();
}
