#include "records.h"
#include "ui_records.h"

records::records(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::records)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    FillTable();
}

records::~records()
{
    delete ui;
}

void records::FillTable()
{
    QFile rec_file("D:\\FifteenGame\\records.txt");
    QString str;
    int i=0;
    if(rec_file.open(QIODevice::ReadOnly))
    {
        while(!rec_file.atEnd())
        {
            str = rec_file.readLine();
            str.chop(2);
            ui->tableWidget->setItem(0,i++,new QTableWidgetItem(str));
        }
    }

}


