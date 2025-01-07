#include "SqlSelectQueryBuilder.h"

SqlSelectQueryBuilder::SqlSelectQueryBuilder() : table_(""), where_clauses_() {}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) {
	columns_.push_back(column);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
	table_ = table;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column, const std::string& value) {
	where_clauses_.emplace_back(column + "=" + value);
	return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() {
	std::ostringstream query;

	if (columns_.empty()) {
		query << "SELECT *";
	}
	else {
		query << "SELECT " << Join(columns_, ", ");
	}

	if (!table_.empty()) {
		query << " FROM " << table_;
	}

	if (!where_clauses_.empty()) {
		query << " WHERE " << Join(where_clauses_, " AND ");
	}

	query << ";";

	return query.str();
}



std::string SqlSelectQueryBuilder::Join(const std::vector<std::string>& elements, const std::string& delimiter) {
	std::ostringstream joined;
	for (size_t i = 0; i < elements.size(); ++i) {
		if (i != 0) {
			joined << delimiter;
		}
		joined << elements[i];
	}
	return joined.str();
}
