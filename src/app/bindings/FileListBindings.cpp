/**
 * @file FileListBindings.cpp
 * @brief Implementation of FileListView keyboard bindings.
 *
 * @author Hugo Fabresse
 */

#include "FileListBindings.h"
#include "app/events/EventBus.h"
#include "app/input/InputMap.h"
#include "model/filesystem/FileSystemModel.h"

namespace dentry::app::bindings {

    WidgetBindings fileList(ui::FileListView* view, ui::ToolBar *toolbar, app::FileOperationController *fileOps) {
        return WidgetBindings{
            view,
            [view, toolbar, fileOps](InputMap* map) {
                map->bind(Qt::Key_J, [view] {
                    auto *sm = view->selectionModel();
                    auto next = view->model()->index(sm->currentIndex().row() + 1, 0);
                    if (next.isValid())
                        sm->setCurrentIndex(next, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                });

                map->bind(Qt::Key_K, [view] {
                    auto *sm = view->selectionModel();
                    auto prev = view->model()->index(sm->currentIndex().row() - 1, 0);
                    if (prev.isValid())
                        sm->setCurrentIndex(prev, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                });

                map->bind({Qt::Key_G, Qt::Key_G}, [view] {
                    auto first = view->model()->index(0, 0);
                    if (first.isValid())
                        view->selectionModel()->setCurrentIndex(first, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                });

                map->bind(Qt::Key_G, [view] {
                    auto last = view->model()->index(view->model()->rowCount() - 1, 0);
                    if (last.isValid())
                        view->selectionModel()->setCurrentIndex(last, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                }, Qt::ShiftModifier);

                map->bind(Qt::Key_L, [view] {
                    auto cur = view->currentIndex();
                    if (cur.isValid()) emit view->activated(cur);
                });
                map->bind(Qt::Key_Return, [view] {
                    auto cur = view->currentIndex();
                    if (cur.isValid()) emit view->activated(cur);
                });

                map->bind(Qt::Key_H, [view] { emit view->activated({}); });
                map->bind(Qt::Key_Backspace, [view] { emit view->activated({}); });

                map->bind(Qt::Key_Tab, [] {
                    emit events::EventBus::instance()->focusWidget("SideBar");
                });

                map->bind(Qt::Key_AsciiTilde, [toolbar] {
                    if (toolbar)
                        toolbar->triggerHome();
                });

                map->bind(Qt::Key_Period, [toolbar] {
                    if (toolbar)
                        toolbar->toggleHidden();
                });

                map->bind(Qt::Key_Less, [toolbar] {
                    if (toolbar)
                        toolbar->backRequested();
                });

                map->bind(Qt::Key_F, [toolbar] {
                    if (toolbar)
                        toolbar->focusSearch();
                });

                map->bind(Qt::Key_Y, [view, fileOps] {
                    if (fileOps && !view->selectedPaths().isEmpty())
                        fileOps->onCopyRequested(view->selectedPaths());
                });

                map->bind(Qt::Key_D, [view, fileOps] {
                    if (fileOps && !view->selectedPaths().isEmpty())
                        fileOps->onCutRequested(view->selectedPaths());
                });

                map->bind(Qt::Key_P, [view, fileOps] {
                    if (!fileOps) return;
                    auto *m = qobject_cast<model::FileSystemModel *>(view->model());
                    if (m && !fileOps->clipboard()->isEmpty())
                        fileOps->onPasteRequested(m->currentPath());
                });

                map->bind(Qt::Key_D, [view, fileOps] {
                    if (fileOps && !view->selectedPaths().isEmpty())
                        fileOps->onDeleteRequested(view->selectedPaths());
                }, Qt::ShiftModifier);

                map->bind(Qt::Key_R, [view, fileOps] {
                    if (fileOps && view->selectedPaths().size() == 1)
                        fileOps->onRenameRequested(view->selectedPaths().first());
                });

                map->bind(Qt::Key_A, [view, fileOps] {
                    if (!fileOps) return;
                    auto *m = qobject_cast<model::FileSystemModel *>(view->model());
                    if (m) fileOps->onCreateFileRequested(m->currentPath());
                });

                map->bind(Qt::Key_A, [view, fileOps] {
                    if (!fileOps) return;
                    auto *m = qobject_cast<model::FileSystemModel *>(view->model());
                    if (m) fileOps->onCreateFolderRequested(m->currentPath());
                }, Qt::ShiftModifier);

                map->bind(Qt::Key_M, [view] {
                    emit view->contextMenuKeyPressed();
                });
            }
        };
    }

} // namespace dentry::app::bindings
