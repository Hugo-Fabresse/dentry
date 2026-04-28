// src/ui/components/StatusBar.cpp
#include "log/Logger.h"
#include "ui/components/StatusBar.h"

namespace dentry::ui {

    StatusBar::StatusBar(QWidget *parent)
        : UIComponent(parent) {
        setupWidgets();
        build();

        setObjectName("StatusBar");

        log::info("Ui") << "StatusBar built";
    }

    void StatusBar::setupWidgets() {
        m_statsLabel     = new QLabel(this);
        m_selectionLabel = new QLabel(this);

        addWidget(m_statsLabel);
        addPermanentWidget(m_selectionLabel);
    }

    void StatusBar::setDirectoryStats(int folderCount, int fileCount) {
        m_folderCount = folderCount;
        m_fileCount   = fileCount;
        updateDisplay();
    }

    void StatusBar::setSelectionCount(int count) {
        m_selectionCount = count;
        updateDisplay();
    }

    void StatusBar::clear() {
        m_folderCount    = 0;
        m_fileCount      = 0;
        m_selectionCount = 0;
        updateDisplay();
    }

    void StatusBar::updateDisplay() {
        m_statsLabel->setText(
            QString("%1 folder(s)  ·  %2 file(s)")
                .arg(m_folderCount)
                .arg(m_fileCount)
        );

        if (m_selectionCount > 0)
            m_selectionLabel->setText(QString("%1 selected").arg(m_selectionCount));
        else
            m_selectionLabel->clear();
    }

} // namespace dentry::ui
