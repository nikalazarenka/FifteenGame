#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>

namespace Ui {
class records;
}

class records : public QWidget
{
    Q_OBJECT

public:
    explicit records(QWidget *parent = nullptr);
    ~records();

private:
    Ui::records *ui;

private:
    void FillTable();

};

#endif // RECORDS_H
