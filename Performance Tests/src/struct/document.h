//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_DOCUMENT_H
#define STMBENCH_DOCUMENT_H

#include <string>
#include <utility>
#include <utility>

// TODO inherit this class and Manual from the same base class

using namespace std;

namespace sb7 {

    class CompositePart;

    class Document {
    public:
        Document(int id, string title, string text)
                : m_id(id), m_title(std::move(std::move(title))), m_text(std::move(std::move(text))) {}

        virtual ~Document() = default;

        void setPart(CompositePart *cpart) {
            m_part = cpart;
        }

        CompositePart *getCompositePart() const {
            return m_part;
        }

        int getDocumentId() const {
            return m_id;
        }

        string getTitle() const {
            return m_title;
        }

        void nullOperation() const {
        }

        int searchText(char ch) const;

        bool replaceText(const string &from, const string &to);

        bool textBeginsWith(const string &prefix) const {
            return (m_text.find(prefix) == 0);
        }

        string getText() const {
            return m_text;
        }

    private:
        int m_id;
        string m_title;
        string m_text;
        CompositePart *m_part{};
    };

}

#endif //STMBENCH_DOCUMENT_H
