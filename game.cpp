#include "game.h"
#include "ui_game.h"
#include <QScreen>
#include <QLabel>
#include <math.h>
#include <windows.h>
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
    lbl_score_p1 = new QLabel(this);
    lbl_score_p2 = new QLabel(this);
    lbl_score_p1->setGeometry(QRect(width()/2-150,height()-270,300,35));
    lbl_score_p2->setGeometry(QRect(width()/2-150,200,300,35));
    QFont score_font = lbl_score_p1->font();
    score_font.setPointSize(20);
    score_font.setBold(true);
    lbl_score_p1->setFont(score_font);
    lbl_score_p2->setFont(score_font);
    lbl_score_p1->setText("SCORE : "+QString::number(player1.score));
    lbl_score_p2->setText("SCORE : "+QString::number(player2.score));
    lbl_score_p1->setAlignment(Qt::AlignCenter);
    lbl_score_p2->setAlignment(Qt::AlignCenter);
    lbl_score_p1->setParent(this);
    lbl_score_p1->show();
    lbl_score_p2->setParent(this);
    lbl_score_p2->show();

    QLabel* lbl_p1 = new QLabel(this);
    lbl_p1->setGeometry(QRect(width()/2-150,height()-240,300,35));
    QFont username_font = lbl_p1->font();
    username_font.setPointSize(20);
    username_font.setBold(true);
    lbl_p1->setFont(username_font);
    lbl_p1->setText(player1.get_username());
    lbl_p1->setAlignment(Qt::AlignCenter);
    lbl_p1->setParent(this);
    lbl_p1->show();
    QLabel* lbl_p2 = new QLabel(this);
    lbl_p2->setGeometry(QRect(width()/2-150,170,300,35));
    lbl_p2->setFont(username_font);
    lbl_p2->setText(player2.get_username());
    lbl_p2->setAlignment(Qt::AlignCenter);
    lbl_p2->setParent(this);
    lbl_p2->show();
    for (int i = 0 ; i < 11 ; i++)
    {
        all_cards[i].set_value(i+1);
        all_cards[i].set_type(parrot);
        all_cards[i].set_number(i);
        customized_button *new_button = new customized_button(all_cards[i]);
        new_button->setEnabled(false);
        new_button->change_obj_name();
        all_cards_btn[i] = new_button;
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
    }
    for (int j = 0 ; j < 56 ; j++)
    {
        connect(all_cards_btn[j],SIGNAL(sig_card_clicked(customized_button*)),this,SLOT(slo_selected_p1_card_btn(customized_button*)));
    }
}


void game::rasie_p2_cards()
{
    for (int i = 0 ; i < player2.cards.size() ; i++)
    {
        player2.cards[i]->raise();
    }
}

void game::rasie_p1_cards()
{
    for (int i = 0 ; i < player1.cards.size() ; i++)
    {
        player1.cards[i]->raise();
    }
}

void game::rasie_p2_win_cards()
{
    for (int i = 0 ; i < player2.win_cards.size() ; i++)
    {
        player2.win_cards[i]->raise();
    }
}

void game::rasie_p1_win_cards()
{
    for (int i = 0 ; i < player1.win_cards.size() ; i++)
    {
        player1.win_cards[i]->raise();
    }
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
        all_cards_btn[index[0]]->change_card_StyleSheet();
        all_cards_btn[index[0]]->setParent(ui->centralwidget);
        all_cards_btn[index[0]]->show();
        player2.cards.append(all_cards_btn[index[1]]);
        all_cards_btn[index[1]]->setStyleSheet(BACK);
        all_cards_btn[index[1]]->setParent(ui->centralwidget);
        all_cards_btn[index[1]]->show();

        if(player1.cards[0]->get_btn_card() > player2.cards[0]->get_btn_card() )
        {
            turn = p1;
        }
        else
        {
            turn = p2;
        }
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
        player1.cards[i]->change_card_StyleSheet();
        player1.cards[i]->setParent(ui->centralwidget);
        player1.cards[i]->show();
    }
    for (int i = 0 ; i < player2.cards.size() ; i++)
    {
        player2.cards[i]->setStyleSheet(BACK);
        player2.cards[i]->setParent(ui->centralwidget);
        player2.cards[i]->show();
    }
    rasie_p2_cards();
    rasie_p1_cards();
    emit sig_send_card();
    dealer_animation();
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

