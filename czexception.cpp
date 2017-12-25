#include "czexception.h"

CZException::CZException()
{

}

CZException::CZException(const char *szError)
    :std::exception(szError)
{

}

CZException::CZException(const QString &strError)
    :std::exception(strError.toStdString().data())
{
}
