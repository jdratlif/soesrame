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

#include <cmath>

#include <QActionGroup>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QMimeData>
#include <QRegExpValidator>
#include <QScreen>
#include <QUrl>

#include "view/aboutdialog.hh"
#include "view/mainwindow.hh"

using namespace soesrame;

MainWindow::MainWindow()
    : QMainWindow(), aboutDialog(nullptr), ignoreSignals(false), open(false) {
    // setup widgets
    ui.setupUi(this);

    // connect signals
    connect(this, SIGNAL(sramFileOpened()), this, SLOT(onSRAMFileOpened()));
    connect(this, SIGNAL(sramFileOpened()), this, SIGNAL(uiChanged()));
    connect(this, SIGNAL(uiChanged()), this, SLOT(onUIChanged()));

    // make Game menu actions exclusive
    auto *gameActionGroup = new QActionGroup(this);
    gameActionGroup->addAction(ui.gameGame1);
    gameActionGroup->addAction(ui.gameGame2);
    gameActionGroup->addAction(ui.gameGame3);
    gameActionGroup->addAction(ui.gameGame4);
    gameActionGroup->setExclusive(true);

    auto *regionActionGroup = new QActionGroup(this);
    regionActionGroup->addAction(ui.regionUnitedStates);
    regionActionGroup->addAction(ui.regionEngland);
    regionActionGroup->addAction(ui.regionFrance);
    regionActionGroup->addAction(ui.regionGermany);
    regionActionGroup->addAction(ui.regionSpain);
    regionActionGroup->setExclusive(true);

    // take a guess at the proper region
    switch (QLocale::system().language()) {
        case QLocale::Spanish:
            setRegion(REGION_SPAIN);
            ui.regionSpain->setChecked(true);
            break;

        case QLocale::German:
            setRegion(REGION_GERMANY);
            ui.regionGermany->setChecked(true);
            break;

        case QLocale::French:
            setRegion(REGION_FRANCE);
            ui.regionFrance->setChecked(true);
            break;

        case QLocale::English:
        case QLocale::C:
            if (QLocale::system().country() == QLocale::UnitedKingdom) {
                setRegion(REGION_ENGLAND);
                ui.regionEngland->setChecked(true);
            } else {
                setRegion(REGION_UNITEDSTATES);
            }
            break;

        default:
            // default to English European Version
            setRegion(REGION_ENGLAND);
            ui.regionEngland->setChecked(true);
    }

    // setup validators
    auto *under6Validator      = new QIntValidator(0, 6, this);
    auto *under100Validator    = new QIntValidator(0, 99, this);
    auto *under1000Validator   = new QIntValidator(0, 999, this);
    auto *any24BitValidator    = new QIntValidator(0, 16777215, this);
    auto *levelValidator       = new QIntValidator(1, 99, this);
    auto *weaponLevelValidator = new QIntValidator(0, 255, this);

    // money validators
    ui.talonsText->setValidator(any24BitValidator);
    ui.jewelsText->setValidator(any24BitValidator);
    ui.goldCoinsText->setValidator(any24BitValidator);
    ui.creditsText->setValidator(any24BitValidator);

    // stat validators
    ui.boyLevelText->setValidator(levelValidator);
    ui.boyCurrentHPText->setValidator(under1000Validator);
    ui.boyExperienceText->setValidator(any24BitValidator);

    ui.dogLevelText->setValidator(levelValidator);
    ui.dogCurrentHPText->setValidator(under1000Validator);
    ui.dogExperienceText->setValidator(any24BitValidator);
    ui.dogAttackLevelText->setValidator(weaponLevelValidator);

    // weapon level validators
    ui.boneCrusherText->setValidator(weaponLevelValidator);
    ui.gladiatorSwordText->setValidator(weaponLevelValidator);
    ui.crusaderSwordText->setValidator(weaponLevelValidator);
    ui.neutronBladeText->setValidator(weaponLevelValidator);

    ui.spidersClawText->setValidator(weaponLevelValidator);
    ui.bronzeAxeText->setValidator(weaponLevelValidator);
    ui.knightBasherText->setValidator(weaponLevelValidator);
    ui.atomSmasherText->setValidator(weaponLevelValidator);

    ui.hornSpearText->setValidator(weaponLevelValidator);
    ui.bronzeSpearText->setValidator(weaponLevelValidator);
    ui.lanceWeaponText->setValidator(weaponLevelValidator);
    ui.laserLanceText->setValidator(weaponLevelValidator);

    // alchemy ingredient validators
    ui.acornText->setValidator(under100Validator);
    ui.ashText->setValidator(under100Validator);
    ui.atlasMedallionText->setValidator(under100Validator);
    ui.boneText->setValidator(under100Validator);
    ui.brimstoneText->setValidator(under100Validator);
    ui.clayText->setValidator(under100Validator);
    ui.crystalText->setValidator(under100Validator);
    ui.dryIceText->setValidator(under100Validator);
    ui.ethanolText->setValidator(under100Validator);
    ui.featherText->setValidator(under100Validator);
    ui.greaseText->setValidator(under100Validator);
    ui.gunpowderText->setValidator(under100Validator);
    ui.ironText->setValidator(under100Validator);
    ui.limestoneText->setValidator(under100Validator);
    ui.meteoriteText->setValidator(under100Validator);
    ui.mudPepperText->setValidator(under100Validator);
    ui.mushroomText->setValidator(under100Validator);
    ui.oilText->setValidator(under100Validator);
    ui.rootText->setValidator(under100Validator);
    ui.vinegarText->setValidator(under100Validator);
    ui.waterText->setValidator(under100Validator);
    ui.waxText->setValidator(under100Validator);

    // alchemy level validators
    ui.acidRainText->setValidator(under100Validator);
    ui.atlasText->setValidator(under100Validator);
    ui.barrierText->setValidator(under100Validator);
    ui.callUpText->setValidator(under100Validator);
    ui.corrosionText->setValidator(under100Validator);
    ui.crushText->setValidator(under100Validator);
    ui.cureText->setValidator(under100Validator);
    ui.defendText->setValidator(under100Validator);
    ui.doubleDrainText->setValidator(under100Validator);
    ui.drainText->setValidator(under100Validator);
    ui.energizeText->setValidator(under100Validator);
    ui.escapeText->setValidator(under100Validator);
    ui.explosionText->setValidator(under100Validator);
    ui.fireballText->setValidator(under100Validator);
    ui.firePowerText->setValidator(under100Validator);
    ui.flashText->setValidator(under100Validator);
    ui.forceFieldText->setValidator(under100Validator);
    ui.hardBallText->setValidator(under100Validator);
    ui.healText->setValidator(under100Validator);
    ui.lanceAlchemyText->setValidator(under100Validator);
    ui.levitateText->setValidator(under100Validator);
    ui.lightningStormText->setValidator(under100Validator);
    ui.miracleCureText->setValidator(under100Validator);
    ui.nitroText->setValidator(under100Validator);
    ui.oneUpText->setValidator(under100Validator);
    ui.reflectText->setValidator(under100Validator);
    ui.regrowthText->setValidator(under100Validator);
    ui.revealerText->setValidator(under100Validator);
    ui.reviveText->setValidator(under100Validator);
    ui.slowBurnText->setValidator(under100Validator);
    ui.speedText->setValidator(under100Validator);
    ui.stingText->setValidator(under100Validator);
    ui.stopText->setValidator(under100Validator);
    ui.superHealText->setValidator(under100Validator);

    // item validators
    ui.petalText->setValidator(under6Validator);
    ui.nectarText->setValidator(under6Validator);
    ui.honeyText->setValidator(under6Validator);
    ui.dogBiscuitText->setValidator(under6Validator);
    ui.wingsText->setValidator(under6Validator);
    ui.essenceText->setValidator(under6Validator);
    ui.pixieDustText->setValidator(under6Validator);
    ui.callBeadText->setValidator(under100Validator);

    // dog collar validators
    ui.leatherCollarText->setValidator(under6Validator);
    ui.spikyCollarText->setValidator(under6Validator);
    ui.defenderCollarText->setValidator(under6Validator);
    ui.spotsCollarText->setValidator(under6Validator);

    // armor validators
    ui.grassVestText->setValidator(under6Validator);
    ui.shellPlateText->setValidator(under6Validator);
    ui.dinoSkinText->setValidator(under6Validator);
    ui.bronzeArmorText->setValidator(under6Validator);
    ui.stoneVestText->setValidator(under6Validator);
    ui.centurionCapeText->setValidator(under6Validator);
    ui.silverMailText->setValidator(under6Validator);
    ui.goldPlatedVestText->setValidator(under6Validator);
    ui.shiningArmorText->setValidator(under6Validator);
    ui.magnaMailText->setValidator(under6Validator);
    ui.titaniumVestText->setValidator(under6Validator);
    ui.virtualVestText->setValidator(under6Validator);

    // bazooka ammunition validators
    ui.thunderBallText->setValidator(under100Validator);
    ui.particleBombText->setValidator(under100Validator);
    ui.cryoBlastText->setValidator(under100Validator);

    // helmet validators
    ui.grassHatText->setValidator(under6Validator);
    ui.shellHatText->setValidator(under6Validator);
    ui.dinoHelmText->setValidator(under6Validator);
    ui.bronzeHelmetText->setValidator(under6Validator);
    ui.obsidianHelmText->setValidator(under6Validator);
    ui.centurionHelmText->setValidator(under6Validator);
    ui.titansCrownText->setValidator(under6Validator);
    ui.dragonHelmText->setValidator(under6Validator);
    ui.knightsHelmText->setValidator(under6Validator);
    ui.lightningHelmText->setValidator(under6Validator);
    ui.oldReliableText->setValidator(under6Validator);
    ui.brainstormText->setValidator(under6Validator);

    // gauntlet validators
    ui.vineBraceletText->setValidator(under6Validator);
    ui.mammothGuardText->setValidator(under6Validator);
    ui.clawGuardText->setValidator(under6Validator);
    ui.serpentBracerText->setValidator(under6Validator);
    ui.bronzeGauntletText->setValidator(under6Validator);
    ui.glovesOfRaText->setValidator(under6Validator);
    ui.ironBracerText->setValidator(under6Validator);
    ui.magiciansRingText->setValidator(under6Validator);
    ui.dragonsClawText->setValidator(under6Validator);
    ui.cybergloveText->setValidator(under6Validator);
    ui.protectorRingText->setValidator(under6Validator);
    ui.virtualGloveText->setValidator(under6Validator);

    // trade good validators
    ui.annihilationAmuletText->setValidator(under100Validator);
    ui.beadsText->setValidator(under100Validator);
    ui.ceramicPotText->setValidator(under100Validator);
    ui.chickenText->setValidator(under100Validator);
    ui.goldenJackalText->setValidator(under100Validator);
    ui.jeweledScarabText->setValidator(under100Validator);
    ui.limestoneTabletText->setValidator(under100Validator);
    ui.perfumeText->setValidator(under100Validator);
    ui.riceText->setValidator(under100Validator);
    ui.spiceText->setValidator(under100Validator);
    ui.souvenirSpoonText->setValidator(under100Validator);
    ui.tapestryText->setValidator(under100Validator);
    ui.ticketForExhibitionText->setValidator(under100Validator);
}

