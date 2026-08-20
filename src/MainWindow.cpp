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

#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFont>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_chapterTree(nullptr)
    , m_contentStack(nullptr)
    , m_backButton(nullptr)
{
    setupUi();
    setupMenuBar();
    loadUnitList();
    connectSignals();

    setWindowTitle("91学习 0.2.1");
    resize(1000, 700);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi()
{
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    QWidget *leftPanel = new QWidget(splitter);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(4, 4, 4, 4);

    m_backButton = new QPushButton("返回单元选择", leftPanel);
    m_backButton->setVisible(false);
    leftLayout->addWidget(m_backButton);

    m_chapterTree = new QTreeWidget(leftPanel);
    m_chapterTree->setHeaderHidden(true);
    QFont font = m_chapterTree->font();
    font.setPointSize(12);
    m_chapterTree->setFont(font);
    leftLayout->addWidget(m_chapterTree);

    m_contentStack = new QStackedWidget(splitter);

    splitter->addWidget(leftPanel);
    splitter->addWidget(m_contentStack);
    splitter->setSizes(QList<int>() << 250 << 750);

    setCentralWidget(splitter);
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("文件");
    QAction *exitAction = new QAction("退出", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    fileMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu("帮助");
    QAction *aboutAction = new QAction("关于", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::loadUnitList()
{
    m_backButton->setVisible(false);
    m_chapterTree->clear();
    setWindowTitle("91学习 0.2.1 - 选择单元");

    QTreeWidgetItem *unit = new QTreeWidgetItem(m_chapterTree);
    unit->setText(0, "硬件");
    unit->setData(0, Qt::UserRole, "unit");
    unit->setData(0, Qt::UserRole + 1, "hardware");
    m_chapterTree->setCurrentItem(unit);

    clearContent();
    showHint("你需要选择一个单元来学习！", "点击左侧栏中你想要学习的单元以开始。");
}

void MainWindow::loadChapterList(const QString &unitId)
{
    m_backButton->setVisible(true);
    m_chapterTree->clear();
    setWindowTitle("91学习 0.2.1 - 硬件");

    QTreeWidgetItem *root = new QTreeWidgetItem(m_chapterTree);
    root->setText(0, "硬件");
    root->setFlags(root->flags() & ~Qt::ItemIsSelectable);

    struct Chapter { QString title; QString file; };
    QList<Chapter> chapters = {
        {"内存和储存", "memory.md"},
        {"CPU和GPU", "cpu-and-gpu.md"},
        {"主板", "motherboard.md"},
        {"电源", "power-supply.md"},
        {"显卡", "graphics-card.md"},
        {"散热系统", "cooling-system.md"},
        {"硬盘与固态硬盘", "storage-hdd-ssd.md"},
        {"USB 接口", "usb.md"},
        {"光驱", "optical-drive.md"}
    };

    for (const auto &ch : chapters) {
        QTreeWidgetItem *item = new QTreeWidgetItem(root);
        item->setText(0, ch.title);
        item->setData(0, Qt::UserRole, "chapter");
        item->setData(0, Qt::UserRole + 1, "doc/Hardware/" + ch.file);
    }

    root->setExpanded(true);
    m_chapterTree->setCurrentItem(root->child(0));
    loadContent("doc/Hardware/memory.md");
}

void MainWindow::loadContent(const QString &filePath)
{
    QString fullPath = QDir::currentPath() + "/../" + filePath;
    QString content = readMarkdownFile(fullPath);

    QTextBrowser *browser = new QTextBrowser(m_contentStack);
    browser->setOpenExternalLinks(false);
    browser->setHtml(content);
    m_contentStack->addWidget(browser);
    m_contentStack->setCurrentWidget(browser);
}

QString MainWindow::readMarkdownFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return QString("<p style='color:red;'>无法读取: %1</p>").arg(path);
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return markdownToHtml(content);
}

QString MainWindow::markdownToHtml(const QString &md)
{
    QString html = "<html><head><style>"
                   "body { font-size: 12pt; font-family: sans-serif; line-height: 1.6; }"
                   "h1 { font-size: 22pt; }"
                   "h2 { font-size: 18pt; }"
                   "h3 { font-size: 14pt; }"
                   "ul { padding-left: 20px; }"
                   "li { margin: 4px 0; }"
                   "</style></head><body>\n";

    QStringList lines = md.split('\n');
    bool inList = false;

    for (const QString &line : lines) {
        QString trimmed = line.trimmed();

        if (trimmed.isEmpty()) {
            if (inList) {
                html += "</ul>\n";
                inList = false;
            }
            continue;
        }

        if (trimmed.startsWith("# ")) {
            if (inList) { html += "</ul>\n"; inList = false; }
            html += "<h1>" + trimmed.mid(2) + "</h1>\n";
        }
        else if (trimmed.startsWith("## ")) {
            if (inList) { html += "</ul>\n"; inList = false; }
            html += "<h2>" + trimmed.mid(3) + "</h2>\n";
        }
        else if (trimmed.startsWith("### ")) {
            if (inList) { html += "</ul>\n"; inList = false; }
            html += "<h3>" + trimmed.mid(4) + "</h3>\n";
        }
        else if (trimmed.startsWith("- ")) {
            if (!inList) {
                html += "<ul>\n";
                inList = true;
            }
            QString item = trimmed.mid(2);
            // 处理加粗 **text**
            int pos = 0;
            bool bold = false;
            QString result;
            while (pos < item.length()) {
                int idx = item.indexOf("**", pos);
                if (idx == -1) {
                    result += item.mid(pos);
                    break;
                }
                result += item.mid(pos, idx - pos);
                if (!bold) {
                    result += "<b>";
                } else {
                    result += "</b>";
                }
                bold = !bold;
                pos = idx + 2;
            }
            if (bold) {
                result += "</b>";
            }
            html += "<li>" + result + "</li>\n";
        }
        else {
            if (inList) { html += "</ul>\n"; inList = false; }
            QString para = trimmed;
            // 处理加粗 **text**
            int pos = 0;
            bool bold = false;
            QString result;
            while (pos < para.length()) {
                int idx = para.indexOf("**", pos);
                if (idx == -1) {
                    result += para.mid(pos);
                    break;
                }
                result += para.mid(pos, idx - pos);
                if (!bold) {
                    result += "<b>";
                } else {
                    result += "</b>";
                }
                bold = !bold;
                pos = idx + 2;
            }
            if (bold) {
                result += "</b>";
            }
            html += "<p>" + result + "</p>\n";
        }
    }

    if (inList) {
        html += "</ul>\n";
    }

    html += "</body></html>";
    return html;
}

void MainWindow::clearContent()
{
    while (m_contentStack->count() > 0) {
        delete m_contentStack->widget(0);
    }
}

void MainWindow::showHint(const QString &title, const QString &desc)
{
    QTextBrowser *hint = new QTextBrowser(m_contentStack);
    hint->setHtml(QString(
                      "<html><head><style>"
                      "body { font-size: 14pt; font-family: sans-serif; color: #888888; text-align: center; padding-top: 100px; }"
                      "</style></head>"
                      "<body>"
                      "<h2 style='color: #666666;'>%1</h2>"
                      "<p>%2</p>"
                      "</body></html>"
                      ).arg(title, desc));
    m_contentStack->addWidget(hint);
    m_contentStack->setCurrentWidget(hint);
}

void MainWindow::connectSignals()
{
    connect(m_chapterTree, &QTreeWidget::clicked, this, &MainWindow::onChapterSelected);
    connect(m_backButton, &QPushButton::clicked, this, &MainWindow::onBackToUnits);
}

void MainWindow::onChapterSelected(const QModelIndex &)
{
    QTreeWidgetItem *item = m_chapterTree->currentItem();
    if (!item) return;

    QString type = item->data(0, Qt::UserRole).toString();

    if (type == "unit") {
        loadChapterList(item->data(0, Qt::UserRole + 1).toString());
    }
    else if (type == "chapter") {
        loadContent(item->data(0, Qt::UserRole + 1).toString());
    }
}

void MainWindow::onBackToUnits()
{
    loadUnitList();
}

void MainWindow::onExit()
{
    QApplication::quit();
}

void MainWindow::onAbout()
{
    QString msg = "<h1 style='text-align: center;'>91学习</h1>"
                  "<p style='text-align: center;'><b>程序版本：</b>0.2.1</p>"
                  "<p style='text-align: center;'><b>Qt 版本：</b>6.11.1</p>"
                  "<p style='text-align: center;'><b>GitHub 开源项目地址：</b><br>"
                  "<a href=\"https://github.com/ChysnTech/91study-dev\">"
                  "https://github.com/ChysnTech/91study-dev</a></p>"
                  "<p style='text-align: center;'>本程序在 <a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">"
                  "GPL v3 许可证</a> 的条款下进行分发。</p>";

    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("关于 91学习");
    msgBox->setTextFormat(Qt::RichText);
    msgBox->setText(msg);
    msgBox->setMinimumSize(500, 300);
    msgBox->exec();
    delete msgBox;
}