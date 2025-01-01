/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "utils/cout_nast.h"
#include "nast/additive_expression_nast.h"
#include "nast/compound_statement_nast.h"
#include "nast/expression_nast.h"
#include "nast/literal_nast.h"
#include "nast/multiplicative_expression_nast.h"
#include "nast/primary_expression_nast.h"
#include "nast/statement_nast.h"
#include <iostream>

namespace nparser {

void coutNAst(const NAst& nAst, int indent)
{
    if (const auto* value = dynamic_cast<const CompoundStatementNAst*>(&nAst))
    {
        std::cout << "CompoundStatement\n";
        for (const auto& child : value->getValue())
        {
            std::cout << std::string(indent, ' ') << "|\n";
            std::cout << std::string(indent, ' ') << "-> ";
            coutNAst(*child, indent + 2);
        }
    }
    else if (const auto* value = dynamic_cast<const StatementNAst*>(&nAst))
    {
        std::cout << "Statement\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getValue(), indent + 2);
    }
    else if (const auto* value = dynamic_cast<const ExpressionNAst*>(&nAst))
    {
        std::cout << "Expression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getValue(), indent + 2);
    }
    else if (const auto* value = dynamic_cast<const AdditiveExpressionNAst*>(&nAst))
    {
        std::cout << "AdditiveExpression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getLeft(), indent + 2);
        if (value->getOpRights().has_value())
        {
            for (const auto& opRight : value->getOpRights().value())
            {
                std::cout << std::string(indent, ' ') << "|\n";
                std::cout << std::string(indent, ' ') << "-> " << opRight.op << "\n";
                std::cout << std::string(indent, ' ') << "|\n";
                std::cout << std::string(indent, ' ') << "-> ";
                coutNAst(*opRight.right, indent + 2);
            }
        }
    }
    else if (const auto* value = dynamic_cast<const MultiplicativeExpressionNAst*>(&nAst))
    {
        std::cout << "MultiplicativeExpression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getLeft(), indent + 2);
        if (value->getOpRights().has_value())
        {
            for (const auto& opRight : value->getOpRights().value())
            {
                std::cout << std::string(indent, ' ') << "|\n";
                std::cout << std::string(indent, ' ') << "-> " << opRight.op << "\n";
                std::cout << std::string(indent, ' ') << "|\n";
                std::cout << std::string(indent, ' ') << "-> ";
                coutNAst(*opRight.right, indent + 2);
            }
        }
    }
    else if (const auto* value = dynamic_cast<const PrimaryExpressionNAst*>(&nAst))
    {
        std::cout << "PrimaryExpression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getValue(), indent + 2);
    }
    else if (const auto* value = dynamic_cast<const LiteralNAst*>(&nAst))
    {
        std::cout << value->getValue() << "\n";
    }
    else
    {
        std::cout << std::string(indent, ' ') << "NAST Tisak di ketahui.\n";
    }
}

} // namespace nparser