// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: MIT

#include "window.hpp"
#include "mainwindow.hpp"

#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QVBoxLayout>

Window::Window(MainWindow *mainWindow)
    : QWidget(mainWindow),
      m_mainWindowRef(mainWindow) {
    QExtMapLibre::Styles styles;
    // styles.emplace_back("https://demotiles.maplibre.org/style.json", "Demo Tiles");
    // styles.emplace_back("https://tiles.openfreemap.org/styles/liberty", "Demo Tiles");
    // styles.emplace_back("https://tiles.openfreemap.org/styles/bright");
    styles.emplace_back("https://demotiles.maplibre.org/styles/osm-bright-gl-style/style.json");
    // styles.emplace_back("http://192.168.100.47:9999/styles/osm-bright-gl-style/style.json");
    // styles.emplace_back("https://demotiles.maplibre.org/debug-tiles/style.json");
// styles.emplace_back("http://192.168.100.47:9999/#12.33/47.32277/11.44801/0/52");


    // QExtMapLibre::Style style{"https://demotiles.maplibre.org/debug-tiles/style.json"};
    // style.type = QExtMapLibre::Style::TerrainMap;
    // styles.emplace_back(style);
    // QExtMapLibre::Style style1{"https://a.tile.openstreetmap.org/{z}/{x}/{y}.png"};
    // style1.type = QExtMapLibre::Style::StreetMap;
    // styles.emplace_back(style1);

    QExtMapLibre::Settings settings;
    settings.setStyles(styles);
    settings.setDefaultZoom(17);
    // settings.setViewportMode(QExtMapLibre::Settings::FlippedYViewport);
    // settings.setDefaultCoordinate(std::make_pair(-74.0066, 40.7135));
    // settings.setConstrainMode(QExtMapLibre::Settings::ConstrainWidthAndHeight);
    settings.setDefaultCoordinate(QExtMapLibre::Coordinate(47.202496, 11.417355));

    m_glWidget = std::make_unique<QExtMapLibre::GLWidget>(settings);
    // m_glWidget->map()->setBearing(-17);

    m_layout = std::make_unique<QVBoxLayout>(this);
    m_layout->addWidget(m_glWidget.get());
    m_buttonDock = std::make_unique<QPushButton>(tr("Undock"), this);
    connect(m_buttonDock.get(), &QPushButton::clicked, this, &Window::dockUndock);
    m_layout->addWidget(m_buttonDock.get());

    setLayout(m_layout.get());

    setWindowTitle(tr("Hello QExtMapLibre"));
}

void Window::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    } else {
        QWidget::keyPressEvent(e);
    }
}

void Window::dockUndock() {
    if (parent() != nullptr) {
        setParent(nullptr);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QGuiApplication::primaryScreen()->size().width() / 2 - width() / 2,
             QGuiApplication::primaryScreen()->size().height() / 2 - height() / 2);
        m_buttonDock->setText(tr("Dock"));
        show();
    } else {
        if (m_mainWindowRef->centralWidget() == nullptr) {
            if (m_mainWindowRef->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                m_buttonDock->setText(tr("Undock"));
                m_mainWindowRef->setCentralWidget(this);
            } else {
                QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
    m_glWidget->map()->setPitch(85);
    m_glWidget->map()->setBearing(71);
}
