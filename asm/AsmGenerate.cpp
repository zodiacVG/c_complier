#include "AsmGenerate.h"

AsmCode::AsmCode() {

}

std::string AsmCode::transRegister(asmRegister reg) {
    if (reg == asmRegister::eax) return ASM_EAX;
    else if (reg == asmRegister::ebx) return ASM_EBX;
    else if (reg == asmRegister::ecx) return ASM_ECX;
    else if (reg == asmRegister::edx) return ASM_EDX;
    else if (reg == asmRegister::ebp) return ASM_EBP;
    else if (reg == asmRegister::esp) return ASM_ESP;
    else return "";
}

std::string AsmCode::generateVar(int offset) {
    std::string ans = ASM_LB + std::string(ASM_EBP);
    if (offset > 0) 
    {
        ans += "-";
        ans += std::to_string(offset);
    } 
    else 
    {
        ans += "+";
        ans += std::to_string(-offset);
    }
    ans += ASM_RB;
    return ans;
}

std::string AsmCode::generateInstanceNumber(int value) {
    std::string ans = DOUBLE_WORD;
    ans += " " + std::to_string(value);
    return ans;
}

void AsmCode::generateBinaryInstructor(std::string instructor, asmRegister reg1, asmRegister reg2) {
    this->codeBuffer += instructor + std::string(" ") + this->transRegister(reg1) 
                        + "," + this->transRegister(reg2) + "\n";
}

void AsmCode::generateBinaryInstructor(std::string instructor, asmRegister reg, std::string var) {
    std::cout<<"";
    this->codeBuffer += instructor + std::string(" ") + this->transRegister(reg) 
                        + "," + var + "\n";
}

void AsmCode::generateBinaryInstructor(std::string instructor, std::string var, asmRegister reg) {
    std::cout<<"";
    this->codeBuffer += instructor + std::string(" ") + var
                        + "," + this->transRegister(reg) + "\n";
}

void AsmCode::generateBinaryInstructor(std::string instructor, std::string var1, std::string var2) {
    this->codeBuffer += instructor + " " + var1 +
                        + ASM_COMMA + var2 + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, asmRegister reg) {
    this->codeBuffer += instructor + " " + this->transRegister(reg) + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, std::string var) {
    this->codeBuffer += instructor + " " + var + "\n";
}

std::string AsmCode::findValueByAddress(asmRegister reg) {
    return ASM_LB + this->transRegister(reg) + ASM_RB;
}

void AsmCode::addCode(std::string code) {
    this->codeBuffer += code;
    this->codeBuffer += "\n";
}

void AsmCode::add(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_ADD, reg1, reg2);
}

void AsmCode::add(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_ADD, reg, var);
}

void AsmCode::sub(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_SUB, reg1, reg2);
}

void AsmCode::sub(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_SUB, reg, var);
}

void AsmCode::mov(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_MOV, reg1, reg2);
}

void AsmCode::mov(asmRegister reg, std::string var) {
    std::cout<<"";
    this->generateBinaryInstructor(ASM_MOV, reg, var);
}

void AsmCode::mov(std::string var, asmRegister reg) {
    std::cout<<"";
    this->generateBinaryInstructor(ASM_MOV, var, reg);
}

void AsmCode::mov(std::string var1, std::string var2) {
    this->generateBinaryInstructor(ASM_MOV, var1, var2);
}

// Save the answer to eax
void AsmCode::mul(asmRegister reg1, asmRegister reg2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg1);
    this->generateUnaryInstructor(ASM_MUL, reg2);
}

void AsmCode::mul(asmRegister reg, std::string var) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg);
    this->generateUnaryInstructor(ASM_MUL, DOUBLE_WORD + var);
}

void AsmCode::mul(std::string var1, std::string var2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var1);
    this->generateUnaryInstructor(ASM_MUL, DOUBLE_WORD + var2);
}

void AsmCode::div(asmRegister reg1, asmRegister reg2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg1);
    this->generateUnaryInstructor(ASM_DIV, reg2);
}

void AsmCode::div(asmRegister reg, std::string var) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg);
    this->generateUnaryInstructor(ASM_DIV, DOUBLE_WORD + var);
}

void AsmCode::div(std::string var, asmRegister reg) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var);
    this->generateUnaryInstructor(ASM_DIV, reg);
}

void AsmCode::div(std::string var1, std::string var2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var1);
    this->generateUnaryInstructor(ASM_DIV, DOUBLE_WORD + var2);
}


void AsmCode::asmXor(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_XOR, reg1, reg2);
}

void AsmCode::push(asmRegister reg) {
    this->generateUnaryInstructor(ASM_PUSH, reg);
}

void AsmCode::push(std::string var) {
    this->generateUnaryInstructor(ASM_PUSH, var);
}

void AsmCode::pop(asmRegister reg) {
    this->generateUnaryInstructor(ASM_POP, reg);
}

void AsmCode::label(std::string label) {
    this->codeBuffer += label + ASM_COLON + "\n";
}

std::ostream& operator<<(std::ostream& os, const AsmCode& code) {
    os << code.codeBuffer;
    return os;
}