void game::clear_move_animations()
{
    int size = all_move_animation.size();
    for (int i = 0 ; i < size ; i++)
        delete all_move_animation[i];
    all_move_animation.clear();
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
    }
    for(int i = 0 ; i < size ; i++)
    {
        QPropertyAnimation *player2_animation = new QPropertyAnimation(player2.cards[i],"geometry");
        player2_animation->setDuration(1000+(i+1)*100);
        player2_animation->setStartValue(QRect(width()/2-w/2, height()/2-h/2, w, h));
        player2_animation->setEndValue(QRect((width()/2-w/2), 60, w, h));
        all_move_animation.append(player2_animation);
        player2_animation->start();
    }
    if (r == 0 && turn == p1)
    {
        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_active_card_click()));
    }
    else if(r > 0)
    {
        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_arrange_card()));
    }
}

void game::slo_arrange_card()
{
    clear_move_animations();
    slo_p1_arrange_card();
    slo_p2_arrange_card();
}


void game::slo_p1_arrange_card()
{
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
    }
}

void game::slo_p2_arrange_card()
{
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
    }
    if (r != 0)
    {
        if (first_flag)
        {
            first_flag = false;
            connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_forecast()));
        }
    }
}


void game::slo_forecast()
{
    if(turn == p2)
    {
        start.exec();
    }
    for(int i = 0 ; i <= player1.cards.size() ; i++)
    {
        customized_button *new_button = new customized_button(i);
        new_button->setEnabled(false);
        connect(new_button,SIGNAL(sig_number_clicked(int)),this,SLOT(slo_selected_num_btn(int)));
        new_button->change_obj_name();
        new_button->setFixedSize(60,60);
        QString temp="QPushButton{border-image: url(:/photos/A" + QString::number(i) + ".png);}QPushButton:pressed{border-image: url(:/photos/C" + QString::number(i) + ".png);}";
        new_button->setStyleSheet(temp);
        all_forecast_btn.append(new_button);
        new_button->setParent(ui->centralwidget);
        new_button->show();
    }
    int s = all_forecast_btn.size();
    for (int j = 0 ; j < s ; j++ )
    {
        QPropertyAnimation *animation = new QPropertyAnimation(all_forecast_btn[j],"geometry");
        animation->setDuration(500);
        int x = (width()/2)-((s)*(60/2))+(j*60);
        animation->setStartValue(QRect(x,height()-500,60,60));
        animation->setEndValue(QRect(x,height()-350,60,60));
        all_move_animation.append(animation);
        animation->start();
    }
    connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_active_num_click()));
}

void game::slo_active_num_click()
{
    int s = all_forecast_btn.size();
    for (int i = 0 ; i < s ; i++)
    {
        all_forecast_btn[i]->setEnabled(true);
    }
}

void game::clear_all_forecast_btn()
{
    int size = all_forecast_btn.size();
    for (int i = 0 ; i < size ; i++)
    {
        delete all_forecast_btn[i];
    }
    all_forecast_btn.clear();
}

void game::inactive_num_click()
{
    int s = all_forecast_btn.size();
    for (int i = 0 ; i < s ; i++)
    {
        all_forecast_btn[i]->setEnabled(false);
    }
}

