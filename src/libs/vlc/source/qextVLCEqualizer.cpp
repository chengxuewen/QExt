/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <cmath>
#include <qextVLCHeaders.h>

#include "qextVLCEqualizer.h"
#include "qextVLCError.h"
#include <qextVLCMediaPlayer.h>

QEXTVLCEqualizer::QEXTVLCEqualizer(QEXTVLCMediaPlayer *vlcMediaPlayer)
    : QObject(vlcMediaPlayer),
      m_vlcMediaPlayer(vlcMediaPlayer),
      m_vlcEqualizer(libvlc_audio_equalizer_new()) {}

QEXTVLCEqualizer::~QEXTVLCEqualizer()
{
    if (m_vlcEqualizer) {
        libvlc_audio_equalizer_release(m_vlcEqualizer);
    }
}

float QEXTVLCEqualizer::amplificationForBandAt(uint bandIndex) const
{
    if (m_vlcEqualizer) {
        float ret = libvlc_audio_equalizer_get_amp_at_index(m_vlcEqualizer, bandIndex);
        if (!std::isnan(ret)) {
            return ret;
        }
    }
    return -1.0;
}

uint QEXTVLCEqualizer::bandCount() const
{
    if (m_vlcEqualizer) {
        return libvlc_audio_equalizer_get_band_count();
    } else {
        return 0;
    }
}

float QEXTVLCEqualizer::bandFrequency(uint bandIndex) const
{
    if (m_vlcEqualizer) {
        return libvlc_audio_equalizer_get_band_frequency(bandIndex);
    } else {
        return -1.0;
    }
}

float QEXTVLCEqualizer::preamplification() const
{
    if (m_vlcEqualizer) {
        return libvlc_audio_equalizer_get_preamp(m_vlcEqualizer);
    } else {
        return 0.0;
    }
}

uint QEXTVLCEqualizer::presetCount() const
{
    return libvlc_audio_equalizer_get_preset_count();
}

QString QEXTVLCEqualizer::presetNameAt(uint index) const
{
    const char *name = libvlc_audio_equalizer_get_preset_name(index);
    if (name == NULL) {
        return QString();
    } else {
        return QString(name);
    }
}

void QEXTVLCEqualizer::loadFromPreset(uint index)
{
    if (m_vlcEqualizer) {
        libvlc_audio_equalizer_release(m_vlcEqualizer);
    }
    m_vlcEqualizer = libvlc_audio_equalizer_new_from_preset(index);
    QEXTVLCError::showErrMsg();
    if (m_vlcEqualizer) {
        emit presetLoaded();
    }
}

void QEXTVLCEqualizer::setAmplificationForBandAt(float amp, uint bandIndex)
{
    if (!m_vlcEqualizer) {
        return;
    }
    libvlc_audio_equalizer_set_amp_at_index(m_vlcEqualizer, amp, bandIndex);
    libvlc_media_player_set_equalizer(m_vlcMediaPlayer->core(), m_vlcEqualizer);
    QEXTVLCError::showErrMsg();
}

void QEXTVLCEqualizer::setEnabled(bool enabled)
{
    if (enabled && m_vlcEqualizer != NULL) {
        libvlc_media_player_set_equalizer(m_vlcMediaPlayer->core(), m_vlcEqualizer);
    } else {
        libvlc_media_player_set_equalizer(m_vlcMediaPlayer->core(), NULL);
    }
}

void QEXTVLCEqualizer::setPreamplification(float value)
{
    if (!m_vlcEqualizer) {
        return;
    }
    libvlc_audio_equalizer_set_preamp(m_vlcEqualizer, value);
    libvlc_media_player_set_equalizer(m_vlcMediaPlayer->core(), m_vlcEqualizer);
    QEXTVLCError::showErrMsg();
}
