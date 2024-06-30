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

#include <string>
#include <memory>

#ifdef HAVE_PROJECTM4
#  include <projectM-4/types.h>
#  include <projectM-4/core.h>
#  include <projectM-4/parameters.h>
#  include <projectM-4/memory.h>
#  include <projectM-4/audio.h>
#  include <projectM-4/render_opengl.h>
#  include <projectM-4/playlist_types.h>
#  include <projectM-4/playlist_core.h>
#  include <projectM-4/playlist_memory.h>
#  include <projectM-4/playlist_items.h>
#  include <projectM-4/playlist_playback.h>
#else
#  include <libprojectM/projectM.hpp>
#endif  // HAVE_PROJECTM4

#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QScopeGuard>
#include <QRandomGenerator>
#include <QMessageBox>

#include "projectmvisualization.h"
#include "projectmpresetmodel.h"
#include "visualizationcontainer.h"

ProjectMVisualization::ProjectMVisualization(VisualizationContainer *container)
    : QObject(container),
      container_(container),
#ifdef HAVE_PROJECTM4
      projectm_instance_(nullptr),
      projectm_playlist_instance_(nullptr),
#endif
      preset_model_(nullptr) {}

ProjectMVisualization::~ProjectMVisualization() {

#ifdef HAVE_PROJECTM4
  if (projectm_playlist_instance_) {
    projectm_playlist_destroy(projectm_playlist_instance_);
  }
  if (projectm_instance_) {
    projectm_destroy(projectm_instance_);
  }
#endif  // HAVE_PROJECTM4

}

void ProjectMVisualization::Init() {

#ifdef HAVE_PROJECTM4
  if (projectm_instance_) {
    return;
  }
#else
  if (projectm_) {
    return;
  }
#endif  // HAVE_PROJECTM4

  // Find the projectM presets

  QStringList data_paths = QStringList() << QStringLiteral("/usr/share")
                                         << QStringLiteral("/usr/local/share");

  const QStringList xdg_data_dirs = QString::fromUtf8(qgetenv("XDG_DATA_DIRS")).split(QLatin1Char(':'));
  for (const QString &xdg_data_dir : xdg_data_dirs) {
    if (!data_paths.contains(xdg_data_dir)) {
      data_paths.append(xdg_data_dir);
    }
  }

#if defined(Q_OS_WIN32)
  data_paths.prepend(QCoreApplication::applicationDirPath());
#endif

  const QStringList projectm_paths = QStringList() << QStringLiteral("projectM/presets")
                                                   << QStringLiteral("projectm-presets");

  QStringList preset_paths;
  QString preset_path;
  for (const QString &data_path : std::as_const(data_paths)) {
    for (const QString &projectm_path : projectm_paths) {
      const QString path = data_path + QLatin1Char('/') + projectm_path;
      if (!QFileInfo::exists(path) || QDir(path).entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot).isEmpty()) {
        preset_paths << path;
        continue;
      }
      preset_path = path;
      break;
    }
  }

  // Create projectM settings
#ifdef HAVE_PROJECTM4
  Q_ASSERT(projectm_instance_ == nullptr);
  Q_ASSERT(projectm_playlist_instance_ == nullptr);
  projectm_instance_ = projectm_create();
  projectm_set_preset_duration(projectm_instance_, 15);
  projectm_set_mesh_size(projectm_instance_, 32, 24);
  projectm_set_fps(projectm_instance_, 35);
  //projectm_set_window_size(projectm_instance_, 512, 512);
  //const char *texture_search_paths[] = { "/usr/local/share/projectM/textures" };
  //projectm_set_texture_search_paths(projectm_instance_, texture_search_paths, 1);
  projectm_playlist_instance_ = projectm_playlist_create(projectm_instance_);
