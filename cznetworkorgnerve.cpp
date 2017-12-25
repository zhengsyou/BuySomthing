#include "cznetworkorgnerve.h"
#include <QNetworkReply>



CZNetworkOrgnerve::CZNetworkOrgnerve()
    :m_bInitSession(false)
{

}

QString CZNetworkOrgnerve::GetCookieData(const QString &strData, const QString &strCookieKey, int nIndex)
{
    QString strRet;
    QString strPattern = QString("%1=[0-9,a-z]+;").arg(strCookieKey);
    QRegExp exp(strPattern);
    if(strData.indexOf(exp) >= 0)
    {
        QStringList lstCapData = exp.capturedTexts();
        if(lstCapData.count() > nIndex)
        {
            strRet = exp.cap(nIndex);
            strRet.replace(";", "");
            strRet.replace(QString("%1=").arg(strCookieKey), "");
        }
    }
    return strRet;
}

QPixmap CZNetworkOrgnerve::getLoginVerificationCodePic()
{
    checkInitSession();
    QNetworkRequest request("https://www.orgnerve.com/Init/verify.html?0.7384840664683736");
    request.setRawHeader("Cookie", QString("yunsuo_session_verify=%1;PHPSESSID=%2;__jsluid=%3").arg(strYunsuoSessionID).arg(strPhpSessID).arg(strJsluID).toLocal8Bit());
    reply = manager.get(request);
    if(QNetworkReply::NoError != reply.error())
    {
        throw CZNetworkException(reply->errorString());
    }

    QPixmap pixmap;
    if(!pixmap.loadFromData(reply->readAll()))
    {
        throw
    }
    return pixmap;
}

void CZNetworkOrgnerve::checkInitSession()throw(CZInitSessionIDException)
{
    if(false == m_bInitSession)
    {
        throw CZInitSessionIDException(QStringLiteral("未初始化Session"));
    }
}

void CZNetworkOrgnerve::InitSessionID() throw(CZInitSessionIDException)
{
    QNetworkRequest request(QUrl("https://www.orgnerve.com/Login/login.html"));
    QNetworkReply *reply = get(request);
    if(QNetworkReply::NoError != reply->error())
    {
        throw CZNetworkException(reply->errorString());
    }

    if(reply->hasRawHeader("Set-Cookie"))
    {
        QString strRetSetCookies = reply->rawHeader("Set-Cookie");
        m_strYunsuoSessionID = GetCookieData(strRetSetCookies, "yunsuo_session_verify");
        m_strPhpSessID = GetCookieData(strRetSetCookies, "PHPSESSID");
        m_strJsluID = GetCookieData(strRetSetCookies, "__jsluid");

        if(m_strYunsuoSessionID.isEmpty() || m_strPhpSessID.isEmpty() || m_strJsluID.isEmpty())
        {
            throw CZInitSessionIDException(QStringLiteral("返回数据中未找到SessionID"));
        }
    }
    else
    {
        throw CZInitSessionIDException(QStringLiteral("返回数据中未找到Set-Cookie"));
    }
    m_bInitSession = true;
}