AsmGenerate::AsmGenerate(std::vector<QuadItem*> quadlist, SymbolTable* roottable) {
    this->quad_list = quadlist;
    //this->tempVar = tempVar;
    this->rootTable = roottable;
    //this->funcTable = funcTable;
    this->preSetLabel();
    /*std::cout<<"begin--initializeasm:--\n";
    for(size_t i=0;i<quad_list.size();i++)
    {
        //std::cout<<"quad_list["<<i<<"]=";
        quad_list[i]->printItemInfor();
        std::cout<<quad_list[i]->quad_item_type<<"\n";
    }
    std::cout<<"end--initializeasm:--\n";*/
    
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}

void AsmGenerate::releaseRegister(asmRegister reg) {
    if (reg == asmRegister::ebx) {
        ebx = 0;
        int index = (int)asmRegister::ebx;
        this->registerUsedVar[index - 1] = "";
    } else if (reg == asmRegister::ecx) {
        ecx = 0;
        int index = (int)asmRegister::ecx;
        this->registerUsedVar[index - 1] = "";
    }
}

asmRegister AsmGenerate::getRegister(std::string var) {
    if (ebx == 0) {
        ebx = 1;
        int index = (int)asmRegister::ebx;
        this->registerUsedVar[index - 1] = var;
        return asmRegister::ebx;
    } else if (ecx == 0) {
        ecx = 1;
        int index = (int)asmRegister::ecx;
        this->registerUsedVar[index - 1] = var;
        return asmRegister::ecx;
    }
}

asmRegister AsmGenerate::findRegister(std::string var) {
    for (int i = 0; i < 6; i++) {
        if (this->registerUsedVar[i] == var) {
            return asmRegister(i + 1);
        }
    }
}

