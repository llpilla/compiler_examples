#include "support.h"

extern void yyerror(const char* s, ...);

using namespace Types;

/* Gives the type of a unary operation */
Type Types::unType (Type next, Ops::Operation op){
    /* Possible unary ops and types:
     * parentesis: returns the type of the expression
     * unary minus: returns the type of the expression if not boolean
     * not: returns boolean but expects boolean*/
    Type returnType;
    switch(op){
        case Ops::notOp:
            returnType = boolean; /*Standard return = bool*/
            if (next != boolean) typeError(op, boolean, next);
            break;
        case Ops::uMinus:
            returnType = integer; /*Standard return = int*/
            if (next == integer || next == real)
                returnType = next;
            else typeError(op, integer, real, next);
            break;
        case Ops::par:
            returnType = next;
            break;
        default:
            returnType = unknown;
    }
    return returnType;
}

/* Gives the type of a binary operation */
Type Types::binType (Type left, Type right, Ops::Operation op){
    /* Possible binary ops and types:
     * Comparison: integer and real
     * Arithmetic: integer and real
     * Logical: boolean
     * Assignment: any
     */
    Type returnType;
    switch(op){
        /*Assignments don't really have types, but lets give them the type of the left side*/
        case Ops::assign:
            returnType = left;
            /*but we still have to check if the right side matches the left side*/
            if (left != right) typeError(op, left, right);
            break;

        /*Arithmetic expressions return integers or reals*/
        case Ops::plus:
        case Ops::times:
        case Ops::div:
        case Ops::minus:
            returnType = integer; /*Standard type: integer*/
            if (left == real && right == real) returnType = real;
            /*and expect integers or reals*/
            if (left != integer && left != real) typeError(op, integer, real, left);
            if (right != integer && right != real) typeError(op, integer, real, right);
            break;

        /*Comparisons return booleans*/
        case Ops::equal:
        case Ops::diff:
        case Ops::less:
        case Ops::great:
        case Ops::lessEq:
        case Ops::greatEq:
            returnType = boolean; /*Standard type: boolean*/
            /*and expect integers or reals*/
            if (left != integer && left != real) typeError(op, integer, real, left);
            if (right != integer && right != real) typeError(op, integer, real, right);
            break;

        /*Logical operations return booleans*/
        case Ops::andOp:
        case Ops::orOp:
            returnType = boolean; /*Standard type: boolean*/
            /*and expect booleans*/
            if (left != boolean) typeError(op, boolean, left);
            if (right != boolean) typeError(op, boolean, right);
            break;

        default:
            returnType = unknown;
    }

    return returnType;
}

/* Informs if coercion is required */
bool Types::coercionNeeded (Type myType, Type otherType){
    return (myType == integer && otherType == real);
}

/*Error messages*/
void Types::typeError (Ops::Operation op, Type expected, Type actual){
    yyerror("semantico: operacao %s espera %s mas recebeu %s.",
            Ops::opName[op].c_str(),
            masTypes[expected].c_str(),
            masTypes[actual].c_str());
}

void Types::typeError (Ops::Operation op, Type expected1, Type expected2, Type actual){
    yyerror("semantico: operacao %s espera %s ou %s mas recebeu %s.",
            Ops::opName[op].c_str(),
            masTypes[expected1].c_str(),
            masTypes[expected2].c_str(),
            masTypes[actual].c_str());

}
