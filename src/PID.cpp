#include "PID.h"
#include <iostream>

using namespace std;

PID::PID() {
    prev_cte_ = 0;
    int_cte_ = 0;
    total_error_ = 0;
}

PID::~PID() {}

void PID::setParameters(double Kp, double Ki, double Kd) {
    prev_cte_ = 0;
    int_cte_ = 0;
    total_error_ = 0;

    Kp_ = Kp;
    Ki_ = Ki;
    Kd_ = Kd;
}

void PID::UpdateError(double cte) {
	int_cte_ += cte;
	
    // update error
    p_error_ = Kp_ * cte;
    i_error_ = Ki_ * int_cte_;
    d_error_ = Kd_ * (cte - prev_cte_);

	prev_cte_ = cte;
    total_error_ += (cte * cte);
}

double PID::Steer() {
    return -(p_error_ + i_error_ + d_error_);
}

double PID::TotalError() {
    return total_error_;
}
