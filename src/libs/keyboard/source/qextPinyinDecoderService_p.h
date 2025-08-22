/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef _QEXTPINYINDECODERSERVICE_P_H
#define _QEXTPINYINDECODERSERVICE_P_H

#include <qextKeyboardGlobal.h>

#include <QObject>

class QExtPinyinDecoderServicePrivate;
class QEXT_KEYBOARD_API QExtPinyinDecoderService : public QObject
{
    Q_OBJECT
public:
    static QExtPinyinDecoderService *instance();
    ~QExtPinyinDecoderService() QEXT_OVERRIDE;

    bool init();
    void flushCache();
    void setLimits(int maxSpelling, int maxHzsLen);

    void resetSearch();
    int search(const QString &spelling);
    int deleteSearch(int pos, bool isPosInSpellingId, bool clearFixedInThisStep);

    void setUserDictionary(bool enabled);
    bool isUserDictionaryEnabled() const;

    QString pinyinString(bool decoded);
    int pinyinStringLength(bool decoded);

    QString candidateAt(int index);
    QList<QString> fetchCandidates(int index, int count, int sentFixedLen);

    int chooceCandidate(int index);
    int cancelLastChoice();

    int fixedLength();
    QVector<int> spellingStartPositions();
    QList<QString> predictionList(const QString &history);

private:
    explicit QExtPinyinDecoderService(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtPinyinDecoderServicePrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPinyinDecoderService)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPinyinDecoderService)
};

#endif // _QEXTPINYINDECODERSERVICE_P_H