void AsmGenerate::generateArithmetic(QuadItem q) {
    std::string instructor;
    OpType optype = q.getOpType();
    int flag = q.getItemType();
    // Special case, assign operate is unary operator.
    if (optype==OpType::assign) 
    {
        Symbol* result = q.getArg(3).var;
        int offset = result->getWidth();
        std::string result_ebp_offset = this->asmcode.generateVar(offset);
        if (flag == 7) {
            std::string tempVar = q.getArg(1).var->getIDName();
            if (tempVar[0] == 't') 
            {
                asmRegister tempVarReg = this->findRegister(tempVar);
                this->asmcode.mov(result_ebp_offset, tempVarReg);
                this->releaseRegister(tempVarReg);
            } else {
                int varOffset = q.getArg(1).var->getWidth();
                std::string varEbpOffset = this->asmcode.generateVar(varOffset);
                this->asmcode.mov(asmRegister::edx, varEbpOffset);
                this->asmcode.mov(result_ebp_offset, asmRegister::edx);
            }
        }
        else {
            int tempVar = q.getArg(1).target;
            this->asmcode.mov(result_ebp_offset, DOUBLE_WORD + std::string(" ") +std::to_string(tempVar));
        }
        return;
    }
    if (optype==OpType::addtion) instructor = ASM_ADD;
    else if (optype==OpType::substract) instructor = ASM_SUB;

    asmRegister tempVar1Reg = asmRegister::unset;
    asmRegister tempVar2Reg = asmRegister::unset;
    asmRegister resultReg = asmRegister::unset;
    int value1, value2;
    std::string arg1IdName = "";
    std::string arg2IdName = "";
    // Result must be temp var or var, cannot be instance number
    std::string resultIdName = q.getArg(3).var->getIDName();
    
    // All args and reslut is var or temp var.
    if (flag == 7) 
    {
        arg1IdName = q.getArg(1).var->getIDName();
        arg2IdName = q.getArg(2).var->getIDName();
        if (arg1IdName[0] == 't') {
            tempVar1Reg = this->findRegister(arg1IdName);
            this->releaseRegister(tempVar1Reg);
        }
        if (arg2IdName[0] == 't') {
            tempVar2Reg = this->findRegister(arg2IdName);
            this->releaseRegister(tempVar2Reg);
        }
        if (resultIdName[0] == 't') {
            resultReg = this->getRegister(resultIdName);
        }
        
        if (tempVar1Reg != asmRegister::unset && tempVar2Reg != asmRegister::unset) 
        {
            if (optype==OpType::addtion || optype==OpType::substract) {
                this->asmcode.generateBinaryInstructor(instructor, tempVar1Reg, tempVar2Reg);
            } else {
                if (optype==OpType::multiply) {
                    this->asmcode.mul(tempVar1Reg, tempVar2Reg);
                } else if (optype==OpType::divide || optype==OpType::mod) {
                    this->asmcode.div(tempVar1Reg, tempVar2Reg);
                }
            }
            if (resultReg != asmRegister::unset) 
            {
                if (optype==OpType::addtion || optype==OpType::substract) {
                    if (tempVar1Reg != resultReg) {
                        this->asmcode.mov(resultReg, tempVar1Reg);
                    }
                } else {
                    if (optype==OpType::multiply || optype==OpType::divide) {
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.mov(resultReg, asmRegister::edx);
                    }
                }
            } else {
                Symbol* result = q.getArg(3).var;
                int offset = result->getWidth();
                std::string ebp_offset = this->asmcode.generateVar(offset);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    if (tempVar1Reg != resultReg) {
                        this->asmcode.mov(ebp_offset, tempVar1Reg);
                    }
                } else {
                    if (optype==OpType::multiply || optype==OpType::divide) {
                        this->asmcode.mov(ebp_offset, asmRegister::eax);
                    } else {
                        this->asmcode.mov(ebp_offset, asmRegister::edx);
                    }
                }
            }
        } 
        else if (tempVar1Reg != asmRegister::unset || tempVar2Reg != asmRegister::unset) {
            asmRegister reg = asmRegister::unset;
            Symbol* vars = NULL;
            std::string var = "";
            if (tempVar1Reg == asmRegister::unset) {
                reg = tempVar2Reg;
                Symbol* vars = q.getArg(1).var;
                int offset = vars->getWidth();
                var = this->asmcode.generateVar(offset);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.generateBinaryInstructor(instructor, var, reg);
                    this->asmcode.mov(reg, var);
                } else {
                    if (optype==OpType::multiply || optype==OpType::divide) {
                        if (optype==OpType::multiply) {
                            this->asmcode.mul(reg, var);
                        } else {
                            this->asmcode.div(var, reg);
                        }
                        this->asmcode.mov(reg, asmRegister::eax);
                    } else {
                        this->asmcode.div(var, reg);
                        this->asmcode.mov(reg, asmRegister::edx);
                    }
                }
            } else {
                reg = tempVar1Reg;
                Symbol* vars = q.getArg(2).var;
                int offset = vars->getWidth();
                var = this->asmcode.generateVar(offset);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.generateBinaryInstructor(instructor, reg, var);
                } else {
                    if (optype==OpType::multiply || optype==OpType::divide) {
                         if (optype==OpType::multiply) {
                            this->asmcode.mul(reg, var);
                        } else {
                            this->asmcode.div(reg, var);
                        }
                        if (reg != resultReg) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(reg, asmRegister::eax);
                        }
                    } else {
                        this->asmcode.div(reg, var);
                        this->asmcode.mov(reg, asmRegister::edx);
                    }
                }
                // this->asmcode.generateBinaryInstructor(instructor, reg, var);
            }
            if (resultReg != asmRegister::unset) {
                if (reg != resultReg) {
                    this->asmcode.mov(resultReg, reg);
                }
            } else {
                Symbol* result = q.getArg(3).var;
                int offset = result->getWidth();
                std::string ebp_offset = this->asmcode.generateVar(offset);
                this->asmcode.mov(ebp_offset, reg);
            }
        } 
        else if (tempVar1Reg == asmRegister::unset && tempVar2Reg == asmRegister::unset){
            Symbol* var1 = q.getArg(1).var;
            Symbol* var2 = q.getArg(2).var;
            std::string var1_ebp_offset = this->asmcode.generateVar(var1->getWidth());
            std::string var2_ebp_offset = this->asmcode.generateVar(var2->getWidth());
            if (resultReg != asmRegister::unset)
            {
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.mov(resultReg, var1_ebp_offset);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, var2_ebp_offset);
                } 
                else 
                {
                    if (optype==OpType::multiply) {
                        this->asmcode.mul(var1_ebp_offset, var2_ebp_offset);
                    } else {
                        this->asmcode.div(var1_ebp_offset, var2_ebp_offset);
                    }
                    if (optype==OpType::mod) {
                        this->asmcode.mov(resultReg, asmRegister::edx);
                    } else {
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    }
                }
            }
        }
    } 
    else if (flag == 6 || flag == 5) 
    {
        if (flag == 6) {
            value1 = q.getArg(1).target;
            std::string instance = this->asmcode.generateInstanceNumber(value1);
            arg2IdName = q.getArg(2).var->getIDName();
            if (arg2IdName[0] == 't') {
                tempVar2Reg = this->findRegister(arg2IdName);
                this->releaseRegister(tempVar2Reg);
                resultReg = this->getRegister(resultIdName);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.generateBinaryInstructor(instructor, tempVar2Reg, instance);
                    if (optype==OpType::substract) {
                        this->asmcode.generateUnaryInstructor(ASM_NEG, tempVar2Reg);
                    }
                    if (resultReg != tempVar2Reg) {
                        this->asmcode.mov(resultReg, tempVar2Reg);
                    }
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    asmRegister regInstance = asmRegister::eax;
                    this->asmcode.mov(regInstance, instance);
                    if (optype==OpType::multiply) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, tempVar2Reg);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, tempVar2Reg);
                        if (optype==OpType::divide) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }                
            } else {
                resultReg = this->getRegister(resultIdName);
                int offset = q.getArg(2).var->getWidth();
                std::string ebpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.asmXor(resultReg, resultReg);
                    this->asmcode.mov(resultReg, instance);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, ebpOffset);
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    this->asmcode.mov(asmRegister::eax, instance);
                    if (optype==OpType::multiply) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, ebpOffset);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, ebpOffset);
                        if (optype==OpType::divide) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            }
        } else {
            value2 = q.getArg(2).target;
            arg1IdName = q.getArg(1).var->getIDName();
            std::string instance = this->asmcode.generateInstanceNumber(value2);
            if (arg1IdName[0] == 't') {
                tempVar1Reg = this->findRegister(arg1IdName);
                this->releaseRegister(tempVar1Reg);
                resultReg = this->getRegister(resultIdName);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.generateBinaryInstructor(instructor, tempVar1Reg, instance);
                    if (resultReg != tempVar1Reg) {
                        this->asmcode.mov(resultReg, tempVar2Reg);
                    }
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    resultReg = this->getRegister(resultIdName);
                    // the instance number use result register.
                    asmRegister regInstance = resultReg;
                    this->asmcode.mov(regInstance, instance);
                    int offset = q.getArg(1).var->getWidth();
                    std::string ebpOffset = this->asmcode.generateVar(offset);
                    this->asmcode.mov(asmRegister::eax, ebpOffset);

                    if (optype==OpType::multiply) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, regInstance);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, regInstance);
                        if (optype==OpType::divide) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            } else {
                resultReg = this->getRegister(resultIdName);
                int offset = q.getArg(1).var->getWidth();
                std::string ebpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
                if (optype==OpType::addtion || optype==OpType::substract) {
                    this->asmcode.asmXor(resultReg, resultReg);
                    this->asmcode.mov(resultReg, ebpOffset);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, instance);
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    asmRegister instanceReg = resultReg;
                    this->asmcode.mov(asmRegister::eax, ebpOffset);
                    this->asmcode.mov(instanceReg, instance);
                    if (optype==OpType::multiply) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, instanceReg);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, instanceReg);
                        if (optype==OpType::divide) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            }
        }
    }
    else if (flag == 4)
     {
        value1 = q.getArg(1).target;
        value2 = q.getArg(2).target;
        std::string instance1 = this->asmcode.generateInstanceNumber(value1);
        std::string instance2 = this->asmcode.generateInstanceNumber(value2);
        resultReg = this->getRegister(resultIdName);
        if (optype==OpType::addtion || optype==OpType::substract) {
            this->asmcode.mov(resultReg, instance1);
            this->asmcode.generateBinaryInstructor(instructor, resultReg, instance2);
        } else {
            this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
            this->asmcode.mov(asmRegister::eax, instance1);
            this->asmcode.mov(resultReg, instance2);
            if (optype==OpType::multiply) {
                this->asmcode.generateUnaryInstructor(ASM_MUL, resultReg);
                this->asmcode.mov(resultReg, asmRegister::eax);
            } else {
                this->asmcode.generateUnaryInstructor(ASM_DIV, resultReg);
                if (optype==OpType::divide) {
                    this->asmcode.mov(resultReg, asmRegister::eax);
                } else {
                    this->asmcode.mov(resultReg, asmRegister::edx);
                }
            }
        }
    }
}

