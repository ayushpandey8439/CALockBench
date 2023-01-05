//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_MANUAL_H
#define STMBENCH_MANUAL_H


#include <string>
#include <utility>

using namespace std;

namespace sb7 {

    class Module;

    class Manual {
    public:
        Manual(int id, string title, string &text)
                : m_id(id), m_title(std::move(title)), m_text(text) {}

        virtual ~Manual() = default;

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
        Module *m_module{};
    };

}


#endif //STMBENCH_MANUAL_H
