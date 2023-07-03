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

game::game(person per1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    par = parent;
    person1 = per1;
    update_file();
    player1.set_username(person1.get_username());
    stop_spy = new QSignalSpy(this,SIGNAL(sig_timeout()));
    this->setFixedSize(this->size());
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - width()) / 2;
    const int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    set_all_cards();
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    seconds_counter = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slo_time_warning()));

    connect(seconds_counter,SIGNAL(timeout()),this ,SLOT(slo_countdown()));
}

game::~game()
{
    delete timer;
//    delete timer2;
    delete stop_spy;
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
    score_font.setFamily("Tempus Sans ITC");
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

    lbl_username_p1 = new QLabel(this);
    lbl_username_p1->setGeometry(QRect(width()/2-150,height()-240,300,35));
    QFont username_font = lbl_username_p1->font();
    username_font.setPointSize(20);
    username_font.setBold(true);
    username_font.setFamily("Tempus Sans ITC");
    lbl_username_p1->setFont(username_font);
    lbl_username_p1->setText(player1.get_username());
    lbl_username_p1->setAlignment(Qt::AlignCenter);
    lbl_username_p1->setParent(this);
    lbl_username_p1->show();
    lbl_username_p2 = new QLabel(this);
    lbl_username_p2->setGeometry(QRect(width()/2-150,170,300,35));
    lbl_username_p2->setFont(username_font);
    lbl_username_p2->setText(player2.get_username());
    lbl_username_p2->setAlignment(Qt::AlignCenter);
    lbl_username_p2->setParent(this);
    lbl_username_p2->show();
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
}


void game::slo_active_card_click()
{
    timer->start(10000);
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
    timer->stop();
    seconds_counter->stop();
    if(timerCountdown < 11)
    {
        timerCountdown = 11;
        lbl_seconds_counter->hide();
        lbl_text_dialog->hide();
        delete lbl_seconds_counter;
        delete lbl_text_dialog;
    }
    int s = player1.cards.size();
    for (int i = 0 ; i < s ; i++)
    {
        player1.cards[i]->setEnabled(false);
    }
}

void game::slo_selected_p1_card_btn(customized_button* input)
{
    timer->stop();
    seconds_counter->stop();
    if(timerCountdown < 11)
    {
        timerCountdown = 11;
        lbl_seconds_counter->hide();
        lbl_text_dialog->hide();
        delete lbl_seconds_counter;
        delete lbl_text_dialog;
    }
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
    if(turn == p2)
    {

        connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_compare_two_cards()));
    }
    emit sig_send_one_card(input->get_btn_card());
}


void game::slo_selected_p2_card_btn()
{
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
            game_win();
        }
    }
}


