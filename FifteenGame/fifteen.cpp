#include "fifteen.h"
#include "ui_fifteen.h"

#include<QMessageBox>

Fifteen::Fifteen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fifteen)
{
    ui->setupUi(this);

    myTime = new QTime(0,0);
    timer = new QTimer();
    timer->setInterval(1000);

    MyFont.setPointSize(36);

    move_count = 0;
    btn_width = 90;
    btn_height = 90;

    ui->gridLayout->setVerticalSpacing(5);
    ui->gridLayout->setHorizontalSpacing(5);

    vec_btn = {ui->btn1, ui->btn2, ui->btn3, ui->btn4, ui->btn5,
               ui->btn6, ui->btn7, ui->btn8, ui->btn9, ui->btn10,
               ui->btn11, ui->btn12, ui->btn13, ui->btn14, ui->btn15};
    vec_num = {"1", "2", "3", "4", "5", "6", "7", "8",
               "9", "10", "11", "12", "13", "14", "15"};

    SetNormalSize();

    foreach (QPushButton * btn, vec_btn)
    {
        connect(btn, SIGNAL(clicked()), this, SLOT(Move()));
    }

    hlp = new help;
    rcrd = new records;
}

Fifteen::~Fifteen()
{
    delete ui;
}

void Fifteen::CurrentImage()
{
    num_rows = sqrt((vec_btn.size())+1);
    img_width = original.width();
    img_height = original.height();
    if(img_width < img_height)
    {
        step = img_width/num_rows;
    }
    else
    {
        step = img_height/num_rows;
    }
    max_width = step * (num_rows - 1);

    for(int i = 0; i<=max_width; i+=step)
    {
        for(int j = 0; j<=max_width; j+=step)
        {
            cropped.push_back(original.copy(QRect(j, i, step, step)));
        }
    }
}

void Fifteen::ImageOnBtn()
{
    CurrentImage();
    for(int k = 0; k < vec_btn.size(); k++)
    {
        vec_btn[k]->setText("");
        vec_btn[k]->setIcon(cropped[k]);
        vec_btn[k]->setIconSize(QSize(btn_width, btn_height));
    }
}

void Fifteen::NumberOnBtn()
{
    MyFont.setBold(true);
    for(int i = 0; i < vec_btn.size(); i++)
    {
        vec_btn[i]->setIconSize(QSize(0, 0));
        vec_btn[i]->setText(vec_num[i]);
        vec_btn[i]->setFont(MyFont);
    }
}

void Fifteen::ShuffleVecBtn()
{
    int tempXFirst;
    int tempYFirst;
    int tempXSecond;
    int tempYSecond;
    int rand_num;
    int rand_special_pos;

    srand(time(NULL));

    timer->start(10);

    rand_special_pos = rand()%(vec_btn.size()-1);
    for(int i = 0; i < vec_btn.size(); i++)
    {
        if(i == rand_special_pos)
            continue;
        do
        rand_num = rand()%(vec_btn.size()-1);
        while(rand_num == i);

        tempXFirst = vec_btn[i]->x();
        tempYFirst = vec_btn[i]->y();
        tempXSecond = vec_btn[rand_num]->x();
        tempYSecond = vec_btn[rand_num]->y();

        vec_btn[i]->setGeometry(tempXSecond, tempYSecond, btn_width, btn_height);
        vec_btn[rand_num]->setGeometry(tempXFirst, tempYFirst, btn_width, btn_height);
    }
    for(int i = 0; i < vec_btn.size(); i++) //чтобы пустая ячейка была статична
    {
        if((vec_btn[i]->x() == ((btn_width + ui->gridLayout->verticalSpacing())*3 + ui->gridLayout->margin()))
                && (vec_btn[i]->y() == ((btn_height + ui->gridLayout->horizontalSpacing())*3 + ui->gridLayout->margin())))
        {
            vec_btn[i]->setGeometry(legal_coord.first,  legal_coord.second, btn_width, btn_height);
            legal_coord.first = (btn_width + ui->gridLayout->verticalSpacing())*3 + ui->gridLayout->margin();
            legal_coord.second = (btn_height + ui->gridLayout->horizontalSpacing())*3 + ui->gridLayout->margin();
        }
    }
}

void Fifteen::MakeRecord()
{
    QFile file_records("D:\\FifteenGame\\records.txt");
    if(file_records.open(QIODevice::Append|QIODevice::Text))
    {
        QTextStream writeRecStream (&file_records);
        writeRecStream << QString("%1\t").arg(move_count) + myTime->toString() + QString("\n");
        file_records.close();
    }
}

