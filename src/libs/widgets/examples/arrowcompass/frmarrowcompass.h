#ifndef FRMARROWCOMPASS_H
#define FRMARROWCOMPASS_H

#include <QWidget>

namespace Ui {
class FrmArrowCompass;
}

class FrmArrowCompass : public QWidget
{
    Q_OBJECT

public:
    explicit FrmArrowCompass(QWidget *parent = 0);
    ~FrmArrowCompass();

private:
    Ui::FrmArrowCompass *ui;

private slots:
    void initForm();
};

#endif // FRMARROWCOMPASS_H
