#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(600,400);
    ui->pictureLabel->setAlignment(Qt::AlignCenter);
    ui->timeSpinBox->setRange(3,20);
    ui->timeSpinBox->setValue(5);

    connect(ui->timeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setDisplayTime()));
    timer=new QTimer(this);
    p=new QPixmap;

    current=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(showPicture()));

    i=ui->timeSpinBox->value();
    connect(ui->browseBtn,SIGNAL(clicked()),this,SLOT(browse()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    ui->pictureLabel->setAlignment(Qt::AlignCenter);
    ui->pictureLabel->setPixmap(pix);
}

void Widget::showPicture()
{

    qreal width=p->width();
    qreal height=p->height();


    if(current<=max)
    {

        p->load(picturePath.at(current));
        if((width/400)>(height/300))
        {
            pix=p->scaled(width*400/width,height*400/width,Qt::KeepAspectRatio);
        }
        else
        {
            pix=p->scaled(width*300/height,height*300/height,Qt::KeepAspectRatio);
        }
        current++;
        update();
    }
    else
    {
        current=0;

        p->load(picturePath.at(0));
        if((width/400)>(height/300))
        {
            pix=p->scaled(width*400/width,height*400/width,Qt::KeepAspectRatio);
        }
        else
        {
            pix=p->scaled(width*300/height,height*300/height,Qt::KeepAspectRatio);
        }
        update();
    }

}

void Widget::setDisplayTime()
{
    i=ui->timeSpinBox->value();
    timer->start(i*1000);
}

void Widget::browse()
{
    QString filedir=QFileDialog::getExistingDirectory(this,tr("«Î—°‘Ò≤È’“¬∑æ∂"),
                  QDir::currentPath(),QFileDialog::ShowDirsOnly);
    if(!filedir.isEmpty())
    {
        QDir dir=QDir(filedir);
        tranvFolder(dir);
        if(max<0)
            return;
        timer->start(i*1000);
    }
    else
        return;
}

void Widget::tranvFolder(const QDir &dir)
{
    QStringList folders;
    folders = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < folders.size(); ++i)
    {
        qApp->processEvents();
        QString strDir = QString("%1/%2").arg(dir.absolutePath()).arg(folders[i]);
        tranvFolder(strDir);
    }
    QStringList files = findFiles(dir);
    showFiles(dir, files);
}

QStringList Widget::findFiles(const QDir &dir)
{
    QStringList filters;
    filters<<"*.jpg"<<"*.bmp"<<"*.jpeg"<<".png"<<"*.xpm";
    QStringList files = dir.entryList(filters);
    return files;
}

void Widget::showFiles(const QDir &dir, const QStringList &files)
{
    for (int i = 0; i < files.size(); ++i)
    {
        QString strFilePath = dir.absoluteFilePath(files[i]);
        picturePath<<strFilePath;
    }
    max=picturePath.count()-1;
}







