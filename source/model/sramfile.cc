/*
 * Secret of Evermore SRAM Editor
 * Copyright (C) 2006 emuWorks
 * http://games.technoplaza.net/
 *
 * This file is part of Secret of Evermore SRAM Editor.
 *
 * Secret of Evermore SRAM Editor is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * Secret of Evermore SRAM Editor is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Secret of Evermore SRAM Editor; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
 
// $Id: sramfile.cc,v 1.22 2006/09/06 14:22:00 technoplaza Exp $

#include <cstring>
#include <fstream>

#include <QtCore/qendian.h>

#include "model/sramfile.hh"

using namespace soesrame;

const std::pair<int, int> SRAMFile::SRAM_ALCHEMY_OFFSETS[] =
    {
        std::pair<int, int>(0x1F7, 0x01),  // acid rain
        std::pair<int, int>(0x1F7, 0x02),  // atlas
        std::pair<int, int>(0x1F7, 0x04),  // barrier
        std::pair<int, int>(0x1F7, 0x08),  // call up
        std::pair<int, int>(0x1F7, 0x10),  // corrosion
        std::pair<int, int>(0x1F7, 0x20),  // crush
        std::pair<int, int>(0x1F7, 0x40),  // cure
        std::pair<int, int>(0x1F7, 0x80),  // defend
        
        std::pair<int, int>(0x1F8, 0x01),  // double drain
        std::pair<int, int>(0x1F8, 0x02),  // drain
        std::pair<int, int>(0x1F8, 0x04),  // energize
        std::pair<int, int>(0x1F8, 0x08),  // escape
        std::pair<int, int>(0x1F8, 0x10),  // explosion
        std::pair<int, int>(0x1F8, 0x20),  // fireball
        std::pair<int, int>(0x1F8, 0x40),  // fire power
        std::pair<int, int>(0x1F8, 0x80),  // flash
        
        std::pair<int, int>(0x1F9, 0x01),  // force field
        std::pair<int, int>(0x1F9, 0x02),  // hard ball
        std::pair<int, int>(0x1F9, 0x04),  // heal
        std::pair<int, int>(0x1F9, 0x08),  // lance
        std::pair<int, int>(0x1F9, 0x10),  // laser (dummied spell)
        std::pair<int, int>(0x1F9, 0x20),  // levitate
        std::pair<int, int>(0x1F9, 0x40),  // lightning storm
        std::pair<int, int>(0x1F9, 0x80),  // miracle cure
        
        std::pair<int, int>(0x1FA, 0x01),  // nitro
        std::pair<int, int>(0x1FA, 0x02),  // one up
        std::pair<int, int>(0x1FA, 0x04),  // reflect
        std::pair<int, int>(0x1FA, 0x08),  // regrowth
        std::pair<int, int>(0x1FA, 0x10),  // revealer
        std::pair<int, int>(0x1FA, 0x20),  // revive
        std::pair<int, int>(0x1FA, 0x40),  // slow burn
        std::pair<int, int>(0x1FA, 0x80),  // speed
        
        std::pair<int, int>(0x1FB, 0x01),  // sting
        std::pair<int, int>(0x1FB, 0x02),  // stop
        std::pair<int, int>(0x1FB, 0x04)   // super heal
    };
    
const std::pair<int, int> SRAMFile::SRAM_CHARM_OFFSETS[] =
    {
        std::pair<int, int>(0x200, 0x20),   // armor polish
        std::pair<int, int>(0x200, 0x40),   // chocobo egg
        std::pair<int, int>(0x200, 0x80),   // insect incense
        
        std::pair<int, int>(0x201, 0x01),   // jade disk
        std::pair<int, int>(0x201, 0x02),   // jaguar ring
        std::pair<int, int>(0x201, 0x04),   // magic gourd
        std::pair<int, int>(0x201, 0x08),   // moxa stick
        std::pair<int, int>(0x201, 0x10),   // oracle bone
        std::pair<int, int>(0x201, 0x20),   // ruby heart
        std::pair<int, int>(0x201, 0x40),   // silver sheath
        std::pair<int, int>(0x201, 0x80),   // staff of life
        
        std::pair<int, int>(0x202, 0x01),   // sun stone
        std::pair<int, int>(0x202, 0x02),   // thug's cloak
        std::pair<int, int>(0x202, 0x04)    // wizard's coin
    };
    
const std::pair<int, int> SRAMFile::SRAM_WEAPON_OFFSETS[] =
    {
        std::pair<int, int>(0x279, 0x02),  // bone crusher
        std::pair<int, int>(0x279, 0x04),  // gladiator sword
        std::pair<int, int>(0x279, 0x08),  // crusader sword
        std::pair<int, int>(0x279, 0x10),  // neutron blade
        
        std::pair<int, int>(0x279, 0x20),  // spider's claw
        std::pair<int, int>(0x279, 0x40),  // bronze axe
        std::pair<int, int>(0x279, 0x80),  // knight basher
        std::pair<int, int>(0x27A, 0x01),  // atom smasher
        
        std::pair<int, int>(0x27A, 0x02),  // horn spear
        std::pair<int, int>(0x27A, 0x04),  // bronze spear
        std::pair<int, int>(0x27A, 0x08),  // lance
        std::pair<int, int>(0x27A, 0x10),  // laser lance
        
        std::pair<int, int>(0x27A, 0x20)   // bazooka
    };

SRAMFile::SRAMFile(const QString &filename) throw(InvalidSRAMFileException)
    : modified(false) {
    std::ifstream file(filename.toAscii().data(), 
                       std::ios_base::in | std::ios_base::binary);
    
    if (!file) {
        throw InvalidSRAMFileException(ISFE_FILENOTFOUND);
    }
    
    file.seekg(0, std::ios_base::end);
    
    if (file.tellg() != static_cast<std::streampos>(SRAM_FILE_SIZE)) {
        throw InvalidSRAMFileException(ISFE_INVALIDSIZE);
    }
    
    file.seekg(0, std::ios_base::beg);
    file.read(reinterpret_cast<char *>(sram), SRAM_FILE_SIZE);
    file.close();
    
    bool valid = false;
    
    for (int game = 3; game >= 0; --game) {
        if (checksum(game) == getChecksum(game)) {
            valid = true;
            this->valid[game] = true;
            setGame(game);
        }
    }
    
    if (!valid) {
        throw InvalidSRAMFileException(ISFE_NOVALIDGAMES);
    }
}

quint16 SRAMFile::checksum(int game) const {
    quint32 checksum = 0x43F;
    
    for (int i = 2; i < SRAM_GAME_SIZE - 1; ++i) {
        unsigned char temp = checksum;
        temp += sram[SRAM_GAME_OFFSET + i + game * SRAM_GAME_SIZE];
        
        checksum &= 0xFF00;
        checksum |= temp;
        checksum <<= 1;
        
        if (checksum > 0xFFFF) {
            checksum -= 0xFFFF;
        }
    }
    
    return static_cast<quint16>(checksum);
}

bool SRAMFile::save(const QString &filename) {
    for (int game = 0; game < 4; ++game) {
        if (isValid(game)) {
            setChecksum(game, checksum(game));
        }
    }
    
    std::ofstream file(filename.toAscii().data(),
                       std::ios_base::out | std::ios_base::binary);
    
    if (!file) {
        return false;
    }
    
    file.write(reinterpret_cast<char *>(sram), SRAM_FILE_SIZE);
    
    if (file.tellp() != static_cast<std::streampos>(SRAM_FILE_SIZE)) {
        return false;
    }
    
    file.close();
    modified = false;
    
    return true;
}

bool SRAMFile::hasAlchemy(enum sf_alchemy alchemy) const {
    Q_ASSERT(isValid(getGame()));
    
    return (offset[SRAM_ALCHEMY_OFFSETS[alchemy].first] &
            SRAM_ALCHEMY_OFFSETS[alchemy].second);
}

void SRAMFile::setAlchemy(enum sf_alchemy alchemy, bool have) {
    Q_ASSERT(isValid(getGame()));
    
    unsigned char *data = offset + SRAM_ALCHEMY_OFFSETS[alchemy].first;
    
    if (have) {
        *data |= SRAM_ALCHEMY_OFFSETS[alchemy].second;
    } else {
        *data &= ~SRAM_ALCHEMY_OFFSETS[alchemy].second;
    }
    
    modified = true;
}

std::pair<int, int> SRAMFile::getAlchemyLevel(enum sf_alchemy alchemy) const {
    Q_ASSERT(isValid(getGame()));
    
    return std::pair<int, int>
        (offset[SRAM_ALCHEMYMAJORLEVELS_OFFSET + (alchemy * 2)],
         offset[SRAM_ALCHEMYMINORLEVELS_OFFSET + (alchemy * 2)]); 
}

void SRAMFile::setAlchemyLevel(enum sf_alchemy alchemy,
                               std::pair<int, int> level) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((level.first >= 0) && (level.first < 10));
    Q_ASSERT((level.second >= 0) && (level.second < 100));
    
    offset[SRAM_ALCHEMYMAJORLEVELS_OFFSET + (alchemy * 2)] = level.first;
    offset[SRAM_ALCHEMYMINORLEVELS_OFFSET + (alchemy * 2)] = level.second;
    
    modified = true;
}

std::pair<int, int> SRAMFile::getAttackLevel() const {
    Q_ASSERT(isValid(getGame()));
    
    return std::pair<int, int>
        (offset[SRAM_DOG_ATTACKLEVEL_OFFSET + 1],
         offset[SRAM_DOG_ATTACKLEVEL_OFFSET]);
}

void SRAMFile::setAttackLevel(std::pair<int, int> level) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((level.first >= 1) && (level.first < 4));
    Q_ASSERT((level.second >= 0) && (level.second < 256));
    
    offset[SRAM_DOG_ATTACKLEVEL_OFFSET + 1] = level.first;
    offset[SRAM_DOG_ATTACKLEVEL_OFFSET] = level.second;
    
    modified = true;
}

bool SRAMFile::hasCharm(enum sf_charm charm) const {
    Q_ASSERT(isValid(getGame()));
    
    return (offset[SRAM_CHARM_OFFSETS[charm].first] &
            SRAM_CHARM_OFFSETS[charm].second);
}

void SRAMFile::setCharm(enum sf_charm charm, bool have) {
    Q_ASSERT(isValid(getGame()));
    
    unsigned char *data = offset + SRAM_CHARM_OFFSETS[charm].first;
    
    if (have) {
        *data |= SRAM_CHARM_OFFSETS[charm].second;
    } else {
        *data &= ~SRAM_CHARM_OFFSETS[charm].second;
    }
    
    modified = true;
}

quint16 SRAMFile::getChecksum(int game) const {
    const quint16 *data =
        reinterpret_cast<const quint16 *>(sram + SRAM_GAME_OFFSET +
                                          game * SRAM_GAME_SIZE +
                                          SRAM_CHECKSUM_OFFSET);
    
    return qFromLittleEndian(*data);
}

void SRAMFile::setChecksum(int game, quint16 checksum) {
    quint16 *data = reinterpret_cast<quint16 *>(sram + SRAM_GAME_OFFSET +
                                                game * SRAM_GAME_SIZE +
                                                SRAM_CHECKSUM_OFFSET);
    
    *data = qToLittleEndian(checksum);
}

quint16 SRAMFile::getCurrentHP(enum sf_hero hero) const {
    Q_ASSERT(isValid(getGame()));
    
    const quint16 *data =
        reinterpret_cast<const quint16 *>(offset +
                                          ((hero == SF_BOY) ?
                                           SRAM_BOY_CURRENTHP_OFFSET :
                                           SRAM_DOG_CURRENTHP_OFFSET));
                                      
    return qFromLittleEndian(*data);
}

void SRAMFile::setCurrentHP(enum sf_hero hero, quint16 hp) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((hp >= 0) && (hp < 1000));
    
    quint16 *data = reinterpret_cast<quint16 *>(offset +
                                                ((hero == SF_BOY) ?
                                                 SRAM_BOY_CURRENTHP_OFFSET :
                                                 SRAM_DOG_CURRENTHP_OFFSET));
                                                 
    *data = qToLittleEndian(hp);
    modified = true;
}

quint32 SRAMFile::getExperience(enum sf_hero hero) const {
    Q_ASSERT(isValid(getGame()));
    
    const quint32 *data =
        reinterpret_cast<const quint32 *>(offset +
                                          ((hero == SF_BOY) ?
                                           SRAM_BOY_EXPERIENCE_OFFSET :
                                           SRAM_DOG_EXPERIENCE_OFFSET));
                                           
    return (qFromLittleEndian(*data) & 0xFFFFFF);
}

void SRAMFile::setExperience(enum sf_hero hero, quint32 experience) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((experience >= 0) && (experience < 16777216));
    
    unsigned char *data = offset + ((hero == SF_BOY) ?
                                    SRAM_BOY_EXPERIENCE_OFFSET :
                                    SRAM_DOG_EXPERIENCE_OFFSET);
    
    data[0] = experience;
    data[1] = experience >> 8;
    data[2] = experience >> 16;
    
    modified = true;
}

void SRAMFile::setGame(int game) {
    Q_ASSERT((game >= 0) && (game < 4));
    
    this->game = game;
    offset = sram + SRAM_GAME_OFFSET + (game * SRAM_GAME_SIZE);
}

int SRAMFile::getIngredient(enum sf_ingredient ingredient) const {
    Q_ASSERT(isValid(getGame()));
    
    return offset[SRAM_INGREDIENTS_OFFSET + ingredient];
}

void SRAMFile::setIngredient(enum sf_ingredient ingredient, int count) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((count >= 0) && (count < 100));
    
    offset[SRAM_INGREDIENTS_OFFSET + ingredient] = count;
    modified = true;
}

int SRAMFile::getItem(enum sf_item item) const {
    Q_ASSERT(isValid(getGame()));
    
    return offset[SRAM_ITEMS_OFFSET + item];
}

void SRAMFile::setItem(enum sf_item item, int count) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((count >= 0) && (count < 100));
    
    offset[SRAM_ITEMS_OFFSET + item] = count;
    modified = true;
}

int SRAMFile::getLevel(enum sf_hero hero) const {
    Q_ASSERT(isValid(getGame()));
    
    return offset[((hero == SF_BOY) ?
                   SRAM_BOY_LEVEL_OFFSET :
                   SRAM_DOG_LEVEL_OFFSET)];
}

void SRAMFile::setLevel(enum sf_hero hero, int level) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((level >= 1) && (level < 100));
    
    offset[((hero == SF_BOY) ?
            SRAM_BOY_LEVEL_OFFSET :
            SRAM_DOG_LEVEL_OFFSET)] = level;
    modified = true;
}

quint16 SRAMFile::getMaxHP(enum sf_hero hero) const {
    Q_ASSERT(isValid(getGame()));
    
    const quint16 *data =
        reinterpret_cast<const quint16 *>(offset +
                                          ((hero == SF_BOY) ?
                                           SRAM_BOY_MAXHP_OFFSET :
                                           SRAM_DOG_MAXHP_OFFSET));
                                      
    return qFromLittleEndian(*data);
}

void SRAMFile::setMaxHP(enum sf_hero hero, quint16 hp) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((hp >= 0) && (hp < 1000));
    
    quint16 *data = reinterpret_cast<quint16 *>(offset +
                                                ((hero == SF_BOY) ?
                                                 SRAM_BOY_MAXHP_OFFSET :
                                                 SRAM_DOG_MAXHP_OFFSET));
                                                 
    *data = qToLittleEndian(hp);
    modified = true;
}

quint32 SRAMFile::getMoney(enum sf_money money) const {
    Q_ASSERT(isValid(getGame()));
    
    const quint32 *data =
        reinterpret_cast<const quint32 *>(offset +
                                          SRAM_MONEY_OFFSET + (money * 3));
                                          
    return (qFromLittleEndian(*data) & 0xFFFFFF);
}

void SRAMFile::setMoney(enum sf_money money, quint32 count) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((count >= 0) && (count < 16777216));
    
    unsigned char *data = offset + SRAM_MONEY_OFFSET + (money * 3);
    
    data[0] = count;
    data[1] = count >> 8;
    data[2] = count >> 16;
    
    modified = true;
}

QString SRAMFile::getName(enum sf_hero hero) const {
    Q_ASSERT(isValid(getGame()));
    
    const char *data =
        reinterpret_cast<const char *>(offset +
                                       ((hero == SF_BOY) ?
                                        SRAM_BOY_NAME_OFFSET :
                                        SRAM_DOG_NAME_OFFSET));
                                               
    return QString::fromAscii(data);
}

void SRAMFile::setName(enum sf_hero hero, const QString &name) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT(name.length() <= 15);
    
    char *data = reinterpret_cast<char *>(offset + ((hero == SF_BOY) ?
                                                    SRAM_BOY_NAME_OFFSET :
                                                    SRAM_DOG_NAME_OFFSET));
                                                    
    std::strcpy(data, name.left(15).toAscii().data());
    
    modified = true;
}

quint16 SRAMFile::getTradeGood(enum sf_tradegood tradegood) const {
    Q_ASSERT(isValid(getGame()));
    
    const quint16 *data =
        reinterpret_cast<const quint16 *>(offset + SRAM_TRADEGOODS_OFFSET);
    
    return qFromLittleEndian(data[tradegood]);
}

void SRAMFile::setTradeGood(enum sf_tradegood tradegood, quint16 count) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT((count >= 0) && (count < 100));
    
    quint16 *data =
        reinterpret_cast<quint16 *>(offset + SRAM_TRADEGOODS_OFFSET);
    
    data[tradegood] = qToLittleEndian(count);
    modified = true;
}

bool SRAMFile::hasWeapon(enum sf_weapon weapon) const {
    Q_ASSERT(isValid(getGame()));
    
    return (offset[SRAM_WEAPON_OFFSETS[weapon].first] &
            SRAM_WEAPON_OFFSETS[weapon].second);
}

void SRAMFile::setWeapon(enum sf_weapon weapon, bool have) {
    Q_ASSERT(isValid(getGame()));
    
    unsigned char *data = offset + SRAM_WEAPON_OFFSETS[weapon].first;
    
    if (have) {
        *data |= SRAM_WEAPON_OFFSETS[weapon].second;
    } else {
        *data &= ~SRAM_WEAPON_OFFSETS[weapon].second;
    }
    
    modified = true;
}

std::pair<int, int> SRAMFile::getWeaponLevel(enum sf_weapon weapon) const {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT(weapon != SF_BAZOOKA);
    
    const unsigned char *data =
        offset + SRAM_WEAPONLEVELS_OFFSET + (weapon * 2);
    
    return std::pair<int, int>(data[1], data[0]);
}

void SRAMFile::setWeaponLevel(enum sf_weapon weapon,
                              std::pair<int, int> level) {
    Q_ASSERT(isValid(getGame()));
    Q_ASSERT(weapon != SF_BAZOOKA);
    Q_ASSERT((level.first >= 1) && (level.first < 4));
    Q_ASSERT((level.second >= 0) && (level.second < 256));
    
    unsigned char *data = offset + SRAM_WEAPONLEVELS_OFFSET + (weapon * 2);
    
    data[1] = level.first;
    data[0] = level.second;
    
    modified = true;
}