bool Fifteen::GameIsSolved()
{
    bool result=false;
//    int x=3,y=3;
//     for(int i = 0; i < vec_btn.size(); i++,x+=95)
//     {
//         if(i%4==0)
//         {
//             y+=95;
//             x=3;
//         }
//         if(vec_btn[i]->x()==x && vec_btn[i]->y()==y)
//             result =true;
//         else
//         {
//             result =false;
//         }

//     }
    if((ui->btn1->x()==3 && ui->btn1->y()==3) && (ui->btn2->x()==98 && ui->btn2->y()==3) && (ui->btn3->x()==193 && ui->btn3->y()==3) && (ui->btn4->x()==288 && ui->btn4->y()==3)
            && (ui->btn5->x()==3 && ui->btn5->y()==98) && (ui->btn6->x()==98 && ui->btn6->y()==98) && (ui->btn7->x()==193 && ui->btn7->y()==98) && (ui->btn8->x()==288 && ui->btn8->y()==98)
            && (ui->btn9->x()==3 && ui->btn9->y()==193) && (ui->btn10->x()==98 && ui->btn10->y()==193) && (ui->btn11->x()==193 && ui->btn11->y()==193) && (ui->btn12->x()==288 && ui->btn11->y()==193)
            && (ui->btn13->x()==3 && ui->btn13->y()==288) && (ui->btn14->x()==98 && ui->btn14->y()==288) && (ui->btn15->x()==193 && ui->btn15->y()==288))
        result=true;

    return result;
}

void Fifteen::SetNormalSize()
{
    if(ui->levelBox->currentText() == "Классическая игра")
    {
        NumberOnBtn();
    }
    else
    {
        ImageOnBtn();
    }

    foreach (auto var, vec_btn)
    {
        var->setFixedWidth(btn_width);
        var->setFixedHeight(btn_height);
    }

    legal_coord.first = (btn_width + ui->gridLayout->verticalSpacing())*3 + ui->gridLayout->margin();
    legal_coord.second = (btn_height + ui->gridLayout->horizontalSpacing())*3 + ui->gridLayout->margin();

    gridLayout_width = btn_width * 4 + ui->gridLayout->spacing();
    gridLayout_height = btn_height * 4 + ui->gridLayout->spacing();

}

void Fifteen::Move()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(((btn->x() == legal_coord.first) || (btn->y() == legal_coord.second))
            && (abs(btn->x() - legal_coord.first) <= (btn_height + ui->gridLayout->spacing()))
            && (abs(btn->y() - legal_coord.second) <= (btn_width + ui->gridLayout->spacing())))
    {
        move_count++;
        ui->count->setText(QString::number(move_count));
        int tempX = legal_coord.first;
        int tempY = legal_coord.second;
        legal_coord.first = btn->x();
        legal_coord.second = btn->y();
        btn->setGeometry(tempX, tempY, btn_width, btn_height);
    }

    if(GameIsSolved()){
        timer->stop();

        QMessageBox mbox;
        mbox.setText(QString("Победа!!!\nПроделано шагов: %1\nЗатраченное время: ").arg(move_count)+myTime->toString());
        mbox.exec();

        ui->btn_shufle->setText("СТАРТ");

        MakeRecord();
        rcrd = new records;
    }
}

void Fifteen::on_btn_shufle_clicked()
{
    delete timer;
    myTime = new QTime(0,0);
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    ui->btn_shufle->setText("ПЕРЕМЕШАТЬ");
    move_count = 0;
    ui->count->setText(QString::number(move_count));
    ShuffleVecBtn();
}

void Fifteen::on_levelBox_currentTextChanged(const QString &arg1)
{
    cropped.clear();
    if(arg1 == "Ночной фонарь")
    {
        original = QPixmap("://image/lamp.png");
        ImageOnBtn();
    }
    else if(arg1 == "Весенний кот")
    {
       original = QPixmap("://image/cat.png");
       ImageOnBtn();
    }
    else if(arg1 == "Рим")
    {
        original = QPixmap("://image/rome.png");
        ImageOnBtn();
    }
    else if(arg1 == "Летний кот")
    {
        original = QPixmap("://image/cat_1.png");
        ImageOnBtn();
    }
    else if(arg1 == "Шрек")
    {
        original = QPixmap("://image/shrek.png");
        ImageOnBtn();
    }
    else if(arg1 == "Кролик")
    {
        original = QPixmap("://image/rabbit.png");
        ImageOnBtn();
    }
    else if(arg1 == "Корги")
    {
        original = QPixmap("://image/corgi.png");
        ImageOnBtn();
    }
    else if(arg1 == "Суши")
    {
        original = QPixmap("://image/sushi.png");
        ImageOnBtn();
    }
    else if(arg1 == "Чизкейк")
    {
        original = QPixmap("://image/cheesecake.png");
        ImageOnBtn();
    }
    else if(arg1 == "Классическая игра")
    {
        NumberOnBtn();
    }
}

void Fifteen::UpdateTime()
{
    *myTime=myTime->addMSecs(10);
    ui->lbl_time->setText(myTime->toString());
}

void Fifteen::on_btn_exit_clicked()
{
    this->close();
}

void Fifteen::on_btn_manual_clicked()
{
    if(!hlp->isActiveWindow())
        hlp->show();
}

void Fifteen::on_btn_records_clicked()
{
    if(!rcrd->isActiveWindow())
        rcrd->show();
}
