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

#include <QPainter>
#include <QDebug>

#include "visualizationopenglwidget.h"
#include "projectmvisualization.h"

VisualizationOpenGLWidget::VisualizationOpenGLWidget(ProjectMVisualization *projectm_visualization, QWidget *parent, Qt::WindowFlags f)
  : QOpenGLWidget(parent, f),
    projectm_visualization_(projectm_visualization) {}

void VisualizationOpenGLWidget::initializeGL() {

  projectm_visualization_->Init();

  QOpenGLFunctions::initializeOpenGLFunctions();
  QOpenGLWidget::initializeGL();

}

void VisualizationOpenGLWidget::paintGL() {

  QPainter p(this);
  p.beginNativePainting();
  projectm_visualization_->RenderFrame();
  p.endNativePainting();
  update();

  //qDebug() << __PRETTY_FUNCTION__ << glGetError();

}

void VisualizationOpenGLWidget::resizeGL(const int width, const int height) {

  projectm_visualization_->Resize(width, height);

}
