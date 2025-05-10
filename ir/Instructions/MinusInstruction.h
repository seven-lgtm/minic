///
/// @file MinusInstruction.h
/// @brief 一元操作指令，如取负
///

#pragma once

#include "Instruction.h"

///
/// @brief 一元运算指令  CMakeLists.txt记得加入该文件cpp/h
///
class MinusInstruction : public Instruction {

public:
    /// @brief 构造函数
    /// @param _op 操作符
    /// @param _result 结果操作数
    /// @param _srcVal 源操作数
    
    MinusInstruction(Function * _func, IRInstOperator _op, Value * _srcVal, Type * _type);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};