#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <iostream>

#include "Chessboard.h"
#include "Setting.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *e);

        Ui::MainWindow *ui;
    protected slots:
        void move();

    private slots:
        void on_startgame_clicked();

        void on_replay_clicked();

       signals:
            void end();

    private:
        QTimer* timer;
        Chessboard _chessboard;
};
#endif // MAINWINDOW_H
