/*Автоматически созданный на основе графического интерфейса файл, содержащий объявление слотов(функций, которые активируются
при нажати на кнопку или иной элемент в интефейсе программы*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bintree.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_5_triggered();

    void on_checkBox_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

private:
    int** FindGamilton(INCTR* grandparent, INCTR* parent, int peaks, int step, int cycle, int** gampath); //Функция добавлена вручную для получения доступа к текстовым полям интерфейса
    void createUI(const QStringList &headers);
};

#endif // MAINWINDOW_H
