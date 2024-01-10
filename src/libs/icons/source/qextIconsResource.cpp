
#include <qextIconsResource.h>

void QExtIconsResource::qextIconsInitResource()
{
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextIcons);
        onceFlag.leave();
    }
}
