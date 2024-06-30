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

#ifndef VISUALIZATIONSELECTORDIALOG_H
#define VISUALIZATIONSELECTORDIALOG_H

#include "config.h"

#include <QDialog>

class QShowEvent;

class ProjectMVisualization;
class Ui_VisualizationSelectorDialog;

class VisualizationSelectorDialog : public QDialog {
  Q_OBJECT

 public:
  explicit VisualizationSelectorDialog(ProjectMVisualization *projectm_visualization, QWidget *parent = nullptr);
  ~VisualizationSelectorDialog();

  void SetVisualization(ProjectMVisualization *projectm_visualization) { projectm_visualization_ = projectm_visualization; }

 protected:
  void showEvent(QShowEvent *e) override;

 private:
  Ui_VisualizationSelectorDialog *ui_;
  ProjectMVisualization *projectm_visualization_;
};

#endif  // VISUALIZATIONSELECTORDIALOG_H
