#pragma once

#include "ast/HAstNode.hxx"
#include "ast/HAstOperatorType.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"

namespace Hyve::AST {
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