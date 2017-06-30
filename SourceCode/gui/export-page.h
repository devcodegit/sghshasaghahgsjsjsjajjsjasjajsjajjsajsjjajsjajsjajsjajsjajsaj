#ifndef EXPORTPAGE_H
#define EXPORTPAGE_H

#include <QWidget>

class QLineEdit;

class ExportPage : public QWidget
{
    Q_OBJECT
public:
    explicit ExportPage(QWidget *parent = 0);

signals:

public slots:

private slots:
    void onOk();
    void onCancel();

private:
    QLineEdit *lineMaHang, *lineSanPham, *lineTenKhachHang, *lineSoDonHang, *lineDiaChiGiaoHang;
};

#endif // EXPORTPAGE_H
