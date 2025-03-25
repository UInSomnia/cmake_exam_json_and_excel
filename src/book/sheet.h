#ifndef INSOMNIA_SHEET_H
#define INSOMNIA_SHEET_H

#include <vector>
#include <sstream>

#include "cell.h"

namespace InSomnia
{
    class Sheet
    {
    public:
        Sheet();
        Sheet(
            const std::string &name,
            std::vector<Cell> &&cells);

        const std::string& get_name() const;
        const std::vector<Cell>& get_cells() const;

        std::string print() const;
        void from_json(const json &input);
        json to_json() const;

    private:
        std::string name;
        std::vector<Cell> cells;
    };
}

#endif