/*void AsmGenerate::generateDefFunction(QuadItem q) {
    std::string funcName = q.getArg(1).var->getIDName();
    this->asmcode.label(funcName);
    int totalOffset = currentTable->getOffset();
    this->asmcode.addCode(ASM_ENTER + std::string(" ") + std::to_string(totalOffset) + ASM_COMMA + "0");
    this->asmcode.push(asmRegister::ebx);
    this->asmcode.push(asmRegister::ecx);
}*/

/*void AsmGenerate::generateReturn(QuadItem q) {
    if (q.getArg(1).target == 0) {
        this->generateEndFunction(q);
        return;
    }
    int flag = q.getItemType();
    if (flag == 7) {
        Symbol* s = q.getArg(1).var;
        std::string name = s->getIDName();
        if (name[0] == 't') {
            asmRegister reg = this->findRegister(name);
            this->releaseRegister(reg);
            this->asmcode.mov(asmRegister::eax, reg);
        } else {
            int offset = s->getWidth();
            std::string varEbpOffset = this->asmcode.generateVar(offset);
            this->asmcode.mov(asmRegister::eax, varEbpOffset);
        }
    } else {
        int value = q.getArg(1).target;
        this->asmcode.mov(asmRegister::eax, std::to_string(value));
    }
    this->asmcode.addCode(ASM_LEAVE);
    this->asmcode.addCode(ASM_RET);
}*/

/*void AsmGenerate::generateEndFunction(QuadItem q) {
    this->asmcode.pop(asmRegister::ecx);
    this->asmcode.pop(asmRegister::ebx);
    this->asmcode.addCode(ASM_LEAVE);
    this->asmcode.addCode(ASM_RET);
}*/

/*void AsmGenerate::generateCallBuildInFunction(QuadItem q, QuadItem arg) {
    std::string funcName = q.getArg(1).var->getIDName();
    int tempVar = 0;
    int varOffSet = 0;
    if (arg.getItemType() == 6) {
        int argValue = arg.getArg(1).target;
        std::string value = std::to_string(argValue);
        if (funcName == "print_int_i") {
            this->asmcode.mov(asmRegister::eax, value);
            this->generateCallFunction(q);
        }
    }
    else {
        std::string argNam = arg.getArg(1).var->getIDName();
        asmRegister tempVarReg = asmRegister::unset;
        if (argNam[0] == 't') {
            tempVarReg = this->findRegister(argNam);
        } else {
            Symbol* s = arg.getArg(1).var;
            varOffSet = s->getWidth();
        }
        if (funcName == "print_int_i") {
            if (tempVarReg != asmRegister::unset) {
                this->asmcode.mov(asmRegister::eax, tempVarReg);
            } else {
                std::string varEbpOffset = this->asmcode.generateVar(varOffSet);
                this->asmcode.mov(asmRegister::eax, varEbpOffset);
            }
            this->generateCallFunction(q);
        } else if (funcName == "read_int_i") {
            this->generateCallFunction(q);
            std::string varEbpOffset = this->asmcode.generateVar(varOffSet);
            this->asmcode.mov(varEbpOffset, asmRegister::eax);
        }
    }
}*/

