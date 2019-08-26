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
 
// $Id: mainwindow.hh,v 1.16 2006/09/02 19:49:22 technoplaza Exp $

#ifndef _SOESRAME_MAINWINDOW_HH_
#define _SOESRAME_MAINWINDOW_HH_

#include "ui_mainwindow.h"

#include "model/sramfile.hh"

namespace soesrame {
    class MainWindow : public QMainWindow {
        Q_OBJECT
        
    private:
        QString *sramFile;
        Ui::MainWindow ui;
        SRAMFile *sram;
        bool ignoreSignals, open;
        
        /**
         * Checks whether the user really wants to close.
         *
         * @return true to close; false otherwise.
         */
        bool confirmClose();
        
        /**
         * Opens an SRAM file.
         *
         * @param filename The file.
         */
        void openSRAM(const QString &filename);
        
        /**
         * Sets the have/have not property of one of the alchemys.
         *
         * @param alchemy The alchemy.
         * @param state 1 to give; 0 to take away.
         */
        void setAlchemy(enum sf_alchemy alchemy, int state);
        
        /**
         * Sets the major level of one of the alchemys.
         *
         * @param alchemy The alchemy.
         * @param value The new value.
         */
        void setAlchemyLevelMajor(enum sf_alchemy alchemy, int value);
        
        /**
         * Sets the minor level of one of the alchemys.
         *
         * @param alchemy The alchemy.
         * @param text The new value.
         */
        void setAlchemyLevelMinor(enum sf_alchemy alchemy, const QString &text);
        
        /**
         * Sets the have/have not property of one of the charms.
         *
         * @param charm The charm.
         * @param state 1 to give; 0 to take away.
         */
        void setCharm(enum sf_charm charm, int state);
        
        /**
         * Sets the current game being edited.
         *
         * @param game The game to edit (0-3).
         */
        void setGame(int game);
        
        /**
         * Sets the amount of one of the alchemy ingredients.
         *
         * @param ingredient The ingredient.
         * @param text The amount.
         */
        void setIngredient(enum sf_ingredient ingredient, const QString &text);
        
        /**
         * Sets the amount of one of the items.
         *
         * @param item The item.
         * @param text The amount.
         */
        void setItem(enum sf_item item, const QString &text);
        
        /**
         * Sets the amount of one of the money types.
         *
         * @param money The money type.
         * @param text The amount.
         */
        void setMoney(enum sf_money money, const QString &text);
        
        /**
         * Sets the amount of one of the trade goods.
         *
         * @param tradegood The trade good.
         * @param text The amount.
         */
        void setTradeGood(enum sf_tradegood tradegood, const QString &text);
        
        /**
         * Sets the have/have not property of one of the weapons.
         *
         * @param weapon The weapon.
         * @param state 1 for give; 0 to take away.
         */
        void setWeapon(enum sf_weapon weapon, int state);
        
        /**
         * Sets the major level of one of the weapons.
         *
         * @param weapon The weapon.
         * @param value The new value.
         */
        void setWeaponLevelMajor(enum sf_weapon weapon, int value);
        
        /**
         * Sets the minor level of one of the weapons.
         *
         * @param weapon The weapon.
         * @param text The new value.
         */
        void setWeaponLevelMinor(enum sf_weapon weapon, const QString &text);
        
        /**
         * Shows the actual weapon/attack level on the status bar.
         *
         * @param level The weapon level.
         * @param weapon The weapon (SF_BAZOOKA for dog's attack level).
         */
        void showActualLevel(std::pair<int, int> level,
                             enum sf_weapon weapon = SF_BAZOOKA);
        
    signals:
        /**
         * Emitted when an SRAM file is opened.
         */
        void sramFileOpened();
        
        /**
         * Emitted when the UI needs updating.
         */
        void uiChanged();
        
    private slots:
        /**
         * Called when the sramFileOpened signal is emitted. Loads all controls
         * with the SRAM values.
         */
        void onSRAMFileOpened();
        
        /**
         * Called when the uiChanged signal is emitted. Updates UI controls
         * appropriate to the SRAM state.
         */
        void onUIChanged();
        
        /**
         * Called when the acid rain alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_acidRainCheck_stateChanged(int state);
        
        /**
         * Called when acid rain's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_acidRainSpinner_valueChanged(int value);
        
        /**
         * Called when acid rain's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_acidRainText_textEdited(const QString &text);
        
        /**
         * Called when the acorn ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_acornText_textEdited(const QString &text);
        
        /**
         * Called when the annihilation amulet count is changed.
         *
         * @param text The new count.
         */
        void on_annihilationAmuletText_textEdited(const QString &text);
        
        /**
         * Called when the armor polish charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_armorPolishCheck_stateChanged(int state);
        
        /**
         * Called when the ash ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_ashText_textEdited(const QString &text);
        
        /**
         * Called when the atlas alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_atlasCheck_stateChanged(int state);
        
        /**
         * Called when atlas's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_atlasSpinner_valueChanged(int value);
        
        /**
         * Called when atlas's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_atlasText_textEdited(const QString &text);
        
        /**
         * Called when the atlas medallion ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_atlasMedallionText_textEdited(const QString &text);

        /**
         * Called when the atom smasher is given or taken away.
         *
         * @param state The new check state.
         */
        void on_atomSmasherCheck_stateChanged(int state);
        
        /**
         * Called when the atom smasher's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_atomSmasherSpinner_valueChanged(int value);
        
        /**
         * Called when the atom smasher's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_atomSmasherText_textEdited(const QString &text);
        
        /**
         * Called when the barrier alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_barrierCheck_stateChanged(int state);
        
        /**
         * Called when barrier's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_barrierSpinner_valueChanged(int value);
        
        /**
         * Called when barrier's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_barrierText_textEdited(const QString &text);
        
        /**
         * Called when the bazooka is given or taken away.
         *
         * @param state The new check state.
         */
        void on_bazookaCheck_stateChanged(int state);
        
        /**
         * Called when the beads count is changed.
         *
         * @param text The new count.
         */
        void on_beadsText_textEdited(const QString &text);
        
        /**
         * Called when the bone ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_boneText_textEdited(const QString &text);
        
        /**
         * Called when the bone crusher is given or taken away.
         *
         * @param state The new check state.
         */
        void on_boneCrusherCheck_stateChanged(int state);
        
        /**
         * Called when the bone crusher's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_boneCrusherSpinner_valueChanged(int value);
        
        /**
         * Called when the bone crusher's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_boneCrusherText_textEdited(const QString &text);
        
        /**
         * Called when the boy's current HP is edited.
         *
         * @param text The new text.
         */
        void on_boyCurrentHPText_textEdited(const QString &text);
        
        /**
         * Called when the boy's experience is edited.
         *
         * @param text The new text.
         */
        void on_boyExperienceText_textEdited(const QString &text);
        
        /**
         * Called when the boy's level is edited.
         *
         * @param text The new text.
         */
        void on_boyLevelText_textEdited(const QString &text);
        
        /**
         * Called when the boy's max HP is edited.
         *
         * @param text The new text.
         */
        void on_boyMaxHPText_textEdited(const QString &text);
        
        /**
         * Called when the boy's name is edited.
         *
         * @param name The new name.
         */
        void on_boyNameText_textEdited(const QString &name);
        
        /**
         * Called when the brainstorm count is changed.
         *
         * @param text The text.
         */
        void on_brainstormText_textEdited(const QString &text);
        
        /**
         * Called when the brimstone ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_brimstoneText_textEdited(const QString &text);
        
        /**
         * Called when the bronze armor count is changed.
         *
         * @param text The text.
         */
        void on_bronzeArmorText_textEdited(const QString &text);
        
        /**
         * Called when the bronze axe is given or taken away.
         *
         * @param state The new check state.
         */
        void on_bronzeAxeCheck_stateChanged(int state);
        
        /**
         * Called when the bronze axe's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_bronzeAxeSpinner_valueChanged(int value);
        
        /**
         * Called when the bronze axe's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_bronzeAxeText_textEdited(const QString &text);
        
        /**
         * Called when the bronze gauntlet count is changed.
         *
         * @param text The text.
         */
        void on_bronzeGauntletText_textEdited(const QString &text);
        
