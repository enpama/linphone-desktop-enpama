/*
 * App.hpp
 * Copyright (C) 2017  Belledonne Communications, Grenoble, France
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Created on: February 2, 2017
 *      Author: Ronan Abhamon
 */

#ifndef APP_H_
#define APP_H_

#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include "../components/notifier/Notifier.hpp"
#include "../externals/single-application/SingleApplication.hpp"

// =============================================================================

class DefaultTranslator;

class App : public SingleApplication {
  Q_OBJECT;

  Q_PROPERTY(QString configLocale READ getConfigLocale WRITE setConfigLocale NOTIFY configLocaleChanged);
  Q_PROPERTY(QString locale READ getLocale CONSTANT);
  Q_PROPERTY(QVariantList availableLocales READ getAvailableLocales CONSTANT);
  Q_PROPERTY(QString qtVersion READ getQtVersion CONSTANT);

public:
  App (int &argc, char *argv[]);
  ~App ();

  void initContentApp ();
  void parseArgs ();

  void tryToUsePreferredLocale ();

  QQmlEngine *getEngine () {
    return &mEngine;
  }

  Notifier *getNotifier () const {
    return mNotifier;
  }

  QQuickWindow *getCallsWindow ();
  QQuickWindow *getMainWindow () const;

  bool hasFocus () const;

  Q_INVOKABLE QQuickWindow *getSettingsWindow ();

  static App *getInstance () {
    return static_cast<App *>(QApplication::instance());
  }

  Q_INVOKABLE static void smartShowWindow (QQuickWindow *window);
  Q_INVOKABLE static QString convertUrlToLocalPath (const QUrl &url);

public slots:
  void quit ();

signals:
  void configLocaleChanged (const QString &locale);

private:
  void registerTypes ();
  void setTrayIcon ();

  QString getConfigLocale () const;
  void setConfigLocale (const QString &locale);

  QString getLocale () const;

  QVariantList getAvailableLocales () const {
    return mAvailableLocales;
  }

  void openAppAfterInit ();

  static QString getQtVersion () {
    return qVersion();
  }

  QCommandLineParser mParser;

  QVariantList mAvailableLocales;
  QString mLocale;

  QQmlApplicationEngine mEngine;

  DefaultTranslator *mTranslator = nullptr;
  Notifier *mNotifier = nullptr;

  QQuickWindow *mCallsWindow = nullptr;
  QQuickWindow *mSettingsWindow = nullptr;
};

#endif // APP_H_
