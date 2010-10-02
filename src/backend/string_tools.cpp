/**
 * \file string_tools.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief Tools for manipulating string.
 */

#include "string_tools.hpp"

#include <systools/string.hpp>

#include <QString>

QString toQString(const systools::String& str)
{
	return QString::fromUtf8(str.toUtf8().toStdString().c_str());
}

systools::String fromQString(const QString& str)
{
	return systools::String::fromUtf8(str.toUtf8().constData());
}

