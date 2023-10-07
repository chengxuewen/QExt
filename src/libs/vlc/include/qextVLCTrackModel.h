/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
*
* License: MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*************************************************************************************/

#ifndef _QEXTVLCTRACKMODEL_H
#define _QEXTVLCTRACKMODEL_H

#include <qextVLCGlobal.h>

#include <QAbstractListModel>

/*!
    \class QEXTVLCTrackModel qextVLCTrackModel.h
    \ingroup QEXTVLC
    \brief Track model

    A model for displaying audio, video and other tracks

    \since QExt 0.11.1
*/
class QEXT_VLC_API QEXTVLCTrackModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /*!
        \enum Roles
        \brief Model data roles
    */
    enum Roles
    {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    /*!
        \brief QEXTVLCTrackModel constructor.
        \param parent parent object
    */
    explicit QEXTVLCTrackModel(QObject *parent = 0);

    /*!
        \brief QEXTVLCTrackModel constructor.
        \param tracks tracks map
        \param parent parent object
    */
    explicit QEXTVLCTrackModel(const QMap<int, QString> &tracks, QObject *parent = 0);

    /*!
        \brief QEXTVLCTrackModel constructor.
        \param other another QEXTVLCTrackModel instance
    */
    explicit QEXTVLCTrackModel(const QEXTVLCTrackModel &other);

    /*!
        \brief Get row count
        \param parent parent model index
        \return count
    */
    int rowCount(const QModelIndex &parent) const;

    /*!
        \brief Model role names
        \return role names hash
    */
    QHash<int, QByteArray> roleNames() const;

    /*!
        \brief Read data from model
        \param index model index
        \param role required role
    */
    QVariant data(const QModelIndex &index, int role) const;

    /*!
        \brief Read data from model
        \param row model row
        \param role required role
    */
    QVariant data(const int row, int role) const;

    /*!
        \brief Clear the model
    */
    void clear();

    /*!
        \brief Load tracks into model
        \param data tracks map id-title
    */
    void load(const QMap<int, QString> &data);

    /*!
        \brief Insert track into model
        \param id track id
        \param title track title
    */
    void insert(const int id, const QString &title);

    /*!
        \brief Get tracks count
        \return count
    */
    int count() const;

signals:
    /*!
        \brief Count changed signal
    */
    void countChanged();

private:
    QMap<int, QString> m_tracksMap;
};

Q_DECLARE_METATYPE(QEXTVLCTrackModel)

#endif // _QEXTVLCTRACKMODEL_H
