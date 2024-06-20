#ifndef SB7_MANUAL_H_
#define SB7_MANUAL_H_

#include <string>

using namespace std;

namespace sb7 {

	class Module;

	class Manual {
		public:
			Manual(int id, const string &title, string &text)
				: m_id(id), m_title(title), m_text(text) { }

			virtual ~Manual() { }

			void setModule(Module *mod) {
				m_module = mod;
			}

			/**
			 * Count number of occurencest of c in text.
			 */
			int countOccurences(char c) const;

			/**
			 * Check whether first and last character of text are equal.
			 */
			bool checkFirstLastCharTheSame() const;

			/**
			 * Check if text starts with character c.
			 */
			bool startsWith(char c) const;

			/**
			 * Replace all characters from with characters to in text.
			 */
			int replaceChar(char from, char to);

		protected:
			int m_id;
			string m_title;
			string m_text;
			Module *m_module;
	};

}


#endif /*SB7_MANUAL_H_*/
