#ifndef _QEXTGRAPHICSVIEW_H
#define _QEXTGRAPHICSVIEW_H

#include <qextGraphicsItems.h>

#include <QGraphicsView>

class QMouseEvent;

#define RULER_SIZE    16

class QEXT_GRAPHICS_API QtCornerBox : public QWidget
{
    Q_OBJECT
public:
    explicit QtCornerBox(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *);
};


class QEXT_GRAPHICS_API QtRuleBar : public QWidget
{
    Q_OBJECT
public:
    explicit QtRuleBar(Qt::Orientation direction, QGraphicsView * view, QWidget * parent = 0  );
    void setRange( double lower , double upper , double max_size );
    void updatePosition( const QPoint & pos );

protected:
    void paintEvent(QPaintEvent *event);
    void drawTicker(QPainter * painter);
    void drawPos(QPainter * painter);
    Qt::Orientation   m_direction;
    QPoint m_lastPos;
    QColor m_faceColor;
    QGraphicsView * m_view;

    double m_lower;
    double m_upper;
    double m_maxsize;
};


class QEXT_GRAPHICS_API DrawView : public QGraphicsView
{
    Q_OBJECT
public:
    DrawView(QGraphicsScene *scene);
    void zoomIn();
    void zoomOut();

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();

    QString currentFile() { return curFile; }
    void setModified( bool value ) { modified = value ; }
    bool isModified() const { return modified; }

signals:
    void positionChanged(int x , int y );

protected:
    void closeEvent(QCloseEvent *event) QEXT_OVERRIDE;

    void mouseMoveEvent(QMouseEvent * event) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_OVERRIDE;
    void scrollContentsBy(int dx, int dy) QEXT_OVERRIDE;
    void updateRuler();
    QtRuleBar *m_hruler;
    QtRuleBar *m_vruler;
    QtCornerBox * box;

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void loadCanvas( QXmlStreamReader *xml );
    QExtGraphicsItemGroup * loadGroupFromXML( QXmlStreamReader * xml );

    QString curFile;
    bool isUntitled;
    bool modified;
};

#endif // _QEXTGRAPHICSVIEW_H
