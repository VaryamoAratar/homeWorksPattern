#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <map>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder();

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept;

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept;

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept;

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;

    std::string BuildQuery();

private:
    std::string table_;
    std::vector<std::string> columns_;
    std::vector<std::string> where_clauses_;

    std::string Join(const std::vector<std::string>& elements, const std::string& delimiter);
};