/*void AsmGenerate::generateCallFunction(QuadItem q) {
    std::string funcName = q.getArg(1).var->getIDName();
    this->asmcode.generateUnaryInstructor(ASM_CALL, funcName);
    if (q.getArg(3).var != NULL) {
        std::string tempVar = q.getArg(3).var->getIDName();
        asmRegister tempReg = this->getRegister(tempVar);
        this->asmcode.mov(tempReg, asmRegister::eax);
    }
    // Protect the esp
    FuncSymbol* func = funcTable.findFunction(funcName);
    int offset = func->getTotalArgOffset();
    if (offset != 0) this->asmcode.add(asmRegister::esp, std::to_string(offset));
}*/

void AsmGenerate::generateSetArg(QuadItem q) {
    int flag = q.getItemType();
    std::string varName = "";
    if (flag == 7) {
        varName = q.getArg(1).var->getIDName();
        if (varName[0] != 't') {
            int offset = q.getArg(1).var->getWidth();
            std::string varEbpOffset = this->asmcode.generateVar(offset);
            this->asmcode.push(DOUBLE_WORD + varEbpOffset);
        } else {
            asmRegister reg = this->findRegister(varName);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        }
    } else {
        int value = q.getArg(1).target;
        std::string instanceNumber = this->asmcode.generateInstanceNumber(value);
        this->asmcode.push(instanceNumber);
    }
}

void AsmGenerate::generateJump(QuadItem q) {
    OpType optype = q.getOpType();
    std::string label = "label" + std::to_string(labelMap[q.getArg(3).target]);
    if (optype==OpType::JUMP) {
        this->asmcode.generateUnaryInstructor(ASM_JUMP, label);
    } else {
        int flag = q.getItemType();
        if (flag == 0) {
            std::string value1 = std::to_string(q.getArg(1).target);
            std::string value2 = std::to_string(q.getArg(2).target);
            this->asmcode.mov(asmRegister::edx, value1);
            this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, value2);
        } else if (flag == 1) {
            std::string value2 = this->asmcode.generateInstanceNumber(q.getArg(2).target);
            std::string var1Name = q.getArg(1).var->getIDName();
            if (var1Name[0] == 't') {
                asmRegister var1Reg = this->findRegister(var1Name);
                this->releaseRegister(var1Reg);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var1Reg, value2);
            } else {
                int offset = q.getArg(1).var->getWidth();
                std::string var1EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var1EbpOffset, value2);
            }
        } else if (flag == 2) {
            std::string value1 = this->asmcode.generateInstanceNumber(q.getArg(1).target);
            std::string var2Name = q.getArg(2).var->getIDName();
            if (var2Name[0] == 't') {
                asmRegister var2Reg = this->findRegister(var2Name);
                this->asmcode.mov(asmRegister::edx, value1);
                this->releaseRegister(var2Reg);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, var2Reg);
            } else {
                int offset = q.getArg(2).var->getWidth();
                std::string var2EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var2EbpOffset, value1);
            }
        } else if (flag == 3) {
            std::string value1 = std::to_string(q.getArg(1).target);
            std::string value2 = std::to_string(q.getArg(2).target);
            if (value1[0] == 't' && value1[0] == 't') {
                asmRegister v1 = this->findRegister(value1);
                asmRegister v2 = this->findRegister(value2);
                this->asmcode.generateBinaryInstructor(ASM_CMP, v1, v2);
            } else if (value1[0] == 't') {
                asmRegister v1 = this->findRegister(value1);
                int offset = q.getArg(2).var->getWidth();
                std::string v2EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, v1, v2EbpOffset);
            } else if (value2[0] == 't') {
                asmRegister v2 = this->findRegister(value2);
                int offset = q.getArg(1).var->getWidth();
                std::string v1EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.mov(asmRegister::edx, v1EbpOffset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, v2);
            } else {
                std::string v1EbpOffset = this->asmcode.generateVar(q.getArg(1).var->getWidth());
                std::string v2EbpOffset = this->asmcode.generateVar(q.getArg(2).var->getWidth());
                this->asmcode.mov(asmRegister::edx, v1EbpOffset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, v2EbpOffset);
            }
        }
        /*if (optype==OpType::JUMP_EQ_GREAT) {
            this->asmcode.generateUnaryInstructor(ASM_JGE, label);
        } else if (optype==OpType::JUMP_GREAT) {
            this->asmcode.generateUnaryInstructor(ASM_JG, label);
        } else if (optype==OpType::JUMP_EQ_SMALL) {
            this->asmcode.generateUnaryInstructor(ASM_JLE, label);
        } else if (optype==OpType::JUMP_SMALL) {
            this->asmcode.generateUnaryInstructor(ASM_JL, label);
        } else if (optype==OpType::JUMP_EQUAL) {
            this->asmcode.generateUnaryInstructor(ASM_JE, label);
        } else if (optype==OpType::JUMP_NOT_EQUAL) {
            this->asmcode.generateUnaryInstructor(ASM_JNE, label);
        }*/
    }
}