auto MainWindow::confirmClose() -> bool {
    if (sram->isModified()) {
        int choice = QMessageBox::question(
            this, tr("Warning: Unsaved Changes"), tr("Save changes?"),
            QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);

        if (choice == QMessageBox::Yes) {
            ui.fileSave->trigger();

            // if the save failed, abort
            if (sram->isModified()) {
                return false;
            }
        } else if (choice == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

void MainWindow::openSRAM(const QString &filename) {
    try {
        sram     = new SRAMFile(filename, region);
        sramFile = new QString(filename);
        open     = true;

        emit sramFileOpened();
    } catch (InvalidSRAMFileException &e) {
        QString temp;

        if (e.getError() == ISFE_INVALIDSIZE) {
            temp = tr("Invalid SRAM File Size");
        } else if (e.getError() == ISFE_NOVALIDGAMES) {
            temp = tr("No Save Games Found");
        }

        QMessageBox::warning(this, tr("Unable to Open SRAM File"), temp,
                             QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void MainWindow::setAlchemy(enum sf_alchemy alchemy, int state) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    sram->setAlchemy(alchemy, (state != 0));
    emit uiChanged();
}

void MainWindow::setAlchemyLevelMajor(enum sf_alchemy alchemy, int value) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getAlchemyLevel(alchemy);
    temp.first               = value;
    sram->setAlchemyLevel(alchemy, temp);

    emit uiChanged();
}

void MainWindow::setAlchemyLevelMinor(enum sf_alchemy alchemy,
                                      const QString  &text) {
    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getAlchemyLevel(alchemy);
    temp.second              = text.toInt();
    sram->setAlchemyLevel(alchemy, temp);

    emit uiChanged();
}

void MainWindow::setCharm(enum sf_charm charm, int state) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    sram->setCharm(charm, (state != 0));
    emit uiChanged();
}

void MainWindow::setGame(int game) {
    Q_ASSERT(open);
    Q_ASSERT((game >= 0) && (game < 4));

    sram->setGame(game);
    emit sramFileOpened();
}

void MainWindow::setIngredient(enum sf_ingredient ingredient,
                               const QString     &text) {
    Q_ASSERT(open);

    sram->setIngredient(ingredient, text.toInt());
    emit uiChanged();
}

void MainWindow::setItem(enum sf_item item, const QString &text) {
    Q_ASSERT(open);

    sram->setItem(item, text.toInt());
    emit uiChanged();
}

void MainWindow::setMoney(enum sf_money money, const QString &text) {
    Q_ASSERT(open);

    sram->setMoney(money, text.toUInt());
    emit uiChanged();
}

void MainWindow::setRegion(enum sf_region region) {
    Q_ASSERT(!open);

    QRegExpValidator *validator;

    this->region = region;

    switch (region) {
        case REGION_GERMANY:
            validator = new QRegExpValidator(
                QRegExp(
                    R"([A-Za-z1-3,\.!'\-&# \x00C4\x00D6\x00DC\x00DF\x00E4\x00F6\x00FC]*)"),
                this);
            break;

        case REGION_SPAIN:
            validator = new QRegExpValidator(
                QRegExp(R"([A-Za-z0-9,\.!'\-& \x00F1]*)"), this);
            break;

        default:
            // US/UK English and French use the same alphabet for names
            validator = new QRegExpValidator(
                QRegExp(R"([A-Za-z0-9,\.!'\-&# ]*)"), this);
    }

    ui.boyNameText->setValidator(validator);
    ui.dogNameText->setValidator(validator);
}

void MainWindow::setTradeGood(enum sf_tradegood tradegood,
                              const QString    &text) {
    Q_ASSERT(open);

    sram->setTradeGood(tradegood, text.toInt());
    emit uiChanged();
}

void MainWindow::setWeapon(enum sf_weapon weapon, int state) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    sram->setWeapon(weapon, (state != 0));
    emit uiChanged();
}

void MainWindow::setWeaponLevelMajor(enum sf_weapon weapon, int value) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getWeaponLevel(weapon);
    temp.first               = value;
    sram->setWeaponLevel(weapon, temp);

    showActualLevel(temp, weapon);
    emit uiChanged();
}

void MainWindow::setWeaponLevelMinor(enum sf_weapon weapon,
                                     const QString &text) {
    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getWeaponLevel(weapon);
    temp.second              = text.toInt();
    sram->setWeaponLevel(weapon, temp);

    showActualLevel(temp, weapon);
    emit uiChanged();
}

void MainWindow::show() {
    QRect screenRect = QApplication::primaryScreen()->availableGeometry();
    QRect windowRect = frameGeometry();

    move(screenRect.width() / 2 - windowRect.width() / 2,
         screenRect.height() / 2 - windowRect.height() / 2);

    emit uiChanged();

    QMainWindow::show();
}

void MainWindow::showActualLevel(std::pair<int, int> level,
                                 enum sf_weapon      weapon) {
    level.second = static_cast<int>(std::floor(level.second / 2.56));

    QString status =
        QString(tr("Actual Level %1:%2")).arg(level.first).arg(level.second);

    switch (weapon) {
        case SF_BONECRUSHER:
            ui.boneCrusherSpinner->setStatusTip(status);
            ui.boneCrusherText->setStatusTip(status);
            break;

        case SF_GLADIATORSWORD:
            ui.gladiatorSwordSpinner->setStatusTip(status);
            ui.gladiatorSwordText->setStatusTip(status);
            break;

        case SF_CRUSADERSWORD:
            ui.crusaderSwordSpinner->setStatusTip(status);
            ui.crusaderSwordText->setStatusTip(status);
            break;

        case SF_NEUTRONBLADE:
            ui.neutronBladeSpinner->setStatusTip(status);
            ui.neutronBladeText->setStatusTip(status);
            break;

        case SF_SPIDERSCLAW:
            ui.spidersClawSpinner->setStatusTip(status);
            ui.spidersClawText->setStatusTip(status);
            break;

        case SF_BRONZEAXE:
            ui.bronzeAxeSpinner->setStatusTip(status);
            ui.bronzeAxeText->setStatusTip(status);
            break;

        case SF_KNIGHTBASHER:
            ui.knightBasherSpinner->setStatusTip(status);
            ui.knightBasherText->setStatusTip(status);
            break;

        case SF_ATOMSMASHER:
            ui.atomSmasherSpinner->setStatusTip(status);
            ui.atomSmasherText->setStatusTip(status);
            break;

        case SF_HORNSPEAR:
            ui.hornSpearSpinner->setStatusTip(status);
            ui.hornSpearText->setStatusTip(status);
            break;

        case SF_BRONZESPEAR:
            ui.bronzeSpearSpinner->setStatusTip(status);
            ui.bronzeSpearText->setStatusTip(status);
            break;

        case SF_LANCEWEAPON:
            ui.lanceWeaponSpinner->setStatusTip(status);
            ui.lanceWeaponText->setStatusTip(status);
            break;

        case SF_LASERLANCE:
            ui.laserLanceSpinner->setStatusTip(status);
            ui.laserLanceText->setStatusTip(status);
            break;

        default:
            ui.dogAttackLevelSpinner->setStatusTip(status);
            ui.dogAttackLevelText->setStatusTip(status);
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (open && !confirmClose()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    // accept file list drops
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    QList<QUrl> urls     = event->mimeData()->urls();
    QString     filename = urls.first().toLocalFile();

    // uri could be something else
    if (filename.isEmpty()) {
        return;
    }

    if (open) {
        ui.fileClose->trigger();

        // we must've decided not to close
        if (open) {
            return;
        }
    }

    openSRAM(filename);
}

void MainWindow::onSRAMFileOpened() {
    Q_ASSERT(sram);

    std::pair<int, int> level;

    ignoreSignals = true;

    // load the hero's names
    ui.boyNameText->setText(sram->getName(SF_BOY));
    ui.dogNameText->setText(sram->getName(SF_DOG));

    // load the money
    ui.talonsText->setText(QString::number(sram->getMoney(SF_TALONS)));
    ui.jewelsText->setText(QString::number(sram->getMoney(SF_JEWELS)));
    ui.goldCoinsText->setText(QString::number(sram->getMoney(SF_GOLDCOINS)));
    ui.creditsText->setText(QString::number(sram->getMoney(SF_CREDITS)));

    // load boy's stats
    ui.boyLevelText->setText(QString::number(sram->getLevel(SF_BOY)));
    ui.boyCurrentHPText->setText(QString::number(sram->getCurrentHP(SF_BOY)));
    ui.boyExperienceText->setText(QString::number(sram->getExperience(SF_BOY)));

    // load dog's stats
    ui.dogLevelText->setText(QString::number(sram->getLevel(SF_DOG)));
    ui.dogCurrentHPText->setText(QString::number(sram->getCurrentHP(SF_DOG)));
    ui.dogExperienceText->setText(QString::number(sram->getExperience(SF_DOG)));

    level = sram->getAttackLevel();
    ui.dogAttackLevelSpinner->setValue(level.first);
    ui.dogAttackLevelText->setText(QString::number(level.second));
    showActualLevel(level);

    // load weapon levels
    level = sram->getWeaponLevel(SF_BONECRUSHER);
    ui.boneCrusherCheck->setChecked(sram->hasWeapon(SF_BONECRUSHER));
    ui.boneCrusherSpinner->setValue(level.first);
    ui.boneCrusherText->setText(QString::number(level.second));
    showActualLevel(level, SF_BONECRUSHER);

    level = sram->getWeaponLevel(SF_GLADIATORSWORD);
    ui.gladiatorSwordCheck->setChecked(sram->hasWeapon(SF_GLADIATORSWORD));
    ui.gladiatorSwordSpinner->setValue(level.first);
    ui.gladiatorSwordText->setText(QString::number(level.second));
    showActualLevel(level, SF_GLADIATORSWORD);

    level = sram->getWeaponLevel(SF_CRUSADERSWORD);
    ui.crusaderSwordCheck->setChecked(sram->hasWeapon(SF_CRUSADERSWORD));
    ui.crusaderSwordSpinner->setValue(level.first);
    ui.crusaderSwordText->setText(QString::number(level.second));
    showActualLevel(level, SF_CRUSADERSWORD);

    level = sram->getWeaponLevel(SF_NEUTRONBLADE);
    ui.neutronBladeCheck->setChecked(sram->hasWeapon(SF_NEUTRONBLADE));
    ui.neutronBladeSpinner->setValue(level.first);
    ui.neutronBladeText->setText(QString::number(level.second));
    showActualLevel(level, SF_NEUTRONBLADE);

    level = sram->getWeaponLevel(SF_SPIDERSCLAW);
    ui.spidersClawCheck->setChecked(sram->hasWeapon(SF_SPIDERSCLAW));
    ui.spidersClawSpinner->setValue(level.first);
    ui.spidersClawText->setText(QString::number(level.second));
    showActualLevel(level, SF_SPIDERSCLAW);

    level = sram->getWeaponLevel(SF_BRONZEAXE);
    ui.bronzeAxeCheck->setChecked(sram->hasWeapon(SF_BRONZEAXE));
    ui.bronzeAxeSpinner->setValue(level.first);
    ui.bronzeAxeText->setText(QString::number(level.second));
    showActualLevel(level, SF_BRONZEAXE);

    level = sram->getWeaponLevel(SF_KNIGHTBASHER);
    ui.knightBasherCheck->setChecked(sram->hasWeapon(SF_KNIGHTBASHER));
    ui.knightBasherSpinner->setValue(level.first);
    ui.knightBasherText->setText(QString::number(level.second));
    showActualLevel(level, SF_KNIGHTBASHER);

    level = sram->getWeaponLevel(SF_ATOMSMASHER);
    ui.atomSmasherCheck->setChecked(sram->hasWeapon(SF_ATOMSMASHER));
    ui.atomSmasherSpinner->setValue(level.first);
    ui.atomSmasherText->setText(QString::number(level.second));
    showActualLevel(level, SF_ATOMSMASHER);

    level = sram->getWeaponLevel(SF_HORNSPEAR);
    ui.hornSpearCheck->setChecked(sram->hasWeapon(SF_HORNSPEAR));
    ui.hornSpearSpinner->setValue(level.first);
    ui.hornSpearText->setText(QString::number(level.second));
    showActualLevel(level, SF_HORNSPEAR);

    level = sram->getWeaponLevel(SF_BRONZESPEAR);
    ui.bronzeSpearCheck->setChecked(sram->hasWeapon(SF_BRONZESPEAR));
    ui.bronzeSpearSpinner->setValue(level.first);
    ui.bronzeSpearText->setText(QString::number(level.second));
    showActualLevel(level, SF_BRONZESPEAR);

    level = sram->getWeaponLevel(SF_LANCEWEAPON);
    ui.lanceWeaponCheck->setChecked(sram->hasWeapon(SF_LANCEWEAPON));
    ui.lanceWeaponSpinner->setValue(level.first);
    ui.lanceWeaponText->setText(QString::number(level.second));
    showActualLevel(level, SF_LANCEWEAPON);

    level = sram->getWeaponLevel(SF_LASERLANCE);
    ui.laserLanceCheck->setChecked(sram->hasWeapon(SF_LASERLANCE));
    ui.laserLanceSpinner->setValue(level.first);
    ui.laserLanceText->setText(QString::number(level.second));
    showActualLevel(level, SF_LASERLANCE);

    ui.bazookaCheck->setChecked(sram->hasWeapon(SF_BAZOOKA));

    // load alchemy ingredients
    ui.acornText->setText(QString::number(sram->getIngredient(SF_ACORN)));
    ui.ashText->setText(QString::number(sram->getIngredient(SF_ASH)));
    ui.atlasMedallionText->setText(
        QString::number(sram->getIngredient(SF_ATLASMEDALLION)));
    ui.boneText->setText(QString::number(sram->getIngredient(SF_BONE)));
    ui.brimstoneText->setText(
        QString::number(sram->getIngredient(SF_BRIMSTONE)));
    ui.clayText->setText(QString::number(sram->getIngredient(SF_CLAY)));
    ui.crystalText->setText(QString::number(sram->getIngredient(SF_CRYSTAL)));
    ui.dryIceText->setText(QString::number(sram->getIngredient(SF_DRYICE)));
    ui.ethanolText->setText(QString::number(sram->getIngredient(SF_ETHANOL)));
    ui.featherText->setText(QString::number(sram->getIngredient(SF_FEATHER)));
    ui.greaseText->setText(QString::number(sram->getIngredient(SF_GREASE)));
    ui.gunpowderText->setText(
        QString::number(sram->getIngredient(SF_GUNPOWDER)));
    ui.ironText->setText(QString::number(sram->getIngredient(SF_IRON)));
    ui.limestoneText->setText(
        QString::number(sram->getIngredient(SF_LIMESTONE)));
    ui.meteoriteText->setText(
        QString::number(sram->getIngredient(SF_METEORITE)));
    ui.mudPepperText->setText(
        QString::number(sram->getIngredient(SF_MUDPEPPER)));
    ui.mushroomText->setText(QString::number(sram->getIngredient(SF_MUSHROOM)));
    ui.oilText->setText(QString::number(sram->getIngredient(SF_OIL)));
    ui.rootText->setText(QString::number(sram->getIngredient(SF_ROOT)));
    ui.vinegarText->setText(QString::number(sram->getIngredient(SF_VINEGAR)));
    ui.waterText->setText(QString::number(sram->getIngredient(SF_WATER)));
    ui.waxText->setText(QString::number(sram->getIngredient(SF_WAX)));

    // load alchemy levels
    level = sram->getAlchemyLevel(SF_ACIDRAIN);
    ui.acidRainCheck->setChecked(sram->hasAlchemy(SF_ACIDRAIN));
    ui.acidRainSpinner->setValue(level.first);
    ui.acidRainText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_ATLAS);
    ui.atlasCheck->setChecked(sram->hasAlchemy(SF_ATLAS));
    ui.atlasSpinner->setValue(level.first);
    ui.atlasText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_BARRIER);
    ui.barrierCheck->setChecked(sram->hasAlchemy(SF_BARRIER));
    ui.barrierSpinner->setValue(level.first);
    ui.barrierText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_CALLUP);
    ui.callUpCheck->setChecked(sram->hasAlchemy(SF_CALLUP));
    ui.callUpSpinner->setValue(level.first);
    ui.callUpText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_CORROSION);
    ui.corrosionCheck->setChecked(sram->hasAlchemy(SF_CORROSION));
    ui.corrosionSpinner->setValue(level.first);
    ui.corrosionText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_CRUSH);
    ui.crushCheck->setChecked(sram->hasAlchemy(SF_CRUSH));
    ui.crushSpinner->setValue(level.first);
    ui.crushText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_CURE);
    ui.cureCheck->setChecked(sram->hasAlchemy(SF_CURE));
    ui.cureSpinner->setValue(level.first);
    ui.cureText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_DEFEND);
    ui.defendCheck->setChecked(sram->hasAlchemy(SF_DEFEND));
    ui.defendSpinner->setValue(level.first);
    ui.defendText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_DOUBLEDRAIN);
    ui.doubleDrainCheck->setChecked(sram->hasAlchemy(SF_DOUBLEDRAIN));
    ui.doubleDrainSpinner->setValue(level.first);
    ui.doubleDrainText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_DRAIN);
    ui.drainCheck->setChecked(sram->hasAlchemy(SF_DRAIN));
    ui.drainSpinner->setValue(level.first);
    ui.drainText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_ENERGIZE);
    ui.energizeCheck->setChecked(sram->hasAlchemy(SF_ENERGIZE));
    ui.energizeSpinner->setValue(level.first);
    ui.energizeText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_ESCAPE);
    ui.escapeCheck->setChecked(sram->hasAlchemy(SF_ESCAPE));
    ui.escapeSpinner->setValue(level.first);
    ui.escapeText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_EXPLOSION);
    ui.explosionCheck->setChecked(sram->hasAlchemy(SF_EXPLOSION));
    ui.explosionSpinner->setValue(level.first);
    ui.explosionText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_FIREBALL);
    ui.fireballCheck->setChecked(sram->hasAlchemy(SF_FIREBALL));
    ui.fireballSpinner->setValue(level.first);
    ui.fireballText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_FIREPOWER);
    ui.firePowerCheck->setChecked(sram->hasAlchemy(SF_FIREPOWER));
    ui.firePowerSpinner->setValue(level.first);
    ui.firePowerText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_FLASH);
    ui.flashCheck->setChecked(sram->hasAlchemy(SF_FLASH));
    ui.flashSpinner->setValue(level.first);
    ui.flashText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_FORCEFIELD);
    ui.forceFieldCheck->setChecked(sram->hasAlchemy(SF_FORCEFIELD));
    ui.forceFieldSpinner->setValue(level.first);
    ui.forceFieldText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_HARDBALL);
    ui.hardBallCheck->setChecked(sram->hasAlchemy(SF_HARDBALL));
    ui.hardBallSpinner->setValue(level.first);
    ui.hardBallText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_HEAL);
    ui.healCheck->setChecked(sram->hasAlchemy(SF_HEAL));
    ui.healSpinner->setValue(level.first);
    ui.healText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_LANCEALCHEMY);
    ui.lanceAlchemyCheck->setChecked(sram->hasAlchemy(SF_LANCEALCHEMY));
    ui.lanceAlchemySpinner->setValue(level.first);
    ui.lanceAlchemyText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_LEVITATE);
    ui.levitateCheck->setChecked(sram->hasAlchemy(SF_LEVITATE));
    ui.levitateSpinner->setValue(level.first);
    ui.levitateText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_LIGHTNINGSTORM);
    ui.lightningStormCheck->setChecked(sram->hasAlchemy(SF_LIGHTNINGSTORM));
    ui.lightningStormSpinner->setValue(level.first);
    ui.lightningStormText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_MIRACLECURE);
    ui.miracleCureCheck->setChecked(sram->hasAlchemy(SF_MIRACLECURE));
    ui.miracleCureSpinner->setValue(level.first);
    ui.miracleCureText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_NITRO);
    ui.nitroCheck->setChecked(sram->hasAlchemy(SF_NITRO));
    ui.nitroSpinner->setValue(level.first);
    ui.nitroText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_ONEUP);
    ui.oneUpCheck->setChecked(sram->hasAlchemy(SF_ONEUP));
    ui.oneUpSpinner->setValue(level.first);
    ui.oneUpText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_REFLECT);
    ui.reflectCheck->setChecked(sram->hasAlchemy(SF_REFLECT));
    ui.reflectSpinner->setValue(level.first);
    ui.reflectText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_REGROWTH);
    ui.regrowthCheck->setChecked(sram->hasAlchemy(SF_REGROWTH));
    ui.regrowthSpinner->setValue(level.first);
    ui.regrowthText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_REVEALER);
    ui.revealerCheck->setChecked(sram->hasAlchemy(SF_REVEALER));
    ui.revealerSpinner->setValue(level.first);
    ui.revealerText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_REVIVE);
    ui.reviveCheck->setChecked(sram->hasAlchemy(SF_REVIVE));
    ui.reviveSpinner->setValue(level.first);
    ui.reviveText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_SLOWBURN);
    ui.slowBurnCheck->setChecked(sram->hasAlchemy(SF_SLOWBURN));
    ui.slowBurnSpinner->setValue(level.first);
    ui.slowBurnText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_SPEED);
    ui.speedCheck->setChecked(sram->hasAlchemy(SF_SPEED));
    ui.speedSpinner->setValue(level.first);
    ui.speedText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_STING);
    ui.stingCheck->setChecked(sram->hasAlchemy(SF_STING));
    ui.stingSpinner->setValue(level.first);
    ui.stingText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_STOP);
    ui.stopCheck->setChecked(sram->hasAlchemy(SF_STOP));
    ui.stopSpinner->setValue(level.first);
    ui.stopText->setText(QString::number(level.second));

    level = sram->getAlchemyLevel(SF_SUPERHEAL);
    ui.superHealCheck->setChecked(sram->hasAlchemy(SF_SUPERHEAL));
    ui.superHealSpinner->setValue(level.first);
    ui.superHealText->setText(QString::number(level.second));

    // load items
    ui.petalText->setText(QString::number(sram->getItem(SF_PETAL)));
    ui.nectarText->setText(QString::number(sram->getItem(SF_NECTAR)));
    ui.honeyText->setText(QString::number(sram->getItem(SF_HONEY)));
    ui.dogBiscuitText->setText(QString::number(sram->getItem(SF_DOGBISCUIT)));
    ui.wingsText->setText(QString::number(sram->getItem(SF_WINGS)));
    ui.essenceText->setText(QString::number(sram->getItem(SF_ESSENCE)));
    ui.pixieDustText->setText(QString::number(sram->getItem(SF_PIXIEDUST)));
    ui.callBeadText->setText(QString::number(sram->getItem(SF_CALLBEAD)));

    // load dog collars
    ui.leatherCollarText->setText(
        QString::number(sram->getItem(SF_LEATHERCOLLAR)));
    ui.spikyCollarText->setText(QString::number(sram->getItem(SF_SPIKYCOLLAR)));
    ui.defenderCollarText->setText(
        QString::number(sram->getItem(SF_DEFENDERCOLLAR)));
    ui.spotsCollarText->setText(QString::number(sram->getItem(SF_SPOTSCOLLAR)));

    // load armor
    ui.grassVestText->setText(QString::number(sram->getItem(SF_GRASSVEST)));
    ui.shellPlateText->setText(QString::number(sram->getItem(SF_SHELLPLATE)));
    ui.dinoSkinText->setText(QString::number(sram->getItem(SF_DINOSKIN)));
    ui.bronzeArmorText->setText(QString::number(sram->getItem(SF_BRONZEARMOR)));
    ui.stoneVestText->setText(QString::number(sram->getItem(SF_STONEVEST)));
    ui.centurionCapeText->setText(
        QString::number(sram->getItem(SF_CENTURIONCAPE)));
    ui.silverMailText->setText(QString::number(sram->getItem(SF_SILVERMAIL)));
    ui.goldPlatedVestText->setText(
        QString::number(sram->getItem(SF_GOLDPLATEDVEST)));
    ui.shiningArmorText->setText(
        QString::number(sram->getItem(SF_SHININGARMOR)));
    ui.magnaMailText->setText(QString::number(sram->getItem(SF_MAGNAMAIL)));
    ui.titaniumVestText->setText(
        QString::number(sram->getItem(SF_TITANIUMVEST)));
    ui.virtualVestText->setText(QString::number(sram->getItem(SF_VIRTUALVEST)));

    // load bazooka ammunition
    ui.thunderBallText->setText(QString::number(sram->getItem(SF_THUNDERBALL)));
    ui.particleBombText->setText(
        QString::number(sram->getItem(SF_PARTICLEBOMB)));
    ui.cryoBlastText->setText(QString::number(sram->getItem(SF_CRYOBLAST)));

    // load helmets
    ui.grassHatText->setText(QString::number(sram->getItem(SF_GRASSHAT)));
    ui.shellHatText->setText(QString::number(sram->getItem(SF_SHELLHAT)));
    ui.dinoHelmText->setText(QString::number(sram->getItem(SF_DINOHELM)));
    ui.bronzeHelmetText->setText(
        QString::number(sram->getItem(SF_BRONZEHELMET)));
    ui.obsidianHelmText->setText(
        QString::number(sram->getItem(SF_OBSIDIANHELM)));
    ui.centurionHelmText->setText(
        QString::number(sram->getItem(SF_CENTURIONHELM)));
    ui.titansCrownText->setText(QString::number(sram->getItem(SF_TITANSCROWN)));
    ui.dragonHelmText->setText(QString::number(sram->getItem(SF_DRAGONHELM)));
    ui.knightsHelmText->setText(QString::number(sram->getItem(SF_KNIGHTSHELM)));
    ui.lightningHelmText->setText(
        QString::number(sram->getItem(SF_LIGHTNINGHELM)));
    ui.oldReliableText->setText(QString::number(sram->getItem(SF_OLDRELIABLE)));
    ui.brainstormText->setText(QString::number(sram->getItem(SF_BRAINSTORM)));

    // load gauntlets
    ui.vineBraceletText->setText(
        QString::number(sram->getItem(SF_VINEBRACELET)));
    ui.mammothGuardText->setText(
        QString::number(sram->getItem(SF_MAMMOTHGUARD)));
    ui.clawGuardText->setText(QString::number(sram->getItem(SF_CLAWGUARD)));
    ui.serpentBracerText->setText(
        QString::number(sram->getItem(SF_SERPENTBRACER)));
    ui.bronzeGauntletText->setText(
        QString::number(sram->getItem(SF_BRONZEGAUNTLET)));
    ui.glovesOfRaText->setText(QString::number(sram->getItem(SF_GLOVESOFRA)));
    ui.ironBracerText->setText(QString::number(sram->getItem(SF_IRONBRACER)));
    ui.magiciansRingText->setText(
        QString::number(sram->getItem(SF_MAGICIANSRING)));
    ui.dragonsClawText->setText(QString::number(sram->getItem(SF_DRAGONSCLAW)));
    ui.cybergloveText->setText(QString::number(sram->getItem(SF_CYBERGLOVE)));
    ui.protectorRingText->setText(
        QString::number(sram->getItem(SF_PROTECTORRING)));
    ui.virtualGloveText->setText(
        QString::number(sram->getItem(SF_VIRTUALGLOVE)));

    // load charms
    ui.armorPolishCheck->setChecked(sram->hasCharm(SF_ARMORPOLISH));
    ui.chocoboEggCheck->setChecked(sram->hasCharm(SF_CHOCOBOEGG));
    ui.insectIncenseCheck->setChecked(sram->hasCharm(SF_INSECTINCENSE));
    ui.jadeDiskCheck->setChecked(sram->hasCharm(SF_JADEDISK));
    ui.jaguarRingCheck->setChecked(sram->hasCharm(SF_JAGUARRING));
    ui.magicGourdCheck->setChecked(sram->hasCharm(SF_MAGICGOURD));
    ui.moxaStickCheck->setChecked(sram->hasCharm(SF_MOXASTICK));
    ui.oracleBoneCheck->setChecked(sram->hasCharm(SF_ORACLEBONE));
    ui.rubyHeartCheck->setChecked(sram->hasCharm(SF_RUBYHEART));
    ui.silverSheathCheck->setChecked(sram->hasCharm(SF_SILVERSHEATH));
    ui.staffOfLifeCheck->setChecked(sram->hasCharm(SF_STAFFOFLIFE));
    ui.sunStoneCheck->setChecked(sram->hasCharm(SF_SUNSTONE));
    ui.thugsCloakCheck->setChecked(sram->hasCharm(SF_THUGSCLOAK));
    ui.wizardsCoinCheck->setChecked(sram->hasCharm(SF_WIZARDSCOIN));

    // load trade goods
    ui.annihilationAmuletText->setText(
        QString::number(sram->getTradeGood(SF_ANNIHILATIONAMULET)));
    ui.beadsText->setText(QString::number(sram->getTradeGood(SF_BEADS)));
    ui.ceramicPotText->setText(
        QString::number(sram->getTradeGood(SF_CERAMICPOT)));
    ui.chickenText->setText(QString::number(sram->getTradeGood(SF_CHICKEN)));
    ui.goldenJackalText->setText(
        QString::number(sram->getTradeGood(SF_GOLDENJACKAL)));
    ui.jeweledScarabText->setText(
        QString::number(sram->getTradeGood(SF_JEWELEDSCARAB)));
    ui.limestoneTabletText->setText(
        QString::number(sram->getTradeGood(SF_LIMESTONETABLET)));
    ui.perfumeText->setText(QString::number(sram->getTradeGood(SF_PERFUME)));
    ui.riceText->setText(QString::number(sram->getTradeGood(SF_RICE)));
    ui.spiceText->setText(QString::number(sram->getTradeGood(SF_SPICE)));
    ui.souvenirSpoonText->setText(
        QString::number(sram->getTradeGood(SF_SOUVENIRSPOON)));
    ui.tapestryText->setText(QString::number(sram->getTradeGood(SF_TAPESTRY)));
    ui.ticketForExhibitionText->setText(
        QString::number(sram->getTradeGood(SF_TICKETFOREXHIBITION)));

    ignoreSignals = false;
}