#else
  projectM::Settings s;
  s.presetURL = preset_path.toStdString();
  s.meshX = 32;
  s.meshY = 24;
  s.textureSize = 512;
  s.fps = 35;
  s.windowWidth = 512;
  s.windowHeight = 512;
  s.smoothPresetDuration = 5;
  s.presetDuration = 15;
  s.shuffleEnabled = true;
  s.softCutRatingsEnabled = false;
  s.easterEgg = 0;
  projectm_ = std::make_unique<projectM>(s);
#endif  // HAVE_PROJECTM4

  Q_ASSERT(preset_model_ == nullptr);
  preset_model_ = new ProjectMPresetModel(this, this);

#ifdef HAVE_PROJECTM4
  projectm_playlist_clear(projectm_playlist_instance_);
  const uint add_count = projectm_playlist_add_path(projectm_playlist_instance_, preset_path.toUtf8().constData(), true, false);
  projectm_playlist_sort(projectm_playlist_instance_, 0, add_count, SORT_PREDICATE_FULL_PATH, SORT_ORDER_ASCENDING);
#endif

  // Start at a random preset.
#ifdef HAVE_PROJECTM4
  const uint count = projectm_playlist_size(projectm_playlist_instance_);
  if (count > 0) {
    projectm_playlist_set_position(projectm_playlist_instance_, QRandomGenerator::global()->bounded(count), true);
  }
#else
  const uint count = projectm_->getPlaylistSize();
  if (count > 0) {
    projectm_->selectPreset(QRandomGenerator::global()->bounded(count), true);
  }
#endif  // HAVE_PROJECTM4

  if (count == 0) {
    qWarning("ProjectM presets could not be found, search path was:\n  %s", preset_paths.join(QLatin1String("\n  ")).toLocal8Bit().constData());
    QMessageBox::warning(nullptr, tr("Missing projectM presets"), tr("Could not load any projectM visualizations."));
  }

}

void ProjectMVisualization::RenderFrame() {

#ifdef HAVE_PROJECTM4
  if (!projectm_instance_) {
    Init();
  }
  Q_ASSERT(projectm_instance_);
#else
  if (!projectm_) {
    Init();
  }
  Q_ASSERT(projectm_);
#endif

#ifdef HAVE_PROJECTM4
  projectm_opengl_render_frame(projectm_instance_);
#else
  projectm_->renderFrame();
#endif

}

void ProjectMVisualization::Resize(const int width, const int height) {

#ifdef HAVE_PROJECTM4
  if (projectm_instance_) {
    projectm_set_window_size(projectm_instance_, static_cast<size_t>(width), static_cast<size_t>(height));
  }
#else
  if (projectm_) {
    projectm_->projectM_resetGL(static_cast<int>(width), static_cast<int>(height));
  }
#endif  // HAVE_PROJECTM4

}

uint ProjectMVisualization::PresetCount() const {

#ifdef HAVE_PROJECTM4
  return projectm_playlist_size(projectm_playlist_instance_);
#else
  return projectm_->getPlaylistSize();
#endif

}

QString ProjectMVisualization::PresetPath(const int &index) const {

#ifdef HAVE_PROJECTM4
  char *projectm_preset_path = projectm_playlist_item(projectm_playlist_instance_, index);
  if (projectm_preset_path) {
    const QScopeGuard projectm_preset_path_deleter = qScopeGuard([projectm_preset_path](){ projectm_playlist_free_string(projectm_preset_path); });
    return QLatin1String(projectm_preset_path);
  }
#else
  if (projectm_) {
    return QString::fromStdString(projectm_->getPresetURL(index));
  }
#endif  // HAVE_PROJECTM4

  return QString();

}

QString ProjectMVisualization::PresetName(const int &index) const {

  return QFileInfo(PresetPath(index)).baseName();

}

void ProjectMVisualization::SetPreset(const int index) {

#ifdef HAVE_PROJECTM4
  if (projectm_playlist_instance_) {
    projectm_playlist_set_position(projectm_playlist_instance_, index, true);
  }
#else
  if (projectm_) {
    projectm_->selectPreset(index, true);
  }
#endif  // HAVE_PROJECTM4

}
