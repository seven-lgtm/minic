///
/// @file BranchInstruction.h
/// @brief 跳转指令 有条件跳转 /无条件跳转
///

#pragma once
#include "Instruction.h"
#include "LabelInstruction.h"

///
/// @brief 跳转指令
///


class BranchInstruction : public Instruction {
public:
    BranchInstruction(Function * func, Value * cond, LabelInstruction * trueLabel, LabelInstruction * falseLabel);
    void toString(std::string & str) override;
    LabelInstruction * getTrueLabel() const;
    LabelInstruction * getFalseLabel() const;
    Value * getCond() const; 

private:
    Value * cond;                  // 条件变量（类型必须为 i1）
    LabelInstruction * trueLabel;  // 条件为真时跳转的标签
    LabelInstruction * falseLabel; // 条件为假时跳转的标签
};
