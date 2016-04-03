/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <memory>
#include <QDialog>

class QxtLoggerEngine;
namespace Ui { class LogView; }

namespace elapse {

/*!
 * \brief Logging utilities.
 * \ingroup logging
 */

namespace log {

class TableModelLoggerEngine;
class LogFilterProxyModel;


/*!
 * \brief The LogView class provides a dialog for viewing log messages.
 * \ingroup widgets
 * \ingroup logging
 */

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = 0);
    ~LogView();

    QxtLoggerEngine *loggerEngine();

signals:
    void visibilityChanged(bool visible);

private slots:
    void setFilterLevel(int idx);

protected:
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    std::unique_ptr<Ui::LogView> ui;
    std::unique_ptr<TableModelLoggerEngine> engine;
    std::unique_ptr<LogFilterProxyModel> proxyModel;
};

}} // namespace elapse::log

#endif // LOGVIEW_H