        /**
         * Called when the bronze helmet count is changed.
         *
         * @param text The text.
         */
        void on_bronzeHelmetText_textEdited(const QString &text);
        
        /**
         * Called when the bronze spear is given or taken away.
         *
         * @param state The new check state.
         */
        void on_bronzeSpearCheck_stateChanged(int state);
        
        /**
         * Called when the bronze spear's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_bronzeSpearSpinner_valueChanged(int value);
        
        /**
         * Called when the bronze spear's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_bronzeSpearText_textEdited(const QString &text);
        
        /**
         * Called when the call bead count is changed.
         *
         * @param text The text.
         */
        void on_callBeadText_textEdited(const QString &text);
        
        /**
         * Called when the call up alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_callUpCheck_stateChanged(int state);
        
        /**
         * Called when call up's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_callUpSpinner_valueChanged(int value);
        
        /**
         * Called when call up's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_callUpText_textEdited(const QString &text);
        
        /**
         * Called when the centurion cape count is changed.
         *
         * @param text The text.
         */
        void on_centurionCapeText_textEdited(const QString &text);
        
        /**
         * Called when the centurion helm count is changed.
         *
         * @param text The text.
         */
        void on_centurionHelmText_textEdited(const QString &text);
        
        /**
         * Called when the ceramic pot count is changed.
         *
         * @param text The new count.
         */
        void on_ceramicPotText_textEdited(const QString &text);
        
        /**
         * Called when the chicken count is changed.
         *
         * @param text The new count.
         */
        void on_chickenText_textEdited(const QString &text);
        
        /**
         * Called when the chocobo egg charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_chocoboEggCheck_stateChanged(int state);
        
        /**
         * Called when the claw guard count is changed.
         *
         * @param text The text.
         */
        void on_clawGuardText_textEdited(const QString &text);
        
        /**
         * Called when the clay ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_clayText_textEdited(const QString &text);
        
        /**
         * Called when the corrosion alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_corrosionCheck_stateChanged(int state);
        
        /**
         * Called when corrosion's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_corrosionSpinner_valueChanged(int value);
        
        /**
         * Called when corrosion's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_corrosionText_textEdited(const QString &text);

        /**
         * Called when the credits are edited.
         *
         * @param text The new text.
         */
        void on_creditsText_textEdited(const QString &text);
        
        /**
         * Called when the crusader sword is given or taken away.
         *
         * @param state The new check state.
         */
        void on_crusaderSwordCheck_stateChanged(int state);
        
        /**
         * Called when the crusader sword's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_crusaderSwordSpinner_valueChanged(int value);
        
        /**
         * Called when the crusader sword's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_crusaderSwordText_textEdited(const QString &text);
        
        /**
         * Called when the crush alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_crushCheck_stateChanged(int state);
        
        /**
         * Called when crush's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_crushSpinner_valueChanged(int value);
        
        /**
         * Called when crush's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_crushText_textEdited(const QString &text);
        
        /**
         * Called when the cryo-blast count is changed.
         *
         * @param text The text.
         */
        void on_cryoBlastText_textEdited(const QString &text);
        
        /**
         * Called when the crystal ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_crystalText_textEdited(const QString &text);
        
        /**
         * Called when the cure alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_cureCheck_stateChanged(int state);
        
        /**
         * Called when cure's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_cureSpinner_valueChanged(int value);
        
        /**
         * Called when cure's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_cureText_textEdited(const QString &text);
        
        /**
         * Called when the cyberglove count is changed.
         *
         * @param text The text.
         */
        void on_cybergloveText_textEdited(const QString &text);
        
        /**
         * Called when the defend alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_defendCheck_stateChanged(int state);
        
        /**
         * Called when defend's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_defendSpinner_valueChanged(int value);
        
        /**
         * Called when defend's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_defendText_textEdited(const QString &text);
        
        /**
         * Called when the defender collar count is changed.
         *
         * @param text The text.
         */
        void on_defenderCollarText_textEdited(const QString &text);
        
        /**
         * Called when the dino helm count is changed.
         *
         * @param text The text.
         */
        void on_dinoHelmText_textEdited(const QString &text);
        
        /**
         * Called when the dino skin count is changed.
         *
         * @param text The text.
         */
        void on_dinoSkinText_textEdited(const QString &text);
        
        /**
         * Called when the dog's attack level (major) is edited.
         *
         * @param level The new attack level.
         */
        void on_dogAttackLevelSpinner_valueChanged(int level);
        
        /**
         * Called when the dog's attack level (minor) is edited.
         *
         * @param text The new text.
         */
        void on_dogAttackLevelText_textEdited(const QString &text);
        
        /**
         * Called when the dog biscuit count is changed.
         *
         * @param text The text.
         */
        void on_dogBiscuitText_textEdited(const QString &text);
        
        /**
         * Called when the dog's current HP is edited.
         *
         * @param text The new text.
         */
        void on_dogCurrentHPText_textEdited(const QString &text);
        
        /**
         * Called when the dog's experience is edited.
         *
         * @param text The new text.
         */
        void on_dogExperienceText_textEdited(const QString &text);
        
        /**
         * Called when the dog's level is edited.
         *
         * @param text The new text.
         */
        void on_dogLevelText_textEdited(const QString &text);
        
        /**
         * Called when the dog's max HP is edited.
         *
         * @param text The new text.
         */
        void on_dogMaxHPText_textEdited(const QString &text);
        
        /**
         * Called when the dog's name is edited.
         *
         * @param name The new name.
         */
        void on_dogNameText_textEdited(const QString &name);
        
        /**
         * Called when the double drain alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_doubleDrainCheck_stateChanged(int state);
        
        /**
         * Called when double drain's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_doubleDrainSpinner_valueChanged(int value);
        
        /**
         * Called when double drain's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_doubleDrainText_textEdited(const QString &text);
        
        /**
         * Called when the dragon helm count is changed.
         *
         * @param text The text.
         */
        void on_dragonHelmText_textEdited(const QString &text);
        
        /**
         * Called when the dragon's claw count is changed.
         *
         * @param text The text.
         */
        void on_dragonsClawText_textEdited(const QString &text);
        
        /**
         * Called when the drain alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_drainCheck_stateChanged(int state);
        
        /**
         * Called when drain's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_drainSpinner_valueChanged(int value);
        
        /**
         * Called when drain's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_drainText_textEdited(const QString &text);
        
        /**
         * Called when the dry ice ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_dryIceText_textEdited(const QString &text);
        
        /**
         * Called when the energize alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_energizeCheck_stateChanged(int state);
        
        /**
         * Called when energize's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_energizeSpinner_valueChanged(int value);
        
        /**
         * Called when energize's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_energizeText_textEdited(const QString &text);
        
        /**
         * Called when the escape alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_escapeCheck_stateChanged(int state);
        
        /**
         * Called when escape's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_escapeSpinner_valueChanged(int value);
        
        /**
         * Called when escape's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_escapeText_textEdited(const QString &text);
        
        /**
         * Called when the essence count is changed.
         *
         * @param text The text.
         */
        void on_essenceText_textEdited(const QString &text);
        
        /**
         * Called when the ethanol ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_ethanolText_textEdited(const QString &text);
        
        /**
         * Called when the explosion alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_explosionCheck_stateChanged(int state);
        
        /**
         * Called when explosion's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_explosionSpinner_valueChanged(int value);
        
        /**
         * Called when explosion's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_explosionText_textEdited(const QString &text);
        
        /**
         * Called when the feather ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_featherText_textEdited(const QString &text);
    
        /**
         * Called when close from the file menu is selected.
         *
         * @param checked Unused.
         */
        void on_fileClose_triggered(bool checked);
    
        /**
         * Called when exit from the file menu is selected.
         *
         * @param checked Unused.
         */
        void on_fileExit_triggered(bool checked);
        
