/*
 * Qt ProjectM Test Project
 * Copyright 2024, Jonas Kvinge <jonas@jkvinge.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PROJECTMVISUALIZATION_H
#define PROJECTMVISUALIZATION_H

#include "config.h"

#include <memory>
#include <vector>

#ifdef HAVE_PROJECTM4
#  include <projectM-4/types.h>
#  include <projectM-4/playlist_types.h>
#else
#  include <libprojectM/projectM.hpp>
#endif

#include <QObject>
#include <QString>
#include <QRectF>

class QPainter;
class VisualizationContainer;
class ProjectMPresetModel;

class ProjectMVisualization : public QObject {
  Q_OBJECT

 public:
  explicit ProjectMVisualization(VisualizationContainer *container);
  ~ProjectMVisualization();

  ProjectMPresetModel *preset_model() const { return preset_model_; }

  void Init();
  void RenderFrame();
  void Resize(const int width, const int height);

  uint PresetCount() const;
  QString PresetPath(const int index) const;
  QString PresetName(const int index) const;

 public slots:
  void SetPreset(const int index);

 private:
  VisualizationContainer *container_;
#ifdef HAVE_PROJECTM4
  projectm_handle projectm_instance_;
  projectm_playlist_handle projectm_playlist_instance_;
#else
  std::unique_ptr<projectM> projectm_;
#endif
  ProjectMPresetModel *preset_model_;
};

#endif  // PROJECTMVISUALIZATION_H