void MainWindow::onUIChanged() {
    ui.fileClose->setEnabled(open);
    ui.fileSave->setEnabled(open && sram->isModified());
    ui.fileSaveAs->setEnabled(open);

    // you can't change the region after the game is open
    ui.regionUnitedStates->setEnabled(!open);
    ui.regionEngland->setEnabled(!open);
    ui.regionFrance->setEnabled(!open);
    ui.regionGermany->setEnabled(!open);
    ui.regionSpain->setEnabled(!open);

    ui.tabWidget->setVisible(open);

    if (open) {
        ui.gameGame1->setEnabled(sram->isValid(0));
        ui.gameGame2->setEnabled(sram->isValid(1));
        ui.gameGame3->setEnabled(sram->isValid(2));
        ui.gameGame4->setEnabled(sram->isValid(3));

        switch (sram->getGame()) {
            case 0:
                ui.gameGame1->setChecked(true);
                break;
            case 1:
                ui.gameGame2->setChecked(true);
                break;
            case 2:
                ui.gameGame3->setChecked(true);
                break;
            default:
                ui.gameGame4->setChecked(true);
                break;
        }

        ui.boneCrusherSpinner->setEnabled(sram->hasWeapon(SF_BONECRUSHER));
        ui.boneCrusherText->setEnabled(sram->hasWeapon(SF_BONECRUSHER));

        ui.gladiatorSwordSpinner->setEnabled(
            sram->hasWeapon(SF_GLADIATORSWORD));
        ui.gladiatorSwordText->setEnabled(sram->hasWeapon(SF_GLADIATORSWORD));

        ui.crusaderSwordSpinner->setEnabled(sram->hasWeapon(SF_CRUSADERSWORD));
        ui.crusaderSwordText->setEnabled(sram->hasWeapon(SF_CRUSADERSWORD));

        ui.neutronBladeSpinner->setEnabled(sram->hasWeapon(SF_NEUTRONBLADE));
        ui.neutronBladeText->setEnabled(sram->hasWeapon(SF_NEUTRONBLADE));

        ui.spidersClawSpinner->setEnabled(sram->hasWeapon(SF_SPIDERSCLAW));
        ui.spidersClawText->setEnabled(sram->hasWeapon(SF_SPIDERSCLAW));

        ui.bronzeAxeSpinner->setEnabled(sram->hasWeapon(SF_BRONZEAXE));
        ui.bronzeAxeText->setEnabled(sram->hasWeapon(SF_BRONZEAXE));

        ui.knightBasherSpinner->setEnabled(sram->hasWeapon(SF_KNIGHTBASHER));
        ui.knightBasherText->setEnabled(sram->hasWeapon(SF_KNIGHTBASHER));

        ui.atomSmasherSpinner->setEnabled(sram->hasWeapon(SF_ATOMSMASHER));
        ui.atomSmasherText->setEnabled(sram->hasWeapon(SF_ATOMSMASHER));

        ui.hornSpearSpinner->setEnabled(sram->hasWeapon(SF_HORNSPEAR));
        ui.hornSpearText->setEnabled(sram->hasWeapon(SF_HORNSPEAR));

        ui.bronzeSpearSpinner->setEnabled(sram->hasWeapon(SF_BRONZESPEAR));
        ui.bronzeSpearText->setEnabled(sram->hasWeapon(SF_BRONZESPEAR));

        ui.lanceWeaponSpinner->setEnabled(sram->hasWeapon(SF_LANCEWEAPON));
        ui.lanceWeaponText->setEnabled(sram->hasWeapon(SF_LANCEWEAPON));

        ui.laserLanceSpinner->setEnabled(sram->hasWeapon(SF_LASERLANCE));
        ui.laserLanceText->setEnabled(sram->hasWeapon(SF_LASERLANCE));

        ui.acidRainSpinner->setEnabled(sram->hasAlchemy(SF_ACIDRAIN));
        ui.acidRainText->setEnabled(sram->hasAlchemy(SF_ACIDRAIN));

        ui.atlasSpinner->setEnabled(sram->hasAlchemy(SF_ATLAS));
        ui.atlasText->setEnabled(sram->hasAlchemy(SF_ATLAS));

        ui.barrierSpinner->setEnabled(sram->hasAlchemy(SF_BARRIER));
        ui.barrierText->setEnabled(sram->hasAlchemy(SF_BARRIER));

        ui.callUpSpinner->setEnabled(sram->hasAlchemy(SF_CALLUP));
        ui.callUpText->setEnabled(sram->hasAlchemy(SF_CALLUP));

        ui.corrosionSpinner->setEnabled(sram->hasAlchemy(SF_CORROSION));
        ui.corrosionText->setEnabled(sram->hasAlchemy(SF_CORROSION));

        ui.crushSpinner->setEnabled(sram->hasAlchemy(SF_CRUSH));
        ui.crushText->setEnabled(sram->hasAlchemy(SF_CRUSH));

        ui.cureSpinner->setEnabled(sram->hasAlchemy(SF_CURE));
        ui.cureText->setEnabled(sram->hasAlchemy(SF_CURE));

        ui.defendSpinner->setEnabled(sram->hasAlchemy(SF_DEFEND));
        ui.defendText->setEnabled(sram->hasAlchemy(SF_DEFEND));

        ui.doubleDrainSpinner->setEnabled(sram->hasAlchemy(SF_DOUBLEDRAIN));
        ui.doubleDrainText->setEnabled(sram->hasAlchemy(SF_DOUBLEDRAIN));

        ui.drainSpinner->setEnabled(sram->hasAlchemy(SF_DRAIN));
        ui.drainText->setEnabled(sram->hasAlchemy(SF_DRAIN));

        ui.energizeSpinner->setEnabled(sram->hasAlchemy(SF_ENERGIZE));
        ui.energizeText->setEnabled(sram->hasAlchemy(SF_ENERGIZE));

        ui.escapeSpinner->setEnabled(sram->hasAlchemy(SF_ESCAPE));
        ui.escapeText->setEnabled(sram->hasAlchemy(SF_ESCAPE));

        ui.explosionSpinner->setEnabled(sram->hasAlchemy(SF_EXPLOSION));
        ui.explosionText->setEnabled(sram->hasAlchemy(SF_EXPLOSION));

        ui.fireballSpinner->setEnabled(sram->hasAlchemy(SF_FIREBALL));
        ui.fireballText->setEnabled(sram->hasAlchemy(SF_FIREBALL));

        ui.firePowerSpinner->setEnabled(sram->hasAlchemy(SF_FIREPOWER));
        ui.firePowerText->setEnabled(sram->hasAlchemy(SF_FIREPOWER));

        ui.flashSpinner->setEnabled(sram->hasAlchemy(SF_FLASH));
        ui.flashText->setEnabled(sram->hasAlchemy(SF_FLASH));

        ui.forceFieldSpinner->setEnabled(sram->hasAlchemy(SF_FORCEFIELD));
        ui.forceFieldText->setEnabled(sram->hasAlchemy(SF_FORCEFIELD));

        ui.hardBallSpinner->setEnabled(sram->hasAlchemy(SF_HARDBALL));
        ui.hardBallText->setEnabled(sram->hasAlchemy(SF_HARDBALL));

        ui.healSpinner->setEnabled(sram->hasAlchemy(SF_HEAL));
        ui.healText->setEnabled(sram->hasAlchemy(SF_HEAL));

        ui.lanceAlchemySpinner->setEnabled(sram->hasAlchemy(SF_LANCEALCHEMY));
        ui.lanceAlchemyText->setEnabled(sram->hasAlchemy(SF_LANCEALCHEMY));

        ui.levitateSpinner->setEnabled(sram->hasAlchemy(SF_LEVITATE));
        ui.levitateText->setEnabled(sram->hasAlchemy(SF_LEVITATE));

        ui.lightningStormSpinner->setEnabled(
            sram->hasAlchemy(SF_LIGHTNINGSTORM));
        ui.lightningStormText->setEnabled(sram->hasAlchemy(SF_LIGHTNINGSTORM));

        ui.miracleCureSpinner->setEnabled(sram->hasAlchemy(SF_MIRACLECURE));
        ui.miracleCureText->setEnabled(sram->hasAlchemy(SF_MIRACLECURE));

        ui.nitroSpinner->setEnabled(sram->hasAlchemy(SF_NITRO));
        ui.nitroText->setEnabled(sram->hasAlchemy(SF_NITRO));

        ui.oneUpSpinner->setEnabled(sram->hasAlchemy(SF_ONEUP));
        ui.oneUpText->setEnabled(sram->hasAlchemy(SF_ONEUP));

        ui.reflectSpinner->setEnabled(sram->hasAlchemy(SF_REFLECT));
        ui.reflectText->setEnabled(sram->hasAlchemy(SF_REFLECT));

        ui.regrowthSpinner->setEnabled(sram->hasAlchemy(SF_REGROWTH));
        ui.regrowthText->setEnabled(sram->hasAlchemy(SF_REGROWTH));

        ui.revealerSpinner->setEnabled(sram->hasAlchemy(SF_REVEALER));
        ui.revealerText->setEnabled(sram->hasAlchemy(SF_REVEALER));

        ui.reviveSpinner->setEnabled(sram->hasAlchemy(SF_REVIVE));
        ui.reviveText->setEnabled(sram->hasAlchemy(SF_REVIVE));

        ui.slowBurnSpinner->setEnabled(sram->hasAlchemy(SF_SLOWBURN));
        ui.slowBurnText->setEnabled(sram->hasAlchemy(SF_SLOWBURN));

        ui.speedSpinner->setEnabled(sram->hasAlchemy(SF_SPEED));
        ui.speedText->setEnabled(sram->hasAlchemy(SF_SPEED));

        ui.stingSpinner->setEnabled(sram->hasAlchemy(SF_STING));
        ui.stingText->setEnabled(sram->hasAlchemy(SF_STING));

        ui.stopSpinner->setEnabled(sram->hasAlchemy(SF_STOP));
        ui.stopText->setEnabled(sram->hasAlchemy(SF_STOP));

        ui.superHealSpinner->setEnabled(sram->hasAlchemy(SF_SUPERHEAL));
        ui.superHealText->setEnabled(sram->hasAlchemy(SF_SUPERHEAL));
    } else {
        ui.gameGame1->setEnabled(false);
        ui.gameGame2->setEnabled(false);
        ui.gameGame3->setEnabled(false);
        ui.gameGame4->setEnabled(false);
    }
}

