#ifndef FIFTEEN_H
#define FIFTEEN_H

#include "ui_help.h"
#include "help.h"
#include "ui_records.h"
#include "records.h"

#include <QMainWindow>
#include <ctime>
#include <QVector>
#include <QString>
#include <QPair>
#include <QPushButton>
#include <QFont>
#include <QIcon>
#include <QRect>
#include <QPixmap>
#include <cmath>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
class Fifteen;
}

class Fifteen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fifteen(QWidget *parent = nullptr);
    ~Fifteen();

private:
    Ui::Fifteen *ui;
    QFont MyFont;

    QTime *myTime;
    QTimer *timer;

    help *hlp;
    records *rcrd;

    QVector<QPushButton*> vec_btn;
    QVector<QString> vec_num;
    QVector<QPixmap> cropped;
    QPair<int, int> legal_coord;
    QPixmap original;


    int btn_width;
    int btn_height;
    int gridLayout_width;
    int gridLayout_height;
    int move_count;

    int img_width;
    int img_height;
    int max_width;
    int step;
    int num_rows;

private:
    void SetNormalSize();
    void NumberOnBtn();
    void ImageOnBtn();
    void CurrentImage();
    void ShuffleVecBtn();
    void MakeRecord();
    bool GameIsSolved();

private slots:
    void Move();
    void UpdateTime();
    void on_btn_shufle_clicked();
    void on_levelBox_currentTextChanged(const QString &arg1);
    void on_btn_exit_clicked();
    void on_btn_manual_clicked();
    void on_btn_records_clicked();
};

#endif // FIFTEEN_H