void game::slo_selected_num_btn(int number)
{
    clear_move_animations();
    inactive_num_click();
    clear_all_forecast_btn();
    player1.set_forecast_number(number);
    if(turn == p1)
    {
        emit sig_send_forecast();
        start.exec();
    }
    if(turn == p2)
    {
        emit sig_send_forecast();
    }
    forecast_p1_btn = new customized_button(number);
    forecast_p2_btn = new customized_button(player2.get_forecast_number());
    forecast_p1_btn->change_obj_name();
    forecast_p2_btn->change_obj_name();
    QString temp1 , temp2;
    if (number == 0)
    {
        temp1 ="QPushButton{border-image: url(:/photos/B" + QString::number(number) + ".png);}";
    }
    else
    {
        temp1 ="QPushButton{border-image: url(:/photos/A" + QString::number(number) + ".png);}";
    }
    if (player2.get_forecast_number() == 0)
    {
        temp2="QPushButton{border-image: url(:/photos/B" + QString::number(player2.get_forecast_number()) + ".png);}";
    }
    else
    {
        temp2="QPushButton{border-image: url(:/photos/A" + QString::number(player2.get_forecast_number()) + ".png);}";
    }
    forecast_p1_btn->setStyleSheet(temp1);
    forecast_p2_btn->setStyleSheet(temp2);
    forecast_p1_btn->setParent(ui->centralwidget);
    forecast_p2_btn->setParent(ui->centralwidget);
    forecast_p1_btn->show();
    forecast_p2_btn->show();
    QPropertyAnimation *animation1 = new QPropertyAnimation(forecast_p1_btn,"geometry");
    QPropertyAnimation *animation2 = new QPropertyAnimation(forecast_p2_btn,"geometry");
    animation1->setDuration(1000);
    animation2->setDuration(1000);
    animation1->setStartValue(QRect(0,height()-60,60,60));
    animation2->setStartValue(QRect(width()-60,0,60,60));
    animation1->setEndValue(QRect(50,height()-200,120,120));
    animation2->setEndValue(QRect(width()-160,50,120,120));
    all_move_animation.append(animation1);
    all_move_animation.append(animation2);
    animation1->start();
    animation2->start();
    if (turn == p1)
    {
        connect(animation2,SIGNAL(finished()),this,SLOT(slo_active_card_click()));
    }
//    else
//    {
//        connect(animation2,SIGNAL(finished()),this,SLOT(slo_selected_p2_card_btn()));
//    }
}


void game::slo_active_card_click()
{
    if(turn == p1 )
    {
        int s = player1.cards.size();
        for (int i = 0 ; i < s ; i++)
        {
            player1.cards[i]->setEnabled(true);
        }
    }
    else
    {
        QString type_card_p2 = player2.get_selected_card_btn()->get_btn_card().get_type_string();
        int counter = 0;
        for(int i=0 ; i < player1.cards.size() ; i++)
        {
            if( player1.cards[i]->get_btn_card().get_type_string() == type_card_p2 )
            {
                counter++;
            }
        }
        if(counter == 0 || type_card_p2 == "king" || type_card_p2 == "queen" || type_card_p2 == "pirate")
        {
            int s = player1.cards.size();
            for (int i = 0 ; i < s ; i++)
            {
                player1.cards[i]->setEnabled(true);
            }
        }
        else
        {
            for(int i=0 ; i < player1.cards.size() ; i++)
            {
                if( player1.cards[i]->get_btn_card().get_type_string() == type_card_p2 )
                {
                    player1.cards[i]->setEnabled(true);
                }
                else if( player1.cards[i]->get_btn_card().get_type_string() == "king" )
                {
                    player1.cards[i]->setEnabled(true);
                }
                else if( player1.cards[i]->get_btn_card().get_type_string() == "queen" )
                {
                    player1.cards[i]->setEnabled(true);
                }
                else if( player1.cards[i]->get_btn_card().get_type_string() == "pirate" )
                {
                    player1.cards[i]->setEnabled(true);
                }
            }
        }

    }

}

void game::inactive_card_click()
{
    int s = player1.cards.size();
    for (int i = 0 ; i < s ; i++)
    {
        player1.cards[i]->setEnabled(false);
    }
}

