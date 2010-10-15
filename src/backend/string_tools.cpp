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

QString stringListToQString(QList<systools::String> string_list)
{
	QString result = "";

	BOOST_FOREACH(systools::String str, string_list)
	{
		result.append(toQString(str));

		if (str != string_list.back())
		{
			result.append(", ");
		}
	}

	return result;
}

QList<systools::String> QStringToStringList(QString list)
{
	QStringList qstr_list = list.split(",");
	QList<systools::String> str_list;

	BOOST_FOREACH(QString str, qstr_list)
	{
		str_list.push_back(fromQString(str));
	}

	return str_list;
}
