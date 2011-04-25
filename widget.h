#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QStringList>
#include <QDir>


namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);
    //void resizeEvent(QResizeEvent *);

private:
    Ui::Widget *ui;
    QPixmap *p;
    QPixmap pix;
    QTimer *timer;
    QStringList picturePath;
    int current,i;
    int max;
    QString picture;

    QStringList findFiles(const QDir &);
    //实现文件的查找并返回符合条件的文件列表
    void tranvFolder(const QDir &);
    void showFiles(const QDir&, const QStringList&);


    //QRect m_ImageRect;
protected slots:
    void showPicture();
    void setDisplayTime();

    void browse();
};

#endif // WIDGET_H
