/* * This file is part of meego-im-framework *
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Nokia Corporation (directui@nokia.com)
 *
 * If you have questions regarding the use of this file, please contact
 * Nokia at directui@nokia.com.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file LICENSE.LGPL included in the packaging
 * of this file.
 */


#ifndef MTOOLBARID_H
#define MTOOLBARID_H

#include <QObject>
#include <QHash>
#include <QPointer>

#include "mtoolbardata.h"

class MGConfItem;

/*!
 * \brief MToolbarId contains global unique identifier for toolbar.
 *
 * Such identifiers are generated by MToolbarManager::generateId.
 */
class MToolbarId
{
public:
    //! Construct invalid identifier.
    MToolbarId();

    //! Construct identifier with given application \a id and \a service name.
    MToolbarId(int id, const QString &service);

    //! Return true if identifier is valid.
    bool isValid() const;

    //! Returns true if \a other is equal to this object
    bool operator==(const MToolbarId &other) const;

    //! Returns true if \a other is not equal to this object
    bool operator!=(const MToolbarId &other) const;

private:
    //! Id given by application
    int id;

    //! Unique application identifier
    QString service;

    friend uint qHash(const MToolbarId &id);
};

//! Returns hash value for given \a id
uint qHash(const MToolbarId &id);

#endif

