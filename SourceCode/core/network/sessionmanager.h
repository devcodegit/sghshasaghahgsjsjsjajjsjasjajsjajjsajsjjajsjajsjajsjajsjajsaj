#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

namespace Core { namespace Network {

    enum SessionState
    {
        VALID,
        INVALID
    };

    class SessionManager
    {
    public:
        static const QString SESSION_INVALID;

        // Singleton
        static SessionManager* instance()
        {
            static SessionManager s_Instance;
            return &s_Instance;
        }

    private:
        SessionManager(); // Private Constructor
        SessionManager(SessionManager const&);  // Deprecated
        void operator=(SessionManager const&);  // Deprecated

    public:
        void setSessionKey(QString a_sSessionKey);
        QString getSessionKey();

        QString getSessionKeyDirect();

        void invalidSession();

        void resetSession();

        void onSessionExpired(int a_iErrorCode);

    private:
        QString m_sSessionKey;
        SessionState m_eSessionState;
    };

}}
#endif // SESSIONMANAGER_H