void game::game_win()
{
    ui->btn_change->hide();
    ui->btn_exit->hide();
    ui->btn_stop->hide();
    QLabel* lbl_logo = new QLabel(this);
    lbl_logo = new QLabel(this);
    lbl_logo->setParent(ui->centralwidget);
    QPixmap pixmap(":/photos/game logo.png");
    lbl_logo->setPixmap(pixmap);
    lbl_logo->raise();
    lbl_logo->show();
    QLabel* lbl_win = new QLabel(this);
    QFont win_font = lbl_win->font();
    win_font.setPointSize(70);
    win_font.setBold(true);
    win_font.setFamily("Tempus Sans ITC");
    lbl_win->setFont(win_font);
    lbl_win->setAlignment(Qt::AlignCenter);
    lbl_win->setParent(this);
    QLabel* lbl_coin = new QLabel(this);
    QLabel* lbl_coin2 = new QLabel(this);
    QPixmap pixmap2(":/photos/coin.png");
    lbl_coin->setPixmap(pixmap2);
    lbl_coin2->setPixmap(pixmap2);
    QPropertyAnimation* animation = new QPropertyAnimation(lbl_logo,"geometry");
    QPropertyAnimation* animation1u = new QPropertyAnimation(lbl_username_p1,"geometry");
    QPropertyAnimation* animation1s = new QPropertyAnimation(lbl_score_p1,"geometry");
    QPropertyAnimation* animation2u = new QPropertyAnimation(lbl_username_p2,"geometry");
    QPropertyAnimation* animation2s = new QPropertyAnimation(lbl_score_p2,"geometry");
    all_move_animation.append(animation);
    all_move_animation.append(animation1u);
    all_move_animation.append(animation1s);
    all_move_animation.append(animation2u);
    all_move_animation.append(animation2s);
    animation->setStartValue(QRect(width()/2-325,-100,650,375));
    animation->setEndValue(QRect(width()/2-325,50,650,375));
    QRect temp1u = lbl_username_p1->geometry();
    QRect temp1s = lbl_score_p1->geometry();
    QRect temp2u = lbl_username_p2->geometry();
    QRect temp2s = lbl_score_p2->geometry();
    animation1u->setStartValue(temp1u);
    animation1s->setStartValue(temp1s);
    animation2u->setStartValue(temp2u);
    animation2s->setStartValue(temp2s);
    if ((player1.score > player2.score) || p2_exit == true)
    {
        winner = p1;
        person1.set_coin(person1.get_coin()+100);
        update_file();
        lbl_win->setText("YOU WIN !");
        lbl_win->setStyleSheet("QLabel {color: green;}");
        animation1u->setEndValue(QRect(width()/2-500,450,600,70));
        animation1s->setEndValue(QRect(width()/2-100,450,600,70));
        animation2u->setEndValue(QRect(width()/2-500,500,600,70));
        animation2s->setEndValue(QRect(width()/2-100,500,600,70));
    }
    else if(player2.score > player1.score)
    {
        winner = p2;
        lbl_win->setText("YOU LOSE !");
        lbl_win->setStyleSheet("QLabel {color: red;}");
        animation2u->setEndValue(QRect(width()/2-500,450,600,70));
        animation2s->setEndValue(QRect(width()/2-100,450,600,70));
        animation1u->setEndValue(QRect(width()/2-500,500,600,70));
        animation1s->setEndValue(QRect(width()/2-100,500,600,70));
    }
    else
    {
        winner = status::equal;
        person1.set_coin(person1.get_coin()+50);
        update_file();
        lbl_win->setText("Draw !");
        lbl_win->setStyleSheet("QLabel {color: yellow;}");
        animation1u->setEndValue(QRect(width()/2-500,450,600,70));
        animation1s->setEndValue(QRect(width()/2-100,450,600,70));
        animation2u->setEndValue(QRect(width()/2-500,500,600,70));
        animation2s->setEndValue(QRect(width()/2-100,500,600,70));
    }
    update_history();
    lbl_win->show();
    lbl_coin->show();
    lbl_coin2->show();
    QPropertyAnimation* animationw = new QPropertyAnimation(lbl_win,"geometry");
    all_move_animation.append(animationw);
    animationw->setStartValue(QRect(width()/2-300,height(),600,100));
    animationw->setEndValue(QRect(width()/2-300,590,600,100));
    QPropertyAnimation* animationc = new QPropertyAnimation(lbl_coin,"geometry");
    all_move_animation.append(animationc);
    animationc->setStartValue(QRect(width()/2-380,height(),100,100));
    animationc->setEndValue(QRect(width()/2-380,590,100,100));
    QPropertyAnimation* animationc2 = new QPropertyAnimation(lbl_coin2,"geometry");
    all_move_animation.append(animationc2);
    animationc2->setStartValue(QRect(width()/2+290,height(),100,100));
    animationc2->setEndValue(QRect(width()/2+290,590,100,100));
    lbl_win->raise();
    animation->setDuration(700);
    animationw->setDuration(700);
    animationc->setDuration(700);
    animationc2->setDuration(700);
    animation1u->setDuration(700);
    animation1s->setDuration(700);
    animation2u->setDuration(700);
    animation2s->setDuration(700);
    animation->start();
    animationw->start();
    animationc->start();
    animationc2->start();
    animation1u->start();
    animation1s->start();
    animation2u->start();
    animation2s->start();
    connect(all_move_animation[all_move_animation.size()-1],SIGNAL(finished()),this,SLOT(slo_back_to_main()));
}


void game::update_file()
{
    QFile file("account.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream in(&file);
        QString username , password , name , phone , email , temp;
        int coin;
        while(!in.atEnd())
        {
            in >> username >>
                password >>
                name >>
                phone >>
                email >>
                coin >>
                temp;
            if (username == person1.get_username())
            {
                continue;
            }
            if (username == "" || password == "" || name == "" || phone == "" || email == "")
            {
                break;
            }
            person temp ;
            temp.set_username(username);
            temp.set_password(password);
            temp.set_name(name);
            temp.set_phone(phone);
            temp.set_email(email);
            temp.set_coin(coin);
            people.append(temp);
        }
    }
    file.close();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream out(&file);
        for (int i = 0 ; i < people.size() ; i++)
        {
            out << people[i].get_username() << '\n'
                << people[i].get_password() << '\n'
                << people[i].get_name() << '\n'
                << people[i].get_phone() << '\n'
                << people[i].get_email() << '\n'
                << people[i].get_coin() << '\n'
                << "----------------------------------------------------" << '\n';
        }
    }
    file.close();
    people.clear();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream out(&file);
        out << person1.get_username() << '\n'
            << person1.get_password() << '\n'
            << person1.get_name() << '\n'
            << person1.get_phone() << '\n'
            << person1.get_email() << '\n'
            << person1.get_coin() << '\n'
            << "----------------------------------------------------" << '\n';

    }
    file.close();
    QFile gamer_file("gamer.txt");
    if(!gamer_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream outg(&gamer_file);
        outg << person1.get_username() << '\n' <<
            person1.get_password() << '\n' <<
            person1.get_name() << '\n' <<
            person1.get_phone() << '\n' <<
            person1.get_email() << '\n' <<
            person1.get_coin() ;
    }
}


