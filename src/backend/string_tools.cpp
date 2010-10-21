/**
 * \file string_tools.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief Tools for manipulating string.
 */

#include "string_tools.hpp"

#include <systools/string.hpp>

#include <QStringList>

QString toQString(const systools::String& str)
{
	return QString::fromUtf8(str.toUtf8().toStdString().c_str());
}

systools::String fromQString(const QString& str)
{
	return systools::String::fromUtf8(str.toUtf8().constData());
}

QString qStringListToQString(QList<QString> string_list)
{
	return QStringList(string_list).join(",");
}

QList<QString> qStringToQStringList(QString list)
{
	QStringList qstr_list = list.split(",");

	return qstr_list;
}
