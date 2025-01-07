#include "SqlSelectQueryBuilder.h"
#include <iostream>

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");

    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    query_builder.AddWhere({ {"age", "20"}, {"city", "'New York'"} });

    std::string expected_query = "SELECT name, phone FROM students WHERE id=42 AND name=John AND age=20 AND city='New York';";
    std::string actual_query = query_builder.BuildQuery();


    if (actual_query != expected_query) {
        std::cerr << "Запрос не соответствует ожиданиям." << std::endl;
        std::cerr << "Ожидалось: " << expected_query << std::endl;
        std::cerr << "Получено: " << actual_query << std::endl;
    }

    return 0;
}