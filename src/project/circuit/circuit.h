/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_CIRCUIT_H
#define PROJECT_CIRCUIT_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "../../common/exceptions.h"
#include "../../common/filepath.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class XmlFile;
class Workspace;

namespace project {
class Project;
class NetClass;
}

/*****************************************************************************************
 *  Class Circuit
 ****************************************************************************************/

namespace project {

/**
 * @brief The Circuit class
 *
 * @author ubruhin
 * @date 2014-07-03
 */
class Circuit final : public QObject
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit Circuit(Workspace& workspace, Project& project, bool restore) throw (Exception);
        ~Circuit() noexcept;

        // General Methods
        bool save(bool toOriginal, QStringList& errors) noexcept;

    private:

        // make some methods inaccessible...
        Circuit();
        Circuit(const Circuit& other);
        Circuit& operator=(const Circuit& rhs);

        // General
        Workspace& mWorkspace; ///< A reference to the Workspace object (from the ctor)
        Project& mProject; ///< A reference to the Project object (from the ctor)

        // File "core/circuit.xml"
        FilePath mXmlFilepath;
        XmlFile* mXmlFile;

        QHash<QUuid, NetClass*> mNetClasses;

};

} // namespace project

#endif // PROJECT_CIRCUIT_H