/*
 * File: exp.cpp
 * -------------
 * This file implements the EvalState class and the ExpNode class
 * hierarchy.  The public methods are simple enough that they
 * should need no individual documentation.
 *
 * Except for this comment, the exp.cpp file is exactly the same as
 * is appears in Chapter 14.  The only change you need to make in
 * this file is to implement the changes to the EvalState class that
 * allow clients to set and get the number of the next program line.
 */

#include "exp.h"
#include <iostream>
#include "map.h"
#include "myhead.h"


/* Implementation of the EvalState class */

EvalState::EvalState() {
	/* Implemented automatically by Map constructor */
}

EvalState::~EvalState() {
	/* Implemented automatically by Map destructor */
}

void EvalState::setValue(string var, int value) {
	symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
	return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
	return symbolTable.containsKey(var);
}

void EvalState::clear()
{
	symbolTable.clear();
}

/*
 * Implementation of the base ExpNode class.  Neither the
 * constructor or destructor requires any code at this level.
 */

ExpNode::ExpNode() {
	/* Empty */
}

ExpNode::~ExpNode() {
	/* Empty */
}

/*
 * Implementation of the ConstantNode subclass.  For this
 * subclass, the implementation must look up the value in the
 * EvalState, passed to eval.
 */

ConstantNode::ConstantNode(int value) {
	this->value = value;
}

expTypeT ConstantNode::getType() {
	return ConstantType;
}

string ConstantNode::toString() {
	return IntegerToString(value);
}

int ConstantNode::eval(EvalState & state) {
	return value;
}

int ConstantNode::getValue() {
	return value;
}

/*
 * Implementation of the IdentifierNode subclass.  For this
 * subclass, the implementation must look up the value in the
 * symbol table passed to eval.
 */

IdentifierNode::IdentifierNode(string name) {
	this->name = name;
}

expTypeT IdentifierNode::getType() {
	return IdentifierType;
}

string IdentifierNode::toString() {
	return name;
}

int IdentifierNode::eval(EvalState & state) {
	if (!state.isDefined(name)) 
	{
		cout<<"VARIABLE NOT DEFINED\n";
		return -1;
	}
	return state.getValue(name);
}

string IdentifierNode::getName() {
	return name;
}

/*
 * Implementation of the CompoundNode subclass.  For this subclass,
 * the implementation must include explicit code for evaluating each
 * of the operators.
 */

CompoundNode::CompoundNode(char oper, expressionT l, expressionT r) {
	op = oper;
	lhs = l;
	rhs = r;
}

CompoundNode::~CompoundNode() {
	delete lhs;
	delete rhs;
}

expTypeT CompoundNode::getType() {
	return CompoundType;
}

string CompoundNode::toString() {
	return '(' + lhs->toString() + ' ' + op + ' '
	           + rhs->toString() + ')';
}

int CompoundNode::eval(EvalState & state) {
	if (op == '=') {
		if (lhs->getType() != IdentifierType) {
			cout<<"Illegal variable in assignment";
		}
		int val = rhs->eval(state);
		state.setValue(((IdentifierNode *) lhs)->getName(), val);
		return val;
	}
	int left = lhs->eval(state);
	int right = rhs->eval(state);
	switch (op) {
	  case '+': return left + right;
	  case '-': return left - right;
	  case '*': return left * right;
	  case '/': 
	  {
	  	if (right == 0)
	  	{
	  		cout<<"DIVIDE BY ZERO\n";
	  		return -1;
	  	}
	  	return left / right;
	  }
	}
	cout<<"Illegal operator in expression";
	return 0; /* To avoid the warning message */
}

char CompoundNode::getOp() {
	return op;
}

expressionT CompoundNode::getLHS() {
	return lhs;
}

expressionT CompoundNode::getRHS() {
	return rhs;
}
