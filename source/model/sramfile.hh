/*
 * Secret of Evermore SRAM Editor
 * Copyright (C) 2006,2008 emuWorks
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
 
// $Id: sramfile.hh,v 1.23 2008/01/24 01:18:03 technoplaza Exp $

#ifndef SOESRAME_SRAMFILE_HH_
#define SOESRAME_SRAMFILE_HH_

#include <utility>

#include <QString>

#include "exceptions/invalidsramfileexception.hh"

namespace soesrame {
    /// base major alchemy levels offset
    const int SRAM_ALCHEMYMAJORLEVELS_OFFSET = 0x19B;
    
    /// base minor alchemy levels offset
    const int SRAM_ALCHEMYMINORLEVELS_OFFSET = 0x155;
    
    /// offset of the boy's current HP
    const int SRAM_BOY_CURRENTHP_OFFSET = 0x6E;
    
    /// offset of the boy's experience
    const int SRAM_BOY_EXPERIENCE_OFFSET = 0x9A;
    
    /// offset of the boy's level
    const int SRAM_BOY_LEVEL_OFFSET = 0x9D;
    
    /// offset of the boy's max HP
    const int SRAM_BOY_MAXHP_OFFSET = 0x8E;
    
    /// offset of the boy's name
    const int SRAM_BOY_NAME_OFFSET = 0x26;
    
    /// the starting value for the checksum in the US version
    const int SRAM_CHECKSUM_START_US = 0x43F;
    
    /// the starting value for the checksum in the European versions
    const int SRAM_CHECKSUM_START_EUROPE = 0x16FF;
    
    /// offset of the game's checksum
    const int SRAM_CHECKSUM_OFFSET = 0x0;
    
    /// offset of the dog's current HP
    const int SRAM_DOG_CURRENTHP_OFFSET = 0xAF;
    
    /// offset of the dog's experience
    const int SRAM_DOG_EXPERIENCE_OFFSET = 0xDB;
    
    /// offset of the dog's level
    const int SRAM_DOG_LEVEL_OFFSET = 0xDE;
    
    /// offset of the dog's max HP
    const int SRAM_DOG_MAXHP_OFFSET = 0xCF;
    
    /// offset of the dog's name
    const int SRAM_DOG_NAME_OFFSET = 0x4A;
    
    /// offset of the dog's attack level
    const int SRAM_DOG_ATTACKLEVEL_OFFSET = 0x13D;
    
    /// size of the SRAM file
    const int SRAM_FILE_SIZE = 0x2000;
    
    /// base offset of the game data in the SRAM
    const int SRAM_GAME_OFFSET = 0x2;
    
    /// individual save game size
    const int SRAM_GAME_SIZE = 0x331;
    
    /// base alchemy ingredient offset
    const int SRAM_INGREDIENTS_OFFSET = 0x289;
    
    /// base item offset
    const int SRAM_ITEMS_OFFSET = 0x29F;
    
    /// base money offset
    const int SRAM_MONEY_OFFSET = 0xFC;
    
    /// base tradegood offset
    const int SRAM_TRADEGOODS_OFFSET = 0x315;
    
    /// base weapon levels offset
    const int SRAM_WEAPONLEVELS_OFFSET = 0x115;
    
    /// the alchemys
    enum sf_alchemy {
        SF_ACIDRAIN, SF_ATLAS, SF_BARRIER, SF_CALLUP, SF_CORROSION, SF_CRUSH,
        SF_CURE, SF_DEFEND, SF_DOUBLEDRAIN, SF_DRAIN, SF_ENERGIZE, SF_ESCAPE,
        SF_EXPLOSION, SF_FIREBALL, SF_FIREPOWER, SF_FLASH, SF_FORCEFIELD,
        SF_HARDBALL, SF_HEAL, SF_LANCEALCHEMY, SF_LASERDUMMY, SF_LEVITATE,
        SF_LIGHTNINGSTORM, SF_MIRACLECURE, SF_NITRO, SF_ONEUP, SF_REFLECT,
        SF_REGROWTH, SF_REVEALER, SF_REVIVE, SF_SLOWBURN, SF_SPEED, SF_STING,
        SF_STOP, SF_SUPERHEAL
    };
    
    /// the charms
    enum sf_charm {
        SF_ARMORPOLISH, SF_CHOCOBOEGG, SF_INSECTINCENSE, SF_JADEDISK,
        SF_JAGUARRING, SF_MAGICGOURD, SF_MOXASTICK, SF_ORACLEBONE, SF_RUBYHEART,
        SF_SILVERSHEATH, SF_STAFFOFLIFE, SF_SUNSTONE, SF_THUGSCLOAK,
        SF_WIZARDSCOIN
    };
    
    /// the heros
    enum sf_hero {
        SF_BOY, SF_DOG
    };
    
    /// the alchemy ingredients
    enum sf_ingredient {
        SF_WAX, SF_WATER, SF_VINEGAR, SF_ROOT, SF_OIL, SF_MUSHROOM,
        SF_MUDPEPPER, SF_METEORITE, SF_LIMESTONE, SF_IRON, SF_GUNPOWDER,
        SF_GREASE, SF_FEATHER, SF_ETHANOL, SF_DRYICE, SF_CRYSTAL, SF_CLAY,
        SF_BRIMSTONE, SF_BONE, SF_ATLASMEDALLION, SF_ASH, SF_ACORN
    };
    
    /// the items
    enum sf_item {
        SF_PETAL, SF_NECTAR, SF_HONEY, SF_DOGBISCUIT, SF_WINGS, SF_ESSENCE,
        SF_PIXIEDUST, SF_CALLBEAD, SF_GRASSVEST, SF_SHELLPLATE, SF_DINOSKIN,
        SF_BRONZEARMOR, SF_STONEVEST, SF_CENTURIONCAPE, SF_SILVERMAIL,
        SF_GOLDPLATEDVEST, SF_SHININGARMOR, SF_MAGNAMAIL, SF_TITANIUMVEST,
        SF_VIRTUALVEST, SF_GRASSHAT, SF_SHELLHAT, SF_DINOHELM, SF_BRONZEHELMET,
        SF_OBSIDIANHELM, SF_CENTURIONHELM, SF_TITANSCROWN, SF_DRAGONHELM,
        SF_KNIGHTSHELM, SF_LIGHTNINGHELM, SF_OLDRELIABLE, SF_BRAINSTORM,
        SF_VINEBRACELET, SF_MAMMOTHGUARD, SF_CLAWGUARD, SF_SERPENTBRACER,
        SF_BRONZEGAUNTLET, SF_GLOVESOFRA, SF_IRONBRACER, SF_MAGICIANSRING,
        SF_DRAGONSCLAW, SF_CYBERGLOVE, SF_PROTECTORRING, SF_VIRTUALGLOVE,
        SF_LEATHERCOLLAR, SF_SPIKYCOLLAR, SF_DEFENDERCOLLAR, SF_SPOTSCOLLAR,
        SF_THUNDERBALL, SF_PARTICLEBOMB, SF_CRYOBLAST
    };
    
    /// the money types
    enum sf_money {
        SF_TALONS, SF_JEWELS, SF_GOLDCOINS, SF_CREDITS
    };
    
    /// the game regions
    enum sf_region {
        REGION_UNITEDSTATES, REGION_ENGLAND,
        REGION_FRANCE, REGION_GERMANY, REGION_SPAIN
    };
    
    /// the market trading goods
    enum sf_tradegood {
        SF_ANNIHILATIONAMULET, SF_BEADS, SF_CERAMICPOT, SF_CHICKEN,
        SF_GOLDENJACKAL, SF_JEWELEDSCARAB, SF_LIMESTONETABLET, SF_PERFUME,
        SF_RICE, SF_SPICE, SF_SOUVENIRSPOON, SF_TAPESTRY, SF_TICKETFOREXHIBITION
    };
    
    /// the boy's weapons
    enum sf_weapon {
        SF_BONECRUSHER, SF_GLADIATORSWORD, SF_CRUSADERSWORD, SF_NEUTRONBLADE,
        SF_SPIDERSCLAW, SF_BRONZEAXE, SF_KNIGHTBASHER, SF_ATOMSMASHER,
        SF_HORNSPEAR, SF_BRONZESPEAR, SF_LANCEWEAPON, SF_LASERLANCE, SF_BAZOOKA
    };
    
    /// model of a Secret of Evermore SRAM file
    class SRAMFile {
    private:
        int game;
        enum sf_region region;
        unsigned char *offset;
        unsigned char sram[SRAM_FILE_SIZE];
        bool modified, valid[4];
        
        /// the alchemy have/have not offsets
        static const std::pair<int, int> SRAM_ALCHEMY_OFFSETS[];
        
        /// the charm have/have not offsets
        static const std::pair<int, int> SRAM_CHARM_OFFSETS[];
        
        /// the weapon have/have not offsets
        static const std::pair<int, int> SRAM_WEAPON_OFFSETS[];
        
        /**
         * Calculates the checksum for one of the save games.
         *
         * @param game The game to calculate the checksum for.
         *
         * @return The checksum.
         */
        quint16 checksum(int game) const;
        
        /**
         * Gets the checksum value.
         *
         * @param game The game to get the checksum for.
         *
         * @return The checksum.
         */
        quint16 getChecksum(int game) const;
        
        /**
         * Sets the game's checksum value.
         *
         * @param game The game to set the checksum for.
         * @param checksum The new checksum.
         */
        void setChecksum(int game, quint16 checksum);
        
    public:
        /**
         * Creates a new SRAMFile.
         *
         * @param filename The SRAM file to load.
         * @param region The game's region.
         *
         * @throws InvalidSRAMFileException if the file is not a valid Secret of
         *         Evermore SRAM file.
         */
        SRAMFile(const QString &filename, enum sf_region region)
            throw(InvalidSRAMFileException);
        
        /**
         * Saves this SRAMFile back to disk.
         *
         * @param filename The filename to save to.
         *
         * @return true on success; false otherwise.
         */
        bool save(const QString &filename);
        
        /**
         * Checks whether the boy knows a particular alchemy.
         *
         * @param alchemy The alchemy to check for.
         *
         * @return true if the boy knows the alchemy; false otherwise.
         */
        bool hasAlchemy(enum sf_alchemy alchemy) const;
        
        /**
         * Sets whether the boy knows a particular alchemy.
         *
         * @param alchemy The alchemy to set.
         * @param have true to give; false to take away.
         */
        void setAlchemy(enum sf_alchemy alchemy, bool have = true);
        
        /**
         * Gets the alchemy level.
         *
         * @param alchemy The alchemy.
         *
         * @return The level.
         */
        std::pair<int, int> getAlchemyLevel(enum sf_alchemy alchemy) const;
            
        /**
         * Sets the alchemy level.
         *
         * @param alchemy The alchemy.
         * @param level The new level.
         */
        void setAlchemyLevel(enum sf_alchemy alchemy,
                             std::pair<int, int> level);
        
        /**
         * Gets the dog's attack level.
         *
         * @return The attack level (major, progress to next).
         */
        std::pair<int, int> getAttackLevel() const;
        
        /**
         * Sets the dog's attack level.
         *
         * @param level The new level.
         */
        void setAttackLevel(std::pair<int, int> level);
        
        /**
         * Checks whether the heros have a particular charm.
         *
         * @param charm The charm to check for.
         *
         * @return true if they have the charm; false otherwise.
         */
        bool hasCharm(enum sf_charm charm) const;
        
        /**
         * Sets whether the heros have a particular charm.
         *
         * @param charm The charm to set.
         * @param have true to give; false to take away.
         */
        void setCharm(enum sf_charm charm, bool have = true);
        
        /**
         * Gets the current HP of one of the heros.
         *
         * @param hero Which hero's current HP to get.
         *
         * @return The hero's current HP.
         */
        quint16 getCurrentHP(enum sf_hero hero) const;
        
        /**
         * Sets the current HP of one of the heros.
         *
         * @param hero Which hero to set.
         * @param hp The new current HP.
         */
        void setCurrentHP(enum sf_hero hero, quint16 hp);
        
        /**
         * Gets the experience of one of the heros.
         *
         * @param hero Which hero's experience to get.
         *
         * @return The hero's experience.
         */
        quint32 getExperience(enum sf_hero hero) const;
        
        /**
         * Sets the experience of one of the heros.
         *
         * @param hero Which hero to set.
         * @param experience The new experience.
         */
        void setExperience(enum sf_hero hero, quint32 experience);
        
        /**
         * Gets the current game.
         *
         * @return The game.
         */
        int getGame() const;
        
        /**
         * Sets the current game.
         *
         * @param game The new game.
         */
        void setGame(int game = 0);
        
        /**
         * Gets the inventory count for a particular alchemy ingredient.
         *
         * @param ingredient The ingredient.
         *
         * @return The inventory count.
         */
        int getIngredient(enum sf_ingredient ingredient) const;
        
        /**
         * Sets the inventory count for a particular alchemy ingredient.
         *
         * @param ingredient The ingredient.
         * @param count The new inventory count.
         */
        void setIngredient(enum sf_ingredient ingredient, int count);
        
        /**
         * Gets the inventory count for a particular item.
         *
         * @param item The item.
         *
         * @return The inventory count.
         */
        int getItem(enum sf_item item) const;
        
        /**
         * Sets the inventory count for a particular item.
         *
         * @param item The item.
         * @param count The new inventory count.
         */
        void setItem(enum sf_item item, int count);
        
        /**
         * Gets the level of one of the heros.
         *
         * @param hero Which hero's level to get.
         *
         * @return The hero's level.
         */
        int getLevel(enum sf_hero hero) const;
        
        /**
         * Sets the level of one of the heros.
         *
         * @param hero Which hero's level to set.
         * @param level The new level.
         */
        void setLevel(enum sf_hero hero, int level);
        
        /**
         * Gets the max HP of one of the heros.
         *
         * @param hero Which hero's max HP to get.
         *
         * @return The hero's max HP.
         */
        quint16 getMaxHP(enum sf_hero hero) const;
        
        /**
         * Sets the max HP of one of the heros.
         *
         * @param hero Which heros' max HP to set.
         * @param hp The new max HP.
         */
        void setMaxHP(enum sf_hero hero, quint16 hp);
        
        /**
         * Checks whether this SRAMFile has been modified.
         *
         * @return true if modified; false otherwise.
         */
        bool isModified() const;
        
        /**
         * Gets the money count.
         *
         * @param money The money type.
         *
         * @return The money count.
         */
        quint32 getMoney(enum sf_money money) const;
        
        /**
         * Sets the money count.
         *
         * @param money The money type.
         * @param count The new money count.
         */
        void setMoney(enum sf_money money, quint32 count);
        
        /**
         * Gets the name of one of the heros.
         *
         * @param hero Which hero's name to get.
         *
         * @return The name.
         */
        QString getName(enum sf_hero hero) const;
        
        /**
         * Sets the name of one of the heros.
         *
         * @param hero Which hero's name to set.
         * @param name The new name.
         */
        void setName(enum sf_hero hero, const QString &name);
        
        /**
         * Gets the inventory count for one of the trade goods.
         *
         * @param tradegood The trade good.
         *
         * @return The inventory count.
         */
        quint16 getTradeGood(enum sf_tradegood tradegood) const;
        
        /**
         * Sets the inventory count for one of the trade goods.
         *
         * @param tradegood The trade good.
         * @param count The new inventory count.
         */
        void setTradeGood(enum sf_tradegood tradegood, quint16 count);
        
        /**
         * Checks whether the boy has a particular weapon.
         *
         * @param weapon The weapon to check for.
         *
         * @return true if the boy has the weapon; false otherwise.
         */
        bool hasWeapon(enum sf_weapon weapon) const;
        
        /**
         * Sets whether the boy has a particular weapon.
         *
         * @param weapon The weapon to set.
         * @param have true to give; false to take away.
         */
        void setWeapon(enum sf_weapon weapon, bool have = true);
        
        /**
         * Gets the weapon level for one of the weapons.
         *
         * @param weapon The weapon.
         *
         * @return The weapon level (major level, progress to next).
         */
        std::pair<int, int> getWeaponLevel(enum sf_weapon weapon) const;
        
        /**
         * Sets the weapon level for one of the weapons.
         *
         * @param weapon The weapon.
         * @param level The new level.
         */
        void setWeaponLevel(enum sf_weapon weapon, std::pair<int, int> level);
        
        /**
         * Checks if a save game is a valid save.
         *
         * @param game The game to check (0-3).
         *
         * @return true if the game is valid; false otherwise.
         */
        bool isValid(int game) const;
    };
    
    inline int SRAMFile::getGame() const
        { return game; }
        
    inline bool SRAMFile::isModified() const
        { return modified; }
        
    inline bool SRAMFile::isValid(int game) const
        {
            Q_ASSERT((game >= 0) && (game < 4));
            return valid[game];
        }
}

#endif

