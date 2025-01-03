/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_variable.h"
#include "nast/core/nast.h"
#include "nast/variable_nast.h"
#include "parse/parse_data_type.h"
#include "parse/parse_expression.h"
#include <memory>
#include <optional>
#include <string>


namespace nparser {

std::unique_ptr<nparser::NAst> parseVariable(NParser::Utils& utils)
{
    auto variable = std::make_unique<VariableNAst>();

    variable->setDataType(parseDataType(utils));

    utils.expect(nlexer::NToken::Type::IDENTIFIER_TOKEN, "Bukanlah nama variabel yang benar.");

    variable->setName(utils.prevToken().content);

    if (utils.match(nlexer::NToken::Type::ASSIGNMENT_OP))
    {
        utils.eat();
        variable->setInit(parseExpression(utils));
    }

    return variable;
}

} // namespace nparser