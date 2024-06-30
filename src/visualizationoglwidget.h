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

#ifndef VISUALIZATIONOGLWIDGET_H
#define VISUALIZATIONOGLWIDGET_H

#include "config.h"

#include <QGLWidget>

class ProjectMVisualization;

class VisualizationOGLWidget : public QGLWidget {
  Q_OBJECT

 public:
  explicit VisualizationOGLWidget(ProjectMVisualization *projectm_visualization, QWidget *parent = nullptr);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(const int width, const int height) override;

 private:
  ProjectMVisualization *projectm_visualization_;
};

#endif  // VISUALIZATIONOGLWIDGET_H
