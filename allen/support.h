#pragma once

#include <vector>
#include <string>

/* Handles everything related to operations */
namespace Ops {
    enum Operation {
        equal,  // =
        diff,   // ~=
        less,   // <
        great,  // >
        lessEq, // <=
        greatEq,// >=
        andOp,  // AND
        orOp,   // OR
        notOp,  // ~
        plus,   // +
        times,  // *
        div,    // /
        minus,  // -
        assign, // :=
        uMinus, // - unary
        par     // (  ) for printing purposes only
    };

    const std::vector<std::string> opName = {
        "igual",
        "diferente",
        "menor",
        "maior",
        "menor ou igual",
        "maior ou igual",
        "e",
        "ou",
        "nao",
        "soma",
        "multiplicacao",
        "divisao",
        "subtracao",
        "atribuicao",
        "menos unario",
        "parenteses"
    };

    const std::vector<bool> masculineOp = {
        true,   //igual inteiro
        true,   //diferente inteiro
        true,   //menor inteiro
        true,   //maior inteiro
        true,   //menor ou igual inteiro
        true,   //maior ou igual inteiro
        true,   //e booleano
        true,   //ou booleano
        true,   //nao booleano
        false,  //soma inteira
        false,  //multiplicacao inteira
        false,  //divisao inteira
        false,  //subtracao inteira
        false,  //atribuicao intera (nunca usado)
        true,   //menos unario inteiro
        false   //parenteses inteiro (nunca usado)
    };
}

/* Handles everything related to types */
namespace Types {
    enum Type { unknown, integer, real, boolean  }; /*Possible types*/
    static Type lastType; /*Stores the last type found*/
    const std::vector<std::string> femTypes = {"desconhecida", "inteira", "real", "booleana"}; /*Mapping for printing messages*/
    const std::vector<std::string> masTypes = {"desconhecido", "inteiro", "real", "booleano"}; /*Mapping for printing messages*/

    Type unType (Type next, Ops::Operation op); /* Gives the type of a unary operation */
    Type binType (Type left, Type right, Ops::Operation op); /* Gives the type of a binary operation */

    bool coercionNeeded (Type myType, Type otherType); /* Informs if coercion is required */

    /* Error messages */
    void typeError (Ops::Operation op, Type expected, Type actual);
    void typeError (Ops::Operation op, Type expected1, Type expected2, Type actual);
}


