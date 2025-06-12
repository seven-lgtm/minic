#include "LoadInstruction.h"
#include "Value.h"

LoadInstruction::LoadInstruction(Function * _func, Value * srcPtr, Type * type)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, type)
{
    // 操作数0: 源指针（内存地址）
    addOperand(srcPtr);
}

void LoadInstruction::toString(std::string & str)
{
    Value * srcPtr = getOperand(0); 

    str = getIRName() + " = *" + srcPtr->getIRName();
}