#ifndef CZNETWORKORGNERVE_H
#define CZNETWORKORGNERVE_H
#include "cznetworkaccessmanager.h"
#include "czexception.h"

class CZInitSessionIDException : public CZException
{
public:
    CZInitSessionIDException(){};
    CZInitSessionIDException(const char * szError):CZException(szError){};
    CZInitSessionIDException(const QString &strError):CZException(strError){};
};

class CZNetworkException : public CZException
{
public:
    CZNetworkException(){};
    CZNetworkException(const char * szError):CZException(szError){};
    CZNetworkException(const QString &strError):CZException(strError){};
};

class CZNetworkOrgnerve : public CZNetworkAccessManager
{
public:
    CZNetworkOrgnerve();

    void InitSessionID() throw(CZInitSessionIDException);
    QString GetCookieData(const QString &strData, const QString &strCookieKey, int nIndex = 0);
    QPixmap getLoginVerificationCodePic();

    void checkInitSession() throw(CZInitSessionIDException);

private:
    QString m_strYunsuoSessionID;
    QString m_strPhpSessID;
    QString m_strJsluID;
    bool m_bInitSession;
};

#endif // CZNETWORKORGNERVE_H
