#include <qextRange.h>

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtRange &range)
{
    if (stream.version() == 1)
    {
        stream << (qint16)range.start() << (qint16)range.end();
    }
    else
    {
        stream << (qint32)range.start() << (qint32)range.end();
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtRange &range)
{
    if (stream.version() == 1)
    {
        qint16 start, end;
        stream >> start;  range.setStart(start);
        stream >> end;  range.setEnd(end);
    }
    else
    {
        qint32 start, end;
        stream >> start;  range.setStart(start);
        stream >> end;  range.setEnd(end);
    }
    return stream;
}
QDataStream &operator<<(QDataStream &stream, const QExtRangeF &range)
{
    stream << double(range.start()) << double(range.end());
    return stream;
}
QDataStream &operator>>(QDataStream &stream, QExtRangeF &range)
{
    double start, end;
    stream >> start;
    stream >> end;
    range.setStart(qreal(start));
    range.setEnd(qreal(end));
    return stream;
}
#endif // QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QExtRange &range)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QExtRange" << '(' << range.start() << ',' << range.end() << ')';
    return dbg;
}

QDebug operator<<(QDebug dbg, const QExtRangeF &range)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace();
    dbg << "QExtRange" << '(' << range.start() << ',' << range.end() << ')';
    return dbg;
}
#endif
