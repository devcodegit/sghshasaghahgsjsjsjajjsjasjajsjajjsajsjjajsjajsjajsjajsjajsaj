#include "suserinfo.h"
#include <QLabel>

#define POPUP_HEIGHT 100
#define POPUP_WIDTH 300

SUserInfo *SUserInfo::Instance = 0;

SUserInfo::SUserInfo(QWidget *parent) : SDialog(parent)
{
    setWindowTitle("Thông tin");
    QFrame *bg = new QFrame(this);
    bg->setFixedSize(POPUP_WIDTH, POPUP_HEIGHT);

    QLabel *lbl = new QLabel(bg);
    lbl->setObjectName("DefaultLbl");
    lbl->setText("Tên: Nguyễn Văn A\nChức vụ: Nhân viên\nMã nhân viên: A12345");
    lbl->move(10, 10);
    lbl->show();

    setContent(bg);
}

void SUserInfo::setData()
{

}
