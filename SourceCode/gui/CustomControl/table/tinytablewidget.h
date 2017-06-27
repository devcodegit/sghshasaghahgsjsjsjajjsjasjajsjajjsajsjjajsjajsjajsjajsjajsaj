#ifndef TINYTABLEWIDGET_H
#define TINYTABLEWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QMap>
#include <QFrame>
#include <QList>
#include "datahandler.h"
#include "../svgwidget.h"

class QLabel;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;

class MoreItem : public SvgWidget {
    Q_OBJECT
public:
    explicit MoreItem(QWidget *parent = 0);
    void setId(int id);
    int id();
private:
    int _id;
};

class TableCell : public QFrame
{
    Q_OBJECT
public:
    explicit TableCell(const QString &title = "", QWidget *parent = 0);
    void setContent(QWidget * content);
    void setData(DataHandler::data_handler *data);
    void setIndex(int row, int col);
    void reset();
    int row();
    int col();

signals:
    void updateSize(int row, int col, QSize size);
private:
    int _row = -1, _col = -1;
    QLabel *title = 0;
    QLabel *thumb = 0;
    QCheckBox *checkbox = 0;
    QHBoxLayout *layout = 0;
    MoreItem *moreItem = 0;
private:
    void setText(const QString &title);
    void setImage(const QString &url);
    void setCheckbox(bool isChecked);
    void setDropDown(QStringList item);
    void setMore(int moreId);
};

class TinyTableWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TinyTableWidget(QWidget *parent = 0);
    void setHeader(QStringList headers);
    void setData(DataHandler *data);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

private slots:
    void onDataChanged();
    void onUpdateSize(int row, int col, QSize size);

private:
    QList<TableCell*> listHeader;
    QMap<int, QMap<int, TableCell*> > mapCells;
    QFrame *headerFrame = 0;
    QGridLayout *mainLayout = 0;
    int startResize = -1;
    int inLimitZone = -1;
    int currentX = -1;
    int rowCount = 0;

private:
    void initLayout();
    void resizeColumn(int index, int width);
    void resizeRow(int index, int height);
};

#endif // TINYTABLEWIDGET_H
