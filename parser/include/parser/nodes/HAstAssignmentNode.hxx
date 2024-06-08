#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"

namespace Hyve::Parser {
	struct HAstAssignmentNode : public HAstStatementNode {
		HAstOperatorType Operator;
		std::shared_ptr<HAstNode> Target;
		std::shared_ptr<HAstExpressionNode> Value;
		
		HAstAssignmentNode() {
			Type = HAstNodeType::Assignment;
			Operator = HAstOperatorType::ASSIGN;
			StatementType = StatementType::VariableAssignment;
		}
	};
}