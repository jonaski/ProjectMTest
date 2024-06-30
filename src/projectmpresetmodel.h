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

#ifndef PROJECTMPRESETMODEL_H
#define PROJECTMPRESETMODEL_H

#include "config.h"

#include <QString>
#include <QAbstractItemModel>

class ProjectMVisualization;

class ProjectMPresetModel : public QAbstractItemModel {
  Q_OBJECT

  friend class ProjectMVisualization;

 public:
  explicit ProjectMPresetModel(ProjectMVisualization *projectm_visualization, QObject *parent = nullptr);

  enum Role {
    Role_Path = Qt::UserRole,
  };

  // QAbstractItemModel
  QModelIndex index(const int row, const int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, const int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

 public slots:
  void SetPreset(const QModelIndex &index);

 private:
  ProjectMVisualization *projectm_visualization_;
};

#endif  // PROJECTMPRESETMODEL_H
