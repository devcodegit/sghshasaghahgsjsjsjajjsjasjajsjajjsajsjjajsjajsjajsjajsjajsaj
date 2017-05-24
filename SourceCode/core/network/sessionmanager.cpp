#include "sessionmanager.h"

using namespace Core::Network;

const QString SessionManager::SESSION_INVALID = "$session_invalid$";

SessionManager::SessionManager()
    : m_sSessionKey("")
    , m_eSessionState(SessionState::INVALID)
{

}

void SessionManager::setSessionKey(QString a_sSessionKey)
{
    if (a_sSessionKey.length() > 0)
    {
        // Reset state to Valid
        m_eSessionState = SessionState::VALID;
        m_sSessionKey = a_sSessionKey;
        // Stop renew session thread
    }
}

QString SessionManager::getSessionKey()
{
    if (m_eSessionState == SessionState::INVALID)
    {
        // Start renew session intermediate
        return SessionManager::SESSION_INVALID;
    }
    else
    {
        return m_sSessionKey;
    }
}

QString SessionManager::getSessionKeyDirect()
{
    return m_sSessionKey;
}

void SessionManager::invalidSession()
{
    m_eSessionState = SessionState::INVALID;
}

void SessionManager::resetSession()
{
    m_sSessionKey = "";
    m_eSessionState = SessionState::INVALID;
}

void SessionManager::onSessionExpired(int a_iErrorCode)
{
    Q_UNUSED(a_iErrorCode);
}
