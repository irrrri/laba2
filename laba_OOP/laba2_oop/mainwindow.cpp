#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char* QstringToCharArray(QString qstr)
{
    char *str = (char*)malloc(sizeof(char)*(qstr.size() + 1));
    int i;
    for (i = 0; i < qstr.size(); i++)
    {
        str[i] = qstr.at(i).unicode();
    }
    str[i] = 0;
    return str;
}

QString ConvertRowToQTFormat(char *row)
{
    QString string = {};
    string.append(QString::fromUtf8(row));
    return string;
}

void MainWindow::on_fileDialog_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open File"), "D://");
    ui->labelFileName->setText(FileName);
    if (FileName.isEmpty())
        QMessageBox::warning(this, "error", "file can't be opened");
    else{
        fileWork fw(QstringToCharArray(FileName));
        fw.readData();
        checking ch(fw.getStr());
        try
        {
            QString Qstr;
            for (int i = 0; i < ch.getStr().length(); i++)
                Qstr.append(QString(ch.getStr()[i]));
            ui->jsonLabel->setText(Qstr);
            ch.checkValue1(ch.getStr());
            ui->errorLabel->setText("File is correct!!!");
            ui->placeLabel->setText(" ");
        }
        catch (checking::JsonException& in_ar)
        {
            ui->errorLabel->setText(QString::fromStdString(in_ar.getMessage()));
            ui->placeLabel->setText(QString::number(in_ar.getPlace()));
        }
    }
}