void game::slo_selected_p1_card_btn(customized_button* input)
{
    inactive_card_click();
    input->get_btn_card().set_selected(true);
    player1.set_selected_card_btn(input);
    iter it = player1.find_card(input);
    player1.cards.erase(it);
    clear_move_animations();
    QPropertyAnimation *animation = new QPropertyAnimation(input,"geometry");
    animation->setDuration(700);
    QRect temp = input->geometry();
    animation->setStartValue(temp);
    animation->setEndValue(QRect(width()/2-w/2+30, (height()/2-h/2) + 30, w, h));
    all_move_animation.append(animation);
    animation->start();
    slo_p1_arrange_card();
//    if (turn == p1 || r == 0)
//    {
//        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_selected_p2_card_btn()));
//    }
//    else
//    {
//    connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_compare_two_cards()));
//    }
    if(turn == p2)
    {

        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_compare_two_cards()));
    }
    emit sig_send_one_card(input->get_btn_card());
}


void game::slo_selected_p2_card_btn()
{
//    if (player2.get_selected_card_btn() == nullptr)
//    {
//        loop.exec();
//    }
    iter it = player2.find_card(player2.get_selected_card_btn());
    player2.cards.erase(it);
    clear_move_animations();
    QPropertyAnimation *animation = new QPropertyAnimation(player2.get_selected_card_btn(),"geometry");
    animation->setDuration(700);
    QRect temp = player2.get_selected_card_btn()->geometry();
    animation->setStartValue(temp);
    animation->setEndValue(QRect(width()/2-w/2 -30, (height()/2-h/2) - 30, w, h));
    all_move_animation.append(animation);
    animation->start();
    player2.get_selected_card_btn()->change_card_StyleSheet();
    slo_p2_arrange_card();
    if (turn == p1)
    {
        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_compare_two_cards()));
    }
    else
    {
        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_active_card_click()));
    }
}


void game::slo_compare_two_cards()
{
//    if (player2.get_selected_card_btn() == nullptr)
//    {
//        loop.exec();
//    }
    if (turn == p1)
    {
        if (player1.get_selected_card_btn()->get_btn_card()>player2.get_selected_card_btn()->get_btn_card() == true)
        {
            hand_winner = p1;
        }
        else
        {
            hand_winner = p2;
        }
    }
    else
    {
        if (player2.get_selected_card_btn()->get_btn_card()>player1.get_selected_card_btn()->get_btn_card() == true)
        {
            hand_winner = p2;
        }
        else
        {
            hand_winner = p1;
        }
    }
    hand_win();
}


void game::hand_win()
{
    Sleep(700);
    clear_move_animations();
    static int a1 = 0;
    static int a2 = 0;
    if (hand_winner == p1)
    {
        int size = player1.win_cards.size();
        player1.win_cards.append(player1.get_selected_card_btn());
        player1.win_cards.append(player2.get_selected_card_btn());
        rasie_p1_win_cards();
        for (int i = size ; i < size + 2 ; i++)
        {
            QPropertyAnimation *animation = new QPropertyAnimation(player1.win_cards[i],"geometry");
            animation->setDuration(700);
            QRect temp = player1.win_cards[i]->geometry();
            animation->setStartValue(temp);
            animation->setEndValue(QRect(175, (height() - 120) - (a1 * 15), w/3, h/3));
            all_move_animation.append(animation);
            animation->start();
            player1.win_cards[i]->setStyleSheet(BACK);
        }
        a1++;
        if (r != 0)
        {
            if (player1.get_forecast_number() == (player1.win_cards.size()/2))
            {
                QString temp="QPushButton{border-image: url(:/photos/B" + QString::number(player1.get_forecast_number()) + ".png);}";
                forecast_p1_btn->setStyleSheet(temp);
            }
            else if (player1.get_forecast_number() < (player1.win_cards.size()/2))
            {
                QString temp="QPushButton{border-image: url(:/photos/C" + QString::number(player1.get_forecast_number()) + ".png);}";
                forecast_p1_btn->setStyleSheet(temp);
            }
        }
    }
    else
    {
        int size = player2.win_cards.size();
        player2.win_cards.append(player1.get_selected_card_btn());
        player2.win_cards.append(player2.get_selected_card_btn());
        rasie_p2_win_cards();
        for (int i = size ; i < size + 2 ; i++)
        {
            QPropertyAnimation *animation = new QPropertyAnimation(player2.win_cards[i],"geometry");
            animation->setDuration(700);
            QRect temp = player2.win_cards[i]->geometry();
            animation->setStartValue(temp);
            animation->setEndValue(QRect(width() - 200, 60 + (a2 * 15) , w/3, h/3));
            all_move_animation.append(animation);
            animation->start();
            player2.win_cards[i]->setStyleSheet(BACK);
        }
        a2++;
        if (r != 0)
        {
            if (player2.get_forecast_number() == (player2.win_cards.size()/2))
            {
                QString temp="QPushButton{border-image: url(:/photos/B" + QString::number(player2.get_forecast_number()) + ".png);}";
                forecast_p2_btn->setStyleSheet(temp);
            }
            else if (player2.get_forecast_number() < (player2.win_cards.size()/2))
            {
                QString temp="QPushButton{border-image: url(:/photos/C" + QString::number(player2.get_forecast_number()) + ".png);}";
                forecast_p2_btn->setStyleSheet(temp);
            }
        }
    }
    player1.set_selected_card_btn(nullptr);
    player2.set_selected_card_btn(nullptr);
    turn = hand_winner;
    if (player1.cards.size() != 0)
    {
        if (turn == p1)
            connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_active_card_click()));
