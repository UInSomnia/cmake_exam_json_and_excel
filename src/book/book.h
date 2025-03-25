#ifndef INSOMNIA_BOOK_H
#define INSOMNIA_BOOK_H

#include "sheet.h"

namespace InSomnia
{
    class Book
    {
    public:
        Book();
        Book(
            const std::string &name,
            std::vector<Sheet> &&sheets);

        const std::string& get_name() const;
        const std::vector<Sheet>& get_sheets() const;

        std::string print() const;
        void from_json(const json &input);
        json to_json() const;

    private:
        std::string name;
        std::vector<Sheet> sheets;
    };
}

#endif
