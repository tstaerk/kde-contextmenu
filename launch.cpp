/*
 *   Copyright 2009 by Chani Armitage <chani@kde.org>
 *   Copyright 2013 by Thorsten Staerk <kde@staerk.de>
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

ConTextMenu::ConTextMenu(QObject *parent, const QVariantList &args)
    : Plasma::ContainmentActions(parent, args)
    , m_action(new QAction(this))
{
    m_menu = new KMenu();
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(switchTo(QAction*)));
    m_action->setMenu(m_menu);
}

ConTextMenu::~ConTextMenu()
{
    delete m_menu;
}

void ConTextMenu::init(const KConfigGroup &)
{
}

void ConTextMenu::contextEvent(QEvent *event)
{
    makeMenu();
    m_menu->adjustSize();
    m_menu->exec(popupPosition(m_menu->size(), event));
}

void ConTextMenu::makeMenu()
{
    addApps(m_menu);
}

QList<QAction *> ConTextMenu::contextualActions()
{
    m_menu->clear(); // otherwise every time you build it it will duplicate its content
    makeMenu();
    QList<QAction *> list;
    list << m_action;
    return list;
}

bool ConTextMenu::addApps(QMenu *menu)
{
    QAction* action = menu->addAction(KIcon("system-run"), "Open a console");
    action->setData("kde4-konsole.desktop");

    action = menu->addAction(KIcon("firefox"), "Surf the web");
    action->setData("firefox.desktop");
    
    action = menu->addAction(KIcon("ksnapshot"), "Take a screenshot");
    action->setData("kde4-ksnapshot.desktop");

    Plasma::Containment *c = containment();
    Q_ASSERT(c);
    menu->addAction(c->action("configure"));   
    
    return true;
}

void ConTextMenu::switchTo(QAction *action)
{
    QString source = action->data().toString();
    kDebug() << source;
    Plasma::Service *service = dataEngine("apps")->serviceForSource(source);
    if (service) 
    {
        service->startOperationCall(service->operationDescription("launch"));
    }
}

#include "launch.moc"
