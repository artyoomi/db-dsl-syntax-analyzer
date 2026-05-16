#pragma once

#include "node.h"

using NodePtr = ast::NodePtr;

namespace ast::parser {

auto parse(const std::string& input) -> NodePtr;

}
