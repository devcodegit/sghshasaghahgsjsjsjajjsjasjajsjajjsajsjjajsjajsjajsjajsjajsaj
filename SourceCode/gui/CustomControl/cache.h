#ifndef CACHE_H
#define CACHE_H

#include <QMap>

class QPushButton;

class Cache
{
    static Cache *Instance;
    explicit Cache();
public:
    static Cache *instance() {
        if(!Instance) {
            Instance = new Cache;
        }
        return Instance;
    }
    QPushButton *getWidget(int id);

private:
    QMap<int, QPushButton*> mapEditorWidget;
};

#endif // CACHE_H
