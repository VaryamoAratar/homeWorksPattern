#pragma once
#include "SqlSelectQueryBuilder.h"

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
public:
    AdvancedSqlSelectQueryBuilder& AddWhereGreaterThan(const std::string& column, const std::string& value) noexcept;

    AdvancedSqlSelectQueryBuilder& AddWhereLessThan(const std::string& column, const std::string& value) noexcept;
};