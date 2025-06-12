///
/// @file LoadInstruction.h
/// @brief 加载指令，用于从内存地址加载值
///
#pragma once

#include "Instruction.h"

class Function;
class Value;

///
/// @brief 加载指令类
///
class LoadInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param srcPtr 源指针（内存地址）
    /// @param type 加载的数据类型
    ///
    LoadInstruction(Function * _func, Value * srcPtr, Type * type);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};