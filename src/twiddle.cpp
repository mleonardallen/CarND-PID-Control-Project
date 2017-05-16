#include <iostream>
#include "twiddle.h"
#include <numeric>
using std::vector;


Twiddle::Twiddle() {

    tolerance_ = 0.001;
    index_ = 0;
    initialized_ = false;

    // initialize parameters
    p_ = {0, 0};
    Dp_ = {0.1, 1.0};

    cycle_ = Twiddle::UP;
}

Twiddle::~Twiddle() {}

void Twiddle::tune(double error) {

    if (!initialized_) {
        // get baseline error
        best_error_ = error;
        p_[index_] += Dp_[index_];
        initialized_ = true;
        return;
    }

    // discontinue algorithm if finely tuned.
    double sum = std::accumulate(Dp_.begin(), Dp_.end(), 0.0);
    if (sum <= tolerance_) {
        return;
    }

    int nextIndex = index_ < p_.size() ? index_ + 1 : 0;
    
    if (error < best_error_) {
        best_error_ = error;
        Dp_[index_] *= 1.1;
        // update index
        index_ = nextIndex;
        p_[index_] += Dp_[index_];
        cycle_ = Twiddle::UP;
    } else if (cycle_ == Twiddle::UP) {
        p_[index_] -= 2 * Dp_[index_]; // -2x to account for +1x on UP cycle
        cycle_ = Twiddle::DOWN;
    } else {
        p_[index_] += Dp_[index_]; // reset to initial value
        Dp_[index_] *= 0.9;
        // update index
        index_ = nextIndex;
        p_[index_] += Dp_[index_];
        cycle_ = Twiddle::UP;
    }
}

vector<double> Twiddle::Parameters() {
    std::cout << "getting parameters" << std::endl;
    std::cout << "p: " << p_[0] << " " << p_[1] << std::endl;
    std::cout << "Dp: " << Dp_[0] << " " << Dp_[1] << std::endl;
    return p_;
}