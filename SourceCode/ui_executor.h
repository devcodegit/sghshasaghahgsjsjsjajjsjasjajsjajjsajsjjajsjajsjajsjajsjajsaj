#ifndef UI_EXECUTOR_H
#define UI_EXECUTOR_H

#include <QObject>
#include <functional>

typedef std::function<void ()> SimpleFunc;

/**
 * @brief The UIExecutor class
 */
class UIExecutor : public QObject
{
    Q_OBJECT

    //
    // Singleton
private:
    static UIExecutor *_instance;
    explicit UIExecutor(QObject *parent = 0);
    static UIExecutor *instance();

    //
    // Public events
signals:
    void invokeSignal(const SimpleFunc &func);

    //
    // Public methods
public:
    /**
     * @brief Invoke this method when application starts to ensure
     * slot is connected on UI thread.
     */
    static void init();

    /**
     * @brief Invoke this method to execute "func" in UI thread
     */
    static void invoke(const SimpleFunc &func);

    //
    // Private event handlers
private slots:
    void invokeHandler(const SimpleFunc &func);

};

#endif // UI_EXECUTOR_H
