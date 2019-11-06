#ifndef CATCH_QT_H
#define CATCH_QT_H

#include "catch/catch.hpp"
#include <QString>
#include <QVariant>
#include <iostream>

QT_BEGIN_NAMESPACE
inline std::ostream &operator<<(std::ostream &os, const QLatin1String &value)
{
    return os << '"' << value.latin1() << '"';
}

inline std::ostream &operator<<(std::ostream &os, const QString &value)
{
    return os << '"' << value.toLocal8Bit().constData() << '"';
}

inline std::ostream &operator<<(std::ostream &os, const QVariant &value)
{
    return os << value.toString();
}
QT_END_NAMESPACE

#endif // CATCH_QT_H
