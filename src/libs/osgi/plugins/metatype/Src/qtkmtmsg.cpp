#include "qtkmtmsg_p.h"

#include <QtGlobal>

const char* QTKMTMsg::CONTEXT = "QTKMTMsg";

const char* QTKMTMsg::SERVICE_DESCRIPTION = QT_TRANSLATE_NOOP("QTKMTMsg", "QTK Metatype Service - qtk Implementation");

const char* QTKMTMsg::UNEXPECTED_ELEMENT = QT_TRANSLATE_NOOP("QTKMTMsg", "Unexpected element %1.");
const char* QTKMTMsg::UNEXPECTED_TEXT = QT_TRANSLATE_NOOP("QTKMTMsg", "Unexpected text %1.");
const char* QTKMTMsg::MISSING_ATTRIBUTE = QT_TRANSLATE_NOOP("QTKMTMsg", "Missing attribute %1 in tag %2.");
const char* QTKMTMsg::OCD_ID_NOT_FOUND = QT_TRANSLATE_NOOP("QTKMTMsg", "Object Class Definition ID not found %1.");
const char* QTKMTMsg::nullptr_DEFAULTS = QT_TRANSLATE_NOOP("QTKMTMsg", "Default value cannot be null when cardinality is zero.");
const char* QTKMTMsg::MISSING_ELEMENT = QT_TRANSLATE_NOOP("QTKMTMsg", "Missing element %1 (Reference ID = %2.)");

const char* QTKMTMsg::EXCEPTION_MESSAGE = QT_TRANSLATE_NOOP("QTKMTMsg", "Unexpected exception %1 with message %2.");
const char* QTKMTMsg::nullptr_IS_INVALID = QT_TRANSLATE_NOOP("QTKMTMsg", "Cannot validate an empty value.");
const char* QTKMTMsg::VALUE_OUT_OF_RANGE = QT_TRANSLATE_NOOP("QTKMTMsg", "Value %1 is out of range.");
const char* QTKMTMsg::VALUE_OUT_OF_OPTION = QT_TRANSLATE_NOOP("QTKMTMsg", "Value %1 is out of Option.");
const char* QTKMTMsg::TOO_MANY_VALUES = QT_TRANSLATE_NOOP("QTKMTMsg", "Found too many values in %1 when expecting %2 values.");
const char* QTKMTMsg::nullptr_OPTIONS = QT_TRANSLATE_NOOP("QTKMTMsg", "Cannot set Option labels or values empty.");
const char* QTKMTMsg::INCONSISTENT_OPTIONS = QT_TRANSLATE_NOOP("QTKMTMsg", "Labels and Values of Option have different sizes.");
const char* QTKMTMsg::INVALID_OPTIONS = QT_TRANSLATE_NOOP("QTKMTMsg", "Option value %1 is invalid because of %2.");
const char* QTKMTMsg::INVALID_DEFAULTS = QT_TRANSLATE_NOOP("QTKMTMsg", "Defaults value %1 is invalid because of %2.");

const char* QTKMTMsg::METADATA_NOT_FOUND = QT_TRANSLATE_NOOP("QTKMTMsg", "Plugin(ID=\"%1\", name=\"%2\") has no MetaData file.");
const char* QTKMTMsg::ASK_INVALID_LOCALE = QT_TRANSLATE_NOOP("QTKMTMsg", "OCD(ID=\"%1\") cannot support this locale \"%2\".");
const char* QTKMTMsg::TOKENIZER_GOT_INVALID_DATA = QT_TRANSLATE_NOOP("QTKMTMsg", "The Tokenizer got invalid data.");
const char* QTKMTMsg::INVALID_PID_METATYPE_PROVIDER_IGNORED = QT_TRANSLATE_NOOP("QTKMTMsg", "Plugin %1 with ID %2 provided a QTKMetaTypeProvider with an invalid property. Property %3 with value %4 was not of the expected type (QString or QStringList) and will be ignored.");
