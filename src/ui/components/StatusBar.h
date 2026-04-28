// src/ui/components/StatusBar.h
#pragma once

#include "ui/UIComponent.h"

#include <QLabel>
#include <QPointer>
#include <QStatusBar>

namespace dentry::ui {

class StatusBar : public UIComponent<QStatusBar, void> {
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() override = default;

    StatusBar(const StatusBar &)            = delete;
    StatusBar &operator=(const StatusBar &) = delete;
    StatusBar(StatusBar &&)                 = delete;
    StatusBar &operator=(StatusBar &&)      = delete;

public slots:
    void setDirectoryStats(int folderCount, int fileCount);
    void setSelectionCount(int count);
    void clear();

private:
    void setupWidgets();
    void updateDisplay();

    QPointer<QLabel> m_statsLabel;
    QPointer<QLabel> m_selectionLabel;

    int m_folderCount    = 0;
    int m_fileCount      = 0;
    int m_selectionCount = 0;
};

} // namespace dentry::ui
