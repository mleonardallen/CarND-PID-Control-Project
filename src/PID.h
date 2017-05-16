#ifndef PID_H
#define PID_H

class PID {

public:
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * 
  */
  void setParameters(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  double Steer();

  /*
  * Calculate the total PID error.
  */
  double TotalError();

private:
  /*
  * Errors
  */
  double p_error_;
  double i_error_;
  double d_error_;

  /*
  * Coefficients
  */ 
  double Kp_;
  double Ki_;
  double Kd_;

  double prev_cte_;
  double int_cte_;
  double total_error_;

  // std::vector<double> dP_;
};

#endif /* PID_H */
