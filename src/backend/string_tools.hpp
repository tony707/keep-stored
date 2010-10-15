/**
 * \file string_tools.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief Tools for manipulating string.
 */

#ifndef KEEP_STORED_STRING_TOOLS_HPP
#define KEEP_STORED_STRING_TOOLS_HPP

#include <QList>

#include <boost/foreach.hpp>

namespace systools
{
	class String;
}

class QString;

/**
 * \brief Convert a systools::String to a QString.
 * \param str The string to convert.
 * \return The string.
 */
QString toQString(const systools::String& str);

/**
 * \brief Convert a QString to a systools::String.
 * \param str The string to convert.
 * \return The string.
 */
systools::String fromQString(const QString& str);

/**
 * \brief Convert a systools::String list to a QString.
 * \param string_list The string list to convert.
 * \return The string.
 */
QString stringListToQString(QList<systools::String> string_list);

/**
 * \brief Convert a QString to a systools::String list.
 * \param str The string to convert.
 * \return The string list.
 */
QList<systools::String> QStringToStringList(QString list);

#endif /* KEEP_STORED_STRING_TOOLS_HPP */

