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

#include <QAbstractItemModel>
#include <QString>
#include <QStringList>

#include "projectmpresetmodel.h"
#include "projectmvisualization.h"

ProjectMPresetModel::ProjectMPresetModel(ProjectMVisualization *projectm_visualization, QObject *parent)
    : QAbstractItemModel(parent),
      projectm_visualization_(projectm_visualization) {}

int ProjectMPresetModel::rowCount(const QModelIndex &idx) const {

  Q_UNUSED(idx);

  return static_cast<int>(projectm_visualization_->PresetCount());

}

int ProjectMPresetModel::columnCount(const QModelIndex &idx) const {

  Q_UNUSED(idx);

  return 1;

}

QModelIndex ProjectMPresetModel::index(const int row, const int column, const QModelIndex &idx) const {

  Q_UNUSED(idx);

  return createIndex(row, column);

}

QModelIndex ProjectMPresetModel::parent(const QModelIndex &child) const {

  Q_UNUSED(child);

  return QModelIndex();

}

QVariant ProjectMPresetModel::data(const QModelIndex &index, const int role) const {

  switch (role) {
    case Qt::DisplayRole:
      return projectm_visualization_->PresetName(index.row());
    case Role::Role_Path:
      return projectm_visualization_->PresetPath(index.row());
    default:
      return QVariant();
  }

}

Qt::ItemFlags ProjectMPresetModel::flags(const QModelIndex &idx) const {

  if (idx.isValid()) {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
  }

  return QAbstractItemModel::flags(idx);

}

void ProjectMPresetModel::SetPreset(const QModelIndex &idx) {
  projectm_visualization_->SetPreset(idx.row());
}
