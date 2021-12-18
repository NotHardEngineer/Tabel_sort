#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

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

int Search_Binary (double arr[], int left, int right, int key)
{
    int midd = 0;
    while (1)
    {
        midd = (left + right) / 2;

        if (key < arr[midd])   {     // если искомое меньше значения в ячейке
            right = midd - 1; }      // смещаем правую границу поиска
        else if (key > arr[midd]){   // если искомое больше значения в ячейке
            left = midd + 1;  }      // смещаем левую границу поиска
        else{                       // иначе (значения равны)
            return midd;            // функция возвращает индекс ячейки
        }
        if (left > right)  {         // если границы сомкнулись
            return -1;}
    }
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

void monke(double *array, int NofRows){
    bool flag = 0;
    while(!flag){
        for (int i=1; i<NofRows;i++)//проходим по всем строкам
        {
            double tmp=array[i];//временная переменная равная элементу i
            int rand_idx = rand() % NofRows;//генерируем случайное число из массива

            //меняем элементы местами
            array[i] = array[rand_idx];
            array[rand_idx] = tmp;


            for (int i=1; i<NofRows; i++)// проверяем на верную расстановку
            {
                if (array[i-1]>array[i])//если неверно
                {
                    flag = false;//флаг верной расстановки +
                    break;//останавливаем цикл

                }
                else{//верно
                    flag = true;//флаг верной расстановки -
                }
            }
        }
    }
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

bool Widget::GetDoubleFromLineEdit(QLineEdit *line, double &value){
    bool ok;
    value = line->text().toDouble(&ok);
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
                    i+= 1;
                }
                else {
                    temp = array[i];
                    array[i] = array[i-1];
                    array[i-1] = temp;
                    i = i - 1;
                }
            }
            break;
        }
        case 4:
        {
            //херовая
            if(NofRows < 10){
                monke(array, NofRows);
            }
            else{
                QMessageBox msgBox;
                msgBox.setText("Не нужно оно тебе, это будет долго");
                msgBox.exec();
            }
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


void Widget::on_search_Button_clicked()
{
    double search;
    bool ok = GetDoubleFromLineEdit(ui->search_LineEdit,search);
    if (ok){
        int NofRows = ui->tableWidget->rowCount();
        bool flag = 1;
        double *array = new double[NofRows];
        for (int n = 0; n < NofRows; n ++){
            if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
                flag = 0;
                break;
            }
        }
        for (int i=1; i<NofRows; i++) // проверяем на верную расстановку
        {
            if (array[i-1]>array[i]) //если неверно
            {
                flag = false; //флаг верной расстановки +
                break; //останавливаем цикл

            }
            else //верно
            {
                flag = true; //флаг верной расстановки
            }
        }

        int searchcount = 0;
        QString searchItemsNumbers = "";
        if(flag){
            int mid = NofRows /2;//поиск номера среднего элемента
            int left = 0;
            int right = NofRows -1;

            int lastLeft = -1;
            int lastRight = -1;
            while(abs(array[mid]-search)>pow(10,-15) && abs(array[mid+1]-search)>pow(10,-15))
            {
                if((left == lastLeft) && (right == lastRight))//граница не изменена
                {
                    break;//выход из цикла так как не найдено значение
                }
                lastLeft = left;
                lastRight = right;
                if(search<array[mid])//числло которое ищем меньше центрального элемента
                {
                    right = mid;//устанавливаем правую границу
                }
                else//число которое ищем больше центрального эл-та
                {
                    left = mid;//устанавливаем левую границу
                }
                mid = (left+right)/2;//ищем номер нового центрального эл-та
            }


            if(abs(array[mid]-search)<pow(10,-15))
            {
                //если совпадает центр число то ничего не меняем
            }

            else if(abs(array[mid+1]-search)<pow(10,-15))//если искомое число справа от центра
            {
                mid ++;//сдвигаем границу вправо
            }
            else
            {
                mid = -1 ;//сдвигаем границу влево
            }

            if(mid != -1)//если значение было найдено
            {
                if(mid>0)//если не в самом левом углу
                {
                    int index = mid -1;
                    while(abs(array[index] - search) <pow(10,-15))//пока число из массива с номером индекса равно искомому
                    {
                        if (index == 0)//дошли до левой границы
                        {
                            index--;
                            break;//выходим из цикла
                        }
                        index -- ;//идем влево
                    }
                    index++;//сдвигаемся вправо так как жостигли невозможного элемента

                    for(int i =index; i<mid; i++)//идем по всем индексам
                    {
                        searchcount++;//ув-ем кол-во найденных элементов на 1
                        ui->tableWidget->item(i,0)->setBackground(Qt::blue);//красим элемент в синий

                        if(searchItemsNumbers != "")
                        {
                            searchItemsNumbers.append(", ");
                        }
                        searchItemsNumbers.append(QString::number(i+1));//добавляем номер столбца
                    }
                }
                searchcount++;
                ui->tableWidget->item(mid,0)->setBackground(Qt::blue);
                if(searchItemsNumbers != "")
                {
                    searchItemsNumbers.append(", ");
                }
                searchItemsNumbers.append(QString::number(mid+1));
                if(mid<NofRows-1)//если мы не в самом правом углу
                {
                    int index = mid+1;//начинаем с эл-та который стоит слева
                    while(abs(array[index]-search)<pow(10,-15))//пока число из массива с номером индекса равно искомому
                    {
                        if(index == NofRows -1)//если дошли до правой границы
                        {
                            index ++;//ув-ем индекс
                            break;//выходим из цикла
                        }
                        index++;//сдвигаем индекс влево
                    }
                    index--;//сдвигаем индекс вправо т к дошли до невозможного эл-та
                    for(int i = mid+1; i<=index;i++)
                    {
                        searchcount++;
                        ui->tableWidget->item(i,0)->setBackground(Qt::blue);

                        if(searchItemsNumbers != "")
                        {
                            searchItemsNumbers.append(", ");
                        }
                        searchItemsNumbers.append(QString::number(i+1));
                    }
                }
            }
            else//нет искомых чисел в таблице
            {
                searchItemsNumbers = "Не найдено";
            }

        }
        else{
            for(int i =0;i<NofRows;i++)
            {
                if(abs(array[i]-search)<pow(10,-15))
                {
                    searchcount++;
                    ui->tableWidget->item(i,0)->setBackground(Qt::blue);
                    if(searchItemsNumbers !="") // если в строке уже есть зн-я
                    {
                        searchItemsNumbers.append(", ");
                    }
                    //добавляем число
                    searchItemsNumbers.append(QString::number(i+1));//добавляем номера строка в которых найдено совпдаение
                }
            }
        }
        ui->label_seeked->setNum(searchcount);//выводим кол-во найденных элементов
        ui->vertexLabels->setText(searchItemsNumbers);//выводим строки найденных эл-ов
        delete[] array;
        array = 0;
    }
}


