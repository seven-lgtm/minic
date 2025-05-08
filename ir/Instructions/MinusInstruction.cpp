///
/// @file BinaryInstruction.cpp
/// @brief 取负操作指令
///
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#include "MinusInstruction.h"

/// @brief 构造函数
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal 源操作数1

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
            // 取
            str = getIRName() + " = neg " + src->getIRName();
            break;
        default:
            // 未知指令
            Instruction::toString(str);
            break;
    }
}
