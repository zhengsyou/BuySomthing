#ifndef CZORGNERVE_H
#define CZORGNERVE_H

#include <QString>
#include "czexception.h"
#include "cznetworkaccessmanager.h"

class CZInitException : public CZException
{
public:
    CZInitException(const char * szError);
    CZInitException(const QString &strError);
};

class CZOrgnerve
{
public:
    CZOrgnerve();

    void saveConfig();
    void loadConfigFormFile();

    QString getUser() const;
    void setUser(const QString &strUser);

    QString getPassword() const;
    void setPassword(const QString &strPassword);

    QString getUUID() const;
    void setUUID(const QString &strUUID);




private:

    QString m_strUser;
    QString m_strPassword;
    QString m_strUUID;

};

#endif // CZORGNERVE_H
