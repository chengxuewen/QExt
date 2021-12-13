/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCEQUALIZER_H
#define _QEXTVLCEQUALIZER_H

#include <qextVLCGlobal.h>

#include <QtCore/QObject>

class QEXTVLCMediaPlayer;

struct libvlc_equalizer_t;

/*!
    \class QEXTVLCEqualizer qextVLCEqualizer.h
    \ingroup QEXTVLC
    \brief Audio equalizer

    \since libVLC 2.2
*/
class QEXT_VLC_API QEXTVLCEqualizer : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCEqualizer constructor
    */
    explicit QEXTVLCEqualizer(QEXTVLCMediaPlayer *vlcMediaPlayer);

    /*!
        \brief QEXTVLCEqualizer destructor
    */
    ~QEXTVLCEqualizer();

    /*!
        \brief Get the amplification value for a particular equalizer frequency band.
        \param bandIndex index, counting from zero, of the frequency band to get
        \return amplification value (Hz); -1.0 if there is no such frequency band
     */
    float amplificationForBandAt(uint bandIndex) const;

    /*!
        \brief Get the number of distinct frequency bands for an equalizer.
        \return number of frequency bands
     */
    uint bandCount() const;

    /*!
        \brief Get a particular equalizer band frequency.

        This value can be used, for example, to create a label for an equalizer band control in a user interface.

        \param bandIndex index of the band, counting from zero
        \return equalizer band frequency (Hz), or -1 if there is no such band
     */
    float bandFrequency(uint bandIndex) const;

    /*!
        \brief Get the current pre-amplification value from an equalizer.
        \return preamp value (Hz)
     */
    float preamplification() const;

    /*!
        \brief Get the number of equalizer presets.
        \return number of presets
     */
    uint presetCount() const;

    /*!
        \brief Get the name of a particular equalizer preset.

        This name can be used, for example, to prepare a preset label or menu in a user interface.

        \param index index of the preset, counting from zero
        \return preset name, or an empty string if there is no such preset
     */
    QString presetNameAt(uint index) const;

public slots:
    /*!
        \brief Load from preset
        \param index index of the preset, counting from zero
     */
    void loadFromPreset(uint index);

    /*!
        \brief Set a new amplification value for a particular equalizer frequency band.

        The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
        The supplied amplification value will be clamped to the -20.0 to +20.0 range.

        \param amp amplification value (-20.0 to 20.0 Hz)
        \param bandIndex counting from zero, of the frequency band to set
     */
    void setAmplificationForBandAt(float amp, uint bandIndex);

    /*!
        \brief Enable or disable equalizer
        \param enabled toggle flag
     */
    void setEnabled(bool enabled);

    /*!
        \brief Set a new pre-amplification value for an equalizer.

        The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
        The supplied amplification value will be clamped to the -20.0 to +20.0 range.

        \param value preamp value in (-20.0 to 20.0 Hz)
     */
    void setPreamplification(float value);

signals:
    /*!
        \brief Emitted when preset is loaded
     */
    void presetLoaded();

private:
    QEXTVLCMediaPlayer *m_vlcMediaPlayer;
    libvlc_equalizer_t *m_vlcEqualizer;
};

#endif // _QEXTVLCEQUALIZER_H
