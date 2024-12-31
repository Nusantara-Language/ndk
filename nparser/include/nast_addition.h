/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NAST_ADDITION_H
#define NAST_ADDITION_H

#include "nast/compound_statement_nast.h"
#include "nast/expression_nast.h"
#include "nast/nast.h"
#include "nast/int_nast.h"
#include "nast/op_nast.h"
#include "nast/statement_nast.h"
#include <iostream>
#include <memory>
#include <string>

namespace nparser {

inline void coutNAst(const NAst& nAst, int jarak = 0)
{
    if (const auto* value = dynamic_cast<const CompoundStatementNAst*>(&nAst))
    {
        std::cout << "CompoundStatement:\n";
        for (const auto& child : value->getValue())
        {
            std::cout << std::string(jarak, ' ') << "|\n";
            std::cout << std::string(jarak, ' ') << "-> ";
            coutNAst(*child, jarak + 2);
        }
    }
    else if (const auto* value = dynamic_cast<const ExpressionNAst*>(&nAst))
    {
        std::cout << "Expression:\n";
        std::cout << std::string(jarak, ' ') << "|\n";
        std::cout << std::string(jarak, ' ') << "-> ";
        coutNAst(*value->getValue(), jarak + 2);
    }
    else if (const auto* value = dynamic_cast<const IntNAst*>(&nAst))
    {
        std::cout << "Int: " << value->getValue() << "\n";
    }
    else if (const auto* value = dynamic_cast<const OpNAst*>(&nAst))
    {
        std::cout << "Operator: " << value->getOp() << "\n";
        std::cout << std::string(jarak, ' ') << "|\n";
        std::cout << std::string(jarak, ' ') << "-> ";
        coutNAst(*value->getLeft(), jarak + 2);
        std::cout << std::string(jarak, ' ') << "|\n";
        std::cout << std::string(jarak, ' ') << "-> ";
        coutNAst(*value->getRight(), jarak + 2);
    }
    else if (const auto* value = dynamic_cast<const StatementNAst*>(&nAst))
    {
        std::cout << "Statement:\n";
        std::cout << std::string(jarak, ' ') << "|\n";
        std::cout << std::string(jarak, ' ') << "-> ";
        coutNAst(*value->getValue(), jarak + 2);
    }
    else
    {
        std::cout << std::string(jarak, ' ') << "NAST Tisak di ketahui.\n";
    }
}

} // namespace nparser

#endif