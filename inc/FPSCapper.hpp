#ifndef FPSCAPPER_HPP
#define FPSCAPPER_HPP

#include <chrono>
#include <thread>
#include <iostream>

template<class TimeUnit>
class FPSCapper {
public:
  FPSCapper(int const in_fps);
  int GetFPS() const;
  long long GetFrameDuration() const;
  void SleepToNextFrame();
private:
  int fps;
  TimeUnit frame_duration;
  std::chrono::time_point<std::chrono::system_clock> start;
};

template<class TimeUnit> 
FPSCapper<TimeUnit>::FPSCapper(int const in_fps) :
  fps{in_fps}, frame_duration{TimeUnit{std::chrono::seconds{1}}/fps}, start{std::chrono::system_clock::now()} {}

template<class TimeUnit>
int FPSCapper<TimeUnit>::GetFPS() const {
  return fps;
}

template<class TimeUnit>
long long FPSCapper<TimeUnit>::GetFrameDuration() const {
  return frame_duration.count();
}

template<class TimeUnit> 
void FPSCapper<TimeUnit>::SleepToNextFrame() {
  auto const duration = TimeUnit{std::chrono::system_clock::now() - start};
  if(duration < frame_duration) std::this_thread::sleep_for(frame_duration - duration);
  start = std::chrono::system_clock::now();
}

#endif
