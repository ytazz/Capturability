#include "timer.h"

namespace Capt {

Timer::Timer(){
  start_ = std::chrono::system_clock::now();
  end_   = std::chrono::system_clock::now();
}

Timer::~Timer(){
}

void Timer::start(){
  start_ = std::chrono::system_clock::now();
}

void Timer::end(){
  end_ = std::chrono::system_clock::now();
}

void Timer::print(){
  elapsed_ = std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
  printf("%d.%d [ms]\n", elapsed_ / 1000, elapsed_ % 1000);
}

double Timer::get(){
  double t = double(elapsed_) / 1000.0;
  return t;
}

} // namespace Capt