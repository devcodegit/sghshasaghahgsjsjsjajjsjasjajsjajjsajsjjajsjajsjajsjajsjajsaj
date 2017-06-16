#include "page-ui-manager.h"
#include <QResizeEvent>

PageUIManager *PageUIManager::Instance = 0;

PageUIManager::PageUIManager(QWidget *parent) : QWidget(parent)
{

}

void PageUIManager::addPage(PageUIManager::Page_ID id, QWidget *page)
{
    if(!page) return;
    page->setParent(this);
    page->move(0,0);
    mapPage.insert(id, page);
}

void PageUIManager::navigate(PageUIManager::Page_ID id)
{
    QWidget *page = mapPage.value(id, 0);
    if(!page || page == currentPage) return;
    page->show();
    page->raise();
    currentPage->hide();
    currentPage = page;
}

void PageUIManager::resizeEvent(QResizeEvent *event)
{
    for(QMap<Page_ID, QWidget*>::iterator it = mapPage.begin(); it != mapPage.end(); it++) {
        if(it.value()) {
            it.value()->resize(event->size());
        }
    }
}
