#include "manual.h"

using namespace sb7;

int sb7::Manual::countOccurences(char c) const {
	string::const_iterator curr;
	string::const_iterator end = m_text.end();
	int cnt = 0;

	for(curr = m_text.begin();curr != end;curr++) {
		if(*curr == c) {
			cnt++;
		}
	}

	return cnt;
}

bool sb7::Manual::checkFirstLastCharTheSame() const {
	return *(m_text.begin()) == *(m_text.rbegin());
}

bool sb7::Manual::startsWith(char c) const {
	return *(m_text.begin()) == c;
}

int sb7::Manual::replaceChar(char from, char to) {
	string::iterator curr;
	string::iterator end = m_text.end();
	int cnt = 0;

	for(curr = m_text.begin();curr != end;curr++) {
		char c = *curr;

		if(c == from) {
			*curr = to;
			cnt++;
		}
	}

	return cnt;
}
