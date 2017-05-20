#include "detailwidget.h"
#include <QFrame>
#include <QBoxLayout>
#include <QLabel>

#define DIALOG_HEIGHT 300
#define DIALOG_WIDTH 500

DetailWidget::DetailWidget(QWidget *parent) : SDialog(parent)
{
    setWindowTitle("Thông tin đơn hàng");
    QFrame *bg = new QFrame;
    bg->setFixedSize(DIALOG_WIDTH, DIALOG_HEIGHT);
    QVBoxLayout *layout = new QVBoxLayout(bg);
    layout->setAlignment(Qt::AlignTop);
    QLabel *label1 = new QLabel("Tên: <Đơn hàng 1>");
    QLabel *label2 = new QLabel("Ngày xuất: <dd/MM/yyyy>");
    QLabel *label3 = new QLabel("Thông tin thêm: <Thông tin>");
    QLabel *label4 = new QLabel("Ghi chú: <Ghi chú ở đây>");
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    layout->addWidget(label4);
    setContent(bg);
}
