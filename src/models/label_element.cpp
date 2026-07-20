#include "label_element.h"
#include <QUuid>

namespace LabelDesigner {

void LabelElement::generateId() {
    m_id = QUuid::createUuid().toString(QUuid::WithoutBraces);
}

} // namespace LabelDesigner
