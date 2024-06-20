#ifndef SB7_CONNECTION_H_
#define SB7_CONNECTION_H_

using namespace std;

namespace sb7 {

	class AtomicPart;

	class Connection {
		public:
			Connection(AtomicPart *from, AtomicPart *to,
					const string &type, int length)
				: m_type(type), m_length(length), m_from(from), m_to(to) {
			}

			virtual ~Connection() { }

			Connection *getReversed() const {
				return new Connection(m_to, m_from, m_type, m_length);
			}

			AtomicPart *getDestination() const {
				return m_to;
			}

			AtomicPart *getSource() const {
				return m_from;
			}

		private:
			string m_type;
			int m_length;
			AtomicPart *m_from;
			AtomicPart *m_to;
	};
}

#endif /*SB7_CONNECTION_H_*/
