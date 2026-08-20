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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QTextBrowser>
#include <QStackedWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void setupMenuBar();
    void loadUnitList();
    void loadChapterList(const QString &unitId);
    void loadContent(const QString &filePath);
    void clearContent();
    void showHint(const QString &title, const QString &desc);
    QString readMarkdownFile(const QString &filePath);
    QString markdownToHtml(const QString &md);
    void connectSignals();

    QTreeWidget *m_chapterTree;
    QStackedWidget *m_contentStack;
    QPushButton *m_backButton;

private slots:
    void onChapterSelected(const QModelIndex &index);
    void onBackToUnits();
    void onExit();
    void onAbout();
};

#endif
