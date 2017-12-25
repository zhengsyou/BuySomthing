#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cznetworkaccessmanager.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QList>
#include <QNetworkCookie>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    CZNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://www.orgnerve.com/Login/login.html"));
    QNetworkReply *reply = manager.get(request);
    QString strRet = reply->readAll();
    QVariant varData = reply->header(QNetworkRequest::SetCookieHeader);

    if(reply->hasRawHeader("Set-Cookie"))
    {
        //qDebug() << "has set-cookie";
        QString strRetSetCookies = reply->rawHeader("Set-Cookie");
        QString strYunsuoSessionID = GetCookieData(strRetSetCookies, "yunsuo_session_verify");
        QString strPhpSessID = GetCookieData(strRetSetCookies, "PHPSESSID");
        QString strJsluID = GetCookieData(strRetSetCookies, "__jsluid");

        request.setUrl(QUrl("https://www.orgnerve.com/Init/verify.html?0.7384840664683736"));
        request.setRawHeader("Cookie", QString("yunsuo_session_verify=%1;PHPSESSID=%2;__jsluid=%3").arg(strYunsuoSessionID).arg(strPhpSessID).arg(strJsluID).toLocal8Bit());
        reply = manager.get(request);
        QByteArray aryPng = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(aryPng);

        ui->labelVerificationCodePic->setPixmap(pixmap);
    }
}

QString MainWindow::GetCookieData(const QString &strData, const QString &strCookieKey, int nIndex)
{
    QString strRet;
    QString strPattern = QString("%1=[0-9,a-z]+;").arg(strCookieKey);
    QRegExp exp(strPattern);
    if(strData.indexOf(exp) >= 0)
    {
        QStringList lstCapData = exp.capturedTexts();
        if(lstCapData.count() <= nIndex)
        {
            return strRet;
        }

        strRet = exp.cap(nIndex);
        strRet.replace(";", "");
        strRet.replace(QString("%1=").arg(strCookieKey), "");
    }
    return strRet;
}

void MainWindow::on_pushButtonGetInfo_clicked()
{
    QString strTest = "yunsuo_session_verify=bc64baf847509825f749b37610d07f0c; expires=Sun, 24-Dec-17 15:56:01 GMT; path=/; HttpOnly\nyunsuo_session_verify=bc64baf847509825f749b37610d07f0c; expires=Sun, 24-Dec-17 15:56:01 GMT; path=/; HttpOnly\nyunsuo_session_verify=bc64baf847509825f749b37610d07f0c; expires=Sun, 24-Dec-17 15:56:01 GMT; path=/; HttpOnly\nthink_language=en; expires=Thu, 21-Dec-2017 08:56:01 GMT; Max-Age=3600; path=/\nPHPSESSID=5dpvurjehq0f6dojmec468jsb6; path=/\n__jsluid=ad638970cb4f51ff6c631a06fa65e15c; max-age=31536000; path=/; HttpOnly";
    qDebug() << GetCookieData(strTest, "yunsuo_session_verify");
    qDebug() << GetCookieData(strTest, "yunsuo_session_verify");
    qDebug() << GetCookieData(strTest, "yunsuo_session_verify");
}