void MainWindow::on_boyCurrentHPText_textEdited(const QString &text) {
    Q_ASSERT(open);

    sram->setCurrentHP(SF_BOY, text.toUInt());
    emit uiChanged();
}

void MainWindow::on_boyExperienceText_textEdited(const QString &text) {
    Q_ASSERT(open);

    sram->setExperience(SF_BOY, text.toUInt());
    emit uiChanged();
}

void MainWindow::on_boyLevelText_textEdited(const QString &text) {
    Q_ASSERT(open);

    int level = text.toInt();

    if (level != 0) {
        sram->setLevel(SF_BOY, level);
        emit uiChanged();
    }
}

void MainWindow::on_boyNameText_textEdited(const QString &name) {
    Q_ASSERT(open);

    sram->setName(SF_BOY, name);
    emit uiChanged();
}

void MainWindow::on_dogAttackLevelSpinner_valueChanged(int level) {
    if (ignoreSignals) {
        return;
    }

    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getAttackLevel();
    temp.first               = level;
    sram->setAttackLevel(temp);

    emit uiChanged();
}

void MainWindow::on_dogAttackLevelText_textEdited(const QString &text) {
    Q_ASSERT(open);

    std::pair<int, int> temp = sram->getAttackLevel();
    temp.second              = text.toInt();
    sram->setAttackLevel(temp);

    showActualLevel(temp);
    emit uiChanged();
}

