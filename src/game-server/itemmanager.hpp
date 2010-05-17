/*
 *  The Mana Server
 *  Copyright (C) 2004-2010  The Mana World Development Team
 *
 *  This file is part of The Mana Server.
 *
 *  The Mana Server is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  The Mana Server is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Mana Server.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <string>
#include <map>
#include <vector>

class ItemClass;

class ItemManager
{
    public:
        ItemManager(const std::string &itemFile, const std::string &equipFile) :
                mItemReferenceFile(itemFile),
                mEquipCharSlotReferenceFile(equipFile),
                mItemDatabaseVersion(0) {}
        /**
         * Loads item reference file.
         */
        void initialize();

        /**
         * Reloads item reference file.
         */
        void reload();

        /**
         * Destroy item classes.
         */
        void deinitialize();

        /**
         * Gets the ItemClass having the given ID.
         */
        ItemClass *getItem(int itemId) const;

        /**
         * Gets the version of the loaded item database.
         */
        unsigned int getDatabaseVersion() const;

        const std::string &getEquipNameFromId(unsigned int id) const;

        unsigned int getEquipIdFromName(const std::string &name) const;

        unsigned int getMaxSlotsFromId(unsigned int id) const;

        unsigned int getVisibleSlotCount() const;

        bool isEquipSlotVisible(unsigned int id) const;

    private:
        typedef std::map< int, ItemClass * > ItemClasses;
        // Map a string (name of slot) with (str-id, max-per-equip-slot)
        typedef std::vector< std::pair< std::string, unsigned int > > EquipSlots;
        // Reference to the vector position of equipSlots
        typedef std::vector< unsigned int > VisibleEquipSlots;

        ItemClasses itemClasses; /**< Item reference */
        EquipSlots equipSlots;
        VisibleEquipSlots visibleEquipSlots;

        std::string mItemReferenceFile;
        std::string mEquipCharSlotReferenceFile;
        mutable unsigned int mVisibleEquipSlotCount; // Cache

        unsigned int mItemDatabaseVersion; /**< Version of the loaded items database file.*/
};

extern ItemManager *itemManager;

#endif