void AsmGenerate::generateNeg(QuadItem q) {
    std::string varName = q.getArg(1).var->getIDName();
    std::string result = q.getArg(3).var->getIDName();
    if (varName[0] == 't' && result[0] == 't') {
        asmRegister varReg = this->findRegister(varName);
        this->releaseRegister(varReg);
        asmRegister resultReg = this->getRegister(result);
        if (resultReg != varReg) {
            this->asmcode.mov(resultReg, varReg);
        }
        this->asmcode.generateUnaryInstructor(ASM_NEG, resultReg);
    } else if (varName[0] == 't') {
        asmRegister varReg = this->findRegister(varName);
        this->releaseRegister(varReg);
        int offset = q.getArg(3).var->getWidth();
        std::string ebpOffset = this->asmcode.generateVar(offset);
        this->asmcode.generateUnaryInstructor(ASM_NEG, varReg);
        this->asmcode.mov(ebpOffset, varReg);
    } else if (result[0] == 't') {
        int offset = q.getArg(1).var->getWidth();
        std::string ebpOffset = this->asmcode.generateVar(offset);
        asmRegister resultReg = this->getRegister(result);
        this->asmcode.mov(resultReg, ebpOffset);
        this->asmcode.generateUnaryInstructor(ASM_NEG, resultReg);
    } else {
        int varOff = q.getArg(1).var->getWidth();
        int resultOff = q.getArg(3).var->getWidth();
        std::string varEbpOff = this->asmcode.generateVar(varOff);
        std::string resultEBPOff = this->asmcode.generateVar(resultOff);
        this->asmcode.mov(asmRegister::edx, varEbpOff);
        this->asmcode.generateUnaryInstructor(ASM_NEG, asmRegister::edx);
        this->asmcode.mov(resultEBPOff, asmRegister::edx);
    }
}

void AsmGenerate::generatePower(QuadItem q) {
    int flag = q.getItemType();
    if (flag == 7) {
        std::string var1Name = q.getArg(1).var->getIDName();
        std::string var2Name = q.getArg(2).var->getIDName();
        if (var1Name[0] == 't') {
            asmRegister reg = this->findRegister(var1Name);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        } else {
            int offset = q.getArg(1).var->getWidth();
            std::string varEbpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
            this->asmcode.push(varEbpOffset);
        }
        if (var1Name[1] == 't') {
            asmRegister reg = this->findRegister(var1Name);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        } else {
            int offset = q.getArg(2).var->getWidth();
            std::string varEbpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
            this->asmcode.push(varEbpOffset);
        }
    } else if (flag == 5) {
        std::string arg2Value = this->asmcode.generateInstanceNumber(q.getArg(2).target);
        std::string arg1Name = q.getArg(1).var->getIDName();
        if (arg1Name[0] == 't') {
            asmRegister reg = this->findRegister(arg1Name);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        } else {
            int offset = q.getArg(1).var->getWidth();
            std::string varEbpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
            this->asmcode.push(varEbpOffset);
        }
        this->asmcode.push(arg2Value);
    } else if (flag == 6) {
        std::string arg1Value = this->asmcode.generateInstanceNumber(q.getArg(1).target);
        std::string arg2Name = q.getArg(2).var->getIDName();
        if (arg2Name[0] == 't') {
            asmRegister reg = this->findRegister(arg2Name);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        } else {
            int offset = q.getArg(1).var->getWidth();
            std::string varEbpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
            this->asmcode.push(varEbpOffset);
        }
        this->asmcode.push(arg1Value);
    } else {
        std::string arg1Value = this->asmcode.generateInstanceNumber(q.getArg(1).target);
        std::string arg2Value = this->asmcode.generateInstanceNumber(q.getArg(2).target);
        this->asmcode.push(arg1Value);
        this->asmcode.push(arg2Value);
    }
    this->asmcode.generateUnaryInstructor(ASM_CALL, "pow_i_i");
    std::string result = q.getArg(3).var->getIDName();
    if (result[0] == 't') {
        asmRegister resultReg = this->getRegister(result);
        this->asmcode.mov(resultReg, asmRegister::eax);
    } else {
        std::string resultEbpOffset = this->asmcode.generateVar(q.getArg(3).var->getWidth());
        this->asmcode.mov(resultEbpOffset, asmRegister::eax);
    }
    this->asmcode.add(asmRegister::esp, "8");
}

void AsmGenerate::generateGetAddress(QuadItem q) {
    int offset = q.getArg(1).var->getWidth();
    std::string resultName = q.getArg(3).var->getIDName();
    if (resultName[0] == 't') {
        asmRegister resultReg = this->getRegister(resultName);
        this->asmcode.mov(resultReg, asmRegister::ebp);
        this->asmcode.sub(resultReg, std::to_string(offset));
    } else {
        std::string resultEbpOffset = this->asmcode.generateVar(q.getArg(3).var->getWidth());
        this->asmcode.mov(resultEbpOffset, asmRegister::ebp);
        this->asmcode.generateBinaryInstructor(ASM_ADD, resultEbpOffset, std::to_string(offset));
    }
}

