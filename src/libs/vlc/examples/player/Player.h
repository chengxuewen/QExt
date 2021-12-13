#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>

namespace Ui
{
    class Player;
}

class QEXTVLCInstance;
class QEXTVLCMedia;
class QEXTVLCMediaPlayer;

class Player : public QMainWindow
{
    Q_OBJECT
public:
    explicit Player(QEXTVLCInstance *instance, QWidget *parent = 0);
    ~Player();

private:
    Ui::Player *ui;
    QEXTVLCInstance *m_instance;
    QEXTVLCMedia *m_media;
    QEXTVLCMediaPlayer *m_player;
};

#endif // PLAYER_H