        /**
         * Called when open from the file menu is selected.
         *
         * @param checked Unused.
         */
        void on_fileOpen_triggered(bool checked);
        
        /**
         * Called when save from the file menu is selected.
         *
         * @param checked Unused.
         */
        void on_fileSave_triggered(bool checked);
        
        /**
         * Called when save as from the file menu is selected.
         *
         * @param checked Unused.
         */
        void on_fileSaveAs_triggered(bool checked);
        
        /**
         * Called when the fireball alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_fireballCheck_stateChanged(int state);
        
        /**
         * Called when fireball's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_fireballSpinner_valueChanged(int value);
        
        /**
         * Called when fireball's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_fireballText_textEdited(const QString &text);
        
        /**
         * Called when the fire power alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_firePowerCheck_stateChanged(int state);
        
        /**
         * Called when fire power's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_firePowerSpinner_valueChanged(int value);
        
        /**
         * Called when fire power's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_firePowerText_textEdited(const QString &text);
        
        /**
         * Called when the flash alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_flashCheck_stateChanged(int state);
        
        /**
         * Called when flash's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_flashSpinner_valueChanged(int value);
        
        /**
         * Called when flash's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_flashText_textEdited(const QString &text);
        
        /**
         * Called when the force field alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_forceFieldCheck_stateChanged(int state);
        
        /**
         * Called when force field's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_forceFieldSpinner_valueChanged(int value);
        
        /**
         * Called when force field's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_forceFieldText_textEdited(const QString &text);
        
        /**
         * Called when Game 1 from the game menu is selected.
         *
         * @param checked Unused.
         */
        void on_gameGame1_triggered(bool checked);
        
        /**
         * Called when Game 2 from the game menu is selected.
         *
         * @param checked Unused.
         */
        void on_gameGame2_triggered(bool checked);
        
        /**
         * Called when Game 3 from the game menu is selected.
         *
         * @param checked true Unused.
         */
        void on_gameGame3_triggered(bool checked);
        
        /**
         * Called when Game 4 from the game menu is selected.
         *
         * @param checked Unused.
         */
        void on_gameGame4_triggered(bool checked);
        
        /**
         * Called when the gladiator sword is given or taken away.
         *
         * @param state The new check state.
         */
        void on_gladiatorSwordCheck_stateChanged(int state);
        
        /**
         * Called when the gladiator sword's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_gladiatorSwordSpinner_valueChanged(int value);
        
        /**
         * Called when the gladiator sword's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_gladiatorSwordText_textEdited(const QString &text);
        
        /**
         * Called when the gloves of ra count is changed.
         *
         * @param text The text.
         */
        void on_glovesOfRaText_textEdited(const QString &text);
        
        /**
         * Called when the gold coins are edited.
         *
         * @param text The new text.
         */
        void on_goldCoinsText_textEdited(const QString &text);
        
        /**
         * Called when the gold plated vest count is changed.
         *
         * @param text The text.
         */
        void on_goldPlatedVestText_textEdited(const QString &text);
        
        /**
         * Called when the golden jackal count is changed.
         *
         * @param text The new count.
         */
        void on_goldenJackalText_textEdited(const QString &text);
        
        /**
         * Called when the grass hat count is changed.
         *
         * @param text The text.
         */
        void on_grassHatText_textEdited(const QString &text);
        
        /**
         * Called when the grass vest count is changed.
         *
         * @param text The text.
         */
        void on_grassVestText_textEdited(const QString &text);
        
        /**
         * Called when the grease ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_greaseText_textEdited(const QString &text);
        
        /**
         * Called when the gunpowder ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_gunpowderText_textEdited(const QString &text);
        
        /**
         * Called when the hard ball alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_hardBallCheck_stateChanged(int state);
        
        /**
         * Called when hard ball's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_hardBallSpinner_valueChanged(int value);
        
        /**
         * Called when hard ball's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_hardBallText_textEdited(const QString &text);
        
        /**
         * Called when the heal alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_healCheck_stateChanged(int state);
        
        /**
         * Called when heal's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_healSpinner_valueChanged(int value);
        
        /**
         * Called when heal's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_healText_textEdited(const QString &text);
        
        /**
         * Called when about from the help menu is selected.
         *
         * @param checked Unused.
         */
        void on_helpAbout_triggered(bool checked);
        
        /**
         * Called when the honey count is changed.
         *
         * @param text The text.
         */
        void on_honeyText_textEdited(const QString &text);
        
        /**
         * Called when the horn spear is given or taken away.
         *
         * @param state The new check state.
         */
        void on_hornSpearCheck_stateChanged(int state);
        
        /**
         * Called when the horn spear's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_hornSpearSpinner_valueChanged(int value);
        
        /**
         * Called when the horn spear's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_hornSpearText_textEdited(const QString &text);
        
        /**
         * Called when the insect incense charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_insectIncenseCheck_stateChanged(int state);
        
        /**
         * Called when the iron ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_ironText_textEdited(const QString &text);
        
        /**
         * Called when the iron bracer count is changed.
         *
         * @param text The text.
         */
        void on_ironBracerText_textEdited(const QString &text);
        
        /**
         * Called when the jade disk charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_jadeDiskCheck_stateChanged(int state);
        
        /**
         * Called when the jaguar ring charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_jaguarRingCheck_stateChanged(int state);
        
        /**
         * Called when the jeweled scarab count is changed.
         *
         * @param text The new count.
         */
        void on_jeweledScarabText_textEdited(const QString &text);
        
        /**
         * Called when the jewels are edited.
         *
         * @param text The new text.
         */
        void on_jewelsText_textEdited(const QString &text);
        
        /**
         * Called when the knight basher is given or taken away.
         *
         * @param state The new check state.
         */
        void on_knightBasherCheck_stateChanged(int state);
        
        /**
         * Called when the knight basher's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_knightBasherSpinner_valueChanged(int value);
        
        /**
         * Called when the knight basher's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_knightBasherText_textEdited(const QString &text);
        
        /**
         * Called when the knight's helm count is changed.
         *
         * @param text The text.
         */
        void on_knightsHelmText_textEdited(const QString &text);
        
        /**
         * Called when the lance alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_lanceAlchemyCheck_stateChanged(int state);
        
        /**
         * Called when lance's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_lanceAlchemySpinner_valueChanged(int value);
        
        /**
         * Called when lance's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_lanceAlchemyText_textEdited(const QString &text);
        
        /**
         * Called when the lance is given or taken away.
         *
         * @param state The new check state.
         */
        void on_lanceWeaponCheck_stateChanged(int state);
        
        /**
         * Called when the lance's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_lanceWeaponSpinner_valueChanged(int value);
        
        /**
         * Called when the lance's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_lanceWeaponText_textEdited(const QString &text);
        
        /**
         * Called when the laser lance is given or taken away.
         *
         * @param state The new check state.
         */
        void on_laserLanceCheck_stateChanged(int state);
        
        /**
         * Called when the laser lance's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_laserLanceSpinner_valueChanged(int value);
        
        /**
         * Called when the laser lance's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_laserLanceText_textEdited(const QString &text);
        
        /**
         * Called when the leather collar count is changed.
         *
         * @param text The text.
         */
        void on_leatherCollarText_textEdited(const QString &text);
        
        /**
         * Called when the levitate alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_levitateCheck_stateChanged(int state);
        
        /**
         * Called when levitate's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_levitateSpinner_valueChanged(int value);
        
        /**
         * Called when levitate's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_levitateText_textEdited(const QString &text);
        
        /**
         * Called when the lightning helm count is changed.
         *
         * @param text The text.
         */
        void on_lightningHelmText_textEdited(const QString &text);
        
        /**
         * Called when the lightning storm alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_lightningStormCheck_stateChanged(int state);
        
        /**
         * Called when lightning storm's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_lightningStormSpinner_valueChanged(int value);
        
        /**
         * Called when lightning storm's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_lightningStormText_textEdited(const QString &text);
        
        /**
         * Called when the limestone ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_limestoneText_textEdited(const QString &text);
        
        /**
         * Called when the limestone tablet count is changed.
         *
         * @param text The new count.
         */
        void on_limestoneTabletText_textEdited(const QString &text);
        
