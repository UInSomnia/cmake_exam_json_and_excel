#ifndef INSOMNIA_CELL_H
#define INSOMNIA_CELL_H

#include <cstdint>
#include <string>
#include <format>

#include <nlohmann/json.hpp>

namespace InSomnia
{
    using json = nlohmann::json;

    class Cell
    {
    public:
        Cell();
        Cell(
            const uint32_t row,
            const uint32_t col,
            const std::string &value);
        
        uint32_t get_row() const;
        uint32_t get_col() const;
        const std::string& get_value() const;

        std::string print() const;
        void from_json(const json &input);
        json to_json() const;

    private:
        uint32_t row;
        uint32_t col;
        std::string value;
    };
}

#endif
