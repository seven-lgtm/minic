
///
/// @file StoreInstruction.cpp
/// @brief Move指令，也就是DragonIR的Asssign指令
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

#include "StoreInstruction.h"
#include "Value.h"

#include "VoidType.h"

StoreInstruction::StoreInstruction(Function * _func, Value * dstPtr, Value * srcVal)
    : Instruction(_func, IRInstOperator::IRINST_OP_STORE, VoidType::getType())
{
    // 操作数0: 目标指针（内存地址）
    addOperand(dstPtr);

    // 操作数1: 源值（要存储的值）
    addOperand(srcVal);
}

void StoreInstruction::toString(std::string & str)
{
    Value * dstPtr = getOperand(0);
    Value * srcVal = getOperand(1);

    str = "*" + dstPtr->getIRName() + " = " + srcVal->getIRName();
}