void AsmGenerate::generateAssignMember(QuadItem q) {
    int offsetOfMember = std::atoi(q.getArg(2).var->getIDName().c_str());
    std::string structIdName = q.getArg(3).var->getIDName();
    int offsetOfStruct = currentTable->findSymbolGlobally(structIdName)->getWidth();
    int totalOffset = offsetOfMember + offsetOfStruct;
    this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
    this->asmcode.sub(asmRegister::edx, std::to_string(totalOffset));
    int flag = q.getItemType();
    if (flag == 7) {
        std::string tempValue = q.getArg(1).var->getIDName();
        asmRegister reg;
        if (tempValue[0] == 't') {
            reg = this->findRegister(tempValue);
            this->releaseRegister(reg);
        } else {
            int offsetOfValue = q.getArg(1).var->getWidth();
            reg = this->getRegister("!MOV");
            this->releaseRegister(reg);
            this->asmcode.mov(reg, this->asmcode.generateVar(offsetOfValue));
        }
        this->asmcode.mov(this->asmcode.findValueByAddress(asmRegister::edx), reg);
    } else if (flag == 6) {
        int tempValue = q.getArg(1).target;
        this->asmcode.mov(this->asmcode.findValueByAddress(asmRegister::edx), this->asmcode.generateInstanceNumber(tempValue));
    }
}

void AsmGenerate::generateGetMember(QuadItem q) {
    std::string tempResult = q.getArg(3).var->getIDName();
    std::string structIdName = q.getArg(1).var->getIDName();
    int offsetOfMember = std::atoi(q.getArg(2).var->getIDName().c_str());
    int offsetOfStruct = currentTable->findSymbolGlobally(structIdName)->getWidth();
    asmRegister tempReg = this->getRegister(tempResult);
    int totalOffset = offsetOfMember + offsetOfStruct;
    std::string memberEbpOffset = this->asmcode.generateVar(totalOffset);
    this->asmcode.mov(tempReg, memberEbpOffset);
}

/*void AsmGenerate::generateGetArrayValue(QuadItem& q) {
    std::string resultName = q.getArg(3).var->getIDName();
    asmRegister reg = this->getRegister(resultName);
    int baseOffset = q.getArg(1).var->getWidth();
    int totalOffset = baseOffset;
    if (q.getOpType() == OpType::GET_ARRAY) {
        asmRegister offsetReg = asmRegister::unset;
        std::string offsetEbpStr = "";
        int flag = q.getItemType();
        if (flag == 7) {
            std::string offsetName = q.getArg(2).var->getIDName();
            if (offsetName[0] == 't') {
                offsetReg = this->findRegister(offsetName);
                this->releaseRegister(offsetReg);
                this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
            } else {
                int offset = q.getArg(2).var->getWidth();
                offsetEbpStr = this->asmcode.generateVar(offset);
                this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
            }
            this->asmcode.mov(reg, this->asmcode.findValueByAddress(asmRegister::edx));
        } else {
            int offset = q.getArg(2).target * 4;
            totalOffset += offset;
            this->asmcode.mov(reg, this->asmcode.generateVar(totalOffset));
        }
    } else {
        this->asmcode.mov(reg, this->asmcode.generateVar(totalOffset));
        this->asmcode.mov(reg, this->asmcode.findValueByAddress(reg));
    }
}
*/
/*void AsmGenerate::generateAssignArray(QuadItem& q) {
    int baseOffset = q.getArg(3).var->getWidth();
    int flag = q.getItemType();
    int totalOffset = baseOffset;
    asmRegister offsetReg = asmRegister::unset;
    std::string offsetEbpStr = "";
    if (q.getOpType() == OpType::ASSIGN_ARRAY) {
        std::string offsetName = q.getArg(2).var->getIDName();
        if (offsetName[0] == 't') {
            offsetReg = this->findRegister(offsetName);
            this->releaseRegister(offsetReg);

        } else if (offsetName[0] <= '9' && offsetName[0] >= '0') {
            int offset2 = std::atoi(q.getArg(2).var->getIDName().c_str()) * 4;
            baseOffset += offset2;
        } else {
            int offset = q.getArg(2).var->getWidth();
            offsetEbpStr = this->asmcode.generateVar(offset);
        }
    }
    if (flag == 7) {
        std::string varName = q.getArg(1).var->getIDName();
        asmRegister varReg = asmRegister::unset;
        if (varName[0] == 't') {
            varReg = this->findRegister(varName);
            this->releaseRegister(varReg);
        } else {
            std::string valueEbpOffset = this->asmcode.generateVar(q.getArg(1).var->getWidth());
            varReg = this->getRegister("!MOV");
            this->releaseRegister(varReg);
            this->asmcode.mov(varReg, valueEbpOffset);
        }
        if (q.getOpType() == OpType::ASSIGN_POINTER) {
            this->asmcode.mov(asmRegister::edx, this->asmcode.generateVar(totalOffset));
        } else {
            this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
            if (offsetReg != asmRegister::unset) {
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
            } else if (offsetEbpStr != "") {
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
            } else {
                this->asmcode.sub(asmRegister::edx, std::to_string(totalOffset));
            }
        }
        // Find the address
        this->asmcode.mov(this->asmcode.findValueByAddress(asmRegister::edx), varReg);
    } else {
        std::string instanceNum = this->asmcode.generateInstanceNumber(q.getArg(1).target);
        if (q.getOpType() == OpType::ASSIGN_POINTER) {
            this->asmcode.mov(asmRegister::edx, this->asmcode.generateVar(totalOffset));
        } else {
            this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
            if (offsetReg != asmRegister::unset) {
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
                this->asmcode.sub(asmRegister::edx, offsetReg);
            } else if (offsetEbpStr != "") {
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
                this->asmcode.sub(asmRegister::edx, offsetEbpStr);
            } else {
                this->asmcode.sub(asmRegister::edx, std::to_string(totalOffset));
            }
            // this->asmcode.mov(asmRegister::edx, asmRegister::ebp);
            // this->asmcode.sub(asmRegister::edx, std::to_string(totalOffset));
        }
        // Find the address
        this->asmcode.mov(this->asmcode.findValueByAddress(asmRegister::edx), instanceNum);
    }
}
*/
void AsmGenerate::preSetLabel() 
{
    std::vector<QuadItem*> quad;
    int labelNumber = 0;
    for (size_t i = 0; i < quad_list.size(); i++) {
        OpType optype = quad_list[i]->getOpType();
        /*if (this->isJumpQuad(optype)) {
            int lineNum = quad_list[i]->getArg(3).target;
            if (labelMap.count(lineNum) == 0) {
                labelMap[lineNum] = labelNumber;
                labelNumber++;
            }
        }*/
    }
    for (size_t i = 0; i < quad_list.size(); i++) {
        if (labelMap.count(i) > 0) {
            QuadItem q((Symbol*)NULL,OpType::label ,labelMap[i],(Symbol*)NULL);
            quad.push_back(&q);
        }
        quad.push_back(quad_list[i]);
    }
    quad_list=quad;
}

