#include "atomic_part.h"
#include "connection.h"

void sb7::AtomicPart::connectTo(AtomicPart *dest,
		const string &type, int len) const {
	Connection *conn = new Connection((AtomicPart *)this, dest, type, len);
	m_to->add(conn);
	dest->addConnectionFromOtherPart(conn);
}