        /**
         * Called when the magic gourd charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_magicGourdCheck_stateChanged(int state);
        
        /**
         * Called when the magna mail count is changed.
         *
         * @param text The text.
         */
        void on_magnaMailText_textEdited(const QString &text);
        
        /**
         * Called when the magicians ring count is changed.
         *
         * @param text The text.
         */
        void on_magiciansRingText_textEdited(const QString &text);
        
        /**
         * Called when the mammoth guard count is changed.
         *
         * @param text The text.
         */
        void on_mammothGuardText_textEdited(const QString &text);
        
        /**
         * Called when the meteorite ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_meteoriteText_textEdited(const QString &text);
        
        /**
         * Called when the miracle cure alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_miracleCureCheck_stateChanged(int state);
        
        /**
         * Called when miracle cure's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_miracleCureSpinner_valueChanged(int value);
        
        /**
         * Called when miracle cure's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_miracleCureText_textEdited(const QString &text);
        
        /**
         * Called when the moxa stick charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_moxaStickCheck_stateChanged(int state);
        
        /**
         * Called when the mud pepper ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_mudPepperText_textEdited(const QString &text);
        
        /**
         * Called when the mushroom ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_mushroomText_textEdited(const QString &text);
        
        /**
         * Called when the nectar count is changed.
         *
         * @param text The text.
         */
        void on_nectarText_textEdited(const QString &text);
        
        /**
         * Called when the neutron blade is given or taken away.
         *
         * @param state The new check state.
         */
        void on_neutronBladeCheck_stateChanged(int state);
        
        /**
         * Called when the neutron blade's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_neutronBladeSpinner_valueChanged(int value);
        
        /**
         * Called when the neutron blade's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_neutronBladeText_textEdited(const QString &text);
        
        /**
         * Called when the nitro alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_nitroCheck_stateChanged(int state);
        
        /**
         * Called when 's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_nitroSpinner_valueChanged(int value);
        
        /**
         * Called when 's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_nitroText_textEdited(const QString &text);
        
        /**
         * Called when the obsidian helm count is changed.
         *
         * @param text The text.
         */
        void on_obsidianHelmText_textEdited(const QString &text);
        
        /**
         * Called when the oil ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_oilText_textEdited(const QString &text);
        
        /**
         * Called when the old reliable count is changed.
         *
         * @param text The text.
         */
        void on_oldReliableText_textEdited(const QString &text);
        
        /**
         * Called when the one up alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_oneUpCheck_stateChanged(int state);
        
        /**
         * Called when one up's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_oneUpSpinner_valueChanged(int value);
        
        /**
         * Called when one up's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_oneUpText_textEdited(const QString &text);
        
        /**
         * Called when the oracle bone charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_oracleBoneCheck_stateChanged(int state);
        
        /**
         * Called when the particle bomb count is changed.
         *
         * @param text The text.
         */
        void on_particleBombText_textEdited(const QString &text);
        
        /**
         * Called when the perfume count is changed.
         *
         * @param text The new count.
         */
        void on_perfumeText_textEdited(const QString &text);
        
        /**
         * Called when the petal count is changed.
         *
         * @param text The text.
         */
        void on_petalText_textEdited(const QString &text);
        
        /**
         * Called when the pixie dust count is changed.
         *
         * @param text The text.
         */
        void on_pixieDustText_textEdited(const QString &text);
        
        /**
         * Called when the protector count is changed.
         *
         * @param text The text.
         */
        void on_protectorRingText_textEdited(const QString &text);
        
        /**
         * Called when the reflect alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_reflectCheck_stateChanged(int state);
        
        /**
         * Called when reflect's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_reflectSpinner_valueChanged(int value);
        
        /**
         * Called when reflect's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_reflectText_textEdited(const QString &text);
        
        /**
         * Called when the regrowth alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_regrowthCheck_stateChanged(int state);
        
        /**
         * Called when regrowth's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_regrowthSpinner_valueChanged(int value);
        
        /**
         * Called when regrowth's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_regrowthText_textEdited(const QString &text);
        
        /**
         * Called when the revealer alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_revealerCheck_stateChanged(int state);
        
        /**
         * Called when revealer's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_revealerSpinner_valueChanged(int value);
        
        /**
         * Called when revealer's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_revealerText_textEdited(const QString &text);
        
        /**
         * Called when the revive alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_reviveCheck_stateChanged(int state);
        
        /**
         * Called when revive's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_reviveSpinner_valueChanged(int value);
        
        /**
         * Called when revive's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_reviveText_textEdited(const QString &text);
        
        /**
         * Called when the rice count is changed.
         *
         * @param text The new count.
         */
        void on_riceText_textEdited(const QString &text);
        
        /**
         * Called when the root ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_rootText_textEdited(const QString &text);
        
        /**
         * Called when the ruby heart charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_rubyHeartCheck_stateChanged(int state);
        
        /**
         * Called when the serpent bracer count is changed.
         *
         * @param text The text.
         */
        void on_serpentBracerText_textEdited(const QString &text);
        
        /**
         * Called when the shell hat count is changed.
         *
         * @param text The text.
         */
        void on_shellHatText_textEdited(const QString &text);
        
        /**
         * Called when the shell plate count is changed.
         *
         * @param text The text.
         */
        void on_shellPlateText_textEdited(const QString &text);
        
        /**
         * Called when the shining armor count is changed.
         *
         * @param text The text.
         */
        void on_shiningArmorText_textEdited(const QString &text);
        
        /**
         * Called when the silver mail count is changed.
         *
         * @param text The text.
         */
        void on_silverMailText_textEdited(const QString &text);
        
        /**
         * Called when the silver sheath charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_silverSheathCheck_stateChanged(int state);
        
        /**
         * Called when the slow burn alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_slowBurnCheck_stateChanged(int state);
        
        /**
         * Called when slow burn's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_slowBurnSpinner_valueChanged(int value);
        
        /**
         * Called when slow burn's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_slowBurnText_textEdited(const QString &text);
        
        /**
         * Called when the souvenir spoon count is changed.
         *
         * @param text The new count.
         */
        void on_souvenirSpoonText_textEdited(const QString &text);
        
        /**
         * Called when the speed alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_speedCheck_stateChanged(int state);
        
        /**
         * Called when speed's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_speedSpinner_valueChanged(int value);
        
        /**
         * Called when speed's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_speedText_textEdited(const QString &text);
        
        /**
         * Called when the spice count is changed.
         *
         * @param text The new count.
         */
        void on_spiceText_textEdited(const QString &text);
        
        /**
         * Called when the spider's claw is given or taken away.
         *
         * @param state The new check state.
         */
        void on_spidersClawCheck_stateChanged(int state);
        
        /**
         * Called when the spider's claw's weapon level (major) is changed.
         *
         * @param value The new value.
         */
        void on_spidersClawSpinner_valueChanged(int value);
        
        /**
         * Called when the spider's claw's weapon level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_spidersClawText_textEdited(const QString &text);
        
        /**
         * Called when the spiky collar count is changed.
         *
         * @param text The text.
         */
        void on_spikyCollarText_textEdited(const QString &text);
        
        /**
         * Called when the spot's collar count is changed.
         *
         * @param text The text.
         */
        void on_spotsCollarText_textEdited(const QString &text);
        
        /**
         * Called when the staff of life charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_staffOfLifeCheck_stateChanged(int state);
        
        /**
         * Called when the sting alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_stingCheck_stateChanged(int state);
        
        /**
         * Called when sting's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_stingSpinner_valueChanged(int value);
        
        /**
         * Called when sting's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_stingText_textEdited(const QString &text);
        
        /**
         * Called when the stone vest count is changed.
         *
         * @param text The text.
         */
        void on_stoneVestText_textEdited(const QString &text);
        
