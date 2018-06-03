#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aboutwindow.h"
#include "HelpBrowser.h"
#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include "graph.h"

namespace Ui {
class MainWindow;
}

class Graph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QCoreApplication* app;
    ~MainWindow();
    void update_matr();
    int get_speed();

public slots:


protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void on_exit_action_triggered();

    void on_matrButton_clicked();

    void on_addNodeButton_clicked();

    void on_deleteNodeButton_clicked();

    void on_AddEdge_clicked();

    void on_DeleteEdgeButton_clicked();

    void on_ClearButton_clicked();

    void on_open_action_triggered();

    void on_save_action_triggered();

    void on_gravityBox_stateChanged(int arg1);

    void on_colorButton_clicked();

    void on_shuffleButton_clicked();

    void on_desButton_clicked();

    void on_weighBox_stateChanged(int arg1);

    void on_save_pos_action_triggered();

    void on_checkBox_stateChanged(int arg1);

    void on_about_action_triggered();

    void on_help_action_triggered();

    void on_Deicstra_clicked();

    void DeicstraResult(int* data);

    void on_Ford_clicked();

    void on_FlowBox_stateChanged(int arg1);

private:
    Graph* gr1;
    Ui::MainWindow *ui;
    QTimer* timer;
};

#endif // MAINWINDOW_H