void game::update_history()
{
    int coin = 0 , win_number = 0 , lose_number = 0 , draw_number = 0 ;
    QString username = "----------" , p2_username_1 = "----------", p2_username_2 = "----------", p2_username_3 = "----------",
        win_lose1 = "-----", win_lose2 = "-----" , win_lose3 = "-----";
    int p1_card_1 = 100 , p1_card_2 = 100 , p1_card_3 = 100 , p2_card_1 = 100 , p2_card_2 = 100 , p2_card_3 = 100 ;
    QFile history_file(person1.get_username()+".txt");
    if(history_file.exists())
    {
        if(!history_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"ERROR !","The operation was not successful !");
            exit(13);
        }
        else
        {
            QTextStream in(&history_file);
            in >> coin >>
                username >>
                win_number >>
                lose_number >>
                draw_number >>
                p2_username_1 >>
                win_lose1 >>
                p1_card_1 >>
                p2_card_1
                >> p2_username_2 >>
                    win_lose2 >>
                    p1_card_2 >>
                    p2_card_2
                >>p2_username_3 >>
                    win_lose3 >>
                    p1_card_3 >>
                    p2_card_3 ;
        }
        history_file.close();
    }
    p2_username_3 = p2_username_2;
    p2_username_2 = p2_username_1;
    p2_username_1 = player2.get_username();
    win_lose3 = win_lose2;
    win_lose2 = win_lose1;
    switch(winner)
    {
    case p1:
        win_lose1 = "Win";
        win_number++;
        break;
    case p2:
        win_lose1 = "Lose";
        lose_number++;
        break;
    case status::equal:
        win_lose1 = "Draw";
        draw_number++;
        break;
    }
    int s = player1.win_cards.size();
    p1_card_3 = p1_card_2;
    p1_card_2 = p1_card_1;
    p1_card_1 = player1.win_cards[s-2]->get_btn_card().get_number();
    p2_card_3 = p2_card_2;
    p2_card_2 = p2_card_1;
    p2_card_1 = player1.win_cards[s-1]->get_btn_card().get_number();
    if(!history_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"ERROR !","The operation was not successful !");
        exit(13);
    }
    else
    {
        QTextStream out(&history_file);
        out << person1.get_coin() << '\n' <<
            person1.get_username() << '\n' <<
            win_number << '\n' <<
            lose_number << '\n' <<
            draw_number << '\n' <<
            p2_username_1 << '\n' <<
            win_lose1 << '\n' <<
            p1_card_1 << '\n' <<
            p2_card_1
            << '\n' << p2_username_2 << '\n' <<
            win_lose2 << '\n' <<
            p1_card_2 << '\n' <<
            p2_card_2
            << '\n' << p2_username_3 << '\n' <<
            win_lose3 << '\n' <<
            p1_card_3 << '\n' <<
            p2_card_3 ;
    }
    history_file.close();
}


void game::slo_back_to_main()
{
    Sleep(5000);
    this->close();
    par->show();
}


void game::on_btn_change_clicked()
{
    if(player1.get_forecast_number() == -1 || player2.get_forecast_number() == -1)
    {
        QMessageBox::information(this,"Skull King","You can't now ! Please try again after you and other player have selected your forecast number");
    }
    else if(player1.get_selected_card_btn() != nullptr || player2.get_selected_card_btn() != nullptr)
    {
        QMessageBox::information(this,"Skull King","A player has selected a card ! please wait .");
    }
    else if(r > 0 && r < 8)
    {
        emit sig_change_card();
    }
}

