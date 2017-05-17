#include "cache.h"
#include <QDebug>
#include <QPushButton>

Cache *Cache::Instance = 0;

Cache::Cache()
{
    mapEditorWidget.clear();
}

QPushButton *Cache::getWidget(int id)
{
    QPushButton *button = mapEditorWidget.value(id, 0);
    if(!button) {
        button = new QPushButton;
        mapEditorWidget.insert(id, button);
    }
    return button;
}

