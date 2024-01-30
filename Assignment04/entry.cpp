/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    left = nullptr; right = nullptr;
    key = "";
    val = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational *v){
    key = k;
    val = new UnlimitedRational(v->get_p(), v->get_q());
    left = nullptr; right = nullptr;
}

SymEntry::~SymEntry(){
    if(val != nullptr){
        delete val; val = nullptr;
    }
}
