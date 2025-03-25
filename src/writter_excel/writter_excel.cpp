#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <OpenXLSX.hpp>

#include "book.h"

namespace InSomnia
{
    void save_to_excel(const InSomnia::Book &book);
    void prepare_worksheet(OpenXLSX::XLDocument &doc, const std::string &sheet_name);
    void remove_worksheet(OpenXLSX::XLDocument& doc, const std::string& sheet_name);
}

int main()
{
    using json = nlohmann::json;
    using InSomnia::Book;

    json json_input;
    std::ifstream fin("data.json");
    fin >> json_input;
    fin.close();

    Book book;
    book.from_json(json_input);
    save_to_excel(book);

    return 0;
}

namespace InSomnia
{
    void save_to_excel(const Book &book)
    {
        const std::string &book_name = book.get_name();
        const std::vector<Sheet> &sheets = book.get_sheets();

        OpenXLSX::XLDocument doc;
        const std::string path = book_name + std::string(".xlsx");
        doc.create(path, OpenXLSX::XLForceOverwrite);

        for (const Sheet &sheet : sheets)
        {
            const std::string &sheet_name = sheet.get_name();
            const std::vector<Cell> &cells = sheet.get_cells();

            prepare_worksheet(doc, sheet_name);
            OpenXLSX::XLWorksheet wks = doc.workbook().worksheet(sheet_name);

            for (const Cell &cell : cells)
            {
                const uint32_t row = cell.get_row();
                const uint32_t col = cell.get_col();
                const std::string &value = cell.get_value();
                wks.cell(row, col).value() = value;
            }
        }
        
        remove_worksheet(doc, "Sheet1");
        doc.save();
    }

    void prepare_worksheet(OpenXLSX::XLDocument &doc, const std::string &sheet_name)
    {
        if (doc.workbook().sheetExists(sheet_name) == false)
        {
            doc.workbook().addWorksheet(sheet_name);
        }
    }

    void remove_worksheet(OpenXLSX::XLDocument& doc, const std::string& sheet_name)
    {
        if (doc.workbook().sheetExists(sheet_name) == true)
        {
            doc.workbook().deleteSheet(sheet_name);
        }
    }
}
