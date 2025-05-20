///
/// @file BranchInstruction.cpp
/// @brief 跳转指令
///
#include "BranchInstruction.h"
#include "VoidType.h"


BranchInstruction::BranchInstruction(Function * func,
                                     Value * cond,
                                     LabelInstruction * trueLabel,
                                     LabelInstruction * falseLabel)
    : Instruction(func, IRInstOperator::IRINST_OP_BRANCH, VoidType::getType()), cond(cond), trueLabel(trueLabel),
      falseLabel(falseLabel)
{}

void BranchInstruction::toString(std::string & str)
{
    str = "bc " + cond->getIRName() + ", label " + trueLabel->getIRName() + ", label " + falseLabel->getIRName();
}

LabelInstruction * BranchInstruction::getTrueLabel() const
{
    return trueLabel;
}
LabelInstruction * BranchInstruction::getFalseLabel() const
{
    return falseLabel;
}

Value * BranchInstruction::getCond() const
{
    return cond;
}

// 指令格式 bc condvar, label X ,label Y