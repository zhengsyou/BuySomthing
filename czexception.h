#ifndef CZEXCEPTION_H
#define CZEXCEPTION_H
#include <exception>
#include <QString>

#define QZStringException(str) ([]()->const char *{\
    return QString(QStringLiteral(str)).toStdString().data();\
})()

class CZException : public std::exception
{
public:
    CZException();
    CZException(const char * szError);
    CZException(const QString &strError);
};

#endif // CZEXCEPTION_H