void Widget::on_maxButton_clicked()
{
    ui->label_seeked->clear();
    ui->vertexLabels->clear();
    int NofRows = ui->tableWidget->rowCount();
    bool flag = 1;
    double *array = new double[NofRows];
    for (int n = 0; n < NofRows; n ++){
        if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
            flag = 0;
            break;
        }
    }
    ui->result_Label->show();
    if(flag)//если верно
    {
        int row = ui->tableWidget->rowCount();

        double max =ui->tableWidget->item(0,0)->text().toDouble(); // заносим значение из таблицы
        for (int i = 1; i < row; i ++) // проходимся по значениям начиная со 2 элемента
        {
            double val = ui->tableWidget->item(i,0)->text().toDouble();
            if(val > max) // сравниваем значение из введенных значений

            {
                max = val; // присваиваем большее значение максимуму
            }
        }
        ui->result_Label->setNum(max); // выводим минимум
    }
    delete[] array;
    array = 0;
}


void Widget::on_avgButton_clicked()
{
    ui->label_seeked->clear();
    ui->vertexLabels->clear();
    int NofRows = ui->tableWidget->rowCount();
    bool flag = 1;
    double *array = new double[NofRows];
    for (int n = 0; n < NofRows; n ++){
        if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
            flag = 0;
            break;
        }
    }
    if(flag)//если все введено успешно
    {
        int row = ui->tableWidget->rowCount();//считаем кол-во элементов
        double ave=0;//переменная для суммы элементов
        double l;
        for(int i = 0;i<row;i++)//суммируем элементы
        {
            l = ui->tableWidget->item(i,0)->text().toDouble();
            ave+=l;

        }
        double res = ave/row;//получаем среднее значение
        ui->result_Label->show();//показываем результат
        ui->result_Label->setNum(res);//выводим среднее значени
    }
    else//не успешно
    {
        ui->result_Label->hide();//скрываем результат
    }
    delete[] array;
    array = 0;
}


