#include <qextRange.h>

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtRange &range)
{
    if (stream.version() == 1)
    {
        stream << (qint16)range.min() << (qint16)range.max();
    }
    else
    {
        stream << (qint32)range.min() << (qint32)range.max();
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtRange &range)
{
    if (stream.version() == 1)
    {
        qint16 start, end;
        stream >> start;  range.setMin(start);
        stream >> end;  range.setMax(end);
    }
    else
    {
        qint32 start, end;
        stream >> start;  range.setMin(start);
        stream >> end;  range.setMax(end);
    }
    return stream;
}
QDataStream &operator<<(QDataStream &stream, const QExtRangeF &range)
{
    stream << double(range.min()) << double(range.max());
    return stream;
}
QDataStream &operator>>(QDataStream &stream, QExtRangeF &range)
{
    double start, end;
    stream >> start;
    stream >> end;
    range.setMin(qreal(start));
    range.setMax(qreal(end));
    return stream;
}
#endif // QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QExtRange &range)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QExtRange" << '(' << range.min() << ',' << range.max() << ')';
    return dbg;
}

QDebug operator<<(QDebug dbg, const QExtRangeF &range)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QExtRange" << '(' << range.min() << ',' << range.max() << ')';
    return dbg;
}
#endif