        /**
         * Called when the stop alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_stopCheck_stateChanged(int state);
        
        /**
         * Called when stop's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_stopSpinner_valueChanged(int value);
        
        /**
         * Called when stop's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_stopText_textEdited(const QString &text);
        
        /**
         * Called when the sun stone charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_sunStoneCheck_stateChanged(int state);
        
        /**
         * Called when the super heal alchemy is given or taken away.
         *
         * @param state The new check state.
         */
        void on_superHealCheck_stateChanged(int state);
        
        /**
         * Called when super heal's alchemy level (major) is changed.
         *
         * @param value The new value.
         */
        void on_superHealSpinner_valueChanged(int value);
        
        /**
         * Called when super heal's alchemy level (minor) is changed.
         *
         * @param text The new value.
         */
        void on_superHealText_textEdited(const QString &text);
        
        /**
         * Called when the talons are edited.
         *
         * @param text The new text.
         */
        void on_talonsText_textEdited(const QString &text);
        
        /**
         * Called when the tapestry count is changed.
         *
         * @param text The new count.
         */
        void on_tapestryText_textEdited(const QString &text);
        
        /**
         * Called when the thug's cloak charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_thugsCloakCheck_stateChanged(int state);
        
        /**
         * Called when the thunder ball count is changed.
         *
         * @param text The text.
         */
        void on_thunderBallText_textEdited(const QString &text);
        
        /**
         * Called when the ticket for exhibition count is changed.
         *
         * @param text The new count.
         */
        void on_ticketForExhibitionText_textEdited(const QString &text);
        
        /**
         * Called when the titanium vest count is changed.
         *
         * @param text The text.
         */
        void on_titaniumVestText_textEdited(const QString &text);
        
        /**
         * Called when the titan's crown count is changed.
         *
         * @param text The text.
         */
        void on_titansCrownText_textEdited(const QString &text);
        
        /**
         * Called when the vine bracelet count is changed.
         *
         * @param text The text.
         */
        void on_vineBraceletText_textEdited(const QString &text);
        
        /**
         * Called when the vinegar ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_vinegarText_textEdited(const QString &text);
        
        /**
         * Called when the virtual glove count is changed.
         *
         * @param text The text.
         */
        void on_virtualGloveText_textEdited(const QString &text);
        
        /**
         * Called when the virtual vest count is changed.
         *
         * @param text The text.
         */
        void on_virtualVestText_textEdited(const QString &text);
        
        /**
         * Called when the water ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_waterText_textEdited(const QString &text);
        
        /**
         * Called when the wax ingredient count is changed.
         *
         * @param text The new text.
         */
        void on_waxText_textEdited(const QString &text);
        
        /**
         * Called when the wings count is changed.
         *
         * @param text The text.
         */
        void on_wingsText_textEdited(const QString &text);
        
        /**
         * Called when the wizard's coin charm is given or taken away.
         *
         * @param state The new check state.
         */
        void on_wizardsCoinCheck_stateChanged(int state);
        
    protected:
        /**
         * Callback triggered when a close event is sent. Used to confirm user's
         * choice when unsaved data is present.
         *
         * @param event The triggering event.
         */
        void closeEvent(QCloseEvent *event);
        
        /**
         * Callback triggered when a drag event occurs. Used to accept or reject
         * drags.
         *
         * @param event The triggering event.
         */
        void dragEnterEvent(QDragEnterEvent *event);
        
        /**
         * Callback triggered when a drop event occurs. Used to handle drops on
         * the application.
         *
         * @param event The event.
         */
        void dropEvent(QDropEvent *event);
        
    public:
        /**
         * Creates a new MainWindow.
         */
        MainWindow();
        
        /**
         * Shows this MainWindow.
         */
        void show();
    };
    
