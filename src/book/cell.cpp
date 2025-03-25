#include "cell.h"

namespace InSomnia
{
    Cell::Cell()
    {
        this->row = -1;
        this->col = -1;
    }

    Cell::Cell(
        const uint32_t row,
        const uint32_t col,
        const std::string &value)
    {
        this->row = row;
        this->col = col;
        this->value = value;
    }
    
    uint32_t Cell::get_row() const
    {
        return row;
    }

    uint32_t Cell::get_col() const
    {
        return col;
    }

    const std::string& Cell::get_value() const
    {
        return value;
    }

    std::string Cell::print() const
    {
        return std::format("({}; {}) -> {}", row, col, value);
    }

    void Cell::from_json(const json &input)
    {
        if (input.contains("row") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'cell->row'");
        }
        if (input.contains("col") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'cell->col'");
        }
        if (input.contains("val") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'cell->val'");
        }

        row = input["row"].get<uint32_t>();
        col = input["col"].get<uint32_t>();
        value = input["val"].get<std::string>();
    }

    json Cell::to_json() const
    {
        json object_cell;
        object_cell["row"] = row;
        object_cell["col"] = col;
        object_cell["val"] = value;
        return object_cell;
    }
}
