#include "cellStr.h"

String cellStr(Field* f, int width) {
	String s = f->getName();

	if (f->getType() == FieldType::PROPERTY) {
		Property* prop = (Property*)f;

		if (prop->isBought()) {
			s += " ";
			s += prop->getOwner()->getUserName();
		}

		if (prop->getPropertyType() == PropertyType::BUILDABLE_PROPERTY) {
			BuildableProperty* bp = (BuildableProperty*)prop;

			if (bp->getHasCastle()) {
				s += " Castle";
			}
			else if (bp->getCottageCount() > 0) {
				s += " C:";
				char countStr[2];
				countStr[0] = '0' + bp->getCottageCount();
				countStr[1] = '\0';
				s += String(countStr);
			}
		}
	}

	if (s.getLenght() > width - 1) {
		if (s.getLenght() > width - 1) {
			String truncated;
			const char* data = s.getData();
			for (int i = 0; i < width - 1; ++i) {
				char c[2];
				c[0] = data[i];
				c[1] = '\0';
				truncated += c;
			}
			s = truncated;
		}
	}

	return s;
}