/*bool AsmGenerate::isJumpQuad(OpType optype) {
    return optype==OpType::JUMP || optype==OpType::JUMP_SMALL || optype==OpType::JUMP_EQ_SMALL ||
        optype==OpType::JUMP_GREAT || optype==OpType::JUMP_EQ_GREAT || optype==OpType::JUMP_EQUAL ||
        optype==OpType::JUMP_NOT_EQUAL;
}*/

void AsmGenerate::generate()
{
    //currentTable = rootTable;
    // Set header info
    this->asmcode.addCode("\%include \"asm/aso_io.inc\"\n section .text\nglobal main\n");
    std::cout<<quad_list.size();
    for (size_t i = 0; i < this->quad_list.size(); i++) 
    {
        QuadItem *q = quad_list[i];
        OpType optype = q->getOpType();
        //q->printItemInfor();

        /*if (optype==OpType::FUNC_DEF) {
            if (currentTable == rootTable) {
                currentTable = currentTable->getfirstChildTable();
            } else {
                currentTable = currentTable->getNextSiblingTable();
            }
            this->generateDefFunction(q);
        }
        else*/ if (optype==OpType::addtion || optype==OpType::substract ||
                 optype==OpType::divide || optype==OpType::multiply ||
                 optype==OpType::assign || optype==OpType::mod) {
            this->generateArithmetic(*q);
        }
        //q->printItemInfor();
        /*else if (optype==OpType::PARAM) {
            QuadItem& next = quad_list[i + 1];
            if (next.getOpType() == OpType::CALL) {
                if (next.getArg(1).var->getIDName() == "print_int_i" || 
                    next.getArg(1).var->getIDName() == "read_int_i") {
                        this->generateCallBuildInFunction(next, q);
                        i = i + 1;
                        continue;
                    }
            }
            // Push the args to stack
            this->generateSetArg(q);
        }*/
        /*else if (optype==OpType::CALL) {
            this->generateCallFunction(q);
        } else if (optype==OpType::END_FUNCTION) {
            this->generateEndFunction(q);
        } else if (optype==OpType::RETURN) {
            this->generateReturn(q);
        } else if (optype==OpType::label) {
            int labelIndex = q->getArg(1).target;
            this->asmcode.label("label" + std::to_string(labelIndex));
        } /*else if (this->isJumpQuad(optype)) {
            this->generateJump(*q);
        } else if (optype==OpType::power) {
            this->generatePower(*q);
        } else if (optype==OpType::uminus) {
            this->generateNeg(*q);
        }/* else if (optype==OpType::GET_ADDRESS) {
            this->generateGetAddress(q);
        } else if (optype==OpType::ASSIGN_STRUCT) {
            this->generateAssignMember(q);
        } else if (optype==OpType::GET_STRUCT) {
            this->generateGetMember(q);
        } else if (optype==OpType::ASSIGN_ARRAY || optype==OpType::ASSIGN_POINTER) {
            this->generateAssignArray(q);
        } else if (optype==OpType::GET_ARRAY || optype==OpType::GET_VALUE) {
            this->generateGetArrayValue(q);
        }*/
    }

    //write
    
    std::ofstream out("asm/asm_io.asm",ios::app);
    out<<(out,this->asmcode);
    std::cout<<"write ok!!\n";
    out.close();
}