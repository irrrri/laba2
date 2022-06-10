#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <qmessagebox.h>

#include "filework.h"
#include "checking.h"
#include "filework.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileDialog_clicked();

    void on_checkBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
