#ifndef _RPSPLASHSCREEN_H
#define _RPSPLASHSCREEN_H

#include <QPainter>
#include <QSplashScreen>

class RPSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit RPSplashScreen();

protected:
    void drawContents(QPainter *painter) override;
};

#endif // _RPSPLASHSCREEN_H
