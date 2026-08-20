/*
 * Copyright (C) 2026 DebArch91工作室
 *
 * This file is part of 91study.
 *
 * 91study is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 91study is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QFont>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("91学习");
    app.setOrganizationName("DebArch91工作室");
    app.setApplicationVersion("0.2.1");

    QFont defaultFont = app.font();
    defaultFont.setPointSize(12);
    app.setFont(defaultFont);

    MainWindow window;
    window.show();

    return app.exec();
}