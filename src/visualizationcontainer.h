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

#ifndef VISUALIZATIONCONTAINER_H
#define VISUALIZATIONCONTAINER_H

#include "config.h"

#include <QMainWindow>

class ProjectMVisualization;
class VisualizationSelectorDialog;

class QMenu;
class QMouseEvent;
class QContextMenuEvent;
class QKeyEvent;

class VisualizationContainer : public QMainWindow {
  Q_OBJECT

 public:
  explicit VisualizationContainer(QWidget *parent = nullptr);

 protected:
  void mouseDoubleClickEvent(QMouseEvent *e) override;
  void contextMenuEvent(QContextMenuEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private slots:
  void ShowPopupMenu(const QPoint &pos);
  void ToggleFullscreen();

 private:
  ProjectMVisualization *projectm_visualization_;
  VisualizationSelectorDialog *selector_dialog_;
  QMenu *menu_;
};

#endif  // VISUALIZATIONCONTAINER_H
