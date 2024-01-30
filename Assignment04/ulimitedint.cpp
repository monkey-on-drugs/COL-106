/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "ulimitedint.h"

int my_greater(int size1, int size2, int* arr1, int* arr2){
    if(size1 > size2){
        return 1;
    }
    else if(size1 < size2){
        return 2;
    }
    else{
        for(int i = size1 - 1; i >= 0; i--){
            if(arr1[i] > arr2[i]){
                return 1;
            }
            else if(arr1[i] < arr2[i]){
                return 2;
            }
        }
    }
    return 0;
}

int my_max(const int& a, const int& b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

//Explain each function in detail here
//Below function is the default constructor
UnlimitedInt::UnlimitedInt() {
    size = 0;
    sign = 1;
    capacity = 0;
    unlimited_int = nullptr;
}

UnlimitedInt::UnlimitedInt(string s) {
    size = 0;
    sign = 1;
    capacity = 0;
    unlimited_int = nullptr;
    if (s[0] == '-') {
        sign = -1;
        size = s.size() - 1;
    }
    else {
        size = s.size();
    }
    if(s[0] == '0'){
        sign = 0;
        size = 1;
    }
    
    capacity = size;
    unlimited_int = new int[capacity];

    for(int j = 0; j < size; j++){
        unlimited_int[j] = s[s.size() - j - 1] - '0';
    }
}

UnlimitedInt::UnlimitedInt(int i) {
    size = 0;
    sign = 1;
    capacity = 0;
    unlimited_int = nullptr;

    if (i == 0) {
        size = 1; sign = 0;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        return;
    }

    if (i < 0) {
        sign = -1;
        i = -i;
    }

    int temp = i;
    while (temp > 0) {
        temp /= 10;
        size++;
    }
    capacity = size;
    unlimited_int = new int[capacity];
    for (int j = 0; j < size; j++) {
        unlimited_int[j] = i % 10;
        i /= 10;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    size = sz;
    sign = sgn;
    capacity = cap;
    unlimited_int = ulimited_int;
}

UnlimitedInt::~UnlimitedInt() {
    if(unlimited_int != nullptr){
        delete[] unlimited_int;
        unlimited_int = nullptr;
    }
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;

}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int* arr1 = i1->get_array();
    int* arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if(sign1 == 0){
        UnlimitedInt* ans = new UnlimitedInt(i2->to_string());
        return ans;
    }
    else if(sign2 == 0){
        UnlimitedInt* ans = new UnlimitedInt(i1->to_string());
        return ans;
    }
    UnlimitedInt* ans;
    if(sign1 == sign2){
        int size = my_max(size1, size2) + 1;
        int* arr = new int[size];
        int carry = 0;
        int i = 0;
        while (i < size1 && i < size2) {
            arr[i] = arr1[i] + arr2[i] + carry;
            carry = arr[i] / 10;
            arr[i] %= 10;
            i++;
        }
        while (i < size1) {
            arr[i] = arr1[i] + carry;
            carry = arr[i] / 10;
            arr[i] %= 10;
            i++;
        }
        while (i < size2) {
            arr[i] = arr2[i] + carry;
            carry = arr[i] / 10;
            arr[i] %= 10;
            i++;
        }
        arr[i] = carry;
        if (arr[i] == 0) {
            size--;
        }
        ans = new UnlimitedInt(arr, size, sign1, size);
    }
    else{
        UnlimitedInt* temp_smaller;
        UnlimitedInt* temp_bigger;

        int checker = my_greater(size1, size2, arr1, arr2);

        if(checker == 0){
            return new UnlimitedInt(0);
        }
        else if(checker == 1){
            temp_smaller = new UnlimitedInt(i2->to_string());
            temp_smaller->sign *= -1;
            temp_bigger = new UnlimitedInt(i1->to_string()); 
        }
        else{
            temp_smaller = new UnlimitedInt(i1->to_string());
            temp_smaller->sign *= -1;
            temp_bigger = new UnlimitedInt(i2->to_string());
        }

        ans = UnlimitedInt::sub(temp_bigger, temp_smaller);
        delete temp_smaller; delete temp_bigger;
    }
    return ans;
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int* arr1 = i1->get_array();
    int* arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if(sign1 == 0 || sign2 == 0){
        if(sign1 == 0){
            UnlimitedInt* ans = new UnlimitedInt(i2->to_string());
            ans->sign *= -1;
            return ans;
        }
        else if(sign2 == 0){
            UnlimitedInt* ans = new UnlimitedInt(i1->to_string());
            return ans;
        }
    }

    int checker = my_greater(size1, size2, arr1, arr2);
    int smaller_size, bigger_size;
    int* smaller_arr; int* bigger_arr;

    if(sign1 == sign2 && checker == 0){
        return new UnlimitedInt(0);
    }
    else if(checker == 1){
        bigger_size = size1; bigger_arr = arr1;
        smaller_size = size2; smaller_arr = arr2; 
    }
    else if(checker == 2){
        bigger_size = size2; bigger_arr = arr2;
        smaller_size = size1; smaller_arr = arr1;
    }
    UnlimitedInt* ans;
    if(sign1 == sign2){
        int size = my_max(size1, size2);
        int* arr = new int[size];
        int borrow = 0;
        int i = 0;
        while (i < smaller_size) {
            arr[i] = (bigger_arr[i] - borrow) - smaller_arr[i];
            if (arr[i] < 0) {
                arr[i] += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            i++;
        }
        while (i < bigger_size) {
            arr[i] = (bigger_arr[i] - borrow);
            if (arr[i] < 0) {
                arr[i] += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            i++;
        }
        while (arr[size - 1] == 0 && size > 1) {
            size--;
        }
        if(checker == 1){
            ans = new UnlimitedInt(arr, size, sign1, size);
        }
        else if(checker == 2){
            ans = new UnlimitedInt(arr, size, -sign1, size);
        }

    }
    else{
        UnlimitedInt* temp_smaller;
        UnlimitedInt* temp_bigger;
        if(checker == 1){
            temp_smaller = new UnlimitedInt(i2->to_string());
            temp_smaller->sign *= -1;
            temp_bigger = new UnlimitedInt(i1->to_string()); 
        }
        else if(checker == 2){
            temp_smaller = new UnlimitedInt(i1->to_string());
            temp_bigger = new UnlimitedInt(i2->to_string());
            temp_bigger->sign *= -1;
        }
        else{
            temp_smaller = new UnlimitedInt(i2->to_string());
            temp_smaller->sign *= -1;
            temp_bigger = new UnlimitedInt(i1->to_string());
        }
        ans = UnlimitedInt::add(temp_bigger, temp_smaller);
        delete temp_smaller; delete temp_bigger;
    }
    return ans;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int* arr1 = i1->get_array();
    int* arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if(sign1 == 0 || sign2 == 0){
        return new UnlimitedInt(0);
    }
    if(size1 == 1 && arr1[0] == 1){
        UnlimitedInt* ans = new UnlimitedInt(i2->to_string());
        ans->sign = sign1 * sign2;
        return ans;
    }
    if(size2 == 1 && arr2[0] == 1){
        UnlimitedInt* ans = new UnlimitedInt(i1->to_string());
        ans->sign = sign1 * sign2;
        return ans;
    }

    int size = size1 + size2;
    int* arr = new int[size];
    for(int i = 0; i < size; i++){
        arr[i] = 0;
    }
    UnlimitedInt* ans = new UnlimitedInt(arr, size, 1, size);

    int checker = my_greater(size1, size2, arr1, arr2);
    int smaller_size, bigger_size;
    int* smaller_arr; int* bigger_arr;

    if(checker == 1 || checker == 0){
        bigger_size = size1; bigger_arr = arr1;
        smaller_size = size2; smaller_arr = arr2;
    }
    else if(checker == 2){
        bigger_size = size2; bigger_arr = arr2;
        smaller_size = size1; smaller_arr = arr1;
    }

    for(int i = 0; i < smaller_size; i++){
        int* temp = new int[size];
        for(int j = 0; j < bigger_size; j++){
            temp[i + j] = smaller_arr[i] * bigger_arr[j];
        }
        for(int j = 0; j < i; j++){
            temp[j] = 0;
        }
        for(int j = i + bigger_size; j < size; j++){
            temp[j] = 0;
        }
        UnlimitedInt* temp_u_int = new UnlimitedInt(temp, size, 1, size);
        ans = UnlimitedInt::add(ans, temp_u_int);
        delete temp_u_int;
    }
    for(int i = size - 1; i >= 0; i--){
        if(ans->get_array()[i] == 0){
            ans->size--;
        }
        else{
            break;
        }
    }

    if (sign1 == sign2) {
        return ans;
    }
    else {
        ans->sign = -1;
        return ans;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int* arr1 = i1->get_array();
    int* arr2 = i2->get_array();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if (sign1 == 0) {
        return new UnlimitedInt(0);
    }
    if(size1 < size2){
        if(sign1 == sign2){
            return new UnlimitedInt(0);
        }
        else{
            return new UnlimitedInt(-1);
        }
    }
    if(size2 == 1 && arr2[0] == 1){
        UnlimitedInt* ans = new UnlimitedInt(i1->to_string());
        ans->sign = sign1 * sign2;
        return ans;
    }

    int checker = my_greater(size1, size2, arr1, arr2);

    if(checker == 0){
        if(sign1 == sign2){
            return new UnlimitedInt(1);
        }
        else{
            return new UnlimitedInt(-1);
        }
    }
    bool is_s1_changed = false;
    bool is_s2_changed = false;
    bool both_changed = false;
    if(sign1 == -1){
        i1->sign = 1;
        is_s1_changed = true;
    }
    if(sign2 == -1){
        i2->sign = 1;
        is_s2_changed = true;
    }
    if(is_s1_changed && is_s2_changed){
        both_changed = true;
    }

    UnlimitedInt* quotient = new UnlimitedInt(0);
    UnlimitedInt* dividend = new UnlimitedInt(0);
    UnlimitedInt* ten = new UnlimitedInt(10);
    UnlimitedInt* temp1; UnlimitedInt* temp2;

    for (int i = size1 - 1; i >= 0; i--) {
        temp2 = new UnlimitedInt(dividend->to_string()); delete dividend;
        dividend = UnlimitedInt::mul(temp2, ten); delete temp2;

        temp1 = new UnlimitedInt(arr1[i]);
        temp2 = new UnlimitedInt(dividend->to_string()); delete dividend;
        dividend = UnlimitedInt::add(temp2, temp1); delete temp1; delete temp2;

        int q = 0;
        while (my_greater(dividend->get_size(), size2, dividend->get_array(), arr2) != 2) {
            temp2 = new UnlimitedInt(dividend->to_string()); delete dividend;
            dividend = UnlimitedInt::sub(temp2, i2); delete temp2;
            q++;
        }

        temp2 = new UnlimitedInt(quotient->to_string()); delete quotient;
        quotient = UnlimitedInt::mul(temp2, ten); delete temp2;

        temp1 = new UnlimitedInt(q);
        temp2 = new UnlimitedInt(quotient->to_string()); delete quotient;
        quotient = UnlimitedInt::add(temp2, temp1); delete temp1; delete temp2;
    }
    delete ten;

    if ((is_s1_changed || is_s2_changed) && !both_changed) {
        if((dividend->sign != 0)){
            UnlimitedInt* one = new UnlimitedInt(1);
            quotient = UnlimitedInt::add(quotient, one);
            delete one;
            quotient->sign *= -1;
        }
        else{
            quotient->sign *= -1;
        }
        
    }

    if(is_s1_changed){
        i1->sign = -1;
    }
    if(is_s2_changed){
        i2->sign = -1;
    }

    return quotient;
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    if(i1->get_sign() == 0){
        return new UnlimitedInt(0);
    }

    UnlimitedInt* quotient = UnlimitedInt::div(i1, i2); UnlimitedInt* product; UnlimitedInt* ans;

    bool is_changed = false;
    if(sign1 == sign2){
        if(sign1 == -1){
            i1->sign *= -1; i2->sign *= -1; is_changed = true;
        }
        product = UnlimitedInt::mul(quotient, i2);
        ans = UnlimitedInt::sub(i1, product);
        if(is_changed){
            i1->sign *= -1; i2->sign *= -1;
        }
    }
    else{
        if(sign2 == -1 && sign1 == 1){
            i2->sign *= -1; i1->sign *= -1; is_changed = true;
        }
        product = UnlimitedInt::mul(quotient, i2);
        ans = UnlimitedInt::sub(i1, product);
        if(is_changed){
            i2->sign *= -1; i1->sign *= -1;
        }
    }
    delete quotient; delete product;

    return ans;
}

string UnlimitedInt::to_string()
{
    string s = "";
    if (sign == -1) {
        s += "-";
    }
    for (int i = size - 1; i >= 0; i--) {

        s = s + (std::to_string(unlimited_int[i]));
    }
    return s;
}