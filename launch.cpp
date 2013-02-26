/*
 *   Copyright 2009 by Chani Armitage <chani@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "launch.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QFileInfo>

#include <KDebug>
#include <KIcon>
#include <KMenu>

#include <Plasma/DataEngine>
#include <Plasma/Containment>
#include <Plasma/Service>

FavoritesLauncher::FavoritesLauncher(QObject *parent, const QVariantList &args)
    : Plasma::ContainmentActions(parent, args)
    , m_action(new QAction(this))
{
    m_menu = new KMenu();
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(switchTo(QAction*)));

    m_action->setMenu(m_menu);
}

FavoritesLauncher::~FavoritesLauncher()
{
    delete m_menu;
}

void FavoritesLauncher::init(const KConfigGroup &)
{
}

void FavoritesLauncher::contextEvent(QEvent *event)
{
    makeMenu();
    m_menu->adjustSize();
    m_menu->exec(popupPosition(m_menu->size(), event));
}

QList<QAction *> FavoritesLauncher::contextualActions()
{
    makeMenu();

    QList<QAction *> list;
    list << m_action;
    return list;
}

void FavoritesLauncher::makeMenu()
{
    Plasma::DataEngine *apps = dataEngine("apps");
    if (!apps->isValid()) {
        return;
    }

    m_menu->clear();

    // add the favorites
    KConfig config("kickoffrc");
    KConfigGroup favoritesGroup = config.group("Favorites");
    QList<QString> favoriteList = favoritesGroup.readEntry("FavoriteURLs", QList<QString>());
    addApp(m_menu, favoriteList[0]);
}

bool FavoritesLauncher::addApp(QMenu *menu, const QString &path)
{
    QFileInfo info(path);
    QString source = "kde4-" + info.fileName();
    Plasma::DataEngine::Data app = dataEngine("apps")->query(source);

    QString name = app.value("name").toString();

    app = dataEngine("apps")->query(source);

    KIcon icon("konsole.png");

    QAction *action = menu->addAction(icon, "Konsole");
    action->setData("kde4-konsole.desktop");
    return true;
}

void FavoritesLauncher::switchTo(QAction *action)
{
    QString source = action->data().toString();
    kDebug() << source;
    Plasma::Service *service = dataEngine("apps")->serviceForSource(source);
    if (service) {
        service->startOperationCall(service->operationDescription("launch"));
    }
}

#include "launch.moc"
