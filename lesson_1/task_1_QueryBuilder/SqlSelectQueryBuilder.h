#pragma once
#include <string>
#include <vector>
#include <sstream>

class SqlSelectQueryBuilder {
public:
	SqlSelectQueryBuilder();

	SqlSelectQueryBuilder& AddColumn(const std::string& column);

	SqlSelectQueryBuilder& AddFrom(const std::string& table);

	SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value);

	std::string BuildQuery();

private:
	std::string table_;
	std::vector<std::string> columns_;
	std::vector<std::string> where_clauses_;

	std::string Join(const std::vector<std::string>& elements, const std::string& delimiter);
};
