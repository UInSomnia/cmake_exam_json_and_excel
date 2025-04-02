#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "book.h"

int main()
{
    using json = nlohmann::json;
    using InSomnia::Book;
    using InSomnia::Sheet;
    using InSomnia::Cell;

    std::vector<Cell> cells_students =
    {
        { 1, 1, "Surname" },    { 1, 2, "Name" },       { 1, 3, "Patronymic" },
        { 2, 1, "Smith" },      { 2, 2, "James" },      { 2, 3, "Andrew" },
        { 3, 1, "Williams" },   { 3, 2, "Linda" },      { 3, 3, "Thomas " },
        { 4, 1, "Davis" },      { 4, 2, "Mary" },       { 4, 3, "Michael " },
        { 5, 1, "Rodriguez" },  { 5, 2, "Patricia" },   { 5, 3, "Marie " }
    };

    std::vector<Cell> cells_lessons =
    {
        { 1, 1, "Lesson" },
        { 2, 1, "Physics" },
        { 3, 1, "Math" },
        { 4, 1, "History" },
        { 5, 1, "Astronomy" },
        { 6, 1, "Chemistry" },
        { 7, 1, "Biology" }
    };

    std::vector<Cell> cells_evaluations =
    {
        { 1, 1, "Surname" },    { 1, 2, "Lesson" },     { 1, 3, "Evalution" },
        { 2, 1, "Davis" },      { 2, 2, "Physics" },    { 2, 3, "B" },
        { 3, 1, "Davis" },      { 3, 2, "Math" },       { 3, 3, "A" },
        { 4, 1, "Smith" },      { 4, 2, "Math" },       { 4, 3, "C" },
        { 5, 1, "Williams" },   { 5, 2, "History" },    { 5, 3, "A" },
        { 6, 1, "Williams" },   { 6, 2, "Astronomy" },  { 6, 3, "B" },
        { 7, 1, "Williams" },   { 7, 2, "Chemistry" },  { 7, 3, "C" },
        { 8, 1, "Williams" },   { 8, 2, "Biology" },    { 8, 3, "B" },
        { 9, 1, "Rodriguez" },  { 9, 2, "Physics" },    { 9, 3, "A" },
        { 10, 1, "Rodriguez" }, { 10, 2, "Geometry" },  { 10, 3, "A" },
        { 11, 1, "Rodriguez" }, { 11, 2, "Biology" },   { 11, 3, "A" }
    };

    std::vector<Sheet> sheets =
    {
        { "Students", std::move(cells_students) },
        { "Lessons", std::move(cells_lessons) },
        { "Evaluations", std::move(cells_evaluations) }
    };

    const Book book("report", std::move(sheets));

    const json json_book = book.to_json();

    std::ofstream file_output("data.json");
    if (file_output.is_open() == false)
    {
        std::cout << "File output json not open!\n";
        return 1;
    }
    file_output << std::setw(4) << json_book << "\n";
    file_output.close();

    return 0;
}
