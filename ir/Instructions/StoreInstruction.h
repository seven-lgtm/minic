///
/// @file StoreInstruction.h
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



///
/// @file StoreInstruction.h
/// @brief 存储指令，用于将值存储到内存地址
///
#pragma once

#include "Instruction.h"

class Function;
class Value;

///
/// @brief 存储指令类
///
class StoreInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param dstPtr 目标指针（内存地址）
    /// @param srcVal 源值（要存储的值）
    ///
    StoreInstruction(Function * _func, Value * dstPtr, Value * srcVal);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};