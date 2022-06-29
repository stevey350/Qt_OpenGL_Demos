#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_act_draw_graph_triggered()
{
    ui->openGLWidget->draw_shape(MyOpenGLWidget::Rect);
}


void MainWindow::on_act_clean_graph_triggered()
{
    ui->openGLWidget->draw_shape(MyOpenGLWidget::None);
}


void MainWindow::on_act_wire_frame_triggered()
{
    ui->openGLWidget->set_wire_frame(ui->act_wire_frame->isChecked());
}