void game::on_btn_stop_clicked()
{
    if(stop == false && n_stopped < 2)
    {
       stop = true;
       n_stopped++;
       ui->btn_stop->setText("Resume");
       emit sig_stop();

       ui->btn_change->setEnabled(false);
       ui->btn_exit->setEnabled(false);
       inactive_card_click();
       stop_spy->wait(10000);

       if(stop == true)
       {
            stop = false;
            ui->btn_stop->setText("Stop");
            emit sig_resume();

            ui->btn_change->setEnabled(true);
            ui->btn_exit->setEnabled(true);
            if((turn == p1 && player1.get_selected_card_btn() == nullptr ) || (turn == p2 && player2.get_selected_card_btn() != nullptr))
            {
                if(r == 0)
                {
                   slo_active_card_click();
                }
                else if (turn == p1 &&  player1.get_forecast_number() != -1)
                {
                   slo_active_card_click();
                }
                else if(turn == p2)
                {
                   slo_active_card_click();
                }
            }
        }
    }
    else if(stop == true)
    {
       stop = false;
       ui->btn_stop->setText("Stop");
       emit sig_resume();
       emit sig_timeout();

       ui->btn_change->setEnabled(true);
       ui->btn_exit->setEnabled(true);
       if((turn == p1 && player1.get_selected_card_btn() == nullptr ) || (turn == p2 && player2.get_selected_card_btn() != nullptr))
       {
            if(r == 0)
            {
                slo_active_card_click();
            }
            else if (turn == p1 &&  player1.get_forecast_number() != -1)
            {
                slo_active_card_click();
            }
            else if(turn == p2)
            {
                slo_active_card_click();
            }
       }
    }
    else if(stop == false && n_stopped >= 2)
    {
       QMessageBox::information(this,"Stop","You cannot stop the game anymore !");
    }
}
void game::on_btn_exit_clicked()
{
    QMessageBox msbox(this);
    msbox.setText("Are you sure ?");
    QPushButton *cancel = msbox.addButton(tr("Cancel"),QMessageBox::ActionRole);
    QPushButton *exit = msbox.addButton(tr("Exit"),QMessageBox::ActionRole);
    msbox.exec();
    if(msbox.clickedButton() == cancel)
    {
       msbox.close();
    }
    else if(msbox.clickedButton() == exit)
    {
       timer->stop();
       seconds_counter->stop();
       if(timerCountdown < 11)
       {
            timerCountdown = 11;
            lbl_seconds_counter->hide();
            lbl_text_dialog->hide();
            delete lbl_seconds_counter;
            delete lbl_text_dialog;
       }
       emit sig_exit();
       msbox.close();
       Sleep(800);
       this->close();
       par->show();
    }
}

void game::slo_stop()
{
    ui->btn_change->setEnabled(false);
    ui->btn_exit->setEnabled(false);
    ui->btn_stop->setEnabled(false);
    inactive_card_click();
}
void game::slo_resume()
{
    ui->btn_change->setEnabled(true);
    ui->btn_exit->setEnabled(true);
    ui->btn_stop->setEnabled(true);
    if((turn == p1 && player1.get_selected_card_btn() == nullptr ) || (turn == p2 && player2.get_selected_card_btn() != nullptr))
    {
       if(r == 0)
       {
            slo_active_card_click();
       }
       else if (turn == p1 &&  player1.get_forecast_number() != -1)
       {
            slo_active_card_click();
       }
       else if(turn == p2)
       {
            slo_active_card_click();
       }
    }
}

void game::slo_exit()
{
    timer->stop();
    seconds_counter->stop();
    if(timerCountdown < 11)
    {
       timerCountdown = 11;
       lbl_seconds_counter->hide();
       lbl_text_dialog->hide();
       delete lbl_seconds_counter;
       delete lbl_text_dialog;
    }
    player1.hide_cards();
    player1.hide_win_cards();
    player2.hide_cards();
    player2.hide_win_cards();
    p2_exit = true;
    QMessageBox::information(this,"Exit","Player 2 left the game !");
    game_win();
}

void game::slo_time_warning()
{
    timerCountdown--;
    lbl_seconds_counter = new QLabel(this);
    lbl_seconds_counter->setGeometry(QRect(width()/2-50,height()/2-30,100,100));
    lbl_seconds_counter->setText(QString::number(timerCountdown));

    lbl_text_dialog = new QLabel(this);
    lbl_text_dialog->setGeometry(QRect(width()/2-200,height()/2-100,400,100));
    lbl_text_dialog->setText("You must choose a card !");

    QFont font = lbl_text_dialog->font();
    font.setPointSize(20);
    font.setBold(true);
    font.setFamily("Tempus Sans ITC");
    lbl_seconds_counter->setFont(font);
    lbl_seconds_counter->setAlignment(Qt::AlignCenter);
    lbl_seconds_counter->setParent(this);
    lbl_seconds_counter->setStyleSheet("QLabel {color: red;}");
    lbl_seconds_counter->show();
    lbl_text_dialog->setFont(font);
    lbl_text_dialog->setAlignment(Qt::AlignCenter);
    lbl_text_dialog->setParent(this);
    lbl_text_dialog->setStyleSheet("QLabel {color: red;}");
    lbl_text_dialog->show();

    seconds_counter->start(1000);
}

void game::slo_countdown()
{
    timerCountdown--;
    lbl_seconds_counter->setText(QString::number(timerCountdown));
    if (timerCountdown == 1) {
       int s = player1.cards.size();
       for (int j = 0 ; j < s ; j++)
       {
            if(player1.cards[j]->isEnabled() == true)
            {
            emit player1.cards[j]->clicked(true);
            break;
            }
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
