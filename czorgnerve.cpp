#include "czorgnerve.h"
#include <QSettings>
#include <QException>
#include <QNetworkReply>
#include <QNetworkRequest>

CZInitException::CZInitException(const char *szBuffer)
    :CZException(szBuffer)
{

}

CZInitException::CZInitException(const QString &strError)
    :CZException(strError)
{

}



CZOrgnerve::CZOrgnerve()
{
    loadConfigFormFile();
}

void CZOrgnerve::saveConfig()
{
    QSettings set("./config.ini", QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    set.beginGroup(QStringLiteral("帐号信息"));
    set.setValue(QStringLiteral("帐号"), m_strUser);
    set.setValue(QStringLiteral("密码"), m_strPassword);
    set.setValue(QStringLiteral("优优云ID"), m_strUUID);
    set.endGroup();
}

void CZOrgnerve::loadConfigFormFile()
{
    QSettings set("./config.ini", QSettings::IniFormat);
    set.beginGroup(QStringLiteral("帐号信息"));
    m_strUser = set.value(QStringLiteral("帐号")).toString();
    m_strPassword = set.value(QStringLiteral("密码")).toString();
    m_strUUID = set.value(QStringLiteral("优优云ID")).toString();
    set.endGroup();
}


QString CZOrgnerve::getUUID() const
{
    return m_strUUID;
}

void CZOrgnerve::setUUID(const QString &strUUID)
{
    m_strUUID = strUUID;
}

QString CZOrgnerve::getPassword() const
{
    return m_strPassword;
}

void CZOrgnerve::setPassword(const QString &strPassword)
{
    m_strPassword = strPassword;
}

QString CZOrgnerve::getUser() const
{
    return m_strUser;
}

void CZOrgnerve::setUser(const QString &strUser)
{
    m_strUser = strUser;
}
