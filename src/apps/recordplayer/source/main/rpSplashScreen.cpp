#include "rpSplashScreen.h"

#include <QDebug>

RPSplashScreen::RPSplashScreen()
    : QSplashScreen{QPixmap(), Qt::WindowStaysOnTopHint}
{
    auto pixmap = QPixmap(":/images/RecordPlayer_Logo.png");
    auto size = pixmap.size();
    auto ratio = 800.0 / size.width();
    auto scaledSize = QSize(800, size.height() * ratio);
    auto scaledPixmap = pixmap.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(scaledPixmap);
    this->setFixedHeight(scaledPixmap.height() + 30);
}

void RPSplashScreen::drawContents(QPainter *painter)
{
    QFont font("Microsoft YaHei UI");
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(this->rect(), Qt::AlignHCenter | Qt::AlignBottom, this->message());
    // QSplashScreen::drawContents(painter);
}
