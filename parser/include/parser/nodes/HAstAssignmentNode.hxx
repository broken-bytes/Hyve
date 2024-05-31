#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"

namespace Hyve::Parser {
	struct HAstAssignmentNode : public HAstStatementNode {
		HAstOperatorType Operator;
		HAstAssignmentNode() {
			Type = HAstNodeType::Assignment;
			Operator = HAstOperatorType::ASSIGN;
		}
	};
}