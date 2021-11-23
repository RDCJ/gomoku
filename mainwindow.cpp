#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _chessboard()
{
    ui->setupUi(this);
    ui->replay->setHidden(true);
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(this, SIGNAL(end()), ui->replay, SLOT(show()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::move()
{
    this->repaint();
    if (_chessboard.getState() != 0 && _chessboard.getState() != -2)
        emit end();
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter* pa;
    pa = new QPainter();
    pa->begin(this);
    this->_chessboard.show(pa);
    pa->end();
    delete pa;
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    double mx = e->x();
    double my = e->y();
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
        {
            int x = EDGE_SIZE + i * GRID_SIZE;
            int y = EDGE_SIZE + j * GRID_SIZE;
            if (abs(mx - x) < 16 && abs(my - y) < 16)
            {
                _chessboard.Player_Place(i, j);
                return;
            }
        }
}


void MainWindow::on_startgame_clicked()
{
    _chessboard.begin();
    timer->start(0);
    timer->setInterval(20);
}


void MainWindow::on_replay_clicked()
{
    _chessboard.begin();
}