void Widget::on_minButton_clicked()
{
    ui->label_seeked->clear();

    ui->vertexLabels->clear();
    int NofRows = ui->tableWidget->rowCount();
    bool flag = 1;
    double *array = new double[NofRows];
    for (int n = 0; n < NofRows; n ++){
        if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
            flag = 0;
            break;
        }
    }
    ui->result_Label->show();
    if(flag)//если верно
    {
        int row = ui->tableWidget->rowCount();
        double min =ui->tableWidget->item(0,0)->text().toDouble(); // заносим значение из таблицы
        for (int i = 1; i < row; i ++) // проходимся по значениям начиная со 2 элемента
        {
            double val = ui->tableWidget->item(i,0)->text().toDouble(); // еще одна переменная куда мы заносим значения из таблицы
            // так как нам нужно сравнивать с каким то значением, чтобы найти минимальное
            if(val < min) // сравниваем значение из введенных значений
                // если 2 переменная меньше нашего начального минимума
            {
                min = val; // то присваиваем минимумум значение 2 переменной
            }
        }
        ui->result_Label->setNum(min); // выводим минимум
    }
    delete[] array;
    array = 0;
}


void Widget::on_deliteButton_clicked()
{
    ui->label_seeked->clear();

    ui->vertexLabels->clear();
    int NofRows = ui->tableWidget->rowCount();
    bool flag = 1;
    double *array = new double[NofRows];
    for (int n = 0; n < NofRows; n ++){
        if(!GetDoubleFromItem(ui->tableWidget->item(n,0), array[n])){
            flag = 0;
            break;
        }
    }
    if(flag)//успешно
    {

        bool sort = 1;
        double *clearArray = new double[NofRows];//новый массив без повторов
        int NofRows_bez_pov = 0;//переменная для размера масссива без повторов
        if(sort)
        {
            NofRows_bez_pov = 1;//переменная для размера масссива без повторов
            double value = array[0];
            clearArray[0] = array[0];
            for(int i=1;i<NofRows;i++)
            {
                if(abs(array[i]- value)>0)
                {
                    clearArray[NofRows_bez_pov]=array[i];
                    value = array[i];
                    NofRows_bez_pov++;
                }
            }

        }
        else{

            for(int i=0;i<NofRows;i++)//проходим по всем элементам начального массива
            {
                bool exist_element = false;//переменная существования элемента
                for (int j = 0;j<i;j++)//проходим по всем элементам массива без повторов
                {
                    if( abs(array[i] - array[j])<1e-15 )//если элемент уже есть в таблице
                    {
                        exist_element = true;//существует


                    }
                }
                if(!exist_element) // в массиве этого элемента нет
                {//не существует
                    clearArray[NofRows_bez_pov] = array[i];//элемент в таблице без повторов приравняли к элементу из начального массива
                    NofRows_bez_pov++;//увелечили размер массива без повторов на 1
                }
            }
            for(int i = 0; i<NofRows_bez_pov;i++)
            {
                array[i] = clearArray[i];
            }



        }
        ui->tableWidget->setRowCount(NofRows_bez_pov);//установили число строк равное кол-ву элементов
        delete [] array;
        array = nullptr;

        array = new double[NofRows_bez_pov];
        QString itemtext;//переменная для числа
        for (int i =0;i<NofRows_bez_pov;i++)//проходим по всем строкам
        {
            array[i] = clearArray[i];
            itemtext.setNum(array[i]);//приравниваем переменную к числу из массива
            ui->tableWidget->item(i,0)->setText(itemtext);//добавляем число в таблицу
        }
        delete []  clearArray;
        clearArray = 0;
    }
    delete[] array;
    array = 0;
}