//        else
//            connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_selected_p2_card_btn()));
    }
    else
    {
        a1 = 0;
        a2 = 0;
        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_hide_forecast_btn()));
    }
}

void game::slo_hide_forecast_btn()
{
    if (r != 0)
    {
        forecast_p1_btn->raise();
        forecast_p2_btn->raise();
    }
    int s1 = player1.win_cards.size();
    for (int i = 0 ; i < s1; i++)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(player1.win_cards[i],"geometry");
        animation->setDuration(900);
        QRect temp = player1.win_cards[i]->geometry();
        animation->setStartValue(temp);
        animation->setEndValue(QRect(0, height(), w/3, h/3));
        all_move_animation.append(animation);
        animation->start();
        player1.win_cards[i]->setStyleSheet(BACK);
    }
    int s2 = player2.win_cards.size();
    for (int i = 0 ; i < s2 ; i++)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(player2.win_cards[i],"geometry");
        animation->setDuration(900);
        QRect temp = player2.win_cards[i]->geometry();
        animation->setStartValue(temp);
        animation->setEndValue(QRect(width(), 0, w/3, h/3));
        all_move_animation.append(animation);
        animation->start();
        player2.win_cards[i]->setStyleSheet(BACK);
    }
    if (r != 0)
    {
        QPropertyAnimation *animation1 = new QPropertyAnimation(forecast_p1_btn,"geometry");
        animation1->setDuration(1000);
        QRect temp1 = forecast_p1_btn->geometry();
        animation1->setStartValue(temp1);
        animation1->setEndValue(QRect(0, height() ,60, 60));
        all_move_animation.append(animation1);
        animation1->start();
        QPropertyAnimation *animation2 = new QPropertyAnimation(forecast_p2_btn,"geometry");
        animation2->setDuration(1000);
        QRect temp2 = forecast_p2_btn->geometry();
        animation2->setStartValue(temp2);
        animation2->setEndValue(QRect(width(), 0 ,60, 60));
        all_move_animation.append(animation2);
        animation2->start();
    }
    connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_rate_round()));

}


