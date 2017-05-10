#ifndef SBUTTONOPTION_H
#define SBUTTONOPTION_H

#include <QPushButton>

class QLabel;
class QSvgWidget;

class SButtonOption : public QPushButton
{
    Q_OBJECT
public:
    explicit SButtonOption(QWidget *parent = 0);
    void setText(const QString &text);

signals:

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *ev);

private:
    QLabel *_plbText = 0;
    QSvgWidget *_pIcon = 0;
};

#endif // SBUTTONOPTION_H
