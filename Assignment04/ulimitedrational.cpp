/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedInt* my_gcd(UnlimitedInt* num, UnlimitedInt *den){
    UnlimitedInt* a = new UnlimitedInt(num->to_string()); UnlimitedInt* b = new UnlimitedInt(den->to_string());
    UnlimitedInt* remainder = UnlimitedInt::mod(a, b);
    while(remainder->to_string() != "0"){
        delete a;
        a = b; b = remainder;

        remainder = UnlimitedInt::mod(a, b);
    }
    delete a; delete remainder;
    return b;
}

UnlimitedRational::UnlimitedRational(){
    p = NULL; q = NULL;
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den){
    if(den->get_sign() == 0){
        p = new UnlimitedInt(0); q = new UnlimitedInt(0);
    }
    else if(num->get_sign() == 0){
        p = new UnlimitedInt(0); q = new UnlimitedInt(den->to_string());
    }
    else{
        UnlimitedInt* gcd = my_gcd(num, den);
        p = UnlimitedInt::div(num, gcd);
        q = UnlimitedInt::div(den, gcd);
        delete gcd;
    }
}

UnlimitedRational::~UnlimitedRational(){
    if(p != nullptr){
        delete p; p = nullptr;
    } 
    if(q != nullptr){
        delete q; q = nullptr;
    }
}

UnlimitedInt *UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt *UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    string s = "";
    s += p->to_string() + "/" + q->to_string();
    return s;
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();

    if((b->get_sign() == 0) || (d->get_sign() == 0)){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedRational* result = new UnlimitedRational(zero, zero);
        delete zero;
        return result;
    }

    if(a->get_sign() == 0){
        UnlimitedRational* result = new UnlimitedRational(c, d);
        return result;
    }
    if(c->get_sign() == 0){
        UnlimitedRational* result = new UnlimitedRational(a, b);
        return result;
    }

    UnlimitedInt* product1 = UnlimitedInt::mul(a, d);
    UnlimitedInt* product2 = UnlimitedInt::mul(b, c);
    UnlimitedInt* numerator = UnlimitedInt::add(product1, product2);
    UnlimitedInt* denominator = UnlimitedInt::mul(b, d);
    delete product1; delete product2;

    UnlimitedRational* result = new UnlimitedRational(numerator, denominator);
    delete numerator; delete denominator;
    return result;
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();

    if((b->get_sign() == 0) || (d->get_sign() == 0)){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedRational* result = new UnlimitedRational(zero, zero);
        delete zero;
        return result;
    }
    if(a->get_sign() == 0){
        UnlimitedInt* minus_one = new UnlimitedInt(-1);
        UnlimitedInt* minus_c = UnlimitedInt::mul(c, minus_one);
        UnlimitedRational* result = new UnlimitedRational(minus_c, d);
        delete minus_c; delete minus_one;
        return result;
    }
    if(c->get_sign() == 0){
        UnlimitedRational* result = new UnlimitedRational(a, b);
        return result;
    }

    UnlimitedInt* product1 = UnlimitedInt::mul(a, d);
    UnlimitedInt* product2 = UnlimitedInt::mul(b, c);
    UnlimitedInt* numerator = UnlimitedInt::sub(product1, product2);
    UnlimitedInt* denominator = UnlimitedInt::mul(b, d);
    delete product1; delete product2;

    UnlimitedRational* result = new UnlimitedRational(numerator, denominator);
    delete numerator; delete denominator;
    return result;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();

    if((b->get_sign() == 0) || (d->get_sign() == 0)){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedRational* result = new UnlimitedRational(zero, zero);
        delete zero;
        return result;
    }
    if((a->get_sign() == 0) || (c->get_sign() == 0)){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedInt* one = new UnlimitedInt(1);
        UnlimitedRational* result = new UnlimitedRational(zero, one);
        delete zero; delete one;
        return result;
    }

    UnlimitedInt* numerator = UnlimitedInt::mul(a, c);
    UnlimitedInt* denominator = UnlimitedInt::mul(b, d);

    UnlimitedRational* result = new UnlimitedRational(numerator, denominator);
    delete numerator; delete denominator;
    return result;
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* a = i1->get_p();
    UnlimitedInt* b = i1->get_q();
    UnlimitedInt* c = i2->get_p();
    UnlimitedInt* d = i2->get_q();

    if((b->get_sign() == 0) || (d->get_sign() == 0 || (c->get_sign() == 0))){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedRational* result = new UnlimitedRational(zero, zero);
        delete zero;
        return result;
    }
    if((a->get_sign() == 0)){
        UnlimitedInt* zero = new UnlimitedInt(0);
        UnlimitedInt* one = new UnlimitedInt(1);
        UnlimitedRational* result = new UnlimitedRational(zero, one);
        delete zero; delete one;
        return result;
    }

    UnlimitedInt* numerator = UnlimitedInt::mul(a, d);
    UnlimitedInt* denominator = UnlimitedInt::mul(b, c);

    UnlimitedRational* result = new UnlimitedRational(numerator, denominator);
    delete numerator; delete denominator;
    return result;
}
