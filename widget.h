#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    bool GetIntFromLineEdit(QLineEdit *line, int &value);
    bool GetDoubleFromLineEdit(QLineEdit *line, double &value);
    bool GetDoubleFromItem(QTableWidgetItem *item, double &value);

    void on_rowCount_LineEdit_editingFinished();


    void on_randomButton_clicked();

    void on_reorderButton_clicked();

    void on_search_Button_clicked();

    void on_maxButton_clicked();

    void on_avgButton_clicked();

    void on_minButton_clicked();

    void on_deliteButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
