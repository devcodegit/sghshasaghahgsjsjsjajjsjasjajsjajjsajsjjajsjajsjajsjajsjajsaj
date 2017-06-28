#ifndef TABLECELL_H
#define TABLECELL_H

#include <QFrame>
#include "../svgwidget.h"
#include "datahandler.h"

class QLabel;
class QCheckBox;
class QHBoxLayout;

class MoreItem : public SvgWidget {
    Q_OBJECT
public:
    explicit MoreItem(QWidget *parent = 0);
    void setId(int id);
    int id();
private slots:
    void onRequestMore();
private:
    int _id;
};

class TableCell : public QFrame
{
    Q_OBJECT
public:
    explicit TableCell(QWidget *parent = 0);
    void setContent(QWidget * content);
    void setData(DataHandler::data_handler *data);
    void setIndex(int row, int col);
    void setText(const QString &title, bool isHeader = false);
    void reset();
    int row();
    int col();
    void setActive(bool isActive);
    bool active();

signals:
    void updateSize(int row, int col, QSize size);
private:
    int _row = -1, _col = -1;
    QLabel *title = 0;
    QLabel *thumb = 0;
    QCheckBox *checkbox = 0;
    QHBoxLayout *layout = 0;
    MoreItem *moreItem = 0;
    QString currentState = "";
    bool isActive = true;
private:
    void setImage(const QString &url);
    void setCheckbox(bool isChecked);
    void setDropDown(QStringList item);
    void setMore(int moreId);
    void initUI();
};

#endif // TABLECELL_H