void MainWindow::on_dogCurrentHPText_textEdited(const QString &text) {
    Q_ASSERT(open);

    sram->setCurrentHP(SF_DOG, text.toUInt());
    emit uiChanged();
}

void MainWindow::on_dogExperienceText_textEdited(const QString &text) {
    Q_ASSERT(open);

    sram->setExperience(SF_DOG, text.toUInt());
    emit uiChanged();
}

void MainWindow::on_dogLevelText_textEdited(const QString &text) {
    Q_ASSERT(open);

    int level = text.toInt();

    if (level != 0) {
        sram->setLevel(SF_DOG, level);
        emit uiChanged();
    }
}

void MainWindow::on_dogNameText_textEdited(const QString &name) {
    Q_ASSERT(open);

    sram->setName(SF_DOG, name);
    emit uiChanged();
}

void MainWindow::on_fileClose_triggered(bool) {
    Q_ASSERT(open);

    if (confirmClose()) {
        delete sram;
        delete sramFile;
        open = false;

        emit uiChanged();
    }
}

void MainWindow::on_fileOpen_triggered(bool) {
    if (open && !confirmClose()) {
        return;
    }

    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open Secret of Evermore SRAM File"), "",
        tr("SRAM Files (*.srm)"));

    if (filename.isNull()) {
        return;
    }

    ui.tabWidget->setCurrentIndex(0);
    openSRAM(filename);
}

void MainWindow::on_fileSave_triggered(bool) {
    Q_ASSERT(open);

    if (!sram->save(*sramFile)) {
        QMessageBox::warning(this, tr("Unable to Save SRAM File"),
                             tr("An I/O error occurred while trying to save."),
                             QMessageBox::Ok, QMessageBox::NoButton);
    }

    emit uiChanged();
}

void MainWindow::on_fileSaveAs_triggered(bool) {
    Q_ASSERT(open);

    QString temp = QFileDialog::getSaveFileName(this, tr("Save SRAM File As"),
                                                "", tr("SRAM Files (*.srm)"));

    if (temp.isNull()) {
        return;
    }

    delete sramFile;
    sramFile = new QString(temp);

    ui.fileSave->trigger();
}

void MainWindow::on_helpAbout_triggered(bool) {
    if (!aboutDialog) {
        aboutDialog = new AboutDialog(this);
    }

    aboutDialog->show();
}
