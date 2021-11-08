#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void  Widget::check_push_char(const char& ch)
{
    if(!this->myCal.check_push_exp(ch)){
        PRINT_SYNTAX_ERR;
        return;
    }
    ui->label_cur->setText(QString::fromStdString(this->myCal.getExpMid()));
    ui->label_indicate->setText("");
}

void  Widget::check_push_char(const string& s)
{
    if(!this->myCal.check_push_exp(s)){
        PRINT_SYNTAX_ERR;
        return;
    }
    ui->label_cur->setText(QString::fromStdString(this->myCal.getExpMid()));
    ui->label_indicate->setText("");
}

void Widget::on_btnBrckL_clicked()
{
    check_push_char('(');
}

void Widget::on_btnBrckR_clicked()
{
    check_push_char(')');
}

void Widget::on_btnClear_clicked()
{
    this->myCal.reset();
    ui->label_cur->setText("0");
    ui->label_res->setText("0");
    ui->label_indicate->setText("");
}


void Widget::on_btnDelete_clicked()
{
    QString tmp =ui->label_cur->text();
    if(!ui->label_cur->text().isEmpty())ui->label_cur->setText(QString::fromStdString(myCal.backspace()));
}

void Widget::on_opDiv_clicked()
{
    check_push_char('/');
}

void Widget::on_btnExp_clicked()
{
    check_push_char('^');
}

void Widget::on_btnSqrt_clicked()
{
    // '√'根号无法用char存储
    check_push_char("√");
}

void Widget::on_btnMod_clicked()
{
    check_push_char('%');
}

void Widget::on_opMul_clicked()
{
    check_push_char('*');
}

void Widget::on_num9_clicked()
{
    check_push_char('9');
}

void Widget::on_num8_clicked()
{
    check_push_char('8');
}

void Widget::on_num7_clicked()
{
    check_push_char('7');
}

void Widget::on_opMinus_clicked()
{
    check_push_char('-');
}

void Widget::on_num6_clicked()
{
    check_push_char('6');
}

void Widget::on_num5_clicked()
{
    check_push_char('5');
}

void Widget::on_num4_clicked()
{
    check_push_char('4');
}

void Widget::on_opAdd_clicked()
{
    check_push_char('+');
}

void Widget::on_num3_clicked()
{
    check_push_char('3');
}

void Widget::on_num2_clicked()
{
    check_push_char('2');
}

void Widget::on_num1_clicked()
{
    check_push_char('1');
}

void Widget::on_opReturn_clicked()
{
    string res = myCal.do_calculate();
    ui->label_res->setText(ui->label_cur->text());
    ui->label_cur->setText(QString::fromStdString(res));
    this->myCal.reset();
}

void Widget::on_btn_dot_clicked()
{
    check_push_char('.');
}

void Widget::on_num0_clicked()
{
    check_push_char('0');
}
