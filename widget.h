#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>
#include "calculator.h"

#define PRINT_SYNTAX_ERR do{ui->label_indicate->setText("语法错误");}while(0)

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    void check_push_char(const char&);
    void check_push_char(const string&);
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnBrckL_clicked();

    void on_btnBrckR_clicked();

    void on_btnClear_clicked();

    void on_btnDelete_clicked();

    void on_opDiv_clicked();

    void on_btnExp_clicked();

    void on_btnSqrt_clicked();

    void on_btnMod_clicked();

    void on_opMul_clicked();

    void on_num9_clicked();

    void on_num8_clicked();

    void on_num7_clicked();

    void on_opMinus_clicked();

    void on_num6_clicked();

    void on_num5_clicked();

    void on_num4_clicked();

    void on_opAdd_clicked();

    void on_num3_clicked();

    void on_num2_clicked();

    void on_num1_clicked();

    void on_opReturn_clicked();

    void on_btn_dot_clicked();

    void on_num0_clicked();

private:
    Ui::Widget *ui;
    Calculator myCal;
};

#endif // WIDGET_H
