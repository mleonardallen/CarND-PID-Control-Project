#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>

class Twiddle {

public:
  /*
  * Constructor
  */
  Twiddle();

  /*
  * Destructor.
  */
  virtual ~Twiddle();

  std::vector<double> Parameters();
  void tune(double);

private:

  enum Cycle {
    UP,
    DOWN
  } cycle_;

  double best_error_;

  double tolerance_;

  int index_;

  bool initialized_;

  std::vector<double> p_;

  std::vector<double> Dp_;

};

#endif /* TWIDDLE_H */
