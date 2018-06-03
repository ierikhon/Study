#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"

#include <QTextStream>
#include <QByteArray>
#include <QInputDialog>
#include <QFileDialog>
#include <cstdlib>
#include <ctime>
#include <QTimer>

#include <QGraphicsScene>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gr1 = new Graph;
    gr1->widget = new GraphWidget(0, gr1, this);
    ui->graphicsView->setViewport(gr1->widget);
    srand(time(nullptr));
    timer = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_matr()
{
    on_matrButton_clicked();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    gr1->widget->keyPressEvent(event); //Передача управления виджету
}


void MainWindow::on_exit_action_triggered()
{
    exit(0); //Выход из программы
}

void MainWindow::on_matrButton_clicked() //Построение матрицы
{
    QString matr;
    QTextStream ms(&matr);
    gr1->Inc_Matr(ms);
    ui->incEdit->setPlainText(matr);
}

void MainWindow::on_addNodeButton_clicked() //Добавление вершины
{
    QString name = ui->NodeNameEdit->text();
    if (name.length() > Numb){
        QMessageBox msg;
        msg.setText("Name too Long");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    QByteArray arr = name.toLocal8Bit(); //Конвертация QString в char*
    char* cname = arr.data();
    if (!gr1->FindElem(cname))
        gr1->AddElem(cname);
    else{
        QMessageBox msg;
        msg.setText("Element Already Exists");
        msg.exec();
    }
    ui->NodeNameEdit->clear();
    on_matrButton_clicked(); //После каждой процедуры матрица обновляется
}

void MainWindow::on_deleteNodeButton_clicked() //Удаление вершины
{
    QString name = ui->NodeNameEdit->text();
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    if (gr1->FindElem(cname))
        gr1->RemoveElem(cname);
    else{
        QMessageBox msg;
        msg.setText("Element doesn't Exist");
        msg.exec();
    }
    ui->NodeNameEdit->clear();
    on_matrButton_clicked();
}

void MainWindow::on_AddEdge_clicked()
{
    QString name = ui->NodeNameEdit->text();
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    Elem* el1 = gr1->FindElem(cname);
    if (!el1){
        QMessageBox msg;
        msg.setText("First Element doesn't Exist");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    bool ok;
    QString name2 = QInputDialog::getText(this, "Add Connection", "Enter Name", QLineEdit::Normal, "", &ok);
    QByteArray arr2 = name2.toLocal8Bit();
    char* cname2 = arr2.data();
    Elem* el2 = gr1->FindElem(cname2);
    if (!el2){
        QMessageBox msg;
        msg.setText("Second Element doesn't Exist");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    int weight = 1;
    if (ui->weighBox->isChecked())
        weight = QInputDialog::getInt(this, "Add Connection", "Enter Weight", 1);
    if (!gr1->Is_Egde(el1, el2)){
        gr1->AddEdge(el1, el2, weight);
    }
    else{
        QMessageBox msg;
        msg.setText("Connection Already Exists");
        msg.exec();
    }
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
}

void MainWindow::on_DeleteEdgeButton_clicked() //Удаление ребра
{
    QString name = ui->NodeNameEdit->text();
    QByteArray arr = name.toLocal8Bit();
    char* cname = arr.data();
    Elem* el1 = gr1->FindElem(cname);
    if (!el1){
        QMessageBox msg;
        msg.setText("Element doesn't Exist");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    bool ok;
    QString name2 = QInputDialog::getText(this, "Delete Connection", "Enter Name", QLineEdit::Normal, "", &ok);
    QByteArray arr2 = name2.toLocal8Bit();
    char* cname2 = arr2.data();
    Elem* el2 = gr1->FindElem(cname2);
    if (!el2){
        QMessageBox msg;
        msg.setText("Second Element doesn't Exist");
        msg.exec();
        ui->NodeNameEdit->clear();
        return;
    }
    if (gr1->Is_Egde(el1, el2)){
        gr1->RemoveEdge(el1, el2);
    }
    else{
        QMessageBox msg;
        msg.setText("No Such Connection");
        msg.exec();
    }
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
}

void MainWindow::on_ClearButton_clicked() //Сброс графа
{
    gr1->Clear();
    on_matrButton_clicked();
    ui->NodeNameEdit->clear();
    gr1->widget->update();
}

void MainWindow::on_open_action_triggered() //Открытие из файла
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QString(), "All Files(*)");
    on_ClearButton_clicked();
    gr1->ReadFile(fileName);
    on_matrButton_clicked();
    ui->weighBox->setChecked(gr1->weights);
}

void MainWindow::on_save_action_triggered() //Сохранение в файл
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File");
    gr1->SaveFile(fileName);
}

void MainWindow::on_gravityBox_stateChanged(int arg1) //Изменение гравитации
{
    if (arg1 == 0){
        gr1->widget->SetGravity(0);
    }
    else
        gr1->widget->SetGravity(1);
}

void MainWindow::on_colorButton_clicked() //Рандомизация цветов
{
    gr1->widget->RandomColors();
}

void MainWindow::on_shuffleButton_clicked() //Перетасовка вершин
{
    gr1->widget->shuffle();
}

void MainWindow::on_desButton_clicked() //Убрать ориентацию графа
{
    gr1->Desorientate();
    gr1->widget->update();
    on_matrButton_clicked();
}

void MainWindow::on_weighBox_stateChanged(int arg1)
{
    gr1->WeightsOn(arg1);
    on_matrButton_clicked();
}

void MainWindow::on_save_pos_action_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File");
    gr1->SaveFile(fileName, 1);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    gr1->itermarks = arg1;
}