    inline void MainWindow::on_acidRainCheck_stateChanged(int state)
        { setAlchemy(SF_ACIDRAIN, state); }
    inline void MainWindow::on_acidRainSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_ACIDRAIN, value); }
    inline void MainWindow::on_acidRainText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_ACIDRAIN, text); }
    
    inline void MainWindow::on_acornText_textEdited(const QString &text)
        { setIngredient(SF_ACORN, text); }
        
    inline void MainWindow::on_annihilationAmuletText_textEdited(const QString &text)
        { setTradeGood(SF_ANNIHILATIONAMULET, text); }
        
    inline void MainWindow::on_armorPolishCheck_stateChanged(int state)
        { setCharm(SF_ARMORPOLISH, state); }
    
    inline void MainWindow::on_ashText_textEdited(const QString &text)
        { setIngredient(SF_ASH, text); }
        
    inline void MainWindow::on_atlasCheck_stateChanged(int state)
        { setAlchemy(SF_ATLAS, state); }
    inline void MainWindow::on_atlasSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_ATLAS, value); }
    inline void MainWindow::on_atlasText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_ATLAS, text); }
     
    inline void MainWindow::on_atlasMedallionText_textEdited(const QString &text)
        { setIngredient(SF_ATLASMEDALLION, text); }
     
    inline void MainWindow::on_atomSmasherCheck_stateChanged(int state)
        { setWeapon(SF_ATOMSMASHER, state); }
    inline void MainWindow::on_atomSmasherSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_ATOMSMASHER, value); }
    inline void MainWindow::on_atomSmasherText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_ATOMSMASHER, text); }
        
    inline void MainWindow::on_barrierCheck_stateChanged(int state)
        { setAlchemy(SF_BARRIER, state); }
    inline void MainWindow::on_barrierSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_BARRIER, value); }
    inline void MainWindow::on_barrierText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_BARRIER, text); }
        
    inline void MainWindow::on_bazookaCheck_stateChanged(int state)
        { setWeapon(SF_BAZOOKA, state); }
        
    inline void MainWindow::on_beadsText_textEdited(const QString &text)
        { setTradeGood(SF_BEADS, text); }
        
    inline void MainWindow::on_boneText_textEdited(const QString &text)
        { setIngredient(SF_BONE, text); }
        
    inline void MainWindow::on_boneCrusherCheck_stateChanged(int state)
        { setWeapon(SF_BONECRUSHER, state); }
    inline void MainWindow::on_boneCrusherSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_BONECRUSHER, value); }
    inline void MainWindow::on_boneCrusherText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_BONECRUSHER, text); }
        
    inline void MainWindow::on_brainstormText_textEdited(const QString &text)
        { setItem(SF_BRAINSTORM, text); }
        
    inline void MainWindow::on_brimstoneText_textEdited(const QString &text)
        { setIngredient(SF_BRIMSTONE, text); }
        
    inline void MainWindow::on_bronzeArmorText_textEdited(const QString &text)
        { setItem(SF_BRONZEARMOR, text); }
        
    inline void MainWindow::on_bronzeAxeCheck_stateChanged(int state)
        { setWeapon(SF_BRONZEAXE, state); }
    inline void MainWindow::on_bronzeAxeSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_BRONZEAXE, value); }
    inline void MainWindow::on_bronzeAxeText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_BRONZEAXE, text); }
    
    inline void MainWindow::on_bronzeGauntletText_textEdited(const QString &text)
        { setItem(SF_BRONZEGAUNTLET, text); }
    inline void MainWindow::on_bronzeHelmetText_textEdited(const QString &text)
        { setItem(SF_BRONZEHELMET, text); }
        
    inline void MainWindow::on_bronzeSpearCheck_stateChanged(int state)
        { setWeapon(SF_BRONZESPEAR, state); }
    inline void MainWindow::on_bronzeSpearSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_BRONZESPEAR, value); }
    inline void MainWindow::on_bronzeSpearText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_BRONZESPEAR, text); }
        
    inline void MainWindow::on_callBeadText_textEdited(const QString &text)
        { setItem(SF_CALLBEAD, text); }
        
    inline void MainWindow::on_callUpCheck_stateChanged(int state)
        { setAlchemy(SF_CALLUP, state); }
    inline void MainWindow::on_callUpSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_CALLUP, value); }
    inline void MainWindow::on_callUpText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_CALLUP, text); }
        
    inline void MainWindow::on_centurionCapeText_textEdited(const QString &text)
        { setItem(SF_CENTURIONCAPE, text); }
    inline void MainWindow::on_centurionHelmText_textEdited(const QString &text)
        { setItem(SF_CENTURIONHELM, text); }
        
    inline void MainWindow::on_ceramicPotText_textEdited(const QString &text)
        { setTradeGood(SF_CERAMICPOT, text); }
    inline void MainWindow::on_chickenText_textEdited(const QString &text)
        { setTradeGood(SF_CHICKEN, text); }
        
    inline void MainWindow::on_chocoboEggCheck_stateChanged(int state)
        { setCharm(SF_CHOCOBOEGG, state); }
    
    inline void MainWindow::on_clawGuardText_textEdited(const QString &text)
        { setItem(SF_CLAWGUARD, text); }
        
    inline void MainWindow::on_clayText_textEdited(const QString &text)
        { setIngredient(SF_CLAY, text); }
        
    inline void MainWindow::on_corrosionCheck_stateChanged(int state)
        { setAlchemy(SF_CORROSION, state); }
    inline void MainWindow::on_corrosionSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_CORROSION, value); }
    inline void MainWindow::on_corrosionText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_CORROSION, text); }
        
    inline void MainWindow::on_creditsText_textEdited(const QString &text)
        { setMoney(SF_CREDITS, text); }
        
    inline void MainWindow::on_crusaderSwordCheck_stateChanged(int state)
        { setWeapon(SF_CRUSADERSWORD, state); }
    inline void MainWindow::on_crusaderSwordSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_CRUSADERSWORD, value); }
    inline void MainWindow::on_crusaderSwordText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_CRUSADERSWORD, text); }
        
    inline void MainWindow::on_crushCheck_stateChanged(int state)
        { setAlchemy(SF_CRUSH, state); }
    inline void MainWindow::on_crushSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_CRUSH, value); }
    inline void MainWindow::on_crushText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_CRUSH, text); }
        
    inline void MainWindow::on_cryoBlastText_textEdited(const QString &text)
        { setItem(SF_CRYOBLAST, text); }
        
    inline void MainWindow::on_crystalText_textEdited(const QString &text)
        { setIngredient(SF_CRYSTAL, text); }
        
    inline void MainWindow::on_cureCheck_stateChanged(int state)
        { setAlchemy(SF_CURE, state); }
    inline void MainWindow::on_cureSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_CURE, value); }
    inline void MainWindow::on_cureText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_CURE, text); }
        
    inline void MainWindow::on_cybergloveText_textEdited(const QString &text)
        { setItem(SF_CYBERGLOVE, text); }
    
    inline void MainWindow::on_defendCheck_stateChanged(int state)
        { setAlchemy(SF_DEFEND, state); }
    inline void MainWindow::on_defendSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_DEFEND, value); }
    inline void MainWindow::on_defendText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_DEFEND, text); }
        
    inline void MainWindow::on_defenderCollarText_textEdited(const QString &text)
        { setItem(SF_DEFENDERCOLLAR, text); }
    inline void MainWindow::on_dinoHelmText_textEdited(const QString &text)
        { setItem(SF_DINOHELM, text); }
    inline void MainWindow::on_dinoSkinText_textEdited(const QString &text)
        { setItem(SF_DINOSKIN, text); }
    inline void MainWindow::on_dogBiscuitText_textEdited(const QString &text)
        { setItem(SF_DOGBISCUIT, text); }
    
    inline void MainWindow::on_doubleDrainCheck_stateChanged(int state)
        { setAlchemy(SF_DOUBLEDRAIN, state); }
    inline void MainWindow::on_doubleDrainSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_DOUBLEDRAIN, value); }
    inline void MainWindow::on_doubleDrainText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_DOUBLEDRAIN, text); }
    
    inline void MainWindow::on_dragonHelmText_textEdited(const QString &text)
        { setItem(SF_DRAGONHELM, text); }
    inline void MainWindow::on_dragonsClawText_textEdited(const QString &text)
        { setItem(SF_DRAGONSCLAW, text); }
    
    inline void MainWindow::on_drainCheck_stateChanged(int state)
        { setAlchemy(SF_DRAIN, state); }
    inline void MainWindow::on_drainSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_DRAIN, value); }
    inline void MainWindow::on_drainText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_DRAIN, text); }
     
    inline void MainWindow::on_dryIceText_textEdited(const QString &text)
        { setIngredient(SF_DRYICE, text); }
     
    inline void MainWindow::on_energizeCheck_stateChanged(int state)
        { setAlchemy(SF_ENERGIZE, state); }
    inline void MainWindow::on_energizeSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_ENERGIZE, value); }
    inline void MainWindow::on_energizeText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_ENERGIZE, text); }
    
    inline void MainWindow::on_escapeCheck_stateChanged(int state)
        { setAlchemy(SF_ESCAPE, state); }
    inline void MainWindow::on_escapeSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_ESCAPE, value); }
    inline void MainWindow::on_escapeText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_ESCAPE, text); }
        
    inline void MainWindow::on_essenceText_textEdited(const QString &text)
        { setItem(SF_ESSENCE, text); }
     
    inline void MainWindow::on_ethanolText_textEdited(const QString &text)
        { setIngredient(SF_ETHANOL, text); }
     
    inline void MainWindow::on_explosionCheck_stateChanged(int state)
        { setAlchemy(SF_EXPLOSION, state); }
    inline void MainWindow::on_explosionSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_EXPLOSION, value); }
    inline void MainWindow::on_explosionText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_EXPLOSION, text); }
     
    inline void MainWindow::on_featherText_textEdited(const QString &text)
        { setIngredient(SF_FEATHER, text); }
        
    inline void MainWindow::on_fileExit_triggered(bool)
        { close(); }
     
    inline void MainWindow::on_fireballCheck_stateChanged(int state)
        { setAlchemy(SF_FIREBALL, state); }
    inline void MainWindow::on_fireballSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_FIREBALL, value); }
    inline void MainWindow::on_fireballText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_FIREBALL, text); }
    
    inline void MainWindow::on_firePowerCheck_stateChanged(int state)
        { setAlchemy(SF_FIREPOWER, state); }
    inline void MainWindow::on_firePowerSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_FIREPOWER, value); }
    inline void MainWindow::on_firePowerText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_FIREPOWER, text); }
    
    inline void MainWindow::on_flashCheck_stateChanged(int state)
        { setAlchemy(SF_FLASH, state); }
    inline void MainWindow::on_flashSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_FLASH, value); }
    inline void MainWindow::on_flashText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_FLASH, text); }
    
    inline void MainWindow::on_forceFieldCheck_stateChanged(int state)
        { setAlchemy(SF_FORCEFIELD, state); }
    inline void MainWindow::on_forceFieldSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_FORCEFIELD, value); }
    inline void MainWindow::on_forceFieldText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_FORCEFIELD, text); }
        
    inline void MainWindow::on_gameGame1_triggered(bool)
        { setGame(0); }
    inline void MainWindow::on_gameGame2_triggered(bool)
        { setGame(1); }
    inline void MainWindow::on_gameGame3_triggered(bool)
        { setGame(2); }
    inline void MainWindow::on_gameGame4_triggered(bool)
        { setGame(3); }
        
    inline void MainWindow::on_gladiatorSwordCheck_stateChanged(int state)
        { setWeapon(SF_GLADIATORSWORD, state); }
    inline void MainWindow::on_gladiatorSwordSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_GLADIATORSWORD, value); }
    inline void MainWindow::on_gladiatorSwordText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_GLADIATORSWORD, text); }
        
    inline void MainWindow::on_glovesOfRaText_textEdited(const QString &text)
        { setItem(SF_GLOVESOFRA, text); }
        
    inline void MainWindow::on_goldCoinsText_textEdited(const QString &text)
        { setMoney(SF_GOLDCOINS, text); }
        
    inline void MainWindow::on_goldPlatedVestText_textEdited(const QString &text)
        { setItem(SF_GOLDPLATEDVEST, text); }
        
    inline void MainWindow::on_goldenJackalText_textEdited(const QString &text)
        { setTradeGood(SF_GOLDENJACKAL, text); }
        
    inline void MainWindow::on_grassHatText_textEdited(const QString &text)
        { setItem(SF_GRASSHAT, text); }
    inline void MainWindow::on_grassVestText_textEdited(const QString &text)
        { setItem(SF_GRASSVEST, text); }
        
    inline void MainWindow::on_greaseText_textEdited(const QString &text)
        { setIngredient(SF_GREASE, text); }
    inline void MainWindow::on_gunpowderText_textEdited(const QString &text)
        { setIngredient(SF_GUNPOWDER, text); }
        
    inline void MainWindow::on_hardBallCheck_stateChanged(int state)
        { setAlchemy(SF_HARDBALL, state); }
    inline void MainWindow::on_hardBallSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_HARDBALL, value); }
    inline void MainWindow::on_hardBallText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_HARDBALL, text); }
    
    inline void MainWindow::on_healCheck_stateChanged(int state)
        { setAlchemy(SF_HEAL, state); }
    inline void MainWindow::on_healSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_HEAL, value); }
    inline void MainWindow::on_healText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_HEAL, text); }
        
    inline void MainWindow::on_honeyText_textEdited(const QString &text)
        { setItem(SF_HONEY, text); }
        
    inline void MainWindow::on_hornSpearCheck_stateChanged(int state)
        { setWeapon(SF_HORNSPEAR, state); }
    inline void MainWindow::on_hornSpearSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_HORNSPEAR, value); }
    inline void MainWindow::on_hornSpearText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_HORNSPEAR, text); }
        
    inline void MainWindow::on_insectIncenseCheck_stateChanged(int state)
        { setCharm(SF_INSECTINCENSE, state); }
        
    inline void MainWindow::on_ironText_textEdited(const QString &text)
        { setIngredient(SF_IRON, text); }
        
    inline void MainWindow::on_ironBracerText_textEdited(const QString &text)
        { setItem(SF_IRONBRACER, text); }
        
    inline void MainWindow::on_jadeDiskCheck_stateChanged(int state)
        { setCharm(SF_JADEDISK, state); }
    inline void MainWindow::on_jaguarRingCheck_stateChanged(int state)
        { setCharm(SF_JAGUARRING, state); }
        
    inline void MainWindow::on_jeweledScarabText_textEdited(const QString &text)
        { setTradeGood(SF_JEWELEDSCARAB, text); }
        
    inline void MainWindow::on_jewelsText_textEdited(const QString &text)
        { setMoney(SF_JEWELS, text); }
        
    inline void MainWindow::on_knightBasherCheck_stateChanged(int state)
        { setWeapon(SF_KNIGHTBASHER, state); }
    inline void MainWindow::on_knightBasherSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_KNIGHTBASHER, value); }
    inline void MainWindow::on_knightBasherText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_KNIGHTBASHER, text); }
        
    inline void MainWindow::on_knightsHelmText_textEdited(const QString &text)
        { setItem(SF_KNIGHTSHELM, text); }
        
    inline void MainWindow::on_lanceAlchemyCheck_stateChanged(int state)
        { setAlchemy(SF_LANCEALCHEMY, state); }
    inline void MainWindow::on_lanceAlchemySpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_LANCEALCHEMY, value); }
    inline void MainWindow::on_lanceAlchemyText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_LANCEALCHEMY, text); }
        
    inline void MainWindow::on_lanceWeaponCheck_stateChanged(int state)
        { setWeapon(SF_LANCEWEAPON, state); }
    inline void MainWindow::on_lanceWeaponSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_LANCEWEAPON, value); }
    inline void MainWindow::on_lanceWeaponText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_LANCEWEAPON, text); }
        
    inline void MainWindow::on_laserLanceCheck_stateChanged(int state)
        { setWeapon(SF_LASERLANCE, state); }
    inline void MainWindow::on_laserLanceSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_LASERLANCE, value); }
    inline void MainWindow::on_laserLanceText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_LASERLANCE, text); }
        
    inline void MainWindow::on_leatherCollarText_textEdited(const QString &text)
        { setItem(SF_LEATHERCOLLAR, text); }
        
    inline void MainWindow::on_levitateCheck_stateChanged(int state)
        { setAlchemy(SF_LEVITATE, state); }
    inline void MainWindow::on_levitateSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_LEVITATE, value); }
    inline void MainWindow::on_levitateText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_LEVITATE, text); }
        
    inline void MainWindow::on_lightningHelmText_textEdited(const QString &text)
        { setItem(SF_LIGHTNINGHELM, text); }
    
    inline void MainWindow::on_lightningStormCheck_stateChanged(int state)
        { setAlchemy(SF_LIGHTNINGSTORM, state); }
    inline void MainWindow::on_lightningStormSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_LIGHTNINGSTORM, value); }
    inline void MainWindow::on_lightningStormText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_LIGHTNINGSTORM, text); }
        
    inline void MainWindow::on_limestoneText_textEdited(const QString &text)
        { setIngredient(SF_LIMESTONE, text); }
        
    inline void MainWindow::on_limestoneTabletText_textEdited(const QString &text)
        { setTradeGood(SF_LIMESTONETABLET, text); }
        
    inline void MainWindow::on_magicGourdCheck_stateChanged(int state)
        { setCharm(SF_MAGICGOURD, state); }
        
    inline void MainWindow::on_magiciansRingText_textEdited(const QString &text)
        { setItem(SF_MAGICIANSRING, text); }
    inline void MainWindow::on_magnaMailText_textEdited(const QString &text)
        { setItem(SF_MAGNAMAIL, text); }
    inline void MainWindow::on_mammothGuardText_textEdited(const QString &text)
        { setItem(SF_MAMMOTHGUARD, text); }
    
    inline void MainWindow::on_meteoriteText_textEdited(const QString &text)
        { setIngredient(SF_METEORITE, text); }
        
    inline void MainWindow::on_miracleCureCheck_stateChanged(int state)
        { setAlchemy(SF_MIRACLECURE, state); }
    inline void MainWindow::on_miracleCureSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_MIRACLECURE, value); }
    inline void MainWindow::on_miracleCureText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_MIRACLECURE, text); }
        
    inline void MainWindow::on_moxaStickCheck_stateChanged(int state)
        { setCharm(SF_MOXASTICK, state); }
     
    inline void MainWindow::on_mudPepperText_textEdited(const QString &text)
        { setIngredient(SF_MUDPEPPER, text); }
    inline void MainWindow::on_mushroomText_textEdited(const QString &text)
        { setIngredient(SF_MUSHROOM, text); }
        
    inline void MainWindow::on_nectarText_textEdited(const QString &text)
        { setItem(SF_NECTAR, text); }
        
    inline void MainWindow::on_neutronBladeCheck_stateChanged(int state)
        { setWeapon(SF_NEUTRONBLADE, state); }
    inline void MainWindow::on_neutronBladeSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_NEUTRONBLADE, value); }
    inline void MainWindow::on_neutronBladeText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_NEUTRONBLADE, text); }
        
    inline void MainWindow::on_nitroCheck_stateChanged(int state)
        { setAlchemy(SF_NITRO, state); }
    inline void MainWindow::on_nitroSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_NITRO, value); }
    inline void MainWindow::on_nitroText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_NITRO, text); }
        
    inline void MainWindow::on_obsidianHelmText_textEdited(const QString &text)
        { setItem(SF_OBSIDIANHELM, text); }
    inline void MainWindow::on_oldReliableText_textEdited(const QString &text)
        { setItem(SF_OLDRELIABLE, text); }
    
    inline void MainWindow::on_oneUpCheck_stateChanged(int state)
        { setAlchemy(SF_ONEUP, state); }
    inline void MainWindow::on_oneUpSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_ONEUP, value); }
    inline void MainWindow::on_oneUpText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_ONEUP, text); }
        
    inline void MainWindow::on_oilText_textEdited(const QString &text)
        { setIngredient(SF_OIL, text); }
        
    inline void MainWindow::on_oracleBoneCheck_stateChanged(int state)
        { setCharm(SF_ORACLEBONE, state); }
        
    inline void MainWindow::on_particleBombText_textEdited(const QString &text)
        { setItem(SF_PARTICLEBOMB, text); }
        
    inline void MainWindow::on_perfumeText_textEdited(const QString &text)
        { setTradeGood(SF_PERFUME, text); }
    
    inline void MainWindow::on_petalText_textEdited(const QString &text)
        { setItem(SF_PETAL, text); }
    inline void MainWindow::on_pixieDustText_textEdited(const QString &text)
        { setItem(SF_PIXIEDUST, text); }
    inline void MainWindow::on_protectorRingText_textEdited(const QString &text)
        { setItem(SF_PROTECTORRING, text); }
        
    inline void MainWindow::on_reflectCheck_stateChanged(int state)
        { setAlchemy(SF_REFLECT, state); }
    inline void MainWindow::on_reflectSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_REFLECT, value); }
    inline void MainWindow::on_reflectText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_REFLECT, text); }
    
    inline void MainWindow::on_regrowthCheck_stateChanged(int state)
        { setAlchemy(SF_REGROWTH, state); }
    inline void MainWindow::on_regrowthSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_REGROWTH, value); }
    inline void MainWindow::on_regrowthText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_REGROWTH, text); }
    
    inline void MainWindow::on_revealerCheck_stateChanged(int state)
        { setAlchemy(SF_REVEALER, state); }
    inline void MainWindow::on_revealerSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_REVEALER, value); }
    inline void MainWindow::on_revealerText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_REVEALER, text); }
    
    inline void MainWindow::on_reviveCheck_stateChanged(int state)
        { setAlchemy(SF_REVIVE, state); }
    inline void MainWindow::on_reviveSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_REVIVE, value); }
    inline void MainWindow::on_reviveText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_REVIVE, text); }
        
    inline void MainWindow::on_riceText_textEdited(const QString &text)
        { setTradeGood(SF_RICE, text); }
        
    inline void MainWindow::on_rootText_textEdited(const QString &text)
        { setIngredient(SF_ROOT, text); }
        
    inline void MainWindow::on_rubyHeartCheck_stateChanged(int state)
        { setCharm(SF_RUBYHEART, state); }
        
    inline void MainWindow::on_serpentBracerText_textEdited(const QString &text)
        { setItem(SF_SERPENTBRACER, text); }
    inline void MainWindow::on_shellHatText_textEdited(const QString &text)
        { setItem(SF_SHELLHAT, text); }
    inline void MainWindow::on_shellPlateText_textEdited(const QString &text)
        { setItem(SF_SHELLPLATE, text); }
    inline void MainWindow::on_shiningArmorText_textEdited(const QString &text)
        { setItem(SF_SHININGARMOR, text); }
    inline void MainWindow::on_silverMailText_textEdited(const QString &text)
        { setItem(SF_SILVERMAIL, text); }
        
    inline void MainWindow::on_silverSheathCheck_stateChanged(int state)
        { setCharm(SF_SILVERSHEATH, state); }
        
    inline void MainWindow::on_slowBurnCheck_stateChanged(int state)
        { setAlchemy(SF_SLOWBURN, state); }
    inline void MainWindow::on_slowBurnSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_SLOWBURN, value); }
    inline void MainWindow::on_slowBurnText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_SLOWBURN, text); }
        
    inline void MainWindow::on_souvenirSpoonText_textEdited(const QString &text)
        { setTradeGood(SF_SOUVENIRSPOON, text); }
    
    inline void MainWindow::on_speedCheck_stateChanged(int state)
        { setAlchemy(SF_SPEED, state); }
    inline void MainWindow::on_speedSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_SPEED, value); }
    inline void MainWindow::on_speedText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_SPEED, text); }
        
    inline void MainWindow::on_spiceText_textEdited(const QString &text)
        { setTradeGood(SF_SPICE, text); }
        
    inline void MainWindow::on_spidersClawCheck_stateChanged(int state)
        { setWeapon(SF_SPIDERSCLAW, state); }
    inline void MainWindow::on_spidersClawSpinner_valueChanged(int value)
        { setWeaponLevelMajor(SF_SPIDERSCLAW, value); }
    inline void MainWindow::on_spidersClawText_textEdited(const QString &text)
        { setWeaponLevelMinor(SF_SPIDERSCLAW, text); }
        
    inline void MainWindow::on_spikyCollarText_textEdited(const QString &text)
        { setItem(SF_SPIKYCOLLAR, text); }
    inline void MainWindow::on_spotsCollarText_textEdited(const QString &text)
        { setItem(SF_SPOTSCOLLAR, text); }
        
    inline void MainWindow::on_staffOfLifeCheck_stateChanged(int state)
        { setCharm(SF_STAFFOFLIFE, state); }
        
    inline void MainWindow::on_stingCheck_stateChanged(int state)
        { setAlchemy(SF_STING, state); }
    inline void MainWindow::on_stingSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_STING, value); }
    inline void MainWindow::on_stingText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_STING, text); }
        
    inline void MainWindow::on_stoneVestText_textEdited(const QString &text)
        { setItem(SF_STONEVEST, text); }
    
    inline void MainWindow::on_stopCheck_stateChanged(int state)
        { setAlchemy(SF_STOP, state); }
    inline void MainWindow::on_stopSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_STOP, value); }
    inline void MainWindow::on_stopText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_STOP, text); }
        
    inline void MainWindow::on_sunStoneCheck_stateChanged(int state)
        { setCharm(SF_SUNSTONE, state); }
    
    inline void MainWindow::on_superHealCheck_stateChanged(int state)
        { setAlchemy(SF_SUPERHEAL, state); }
    inline void MainWindow::on_superHealSpinner_valueChanged(int value)
        { setAlchemyLevelMajor(SF_SUPERHEAL, value); }
    inline void MainWindow::on_superHealText_textEdited(const QString &text)
        { setAlchemyLevelMinor(SF_SUPERHEAL, text); }
        
    inline void MainWindow::on_talonsText_textEdited(const QString &text)
        { setMoney(SF_TALONS, text); }
        
    inline void MainWindow::on_tapestryText_textEdited(const QString &text)
        { setTradeGood(SF_TAPESTRY, text); }
        
    inline void MainWindow::on_thugsCloakCheck_stateChanged(int state)
        { setCharm(SF_THUGSCLOAK, state); }
        
    inline void MainWindow::on_thunderBallText_textEdited(const QString &text)
        { setItem(SF_THUNDERBALL, text); }
        
    inline void MainWindow::on_ticketForExhibitionText_textEdited(const QString &text)
        { setTradeGood(SF_TICKETFOREXHIBITION, text); }
        
    inline void MainWindow::on_titaniumVestText_textEdited(const QString &text)
        { setItem(SF_TITANIUMVEST, text); }
    inline void MainWindow::on_titansCrownText_textEdited(const QString &text)
        { setItem(SF_TITANSCROWN, text); }
    inline void MainWindow::on_vineBraceletText_textEdited(const QString &text)
        { setItem(SF_VINEBRACELET, text); }
    
    inline void MainWindow::on_vinegarText_textEdited(const QString &text)
        { setIngredient(SF_VINEGAR, text); }
        
    inline void MainWindow::on_virtualGloveText_textEdited(const QString &text)
        { setItem(SF_VIRTUALGLOVE, text); }
    inline void MainWindow::on_virtualVestText_textEdited(const QString &text)
        { setItem(SF_VIRTUALVEST, text); }
    
    inline void MainWindow::on_waterText_textEdited(const QString &text)
        { setIngredient(SF_WATER, text); }
    inline void MainWindow::on_waxText_textEdited(const QString &text)
        { setIngredient(SF_WAX, text); }
        
    inline void MainWindow::on_wingsText_textEdited(const QString &text)
        { setItem(SF_WINGS, text); }
    
    inline void MainWindow::on_wizardsCoinCheck_stateChanged(int state)
        { setCharm(SF_WIZARDSCOIN, state); }
}

#endif

