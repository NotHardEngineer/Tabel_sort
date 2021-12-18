#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void quickSort(double *array, int left, int right)
{
    double pivot; // разрешающий элемент
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = array[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((array[right] >= pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            array[left] = array[right]; // перемещаем элемент [right] на место разрешающего
            left++; // сдвигаем левую границу вправо
        }
        while ((array[left] <= pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            array[right] = array[left]; // перемещаем элемент [left] на место [right]
            right--; // сдвигаем правую границу вправо
        }
    }
    array[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(array, left, pivot - 1);
    if (right > pivot)
        quickSort(array, pivot + 1, right);
}

bool Widget::GetIntFromLineEdit(QLineEdit *line, int &value){
    bool ok;
    value = line->text().toInt(&ok);
    QPalette pal;
    if(!ok){
        pal.setColor(QPalette::Base, Qt::red);

    }
    line->setPalette(pal);
    return ok;
}

bool Widget::GetDoubleFromItem(QTableWidgetItem *item, double &value){
    bool ok = 0;
    if (item != NULL){
        QString s1 = item->text();
        value = s1.toDouble(&ok);
    }
    if(ok){
        item->setBackground(Qt::white);
    }
    else{
        item->setBackground(Qt::red);
    }
    return ok;
}


void Widget::on_rowCount_LineEdit_editingFinished(){
    int inputNofRows = 0;
    bool ok = GetIntFromLineEdit(ui->rowCount_LineEdit, inputNofRows);
    QPalette pal;
    if (ok){
        ui->tableWidget->setRowCount(inputNofRows);
        for(int n = 0; n < inputNofRows; n ++){
            ui->tableWidget->setItem(n, 0, new QTableWidgetItem);
        }
    }
    else{
        pal.setColor(QPalette::Base, Qt::red);
    }
    ui->rowCount_LineEdit->setPalette(pal);

}


void Widget::on_randomButton_clicked()
{
    int NofRows = ui->tableWidget->rowCount();
    for (int n = 0; n < NofRows; n ++){
        QString randS = QString::number(rand());
        QTableWidgetItem *cell_rand = new QTableWidgetItem(randS);
        ui->tableWidget->setItem(n, 0, cell_rand);
    }
}


void Widget::on_reorderButton_clicked()
{
    int NofRows = ui->tableWidget->rowCount();
    bool flag = 1;
    double *array = new double[NofRows];
    for (int n = 0; n < NofRows; n ++){
        if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
            flag = 0;
            break;
        }
    }

    if(flag){
        double temp;
        switch(ui->typeSelectBox->currentIndex()){
        case 0:{
            //метод пузырька

            for (int i = 0; i < NofRows - 1; i++) {
                for (int j = 0; j < NofRows - i - 1; j++) {
                    if (array[j] > array[j + 1]) {
                        temp = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = temp;
                    }
                }
            }
            break;
        }
        case 1:
        {
            //быстрая сортировка
            quickSort(array, 0, NofRows-1);
            break;
        }
        case 2:
        {
            //расчестка
            int jump = NofRows;
            bool swapped = true;
            while (jump > 1 || swapped)
            {
                if (jump > 1){
                    jump = (int)(jump / 1.25);
                }
                swapped = false;
                for (int i = 0; i + jump < NofRows; i++){
                    if (array[i] > array[i + jump]){
                        temp = array[i];
                        array[i] = array[i + 1];
                        array[i + 1] = temp;
                        swapped = true;
                    }
                }
            }
        }
            break;
        case 3:{
            //гномья
            int i = 0;
            while(i < NofRows){
                if (i == 0 || array[i-1] <= array[i]) {
                    i++;
                }
                else {
                    temp = array[i];
                    array[i] = array[i-1];
                    array[i-1] = temp;
                }
            }
        }
        case 4:
        {

            break;
        }
        default:
        {
            break;
        }
        }

        for (int n = 0; n < NofRows; n ++){
            QString s = QString::number(array[n]);
            QTableWidgetItem *cell = new QTableWidgetItem(s);
            ui->tableWidget->setItem(n, 0, cell);
        }
    }

    delete[] array;
    array = 0;
}

