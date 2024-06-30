/*
 * ProjectM Test Project
 * Copyright 2024, Jonas Kvinge <jonas@jkvinge.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "config.h"

#include <QtGlobal>

#include <QMenu>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QDebug>

#include "visualizationcontainer.h"
#ifdef USE_QGLWIDGET
#  include "visualizationoglwidget.h"
#else
#  include "visualizationopenglwidget.h"
#endif
#include "visualizationselectordialog.h"
#include "projectmvisualization.h"

VisualizationContainer::VisualizationContainer(QWidget *parent)
    : QMainWindow(parent),
      projectm_visualization_(new ProjectMVisualization(this)),
      selector_dialog_(new VisualizationSelectorDialog(projectm_visualization_, this)),
      menu_(new QMenu(this)) {

  setWindowTitle(tr("Visualizations"));
  setMinimumSize(200, 200);

#ifdef USE_QGLWIDGET
  setCentralWidget(new VisualizationOGLWidget(projectm_visualization_));
#else
  setCentralWidget(new VisualizationOpenGLWidget(projectm_visualization_));
#endif

  QShortcut *close = new QShortcut(QKeySequence::Close, this);
  QObject::connect(close, &QShortcut::activated, this, &VisualizationContainer::close);

  selector_dialog_->SetVisualization(projectm_visualization_);

  menu_->addAction(QIcon(), tr("Toggle fullscreen"), this, &VisualizationContainer::ToggleFullscreen);
  menu_->addAction(tr("Select visualizations..."), selector_dialog_, &VisualizationContainer::show);
  menu_->addSeparator();
  menu_->addAction(QIcon(), tr("Close visualization"), this, &VisualizationContainer::hide);

}

void VisualizationContainer::mouseDoubleClickEvent(QMouseEvent *e) {
  QMainWindow::mouseDoubleClickEvent(e);
  ToggleFullscreen();
}

void VisualizationContainer::contextMenuEvent(QContextMenuEvent *event) {
  QMainWindow::contextMenuEvent(event);
  ShowPopupMenu(event->pos());
}

void VisualizationContainer::keyReleaseEvent(QKeyEvent *event) {

  if (event->matches(QKeySequence::Close) || event->key() == Qt::Key_Escape) {
    if (isFullScreen()) {
      ToggleFullscreen();
    }
    else {
      hide();
    }
    return;
  }

  QMainWindow::keyReleaseEvent(event);

}

void VisualizationContainer::ToggleFullscreen() {

  setWindowState(windowState() ^ Qt::WindowFullScreen);

}

void VisualizationContainer::ShowPopupMenu(const QPoint &pos) {
  menu_->popup(mapToGlobal(pos));
}
