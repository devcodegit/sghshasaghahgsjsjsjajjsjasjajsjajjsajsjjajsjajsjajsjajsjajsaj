#include "ui_executor.h"

UIExecutor *UIExecutor::_instance = NULL;

UIExecutor::UIExecutor(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<SimpleFunc>("SimpleFunc");
    connect(this, &UIExecutor::invokeSignal, this, &UIExecutor::invokeHandler);
}

UIExecutor *UIExecutor::instance()
{
    if (_instance == NULL)
    {
        _instance = new UIExecutor();
    }

    return _instance;
}

void UIExecutor::init()
{
    instance();
}

void UIExecutor::invoke(const SimpleFunc &func)
{
    emit instance()->invokeSignal(func);
}

void UIExecutor::invokeHandler(const SimpleFunc &func)
{
    func();
}