void MainWindow::on_about_action_triggered()
{
    AboutWindow* ab = new AboutWindow;
    ab->show();
}

void MainWindow::on_help_action_triggered()
{
    HelpBrowser* helpBrowser = new HelpBrowser(":/", "doc/index.htm");
    helpBrowser->resize(800, 600);
    helpBrowser->show();
}

void MainWindow::DeicstraResult(int* data)
{
    int n = gr1->CountElems();
    int i;
    ui->resTableWidget->clear();
    ui->resTableWidget->setRowCount(2);
    ui->resTableWidget->setColumnCount(n);
    for (i=0; i<n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(gr1->operator [](i)->name);
        ui->resTableWidget->setItem(0, i, item);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QString str = QString::number(data[i]);
        item2->setText(str);
        ui->resTableWidget->setItem(1, i, item2);
        int size = QString::number(data[i]).length() * 15;
        if (strlen(gr1->operator [](i)->name)*15 > size)
            size = strlen(gr1->operator [](i)->name)*15;
        ui->resTableWidget->setColumnWidth(i, size);
    }
}

void MainWindow::on_Deicstra_clicked()
{
    bool ok = !(gr1->DeicstraInit(gr1->v0));
    if (ok)
    {
        gr1->DeicstraAlgorithm();
        DeicstraResult(gr1->arr);
    }
    else
    {
        QMessageBox box;
        box.setText("No Element Chosen");
        box.exec();
    }
}

void MainWindow::on_Ford_clicked()
{
    ui->ResultEd->clear();
    bool result;
    int sum = 0;
    while ((result = gr1->FordAlgorithm()))
    {
        if (result)
        {
            QString temp;
            QTextStream strm(&temp);
            strm << gr1->path.min_flow << ": ";
            sum += gr1->path.min_flow;
            for (auto it : gr1->path.way_el)
                strm << it->name << " ";
            strm << "\n";
            QString temp2 = ui->ResultEd->toPlainText();
            temp2.append(temp);
            ui->ResultEd->setPlainText(temp2);
        }
    }
    ui->ResultEd->append("Search completed. Maximal stream is " + QString::number(sum));
}

void MainWindow::on_FlowBox_stateChanged(int arg1)
{
    gr1->flows = arg1;
    gr1->widget->updateEdges();
}
