#ifndef _QEXTCANDIDATELISTWIDGET_H
#define _QEXTCANDIDATELISTWIDGET_H

#include <qextKeyboardGlobal.h>

#include <QWidget>

class QPushButton;
class QExtCandidatesListWidgetPrivate;
class QEXT_KEYBOARD_API QExtCandidatesListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QExtCandidatesListWidget(QWidget *parent = QEXT_NULLPTR);
    ~QExtCandidatesListWidget() QEXT_OVERRIDE;

Q_SIGNALS:
    void chooseText(int id);

public Q_SLOTS:
    void setCandidatesList(const QStringList & texts);
    void onNextPage();
    void onLastPage();
    void clear();

protected:
    void paintEvent(QPaintEvent * event) QEXT_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) QEXT_OVERRIDE;

    QScopedPointer<QExtCandidatesListWidgetPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtCandidatesListWidget)
    QEXT_DISABLE_COPY_MOVE(QExtCandidatesListWidget)
};

#endif // _QEXTCANDIDATELISTWIDGET_H
