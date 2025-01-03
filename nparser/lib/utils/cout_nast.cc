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
#include "nast/assignment_expression_nast.h"
#include "nast/bilangan_bulat_literal_nast.h"
#include "nast/bilangan_desimal_literal_nast.h"
#include "nast/compound_statement_nast.h"
#include "nast/data_type_nast.h"
#include "nast/expression_nast.h"
#include "nast/id_nast.h"
#include "nast/karakter_literal_nast.h"
#include "nast/logical_and_expression_nast.h"
#include "nast/logical_or_expression_nast.h"
#include "nast/logika_literal_nast.h"
#include "nast/multiplicative_expression_nast.h"
#include "nast/primary_expression_nast.h"
#include "nast/statement_nast.h"
#include "nast/teks_literal_nast.h"
#include "nast/unary_expression_nast.h"
#include "nast/variable_nast.h"
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
    else if (const auto* value = dynamic_cast<const AssignmentExpressionNAst*>(&nAst))
    {
        std::cout << "AssignmentExpression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getLeft(), indent + 2);
        if (value->getOpRight().has_value())
        {
            std::cout << std::string(indent, ' ') << "|\n";
            std::cout << std::string(indent, ' ') << "-> " << value->getOpRight().value().op << "\n";
            std::cout << std::string(indent, ' ') << "|\n";
            std::cout << std::string(indent, ' ') << "-> ";
            coutNAst(*value->getOpRight().value().right, indent + 2);
        }
    }
    else if (const auto* value = dynamic_cast<const LogicalAndExpressionNAst*>(&nAst))
    {
        std::cout << "LogicalAndExpression\n";
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
    else if (const auto* value = dynamic_cast<const LogicalOrExpressionNAst*>(&nAst))
    {
        std::cout << "LogicalOrExpression\n";
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
    else if (const auto* value = dynamic_cast<const UnaryExpressionNAst*>(&nAst))
    {
        std::cout << "UnaryExpression\n";
        if (value->getOp().has_value())
        {
            std::cout << std::string(indent, ' ') << "|\n";
            std::cout << std::string(indent, ' ') << "-> " << value->getOp().value() << "\n";
        }
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getValue(), indent + 2);
    }
    else if (const auto* value = dynamic_cast<const PrimaryExpressionNAst*>(&nAst))
    {
        std::cout << "PrimaryExpression\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getValue(), indent + 2);
    }
    else if (const auto* value = dynamic_cast<const VariableNAst*>(&nAst))
    {
        std::cout << "VariableNAst\n";
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> ";
        coutNAst(*value->getDataType(), indent + 2);
        std::cout << std::string(indent, ' ') << "|\n";
        std::cout << std::string(indent, ' ') << "-> " << value->getName() << "\n";
        if (value->getInit().has_value())
        {
            std::cout << std::string(indent, ' ') << "|\n";
            std::cout << std::string(indent, ' ') << "-> ";
            coutNAst(*value->getInit().value(), indent + 2);
        }
    }
    else if (const auto* value = dynamic_cast<const IdNAst*>(&nAst))
    {
        std::cout << "Id: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const BilanganBulatLiteralNAst*>(&nAst))
    {
        std::cout << "BilanganBulatLiteral: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const BilanganDesimalLiteralNAst*>(&nAst))
    {
        std::cout << "BilanganDesimalLiteral: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const KarakterLiteralNAst*>(&nAst))
    {
        std::cout << "KarakterLiteral: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const TeksLiteralNAst*>(&nAst))
    {
        std::cout << "TeksLiteral: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const LogikaLiteralNAst*>(&nAst))
    {
        std::cout << "LogikaLiteral: " << (value->getValue() ? "benar" : "salah") << "\n";
    }
    else if (const auto* value = dynamic_cast<const DataTypeNAst*>(&nAst))
    {
        std::cout << "DataType: " << value->getValue() << "\n";
    }
    else
    {
        std::cout << "NAst Tisak di ketahui.\n";
    }
}

} // namespace nparser