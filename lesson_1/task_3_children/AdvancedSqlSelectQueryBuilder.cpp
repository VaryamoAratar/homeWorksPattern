#include "AdvancedSqlSelectQueryBuilder.h"

    AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhereGreaterThan(const std::string& column, const std::string& value) noexcept {
        where_clauses_.emplace_back(column + ">" + value);
        return *this;
    }

    AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhereLessThan(const std::string& column, const std::string& value) noexcept {
        where_clauses_.emplace_back(column + "<" + value);
        return *this;
    }
