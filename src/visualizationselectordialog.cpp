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

#include <QDialog>
#include <QShowEvent>

#include "visualizationselectordialog.h"
#include "projectmpresetmodel.h"
#include "projectmvisualization.h"
#include "ui_visualizationselectordialog.h"

VisualizationSelectorDialog::VisualizationSelectorDialog(ProjectMVisualization *projectm_visualization, QWidget *parent)
    : QDialog(parent),
      ui_(new Ui_VisualizationSelectorDialog),
      projectm_visualization_(projectm_visualization) {

  ui_->setupUi(this);

}

VisualizationSelectorDialog::~VisualizationSelectorDialog() { delete ui_; }

void VisualizationSelectorDialog::showEvent(QShowEvent *e) {

  if (!ui_->list->model()) {
    ui_->list->setModel(projectm_visualization_->preset_model());
    QObject::connect(ui_->list->selectionModel(), &QItemSelectionModel::currentChanged, projectm_visualization_->preset_model(), &ProjectMPresetModel::SetPreset);
  }

  QDialog::showEvent(e);

}
