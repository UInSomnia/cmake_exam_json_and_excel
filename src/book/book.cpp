#include "book.h"

namespace InSomnia
{
    Book::Book()
    {

    }

    Book::Book(
        const std::string &name,
        std::vector<Sheet> &&sheets)
    {
        this->name = name;
        this->sheets = std::move(sheets);
    }

    const std::string& Book::get_name() const
    {
        return name;
    }

    const std::vector<Sheet>& Book::get_sheets() const
    {
        return sheets;
    }

    std::string Book::print() const
    {
        std::ostringstream oss;
        oss << "name: " << name << "\n";
        oss << "sheets:\n";
        for (const Sheet &sheet : sheets)
        {
            oss << sheet.print() << "\n";
        }
        return oss.str();
    }

    void Book::from_json(const json &input)
    {
        if (input.contains("book") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'book'");
        }
        if (input["book"].contains("name") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'book->name'");
        }
        if (input["book"].contains("sheets") == false)
        {
            throw std::runtime_error("Invalid JSON format: missing 'book->sheets'");
        }
        if (input["book"]["sheets"].is_array() == false)
        {
            throw std::runtime_error("Invalid JSON format: 'book->sheets' is not array");
        }

        name = input["book"]["name"].get<std::string>();
        const std::vector<json> json_sheets = input["book"]["sheets"];

        const uint32_t count_sheets = json_sheets.size();
        sheets = std::vector<Sheet>(count_sheets);
        for (uint32_t i = 0u; i < count_sheets; ++i)
        {
            const json &json_s = json_sheets[i];
            Sheet s;
            s.from_json(json_s);
            sheets[i] = std::move(s);
        }
    }

    json Book::to_json() const
    {
        json object_book;
        object_book["book"]["name"] = name;

        const uint32_t count_sheets = sheets.size();
        std::vector<json> json_array_sheets(count_sheets);
        for (int32_t s = 0; s < count_sheets; ++s)
        {
            const Sheet &sheet = sheets[s];
            json json_sheet = sheet.to_json();
            json_array_sheets[s] = std::move(json_sheet);
        }

        object_book["book"]["sheets"] = std::move(json_array_sheets);

        return object_book;
    }
}
