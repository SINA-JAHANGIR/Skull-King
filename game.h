#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QVector>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QSignalSpy>
#include <QEventLoop>
#include <QTimer>
#include "customized_button.h"
#include "card.h"
#include "player.h"
#include "person.h"
#include <QMediaPlayer>
#include <QtMultimedia>

enum status {p1,p2,equal};

namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(person,QMediaPlayer*,QWidget *parent = nullptr);
    ~game();
    // Functions :
    void game_server_start();
    void game_client_start();

private slots:
    void slo_arrange_card();
    void slo_p1_arrange_card();
    void slo_p2_arrange_card();
    void slo_forecast();
    void slo_active_num_click();
    void slo_selected_num_btn(int);
    void slo_active_card_click();
    void slo_selected_p1_card_btn(customized_button*);
    void slo_selected_p2_card_btn();
    void slo_compare_two_cards();
    void slo_hide_forecast_btn();
    void slo_rate_round();
    void slo_back_to_main();
    void on_btn_change_clicked();
    void on_btn_exit_clicked();
    void on_btn_stop_clicked();
    void slo_stop();
    void slo_resume();
    void slo_exit();
    void slo_time_warning();
    void slo_countdown();

signals:
    void sig_send_card();
    void sig_send_one_card(card);
    void sig_change_card();
    void sig_send_forecast();
    void sig_end_of_round();
    void sig_stop();
    void sig_resume();
    void sig_timeout();
    void sig_exit();
    void sig_end();

private:
    Ui::game *ui;
    // Property :
    card all_cards[56];
    customized_button * all_cards_btn[56];
    player player1;
    player player2;
    QVector<QPropertyAnimation *> all_move_animation;
    QVector<customized_button *> all_forecast_btn;
    customized_button* forecast_p1_btn = nullptr;
    customized_button* forecast_p2_btn = nullptr;
    status turn = p1;
    status hand_winner;
    status winner;
    QLabel* lbl_username_p1;
    QLabel* lbl_username_p2;
    QLabel* lbl_score_p1;
    QLabel* lbl_score_p2;
    int r = 0;
    bool first_flag = true;
    bool wait = true;
    QEventLoop loop;
    QEventLoop start;
    QWidget *par;
    person person1;
    QVector<person> people;
    QString last_cards_p1 , last_cards_p2;
    bool stop = false;
    int n_stopped = 0 ;
    bool p2_exit = false;
    QSignalSpy* stop_spy;
    QTimer* timer;
    QTimer* timer2;
    QTimer* seconds_counter;
    int timerCountdown = 11;
    QLabel* lbl_seconds_counter;
    QLabel* lbl_text_dialog;
    QMediaPlayer* first_music;
    QMediaPlayer* second_music;
    // Functions :
    void set_all_cards();
    void change_StyleSheet(customized_button*);
    void rasie_p2_cards();
    void rasie_p1_cards();
    void rasie_p1_win_cards();
    void rasie_p2_win_cards();
    void make_card(int);
    void dealer_animation();
    void sort_btn_cards(QVector<customized_button*>&);
    void clear_move_animations();
    void clear_all_forecast_btn();
    void inactive_num_click();
    void inactive_card_click();
    void hand_win();
    void game_win();
    void change_card();
    void update_file();
    void update_history();
    friend class client;
    friend class server;
};

#endif // GAME_H
