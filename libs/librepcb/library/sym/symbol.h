/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
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

#ifndef LIBREPCB_LIBRARY_SYMBOL_H
#define LIBREPCB_LIBRARY_SYMBOL_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "../libraryelement.h"
#include "symbolpin.h"

#include <librepcb/common/geometry/circle.h>
#include <librepcb/common/geometry/polygon.h>
#include <librepcb/common/geometry/text.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/
namespace librepcb {
namespace library {

class SymbolGraphicsItem;

/*******************************************************************************
 *  Class Symbol
 ******************************************************************************/

/**
 * @brief The Symbol class represents the part of a component which is added to
 * schematics
 *
 * Following information is considered as the "interface" of a symbol and must
 * therefore never be changed:
 *  - UUID
 *  - Pins (neither adding nor removing pins is allowed)
 *    - UUID
 */
class Symbol final : public LibraryElement,
                     private SymbolPinList::IF_Observer,
                     private PolygonList::IF_Observer,
                     private CircleList::IF_Observer,
                     private TextList::IF_Observer {
  Q_OBJECT

public:
  // Constructors / Destructor
  Symbol()                    = delete;
  Symbol(const Symbol& other) = delete;
  Symbol(const Uuid& uuid, const Version& version, const QString& author,
         const ElementName& name_en_US, const QString& description_en_US,
         const QString& keywords_en_US);
  explicit Symbol(const FilePath& elementDirectory, bool readOnly);
  ~Symbol() noexcept;

  // Getters: Geometry
  SymbolPinList&       getPins() noexcept { return mPins; }
  const SymbolPinList& getPins() const noexcept { return mPins; }
  PolygonList&         getPolygons() noexcept { return mPolygons; }
  const PolygonList&   getPolygons() const noexcept { return mPolygons; }
  CircleList&          getCircles() noexcept { return mCircles; }
  const CircleList&    getCircles() const noexcept { return mCircles; }
  TextList&            getTexts() noexcept { return mTexts; }
  const TextList&      getTexts() const noexcept { return mTexts; }

  // General Methods
  void registerGraphicsItem(SymbolGraphicsItem& item) noexcept;
  void unregisterGraphicsItem(SymbolGraphicsItem& item) noexcept;

  // Operator Overloadings
  Symbol& operator=(const Symbol& rhs) = delete;

  // Static Methods
  static QString getShortElementName() noexcept {
    return QStringLiteral("sym");
  }
  static QString getLongElementName() noexcept {
    return QStringLiteral("symbol");
  }

private:  // Methods
  void listObjectAdded(const SymbolPinList& list, int newIndex,
                       const std::shared_ptr<SymbolPin>& ptr) noexcept override;
  void listObjectAdded(const PolygonList& list, int newIndex,
                       const std::shared_ptr<Polygon>& ptr) noexcept override;
  void listObjectAdded(const CircleList& list, int newIndex,
                       const std::shared_ptr<Circle>& ptr) noexcept override;
  void listObjectAdded(const TextList& list, int newIndex,
                       const std::shared_ptr<Text>& ptr) noexcept override;
  void listObjectRemoved(
      const SymbolPinList& list, int oldIndex,
      const std::shared_ptr<SymbolPin>& ptr) noexcept override;
  void listObjectRemoved(const PolygonList& list, int oldIndex,
                         const std::shared_ptr<Polygon>& ptr) noexcept override;
  void listObjectRemoved(const CircleList& list, int oldIndex,
                         const std::shared_ptr<Circle>& ptr) noexcept override;
  void listObjectRemoved(const TextList& list, int oldIndex,
                         const std::shared_ptr<Text>& ptr) noexcept override;
  /// @copydoc librepcb::SerializableObject::serialize()
  void serialize(SExpression& root) const override;

private:  // Data
  SymbolPinList mPins;
  PolygonList   mPolygons;
  CircleList    mCircles;
  TextList      mTexts;

  SymbolGraphicsItem* mRegisteredGraphicsItem;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace library
}  // namespace librepcb

#endif  // LIBREPCB_LIBRARY_SYMBOL_H
