#include "AdvancedSqlSelectQueryBuilder.h"
#include <iostream>

int main() {
	AdvancedSqlSelectQueryBuilder query_builder;
	query_builder.AddColumns({ "name", "phone" })
		.AddFrom("students");
	query_builder.AddWhereGreaterThan("id", "42");

	std::string expected_query = "SELECT name, phone FROM students WHERE id>42;";
	std::string actual_query = query_builder.BuildQuery();


	// Если проверка не проходит, печатаем ошибку
	if (actual_query != expected_query) {
		std::cerr << "Запрос не соответствует ожиданиям." << std::endl;
		std::cerr << "Ожидалось: " << expected_query << std::endl;
		std::cerr << "Получено: " << actual_query << std::endl;
	}

	return 0;
}