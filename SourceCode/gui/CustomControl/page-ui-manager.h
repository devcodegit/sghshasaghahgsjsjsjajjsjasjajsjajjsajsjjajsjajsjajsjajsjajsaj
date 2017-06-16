#ifndef PAGEUIMANAGER_H
#define PAGEUIMANAGER_H

#include <QWidget>
#include <QMap>

class PageUIManager : public QWidget
{
    Q_OBJECT
    explicit PageUIManager(QWidget *parent = 0);
    static PageUIManager *Instance;
public:
    enum Page_ID {
        SEARCH_PAGE = 0
    };
    static PageUIManager *instance() {
        if(!Instance) {
            Instance = new PageUIManager;
        }
        return Instance;
    }
    void addPage(Page_ID id, QWidget *page);
    void navigate(Page_ID id);
protected:
    virtual void resizeEvent(QResizeEvent *event);
signals:

public slots:

private:
    QMap<Page_ID, QWidget*> mapPage;
    QWidget *currentPage = 0;
};

#endif // PAGEUIMANAGER_H
