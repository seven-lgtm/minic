///
/// @file MinusInstruction.cpp

/// @brief 取负操作指令
///

#include "MinusInstruction.h"

/// @brief 构造函数
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal 源操作数

MinusInstruction::MinusInstruction(Function * _func,
                                     IRInstOperator _op,
                                     Value * _srcVal,
                                     Type * _type)
    : Instruction(_func, _op, _type)
{
    addOperand(_srcVal);
    
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void MinusInstruction::toString(std::string & str)
{

    Value *src = getOperand(0);

    switch (op) {
        
        case IRInstOperator::IRINST_OP_NEG_I:
            // 取负指令
            str = getIRName() + " = neg " + src->getIRName();
            break;
        case IRInstOperator::IRINST_OP_LOAD: 
            str = getIRName() + " = *" + src->getIRName();
            break;
        default:
            // 未知指令
            Instruction::toString(str);
            break;
    }
}
