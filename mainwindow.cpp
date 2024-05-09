#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_pushButton_clicked()
{
    HelpPuzzle *helpPuzzle = new HelpPuzzle();
    helpPuzzle->show();
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
