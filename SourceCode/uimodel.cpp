#include "uimodel.h"
#include <QStringList>
UIModel *UIModel::Instance = 0;
UIModel::UIModel()
{

}

void UIModel::setMainWindow(QWidget *widget)
{
    this->mainWindow = widget;
}

QWidget *UIModel::getMainWindow()
{
    return this->mainWindow;
}

QStringList UIModel::getDataTableHeader()
{
    return QStringList() << "[]" << "Tài liệu" << "Số đơn hàng" << "Ngày đặt hàng" << "Chờ duyệt từ" << "Hình thức thanh toán" << "Giá bán lẻ" << "#" << "Tình trạng" << "Đã in" << "Hành động";
}