void game::slo_rate_round()
{
    Sleep(700);
    if (r == 0)
    {
        r++;
        emit sig_end_of_round();
    }
    else
    {
        forecast_p1_btn->hide();
        forecast_p2_btn->hide();
        delete forecast_p1_btn;
        delete forecast_p2_btn;
        // player1.score :
        if (player1.get_forecast_number() == 0)
        {
            if (player1.win_cards.size() == 0)
            {
                player1.score += (r*10);
            }
            else
            {
                player1.score -= (r*10);
            }
        }
        else
        {
            if (player1.get_forecast_number() == player1.win_cards.size()/2)
            {
                player1.score += (player1.get_forecast_number()*10);
            }
            else
            {
                player1.score -= (abs(player1.get_forecast_number()-(player1.win_cards.size()/2))*10);
            }
        }
        int s1 = player1.win_cards.size();
        for (int i = 0 ; i < s1 ; i += 2)
        {
            if (player1.win_cards[i]->get_btn_card().get_type() == queen ||player1.win_cards[i+1]->get_btn_card().get_type() == queen)
            {
                player1.score += 20;
            }
            if (player1.win_cards[i]->get_btn_card().get_type() == king ||player1.win_cards[i+1]->get_btn_card().get_type() == king)
            {
                player1.score += 15;
            }
            if (player1.win_cards[i]->get_btn_card().get_type() == pirate ||player1.win_cards[i+1]->get_btn_card().get_type() == pirate)
            {
                player1.score += 10;
            }
        }
        // player2.score :
        if (player2.get_forecast_number() == 0)
        {
            if (player2.win_cards.size() == 0)
            {
                player2.score += (r*10);
            }
            else
            {
                player2.score -= (r*10);
            }
        }
        else
        {
            if (player2.get_forecast_number() == player2.win_cards.size()/2)
            {
                player2.score += (player2.get_forecast_number()*10);
            }
            else
            {
                player2.score -= (abs(player2.get_forecast_number()-(player2.win_cards.size()/2))*10);
            }
        }
        int s2 = player2.win_cards.size();
        for (int i = 0 ; i < s2 ; i += 2)
        {
            if (player2.win_cards[i]->get_btn_card().get_type() == queen ||player2.win_cards[i+1]->get_btn_card().get_type() == queen)
            {
                player2.score += 20;
            }
            if (player2.win_cards[i]->get_btn_card().get_type() == king ||player2.win_cards[i+1]->get_btn_card().get_type() == king)
            {
                player2.score += 15;
            }
            if (player2.win_cards[i]->get_btn_card().get_type() == pirate ||player2.win_cards[i+1]->get_btn_card().get_type() == pirate)
            {
                player2.score += 10;
            }
        }
        lbl_score_p1->hide();
        lbl_score_p2->hide();
        lbl_score_p1->setText("SCORE : " + QString::number(player1.score));
        lbl_score_p2->setText("SCORE : " + QString::number(player2.score));
        if (player1.score > 0)
            lbl_score_p1->setStyleSheet("QLabel {color: green;}");
        else if (player1.score == 0)
            lbl_score_p1->setStyleSheet("QLabel {color: black;}");
        else
            lbl_score_p1->setStyleSheet("QLabel {color: red;}");
        if (player2.score > 0)
            lbl_score_p2->setStyleSheet("QLabel {color: green;}");
        else if (player2.score == 0)
            lbl_score_p2->setStyleSheet("QLabel {color: black;}");
        else
            lbl_score_p2->setStyleSheet("QLabel {color: red;}");
        lbl_score_p1->show();
        lbl_score_p2->show();
        if (r < 7)
        {
            r++;
            first_flag = true;
            player1.hide_cards();
            player1.hide_win_cards();
            player2.hide_cards();
            player2.hide_win_cards();
            player1.clear_cards();
            player1.clear_win_cards();
            player2.clear_cards();
            player2.clear_win_cards();
            player1.set_forecast_number(-1);
            player2.set_forecast_number(-1);
            emit sig_end_of_round();
        }
        else
        {
            // ..........................
        }
    }
}
















void game::game_server_start()
{
    make_card(r);
}

void game::game_client_start()
{

}








































void game::on_btn_change_clicked()
{
    if(player1.get_forecast_number() == -1 || player2.get_forecast_number() == -1)
    {
        QMessageBox::information(this,"Change","Please wait");
    }
    else if(player1.get_selected_card_btn() != nullptr || player2.get_selected_card_btn() != nullptr)
    {
        QMessageBox::information(this,"Change","The other player has choose a card. please wait");
    }
    else if(r > 0 && r < 8)
    {
       emit sig_change_card();
    }
}
