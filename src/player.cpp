/*
 *  The Mana World Server
 *  Copyright 2004 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World  is free software; you can redistribute  it and/or modify it
 *  under the terms of the GNU General  Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or any later version.
 *
 *  The Mana  World is  distributed in  the hope  that it  will be  useful, but
 *  WITHOUT ANY WARRANTY; without even  the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 *
 *  You should  have received a  copy of the  GNU General Public  License along
 *  with The Mana  World; if not, write to the  Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  $Id$
 */

#include "player.h"

#include <cassert>

void Player::setDatabaseID(int id)
{
    assert(mDatabaseID == -1);
    mDatabaseID = id;
}

/**
 * Update the internal status.
 */
void Player::update()
{
    // computed stats.
    setStat(STAT_HEAT, 20 + (20 * mRawStats.stats[STAT_VITALITY]));
    setStat(STAT_ATTACK, 10 + mRawStats.stats[STAT_STRENGTH]);
    setStat(STAT_DEFENCE, 10 + mRawStats.stats[STAT_STRENGTH]);
    setStat(STAT_MAGIC, 10 + mRawStats.stats[STAT_INTELLIGENCE]);
    setStat(STAT_ACCURACY, 50 + mRawStats.stats[STAT_DEXTERITY]);
    setStat(STAT_SPEED, mRawStats.stats[STAT_DEXTERITY]);
}

void Player::setInventory(const std::vector<unsigned int> &inven)
{
    inventory = inven;
}

bool Player::addInventory(unsigned int itemId)
{
    // If required weight could be tallied to see if player can pick up more.
    inventory.push_back(itemId);
    return true;
}

bool Player::delInventory(unsigned int itemId)
{
    for (std::vector<unsigned int>::iterator i = inventory.begin();
         i != inventory.end(); i++) {
        if (*i == itemId) {
            inventory.erase(i);
            return true;
        }
    }
    return false;
}

bool Player::hasItem(unsigned int itemId)
{
    for (std::vector<unsigned int>::iterator i = inventory.begin();
         i != inventory.end(); i++)
    {
        if (*i == itemId)
            return true;
    }
    return false;
}

bool Player::equip(unsigned int itemId, unsigned char slot)
{
    // currently this is too simplistic and doesn't check enough
    // but until further functionality is implemented in the
    // server it will suffice
    if (slot < MAX_EQUIP_SLOTS) {
        equipment[slot] = itemId;
        return true;
    } else
        return false;
}

bool Player::unequip(unsigned char slot)
{
    // NOTE: 0 will be invalid item id (or we could use key/value pairs)
    equipment[slot] = 0;
    return true;
}
