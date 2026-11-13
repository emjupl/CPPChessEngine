#include <vector>
#include "types.h"
#include "vector_operations.h"

std::vector<Move> CalculateCaptures(std::vector<Move> attackedFields, uint64_t oppositeFigures){
    std::vector<Move> capturesFields;
    for (size_t i = 0; i < attackedFields.size(); i++) {
        if(attackedFields[i].toField & oppositeFigures){
            PushMoveToVector(attackedFields[i].fromField, attackedFields[i].toField, capturesFields);
        }
    }
    return capturesFields;
}