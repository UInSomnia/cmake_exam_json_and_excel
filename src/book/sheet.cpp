#include "sheet.h"

namespace InSomnia
{
    Sheet::Sheet()
    {

    }

    Sheet::Sheet(
        const std::string &name,
        std::vector<Cell> &&cells)
    {
        this->name = name;
        this->cells = std::move(cells);
    }

    const std::string& Sheet::get_name() const
    {
        return name;
    }

    const std::vector<Cell>& Sheet::get_cells() const
    {
        return cells;
    }

    std::string Sheet::print() const
    {
        std::ostringstream oss;
        oss << "name: " << name << "\n";
        oss << "cells:\n";
        for (const Cell &cell : cells)
        {
            oss << cell.print() << "\n";
        }
        return oss.str();
    }

    void Sheet::from_json(const json &input)
    {
        if (input.contains("name") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'sheet->name'");
        }
        if (input.contains("cells") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'sheet->cells'");
        }
        if (input["cells"].is_array() == false)
        {
            throw std::runtime_error("Invalid JSON format: 'sheet->cells' is not array");
        }

        name = input["name"].get<std::string>();
        const std::vector<json> json_cells = input["cells"];

        const uint32_t count_cells = json_cells.size();
        cells = std::vector<Cell>(count_cells);
        for (uint32_t i = 0u; i < count_cells; ++i)
        {
            const json &json_c = json_cells[i];
            Cell c;
            c.from_json(json_c);
            cells[i] = std::move(c);
        }
    }

    json Sheet::to_json() const
    {
        const uint32_t count_cells = cells.size();
        std::vector<json> json_array_cells(count_cells);
        for (int32_t c = 0; c < count_cells; ++c)
        {
            const Cell &cell = cells[c];
            json json_cell = cell.to_json();
            json_array_cells[c] = std::move(json_cell);
        }

        json object_sheet;
        object_sheet["name"] = name;
        object_sheet["cells"] = std::move(json_array_cells);
        return object_sheet;
    }
}
