#include "fifteen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://image/icon_fifteen.png"));
    Fifteen w;
    w.setFixedSize(580,536);

    QPixmap bkgnd("://image/back.png");
    bkgnd = bkgnd.scaled(w.size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    w.setPalette(palette);
    w.show();

    return a.exec();
}
